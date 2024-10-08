//
// Created by Kunhua Huang on 10/8/24.
//
/*
 * Write a program that creates two children, and connects the standard
 * output of one to the standard input of the other, using the
 * pipe() system call.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int fd[2];
    pipe(fd);
    int rc1 = fork();
    if (rc1 < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc1 == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        printf("Child process 1 PID : %d\n", getpid());
    } else {
        int rc2 = fork();
        if (rc2 < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (rc2 == 0) {
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            char buf[100];
            read(STDIN_FILENO, buf, 100);
            printf("Child process 2 PID : %d\n", getpid());
            printf("Message from child process 1 : %s\n", buf);
        } else {
            printf("Parent process PID : %d\n", getpid());
        }
    }
}