/*
 * ============================================================
 *  AEGIS ENERGY GRID — Formatter Utility
 *  Phase 4: exec()'d by the main system to display vaultDB data
 *
 *  Usage:  ./formatter <vaultDB_path> <request_code>
 *    request_code 1  →  Full Status Report  (entire decrypted matrix)
 *    request_code 2  →  System Logs         (header + first 10 values)
 * ============================================================
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define MATRIX_ROWS   10
#define MATRIX_COLS   10
#define MATRIX_SIZE   (MATRIX_ROWS * MATRIX_COLS)
#define CAESAR_SHIFT  5

typedef struct {
    int timestamp;
    int data_size;
} Header;

/* ─── Pretty-print helpers ──────────────────────────────── */

static void print_separator(int width) {
    for (int i = 0; i < width; i++) putchar('=');
    putchar('\n');
}

static void print_header_banner(void) {
    printf("\n");
    print_separator(56);
    printf("  ██████╗  ███████╗ ████████╗  ██████╗  ███████╗\n");
    printf("  ██╔══██╗ ██╔════╝ ╚══██╔══╝ ██╔═══██╗ ██╔════╝\n");
    printf("  ████████║ █████╗     ██║    ██║   ██║ ███████╗\n");
    printf("  ██╔══██╔╝ ██╔══╝     ██║    ██║   ██║ ╚════██║\n");
    printf("  ██║  ██║  ███████╗   ██║    ╚██████╔╝ ███████║\n");
    printf("  ╚═╝  ╚═╝  ╚══════╝   ╚═╝     ╚═════╝  ╚══════╝\n");
    printf("         AEGIS ENERGY GRID — SECURE VAULT REPORT\n");
    print_separator(56);
}

/* Decode a single Caesar-shifted value back to original */
static int decode(int val) {
    int orig = val - CAESAR_SHIFT;
    if (orig < 0) orig += 101;
    return orig;
}

/* Classify a reactor reading */
static const char *classify(int val) {
    if (val > 90) return "⚠  CRITICAL";
    if (val > 70) return "▲  ELEVATED";
    if (val > 40) return "●  NOMINAL ";
    return            "▼  LOW     ";
}

/* ─── Request handlers ──────────────────────────────────── */

/*
 * show_full_status()
 * Displays the complete decrypted reactor matrix with colour coding.
 */
static void show_full_status(Header *hdr, int *data, int n) {
    print_header_banner();

    /* Format timestamp */
    time_t ts = (time_t)hdr->timestamp;
    char timebuf[64];
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S UTC", gmtime(&ts));

    printf("\n  ┌─ VAULT METADATA ───────────────────────────────┐\n");
    printf("  │  Snapshot Time : %-32s│\n", timebuf);
    printf("  │  Data Points   : %-32d│\n", hdr->data_size);
    printf("  └────────────────────────────────────────────────┘\n\n");

    printf("  ┌─ REACTOR STATE MATRIX (decrypted) ─────────────┐\n");
    printf("  │      ");
    for (int c = 0; c < MATRIX_COLS; c++) printf("C%-2d ", c);
    printf("│\n");
    printf("  │  ────");
    for (int c = 0; c < MATRIX_COLS; c++) printf("────");
    printf("│\n");

    int rows = (n > MATRIX_SIZE) ? MATRIX_ROWS : (n / MATRIX_COLS);
    for (int r = 0; r < rows; r++) {
        printf("  │  R%-2d ", r);
        for (int c = 0; c < MATRIX_COLS && (r * MATRIX_COLS + c) < n; c++) {
            int v = decode(data[r * MATRIX_COLS + c]);
            if (v > 90)      printf("\033[1;31m%3d \033[0m", v);  /* red */
            else if (v > 70) printf("\033[1;33m%3d \033[0m", v);  /* yellow */
            else             printf("\033[1;32m%3d \033[0m", v);  /* green */
        }
        printf("│\n");
    }
    printf("  └────────────────────────────────────────────────┘\n");

    /* Summary statistics */
    int sum = 0, peaks = 0, low = 101, high = -1;
    for (int i = 0; i < n; i++) {
        int v = decode(data[i]);
        sum += v;
        if (v > MATRIX_COLS) peaks++;   /* reuse CRITICAL_PEAK > 90 */
        if (v > 90) peaks++;
        if (v < low)  low  = v;
        if (v > high) high = v;
    }
    /* recount properly */
    peaks = 0;
    for (int i = 0; i < n; i++) if (decode(data[i]) > 90) peaks++;

    printf("\n  ┌─ STATISTICS ───────────────────────────────────┐\n");
    printf("  │  Average Value  : %-30d│\n", (n > 0) ? sum / n : 0);
    printf("  │  Minimum Value  : %-30d│\n", (n > 0) ? low  : 0);
    printf("  │  Maximum Value  : %-30d│\n", (n > 0) ? high : 0);
    printf("  │  Critical Peaks : %-30d│\n", peaks);
    printf("  └────────────────────────────────────────────────┘\n\n");

    printf("  Legend: \033[1;31m■ CRITICAL (>90)\033[0m  "
                      "\033[1;33m■ ELEVATED (>70)\033[0m  "
                      "\033[1;32m■ NOMINAL\033[0m\n\n");
}

/*
 * show_logs()
 * Displays vault header metadata and a brief summary of the first 10
 * encrypted/decrypted value pairs.
 */
static void show_logs(Header *hdr, int *data, int n) {
    print_header_banner();

    time_t ts = (time_t)hdr->timestamp;
    char timebuf[64];
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S UTC", gmtime(&ts));

    printf("\n  ┌─ VAULT LOG REPORT ─────────────────────────────┐\n");
    printf("  │  Snapshot Time : %-32s│\n", timebuf);
    printf("  │  Total Records : %-32d│\n", hdr->data_size);
    printf("  └────────────────────────────────────────────────┘\n\n");

    int show = (n < 10) ? n : 10;
    printf("  ┌─ FIRST %2d VAULT ENTRIES ───────────────────────┐\n", show);
    printf("  │  Idx │ Encrypted │ Decrypted │ Status         │\n");
    printf("  │  ────┼───────────┼───────────┼────────────────│\n");
    for (int i = 0; i < show; i++) {
        int enc  = data[i];
        int orig = decode(enc);
        printf("  │  %3d │ %9d │ %9d │ %-14s  │\n",
               i, enc, orig, classify(orig));
    }
    printf("  └────────────────────────────────────────────────┘\n\n");

    printf("  (Full matrix available with request code 1)\n\n");
}

/* ─── Main ──────────────────────────────────────────────── */

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr,
                "Usage: %s <vaultDB_path> <request_code>\n"
                "  request_code 1 = Full Status\n"
                "  request_code 2 = Logs\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    const char *vault_path   = argv[1];
    int         request_code = atoi(argv[2]);

    /* ── Open and read vaultDB ── */
    int fd = open(vault_path, O_RDONLY);
    if (fd < 0) {
        perror("[Formatter] Cannot open vaultDB");
        fprintf(stderr, "  → Path: %s\n", vault_path);
        return EXIT_FAILURE;
    }

    Header hdr;
    if (read(fd, &hdr, sizeof(Header)) != sizeof(Header)) {
        fprintf(stderr, "[Formatter] Failed to read vault header.\n");
        close(fd);
        return EXIT_FAILURE;
    }

    if (hdr.data_size <= 0 || hdr.data_size > MATRIX_SIZE) {
        fprintf(stderr, "[Formatter] Corrupted vault: invalid data_size=%d\n",
                hdr.data_size);
        close(fd);
        return EXIT_FAILURE;
    }

    int *data = malloc(hdr.data_size * sizeof(int));
    if (!data) {
        perror("[Formatter] malloc");
        close(fd);
        return EXIT_FAILURE;
    }

    int n = 0;
    ssize_t bytes;
    while (n < hdr.data_size) {
        bytes = read(fd, ((char *)data) + n * sizeof(int),
                     (hdr.data_size - n) * sizeof(int));
        if (bytes <= 0) break;
        n += (int)(bytes / sizeof(int));
    }
    close(fd);

    /* ── Dispatch to handler ── */
    switch (request_code) {
    case 1:
        show_full_status(&hdr, data, n);
        break;
    case 2:
        show_logs(&hdr, data, n);
        break;
    default:
        fprintf(stderr,
                "[Formatter] Unknown request code %d. Use 1 or 2.\n",
                request_code);
        free(data);
        return EXIT_FAILURE;
    }

    free(data);
    return EXIT_SUCCESS;
}