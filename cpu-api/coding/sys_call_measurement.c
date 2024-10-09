//
// Created by Kunhua Huang on 10/9/24.
//
/*
 * This file is used to measure the time of system calls.
 */
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#define MAX_EXECUTION 100000

int main(int argc, char* argv[]) {
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < MAX_EXECUTION; i++) {
        write(STDOUT_FILENO, "", 0); // system call write()
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    long seconds = end.tv_sec - start.tv_sec;
    long nanoseconds = end.tv_nsec - start.tv_nsec;

    long avg_seconds = seconds / MAX_EXECUTION;
    long avg_nanoseconds = nanoseconds / MAX_EXECUTION;

    printf("System call write() took: %ld.%09ld\n", seconds, nanoseconds);
    printf("Average time for each system call: %ld.%09ld\n", avg_seconds, avg_nanoseconds);

}