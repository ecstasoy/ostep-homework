//
// Created by Kunhua Huang on 10/8/24.
//
/*
 * Write a program that opens a file (with the open() system call)
 * and then calls fork() to create a new process. Can both the child
 * and parent access the file descriptor returned by open()? What
 * happens when they are writing to the file concurrently, i.e., at the
 * same time?
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int file = open("testfile.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

    if (file < 0) {
        perror("open");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) { // Child process
        const char *child_msg = "Written by child process\n";
        write(file, child_msg, strlen(child_msg));
    } else { // Parent process
        const char *parent_msg = "Written by parent process\n";
        write(file, parent_msg, strlen(parent_msg));
    }

    close(file);

    return 0;
}