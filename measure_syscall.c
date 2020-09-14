https://github.com/TalibPierson/measure_syscall/archive/master.zip/**
 * Homework: System-call latency measurement
 * Talib Pierson
 * 9/12/20
 * Measure the duration in nanoseconds of the read() system call.
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
    /**
     * Time a repeated 0-byte read(),
     * int-dividing how long it takes in nanoseconds
     * by the number of iterations (iters).
     */
    struct timespec t0;
    struct timespec t1;

    // take the measurement
    if (clock_gettime(CLOCK_MONOTONIC, &t0)) {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 16777216; ++i) {
        if (read(STDIN_FILENO, NULL, 0)) {
            perror("read");
            exit(EXIT_FAILURE);
        }
    }
    if (clock_gettime(CLOCK_MONOTONIC, &t1)) {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }

    // determine and display the measurement
    printf("Duration of read: %li ns\n",
           (1000000000 * (t1.tv_sec - t0.tv_sec)
            + t1.tv_nsec - t0.tv_nsec)
           / 16777216);
}

/**
 * References:
 * https://pubs.opengroup.org/onlinepubs/9699919799/
 */
