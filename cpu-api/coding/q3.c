//
// Created by Kunhua Huang on 10/8/24.
//
/*
 * Write another program using fork(). The child process should
 * print “hello”; the parent process should print “goodbye”. You should
 * try to ensure that the child process always prints first; can you do
 * this without calling wait() in the parent?
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) { // Child process
        sleep(1);
        printf("Child process PID : %d\n", getpid());
    } else { // Parent process
        sleep(2);
        printf("Parent process PID : %d\n", getpid());
        printf("This will always be printed after the child process\n");
    }

    return 0;
}