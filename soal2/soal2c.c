#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int pipe_1[2], pipe_2[2];

void exit_on_failed_fork(pid_t child_id) {
    if (child_id < 0)
        exit(EXIT_FAILURE);
}

void list_process() {
    dup2(pipe_1[1], 1);

    close(pipe_1[0]);
    close(pipe_1[1]);

    char *argv[] = {"ps", "aux", NULL};
    execv("/bin/ps", argv);
}

void sort_process() {
    dup2(pipe_1[0], 0);
    dup2(pipe_2[1], 1);

    close(pipe_1[0]);
    close(pipe_1[1]);
    close(pipe_2[0]);
    close(pipe_2[1]);

    char *argv[] = {"sort", "-nrk", "3,3", NULL};
    execv("/usr/bin/sort", argv);
}

void head_process() {
    dup2(pipe_2[0], 0);

    close(pipe_2[0]);
    close(pipe_2[1]);

    char *argv[] = {"head", "-5", NULL};
    execv("/usr/bin/head", argv);
}

int main() {
    if (pipe(pipe_1) < 0)
        exit(1);

    if (pipe(pipe_2) < 0)
        exit(1);

    pid_t child_id;
    child_id = fork();
    exit_on_failed_fork(child_id);

    if (child_id == 0)
        list_process();

    pid_t child_id_2;
    child_id_2 = fork();
    exit_on_failed_fork(child_id_2);

    if (child_id_2 == 0)
        sort_process();

    close(pipe_1[0]);
    close(pipe_1[1]);

    pid_t child_id_3;
    child_id_3 = fork();
    exit_on_failed_fork(child_id_3);

    if (child_id_3 == 0)
        head_process();
}