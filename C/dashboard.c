/*
 * ============================================================
 *  AEGIS ENERGY GRID — Admin Dashboard
 *  Phase 4: Sends request codes to the main system via FIFO
 * ============================================================
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define FIFO_PATH "query_gate"

/*
 * Request codes:
 *   1  — Status  (display all matrix values from vaultDB)
 *   2  — Logs    (display header metadata + first 10 values)
 */

static void print_banner(void) {
    printf("╔══════════════════════════════════════════╗\n");
    printf("║   AEGIS ADMIN DASHBOARD                  ║\n");
    printf("╚══════════════════════════════════════════╝\n\n");
    printf("  Request codes:\n");
    printf("    1  →  Full Status  (all matrix values)\n");
    printf("    2  →  Logs         (header + first 10 values)\n\n");
}

int main(int argc, char *argv[]) {
    print_banner();

    int request_code = 0;

    /* Accept request code from command-line argument or interactive input */
    if (argc >= 2) {
        request_code = atoi(argv[1]);
        printf("[Dashboard] Using command-line request code: %d\n\n",
               request_code);
    } else {
        printf("Enter request code: ");
        fflush(stdout);
        if (scanf("%d", &request_code) != 1) {
            fprintf(stderr, "[Dashboard] Invalid input.\n");
            return EXIT_FAILURE;
        }
    }

    if (request_code != 1 && request_code != 2) {
        fprintf(stderr, "[Dashboard] Unknown request code %d. Use 1 or 2.\n",
                request_code);
        return EXIT_FAILURE;
    }

    /* Open the FIFO for writing.
     * O_WRONLY on a FIFO blocks until the reader (main system) opens it.
     * We use O_NONBLOCK first to detect if the main system is not running,
     * then fall back to a blocking open with a helpful message.          */
    printf("[Dashboard] Connecting to Aegis system via '%s'...\n", FIFO_PATH);

    int fifo_fd = open(FIFO_PATH, O_WRONLY | O_NONBLOCK);
    if (fifo_fd < 0) {
        if (errno == ENXIO) {
            /* No reader yet — try blocking open */
            printf("[Dashboard] Main system not ready. Waiting...\n");
            fifo_fd = open(FIFO_PATH, O_WRONLY);   /* blocking */
        }
        if (fifo_fd < 0) {
            perror("[Dashboard] Cannot open FIFO");
            fprintf(stderr, "  → Is the Aegis main system running?\n");
            fprintf(stderr, "  → Does '%s' exist? (run main system first)\n",
                    FIFO_PATH);
            return EXIT_FAILURE;
        }
    }

    printf("[Dashboard] Connected. Sending request code %d...\n",
           request_code);

    ssize_t written = write(fifo_fd, &request_code, sizeof(int));
    close(fifo_fd);

    if (written != sizeof(int)) {
        perror("[Dashboard] write to FIFO failed");
        return EXIT_FAILURE;
    }

    printf("[Dashboard] Request sent successfully. "
           "Awaiting Aegis response...\n\n");

    /*
     * The main system will now exec formatter with the vaultDB path and
     * request code. Formatter output will appear in the main system's
     * terminal. This is by design: the dashboard triggers the query and
     * formatter.c handles the display on the server side.
     *
     * In a real deployment the dashboard would open a second FIFO for
     * the response. For this project the spec uses exec() on the server
     * side, so display happens there.
     */
    return EXIT_SUCCESS;
}