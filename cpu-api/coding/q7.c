//
// Created by Kunhua Huang on 10/8/24.
//
/*
 * Write a program that creates a child process, and then in the child
 * closes standard output (STDOUT_FILENO).What happens if the child
 * calls printf() to print some output after closing the descriptor?
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        close(STDOUT_FILENO);
        printf("Child process PID : %d\n", getpid());
    } else {
        printf("Parent process PID : %d\n", getpid());
    }

    return 0;
}