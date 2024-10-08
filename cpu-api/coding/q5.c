//
// Created by Kunhua Huang on 10/8/24.
//
/*
 * Now write a program that uses wait() to wait for the child process
 * to finish in the parent. What does wait() return? What happens if
 * you use wait() in the child?
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
        int wc = wait(NULL);
        x = 300;
        printf("Parent process PID : %d,\nValue of x : %d\n", getpid(), x);
        printf("Return value of wait() : %d\n", wc);
    }

    return 0;
}