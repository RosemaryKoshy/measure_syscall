/**
 * Homework: System-call latency measurement
 * Talib Pierson
 * 30 September 2020
 * Measure the duration in nanoseconds of the read() system call.
 */
#include <stdio.h>   // perror(), printf()
#include <stdlib.h>  // EXIT_FAILURE, EXIT_SUCCESS
#include <time.h>    // clock_gettime, CLOCK_MONOTONIC
#include <unistd.h>  // read, STDIN_FILENO

#define ITERATIONS 16777216

/**
 * Time a repeated 0-byte read() syscall, dividing its duration by ITERATIONS.
 * @return  SUCCESS if measurement as desired else FAILURE
 */
int main() {
    struct timespec initial_time;
    struct timespec final_time;

    // take the measurement
    if (clock_gettime(CLOCK_MONOTONIC, &initial_time)) {
        perror("clock_gettime");
        return EXIT_FAILURE;
    }
    for (ssize_t i = 0; i < ITERATIONS; ++i) {
        if (read(STDIN_FILENO, NULL, 0)) {
            perror("read");
            return EXIT_FAILURE;
        }
    }
    if (clock_gettime(CLOCK_MONOTONIC, &final_time)) {
        perror("clock_gettime");
        return EXIT_FAILURE;
    }

    // determine and display the measurement
    printf("Duration of read syscall: %f ns\n",
           (double) (1000000000 * (final_time.tv_sec - initial_time.tv_sec) +
                     final_time.tv_nsec - initial_time.tv_nsec) /
           (double) ITERATIONS);

    return EXIT_SUCCESS;
}

/**
 * References:
 * https://pubs.opengroup.org/onlinepubs/9699919799/
 * https://www.gnu.org/savannah-checkouts/gnu/libc/manual/html_mono/libc.html
 */
