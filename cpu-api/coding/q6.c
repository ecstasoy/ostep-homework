//
// Created by Kunhua Huang on 10/8/24.
//
/*
 * Write a slight modification of the previous program, this time using
 * waitpid() instead of wait(). When would waitpid() be
 * useful?
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int x = 100;
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        x = 200;
        printf("Child process PID : %d,\nValue of x : %d\n", getpid(), x);
    } else {
        int wc = waitpid(-1, NULL, 0);
        x = 300;
        printf("Parent process PID : %d,\nValue of x : %d\n", getpid(), x);
        printf("Return value of waitpid() : %d\n", wc);
    }

    return 0;
}