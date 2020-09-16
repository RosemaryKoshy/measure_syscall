/**
 * Homework: System-call latency measurement
 * Talib Pierson
 * 9/15/20
 * Measure the duration in nanoseconds of the read() system call.
 */
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    /**
     * Time a repeated 0-byte read() system call,
     * int-dividing how long it takes in nanoseconds
     * by the number of iterations.
     */
    if (argc != 2) {
        printf("Usage: %s ITERATIONS\n", basename(argv[0]));
        exit(EXIT_FAILURE);
    }

    const long iterations = strtol(argv[1], NULL, 10);
    if (iterations < 1) {
        printf("%s: ITERATIONS must be a positive integer\n",
               basename(argv[0]));
        exit(EXIT_FAILURE);
    }

    struct timespec initial_time;
    struct timespec final_time;

    // take the measurement
    if (clock_gettime(CLOCK_MONOTONIC, &initial_time)) {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }
    for (long i = 0; i < iterations; ++i) {
        if (read(STDIN_FILENO, NULL, 0)) {
            perror("read");
            exit(EXIT_FAILURE);
        }
    }
    if (clock_gettime(CLOCK_MONOTONIC, &final_time)) {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }

    // determine and display the measurement
    printf("Duration of read syscall: %li ns\n",
           (1000000000 * (final_time.tv_sec - initial_time.tv_sec)
            + final_time.tv_nsec - initial_time.tv_nsec)
           / iterations);
}

/**
 * References:
 * https://pubs.opengroup.org/onlinepubs/9699919799/
 * https://www.gnu.org/savannah-checkouts/gnu/libc/manual/html_mono/libc.html
 */
