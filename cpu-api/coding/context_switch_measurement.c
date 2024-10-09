//
// Created by Kunhua Huang on 10/9/24.
//
/*
 * This file is used to measure the time of context switch.
 */
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sched.h>
#define MAX_EXECUTION 100000

int main(int argc, char* argv[]) {
    struct timespec start, end;
    int pipefd[2];
    char buf;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    }

    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);  // bind to the first CPU core

    if (sched_setaffinity(0, sizeof(cpu_set_t), &set) == -1) {
        perror("sched_setaffinity");
        return -1;
    }

    if (pid == 0) {  // child process
        close(pipefd[0]);  // close the read end of the pipe
        for (int i = 0; i < MAX_EXECUTION; i++) {
            write(pipefd[1], "a", 1);  // write to the pipe
        }
        close(pipefd[1]);  // close the write end of the pipe
    } else {  // parent process
        close(pipefd[1]);  // close the write end of the pipe
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 0; i < MAX_EXECUTION; i++) {
            read(pipefd[0], &buf, 1);  // read from the pipe
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        close(pipefd[0]);  // close the read end of the pipe

        long seconds = end.tv_sec - start.tv_sec;
        long nanoseconds = end.tv_nsec - start.tv_nsec;

        long avg_seconds = seconds / MAX_EXECUTION;
        long avg_nanoseconds = nanoseconds / MAX_EXECUTION;

        printf("Context switch took: %ld.%09ld\n", seconds, nanoseconds);
        printf("Average time for each context switch: %ld.%09ld\n", avg_seconds, avg_nanoseconds);
    }

    return 0;
}