//
// Created by Kunhua Huang on 10/8/24.
//
/*
 * Write a program that calls fork() and then calls some form of
 * exec() to run the program /bin/ls. See if you can try all of the
 * variants of exec(), including (on Linux) execl(), execle(),
 * execlp(), execv(), execvp(), and execvpe(). Why do
 * you think there are so many variants of the same basic call?
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int arg, char* argv[]) {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("Child process PID : %d\n", getpid());
        execl("/bin/ls", "ls", NULL);
        execle("/bin/ls", "ls", NULL, NULL);
        execlp("ls", "ls", NULL);
        execv("/bin/ls", argv);
        execvp("ls", argv);
        execve("/bin/ls", argv, NULL);
    } else {
        printf("Parent process PID : %d\n", getpid());
    }

    return 0;
}