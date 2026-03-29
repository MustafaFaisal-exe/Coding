/*
 * ============================================================
 *  AEGIS ENERGY GRID — Main Reactor Monitoring System
 *  Phases 1-4: Sensors · Analytics · Vault · Dashboard Gateway
 * ============================================================
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <math.h>

/* ─── Constants ─────────────────────────────────────────── */
#define MATRIX_ROWS      10
#define MATRIX_COLS      10
#define MATRIX_SIZE      (MATRIX_ROWS * MATRIX_COLS)
#define CRITICAL_PEAK    90
#define CAESAR_SHIFT     5
#define FIFO_PATH        "query_gate"
#define VAULT_PATH       "vaultDB"
#define SENSOR_INTERVAL  2   /* seconds between sensor readings */

/* ─── Sensor names (for logging) ────────────────────────── */
static const char *SENSOR_NAMES[4] = {"CPU", "Memory", "Heat", "Voltage"};

/* ─── Global reactor state matrix (Phase 2) ─────────────── */
static int g_matrix[MATRIX_ROWS][MATRIX_COLS];

/* ─── Custom protocol header (Phase 3) ──────────────────── */
typedef struct {
    int timestamp;
    int data_size;
} Header;

/* ─── Thread argument for quadrant processing ───────────── */
typedef struct {
    int thread_id;
    int row_start;
    int row_end;
    int col_start;
    int col_end;
} QuadrantArgs;

/* ================================================================
 *  PHASE 1 HELPERS — Sensor simulation
 * ================================================================ */

/* Generate a random integer in [0, 100] */
static int sensor_read(void) {
    return rand() % 101;
}

/*
 * grandchild_sensor()
 * Runs in a grandchild process.  Every SENSOR_INTERVAL seconds it
 * writes one random metric to write-end of its pipe and then exits
 * after enough readings have been collected to fill the matrix.
 *
 * We need MATRIX_SIZE / 4  = 25 readings per grandchild pair
 * (each child averages 2 grandchildren → 25 averages per child,
 * 2 children → 50 averages per round, but we run multiple rounds).
 *
 * Simpler model used here: each grandchild sends MATRIX_SIZE/2
 * values (50) so each child produces 25 averages; two children
 * together deliver 50 values which the parent uses to fill
 * half the matrix per "round".  We run 2 rounds → 100 values.
 *
 * Actually the simplest correct model: send enough readings so
 * that the parent accumulates exactly MATRIX_SIZE = 100 values.
 * With 4 grandchildren each sending N values the parent gets 2N
 * averages (N from child-0, N from child-1).  We want 2N = 100
 * so N = 50.  Each grandchild sends 50 values.
 */
#define READINGS_PER_GRANDCHILD  50

static void grandchild_sensor(int write_fd, int sensor_id) {
    srand((unsigned)(time(NULL) ^ (getpid() << 4) ^ sensor_id));
    for (int i = 0; i < READINGS_PER_GRANDCHILD; i++) {
        int val = sensor_read();
        printf("[GC pid=%d sensor=%s] reading=%d\n",
               getpid(), SENSOR_NAMES[sensor_id], val);
        fflush(stdout);
        write(write_fd, &val, sizeof(int));
        sleep(SENSOR_INTERVAL);
    }
    close(write_fd);
    exit(EXIT_SUCCESS);
}

/*
 * child_aggregator()
 * Reads from two grandchildren pipes, computes the average, and
 * writes the average to the parent pipe.
 */
static void child_aggregator(int gc0_read_fd, int gc1_read_fd,
                              int parent_write_fd, int child_id) {
    for (int i = 0; i < READINGS_PER_GRANDCHILD; i++) {
        int v0, v1;
        ssize_t r0 = read(gc0_read_fd, &v0, sizeof(int));
        ssize_t r1 = read(gc1_read_fd, &v1, sizeof(int));
        if (r0 <= 0 || r1 <= 0) break;   /* sensor closed */

        int avg = (v0 + v1) / 2;
        printf("[Child pid=%d id=%d] avg of (%d,%d) = %d\n",
               getpid(), child_id, v0, v1, avg);
        fflush(stdout);
        write(parent_write_fd, &avg, sizeof(int));
    }
    close(gc0_read_fd);
    close(gc1_read_fd);
    close(parent_write_fd);
    exit(EXIT_SUCCESS);
}

/* ================================================================
 *  PHASE 2 HELPERS — Analytics / Quadrant threads
 * ================================================================ */

/*
 * stabilize_value()
 * Replaces a critical peak with the average of its neighbours.
 * Works entirely within the caller's quadrant boundaries to ensure
 * spatial partitioning (no mutex needed).
 */
static int stabilize_value(int row, int col,
                            int row_start, int row_end,
                            int col_start, int col_end) {
    int sum = 0, count = 0;
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;
            int nr = row + dr;
            int nc = col + dc;
            if (nr >= row_start && nr < row_end &&
                nc >= col_start && nc < col_end) {
                sum += g_matrix[nr][nc];
                count++;
            }
        }
    }
    return (count > 0) ? (sum / count) : g_matrix[row][col];
}

static void *quadrant_worker(void *arg) {
    QuadrantArgs *qa = (QuadrantArgs *)arg;
    int peaks = 0;

    printf("[Thread %d] scanning quadrant rows[%d-%d) cols[%d-%d)\n",
           qa->thread_id, qa->row_start, qa->row_end,
           qa->col_start, qa->col_end);

    for (int r = qa->row_start; r < qa->row_end; r++) {
        for (int c = qa->col_start; c < qa->col_end; c++) {
            if (g_matrix[r][c] > CRITICAL_PEAK) {
                int old = g_matrix[r][c];
                int stab = stabilize_value(r, c,
                                           qa->row_start, qa->row_end,
                                           qa->col_start, qa->col_end);
                g_matrix[r][c] = stab;
                printf("[Thread %d] CRITICAL PEAK at [%d][%d]: %d → %d\n",
                       qa->thread_id, r, c, old, stab);
                peaks++;
            }
        }
    }
    printf("[Thread %d] done. %d peak(s) stabilized.\n",
           qa->thread_id, peaks);
    return NULL;
}

/* ================================================================
 *  PHASE 3 HELPERS — Security Vault pipeline
 * ================================================================ */

/*
 * process_b_encryptor()
 * Reads the matrix as a flat int array from a pipe,
 * applies Caesar Cipher (+5, wraps at 100), writes to output pipe.
 */
static void process_b_encryptor(int in_fd, int out_fd) {
    int data[MATRIX_SIZE];
    int n = 0;
    ssize_t bytes;

    while (n < MATRIX_SIZE) {
        bytes = read(in_fd, ((char *)data) + n * sizeof(int),
                     (MATRIX_SIZE - n) * sizeof(int));
        if (bytes <= 0) break;
        n += (int)(bytes / sizeof(int));
    }
    close(in_fd);

    printf("[Process B — Encryptor] received %d values, applying Caesar +%d\n",
           n, CAESAR_SHIFT);

    for (int i = 0; i < n; i++) {
        data[i] = (data[i] + CAESAR_SHIFT) % 101;   /* wrap in [0,100] */
    }

    /* Write encrypted data to next stage */
    write(out_fd, data, n * sizeof(int));
    close(out_fd);
    exit(EXIT_SUCCESS);
}

/*
 * process_c_packager()
 * Receives encrypted int array, prepends a Header, writes binary to vaultDB.
 */
static void process_c_packager(int in_fd) {
    int data[MATRIX_SIZE];
    int n = 0;
    ssize_t bytes;

    while (n < MATRIX_SIZE) {
        bytes = read(in_fd, ((char *)data) + n * sizeof(int),
                     (MATRIX_SIZE - n) * sizeof(int));
        if (bytes <= 0) break;
        n += (int)(bytes / sizeof(int));
    }
    close(in_fd);

    printf("[Process C — Packager] packaging %d values into %s\n",
           n, VAULT_PATH);

    Header hdr;
    hdr.timestamp = (int)time(NULL);
    hdr.data_size = n;

    int fd = open(VAULT_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open vaultDB");
        exit(EXIT_FAILURE);
    }
    write(fd, &hdr, sizeof(Header));
    write(fd, data, n * sizeof(int));
    close(fd);

    printf("[Process C] vaultDB written: header={ts=%d, size=%d}\n",
           hdr.timestamp, hdr.data_size);
    exit(EXIT_SUCCESS);
}

/* ================================================================
 *  PHASE 4 HELPERS — Admin Dashboard gateway (FIFO)
 * ================================================================ */

static void ensure_fifo(void) {
    /* Remove stale FIFO if it exists from a previous run */
    if (access(FIFO_PATH, F_OK) == 0)
        unlink(FIFO_PATH);

    if (mkfifo(FIFO_PATH, 0644) < 0) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }
    printf("[Aegis] FIFO '%s' created. Waiting for dashboard...\n", FIFO_PATH);
}

/*
 * run_formatter()
 * Uses execv() to launch the formatter utility.
 * We pass the path to vaultDB and the request code as arguments.
 */
static void run_formatter(int request_code) {
    char code_str[16];
    snprintf(code_str, sizeof(code_str), "%d", request_code);

    char *argv[] = { "./formatter", VAULT_PATH, code_str, NULL };
    execv("./formatter", argv);

    /* If we reach here execv failed */
    perror("execv formatter");
    exit(EXIT_FAILURE);
}

/*
 * dashboard_gateway()
 * Loop: open FIFO (blocks until a writer connects), read request,
 * fork a child that exec's formatter. Handles multiple open/close
 * cycles without crashing.
 */
static void dashboard_gateway(void) {
    while (1) {
        /* O_RDONLY on a FIFO blocks until a writer opens the other end */
        int fifo_fd = open(FIFO_PATH, O_RDONLY);
        if (fifo_fd < 0) {
            if (errno == EINTR) continue;   /* interrupted — retry */
            perror("open FIFO");
            break;
        }

        int request_code = 0;
        ssize_t n = read(fifo_fd, &request_code, sizeof(int));
        close(fifo_fd);

        if (n <= 0) {
            /* Dashboard closed without writing — just loop back */
            printf("[Aegis] Dashboard disconnected (no request). Waiting...\n");
            continue;
        }

        printf("[Aegis] Received request code %d from dashboard.\n",
               request_code);

        /* Fork a child to exec formatter (keeps main loop alive) */
        pid_t pid = fork();
        if (pid == 0) {
            run_formatter(request_code);
            /* run_formatter calls exec; never returns on success */
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            waitpid(pid, NULL, 0);
        } else {
            perror("fork formatter");
        }
    }
}

/* ================================================================
 *  MATRIX DISPLAY HELPER
 * ================================================================ */
static void print_matrix(const char *label, int mat[MATRIX_ROWS][MATRIX_COLS]) {
    printf("\n━━━ %s ━━━\n", label);
    for (int r = 0; r < MATRIX_ROWS; r++) {
        for (int c = 0; c < MATRIX_COLS; c++) {
            printf("%3d ", mat[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}

/* ================================================================
 *  MAIN
 * ================================================================ */
int main(void) {
    srand((unsigned)time(NULL));

    printf("╔══════════════════════════════════════════╗\n");
    printf("║   AEGIS ENERGY GRID — Reactor Monitor    ║\n");
    printf("╚══════════════════════════════════════════╝\n\n");

    /* ── PHASE 1: Build process tree & pipe network ────────────
     *
     * Pipe layout (all unnamed):
     *   gc_pipe[0][2]  : GC-0  → Child-0  (gc0_to_c0)
     *   gc_pipe[1][2]  : GC-1  → Child-0  (gc1_to_c0)
     *   gc_pipe[2][2]  : GC-2  → Child-1  (gc2_to_c1)
     *   gc_pipe[3][2]  : GC-3  → Child-1  (gc3_to_c1)
     *   c_pipe[0][2]   : Child-0 → Parent
     *   c_pipe[1][2]   : Child-1 → Parent
     *
     * Each pipe: [0]=read-end  [1]=write-end
     */

    int gc_pipe[4][2];
    int c_pipe[2][2];

    for (int i = 0; i < 4; i++) {
        if (pipe(gc_pipe[i]) < 0) { perror("pipe gc"); exit(EXIT_FAILURE); }
    }
    for (int i = 0; i < 2; i++) {
        if (pipe(c_pipe[i]) < 0) { perror("pipe c"); exit(EXIT_FAILURE); }
    }

    /* ── Fork Child-0 ── */
    pid_t child0 = fork();
    if (child0 < 0) { perror("fork child0"); exit(EXIT_FAILURE); }

    if (child0 == 0) {
        /* ─ Inside Child-0 ─ */
        /* Close unused pipe ends owned by Parent / Child-1 */
        close(c_pipe[1][0]); close(c_pipe[1][1]);  /* child-1's pipe */
        close(c_pipe[0][0]);                        /* read-end stays with parent */
        close(gc_pipe[2][0]); close(gc_pipe[2][1]);
        close(gc_pipe[3][0]); close(gc_pipe[3][1]);

        /* Fork GC-0 (CPU sensor) */
        pid_t gc0 = fork();
        if (gc0 < 0) { perror("fork gc0"); exit(EXIT_FAILURE); }
        if (gc0 == 0) {
            close(gc_pipe[0][0]);
            close(gc_pipe[1][0]); close(gc_pipe[1][1]);
            close(c_pipe[0][1]);
            grandchild_sensor(gc_pipe[0][1], 0);  /* CPU */
        }
        close(gc_pipe[0][1]);  /* child doesn't write to gc0 pipe */

        /* Fork GC-1 (Memory sensor) */
        pid_t gc1 = fork();
        if (gc1 < 0) { perror("fork gc1"); exit(EXIT_FAILURE); }
        if (gc1 == 0) {
            close(gc_pipe[1][0]);
            close(gc_pipe[0][0]);
            close(c_pipe[0][1]);
            grandchild_sensor(gc_pipe[1][1], 1);  /* Memory */
        }
        close(gc_pipe[1][1]);

        /* Aggregate and forward to parent */
        child_aggregator(gc_pipe[0][0], gc_pipe[1][0], c_pipe[0][1], 0);
        /* child_aggregator calls exit() */
    }
    /* Parent closes write-ends it gave to child-0 */
    close(gc_pipe[0][0]); close(gc_pipe[0][1]);
    close(gc_pipe[1][0]); close(gc_pipe[1][1]);
    close(c_pipe[0][1]);

    /* ── Fork Child-1 ── */
    pid_t child1 = fork();
    if (child1 < 0) { perror("fork child1"); exit(EXIT_FAILURE); }

    if (child1 == 0) {
        /* ─ Inside Child-1 ─ */
        close(c_pipe[0][0]); close(c_pipe[0][1]);  /* child-0's pipe fully */
        close(c_pipe[1][0]);

        /* Fork GC-2 (Heat sensor) */
        pid_t gc2 = fork();
        if (gc2 < 0) { perror("fork gc2"); exit(EXIT_FAILURE); }
        if (gc2 == 0) {
            close(gc_pipe[2][0]);
            close(gc_pipe[3][0]); close(gc_pipe[3][1]);
            close(c_pipe[1][1]);
            grandchild_sensor(gc_pipe[2][1], 2);  /* Heat */
        }
        close(gc_pipe[2][1]);

        /* Fork GC-3 (Voltage sensor) */
        pid_t gc3 = fork();
        if (gc3 < 0) { perror("fork gc3"); exit(EXIT_FAILURE); }
        if (gc3 == 0) {
            close(gc_pipe[3][0]);
            close(gc_pipe[2][0]);
            close(c_pipe[1][1]);
            grandchild_sensor(gc_pipe[3][1], 3);  /* Voltage */
        }
        close(gc_pipe[3][1]);

        child_aggregator(gc_pipe[2][0], gc_pipe[3][0], c_pipe[1][1], 1);
    }
    /* Parent closes what it gave to child-1 */
    close(gc_pipe[2][0]); close(gc_pipe[2][1]);
    close(gc_pipe[3][0]); close(gc_pipe[3][1]);
    close(c_pipe[1][1]);

    /* ── Parent reads averages and fills the matrix ── */
    printf("[Parent] Collecting sensor averages...\n");

    int matrix_idx = 0;
    /*
     * We have 2 children each sending READINGS_PER_GRANDCHILD = 50 values.
     * Total = 100 values exactly filling the 10x10 matrix.
     * We read from both child pipes in round-robin.
     */
    int total_expected = MATRIX_SIZE;   /* 100 */
    int received[2]    = {0, 0};
    int target_each    = total_expected / 2;  /* 50 each */

    while (matrix_idx < total_expected) {
        for (int ch = 0; ch < 2 && matrix_idx < total_expected; ch++) {
            if (received[ch] >= target_each) continue;
            int avg;
            ssize_t r = read(c_pipe[ch][0], &avg, sizeof(int));
            if (r <= 0) {
                /* Pipe closed early — fill remaining with 0 */
                while (matrix_idx < total_expected) {
                    g_matrix[matrix_idx / MATRIX_COLS][matrix_idx % MATRIX_COLS] = 0;
                    matrix_idx++;
                }
                break;
            }
            int row = matrix_idx / MATRIX_COLS;
            int col = matrix_idx % MATRIX_COLS;
            g_matrix[row][col] = avg;
            matrix_idx++;
            received[ch]++;
            printf("[Parent] matrix[%d][%d] = %d  (total=%d)\n",
                   row, col, avg, matrix_idx);
        }
    }
    close(c_pipe[0][0]);
    close(c_pipe[1][0]);

    /* Wait for children */
    waitpid(child0, NULL, 0);
    waitpid(child1, NULL, 0);

    print_matrix("RAW REACTOR STATE", g_matrix);

    /* ────────────────────────────────────────────────────────────
     * PHASE 2: Spawn 4 worker threads for quadrant analysis
     *
     *  Thread 0 : rows [0,5) cols [0,5)   — top-left
     *  Thread 1 : rows [0,5) cols [5,10)  — top-right
     *  Thread 2 : rows [5,10) cols [0,5)  — bottom-left
     *  Thread 3 : rows [5,10) cols [5,10) — bottom-right
     * ────────────────────────────────────────────────────────────*/
    printf("[Parent] Matrix full. Spawning 4 quadrant worker threads...\n");

    pthread_t threads[4];
    QuadrantArgs qargs[4] = {
        {0,  0, 5,  0, 5},
        {1,  0, 5,  5, 10},
        {2,  5, 10, 0, 5},
        {3,  5, 10, 5, 10}
    };

    for (int t = 0; t < 4; t++) {
        if (pthread_create(&threads[t], NULL, quadrant_worker, &qargs[t]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }
    for (int t = 0; t < 4; t++) {
        pthread_join(threads[t], NULL);
    }

    print_matrix("STABILIZED REACTOR STATE", g_matrix);

    /* ────────────────────────────────────────────────────────────
     * PHASE 3: Security Vault Pipeline
     *
     *   Parent (A) → pipe_ab → Process B (Encryptor)
     *                        → pipe_bc → Process C (Packager)
     *                                  → vaultDB
     * ────────────────────────────────────────────────────────────*/
    printf("[Parent] Starting Security Vault pipeline...\n");

    int pipe_ab[2], pipe_bc[2];
    if (pipe(pipe_ab) < 0 || pipe(pipe_bc) < 0) {
        perror("pipe vault"); exit(EXIT_FAILURE);
    }

    /* Fork Process C (Packager) first so it's ready to read */
    pid_t proc_c = fork();
    if (proc_c < 0) { perror("fork proc_c"); exit(EXIT_FAILURE); }
    if (proc_c == 0) {
        close(pipe_ab[0]); close(pipe_ab[1]);
        close(pipe_bc[1]);
        process_c_packager(pipe_bc[0]);
    }
    close(pipe_bc[0]);  /* parent doesn't read pipe_bc */

    /* Fork Process B (Encryptor) */
    pid_t proc_b = fork();
    if (proc_b < 0) { perror("fork proc_b"); exit(EXIT_FAILURE); }
    if (proc_b == 0) {
        close(pipe_ab[1]);
        process_b_encryptor(pipe_ab[0], pipe_bc[1]);
    }
    /* Parent closes its read-end of pipe_ab and write-end of pipe_bc */
    close(pipe_ab[0]);
    close(pipe_bc[1]);

    /* Parent (A) writes flat matrix into pipe_ab */
    int flat[MATRIX_SIZE];
    for (int i = 0; i < MATRIX_ROWS; i++)
        for (int j = 0; j < MATRIX_COLS; j++)
            flat[i * MATRIX_COLS + j] = g_matrix[i][j];

    write(pipe_ab[1], flat, MATRIX_SIZE * sizeof(int));
    close(pipe_ab[1]);

    waitpid(proc_b, NULL, 0);
    waitpid(proc_c, NULL, 0);

    printf("[Parent] vaultDB persisted successfully.\n");

    /* ────────────────────────────────────────────────────────────
     * PHASE 4: Admin Dashboard Gateway (FIFO)
     * ────────────────────────────────────────────────────────────*/
    ensure_fifo();
    dashboard_gateway();

    /* Clean up FIFO on exit */
    unlink(FIFO_PATH);
    return 0;
}