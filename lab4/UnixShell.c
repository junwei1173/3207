#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_PIPES 10

void parse_input(char *input, char ***commands, int *num_commands) {
    char *token;
    *num_commands = 0;
    *commands = malloc(MAX_PIPES * sizeof(char *));

    token = strtok(input, "|");
    while (token != NULL) {
        (*commands)[(*num_commands)++] = strdup(token);
        token = strtok(NULL, "|");
    }
    (*commands)[*num_commands] = NULL;
}

void parse_command(char *command, char ***args, char **infile, char **outfile, int *append) {
    char *token = strtok(command, " ");
    int count = 0;
    int capacity = 10;
    *args = malloc(capacity * sizeof(char *));
    *infile = NULL;
    *outfile = NULL;
    *append = 0;

    while (token != NULL) {
        if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " ");
            *infile = token ? strdup(token) : NULL;
        } else if (strcmp(token, ">") == 0 || strcmp(token, ">>") == 0) {
            *append = (strcmp(token, ">>") == 0);
            token = strtok(NULL, " ");
            *outfile = token ? strdup(token) : NULL;
        } else {
            if (count >= capacity) {
                capacity *= 2;
                *args = realloc(*args, capacity * sizeof(char *));
            }
            (*args)[count++] = token;
        }
        token = strtok(NULL, " ");
    }
    (*args)[count] = NULL;
}

void execute_pipeline(char ***commands, int num_commands) {
    int pipes[MAX_PIPES][2];
    pid_t pids[MAX_PIPES + 1];

    for (int i = 0; i < num_commands - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < num_commands; i++) {
        char **args, *infile, *outfile;
        int append;
        parse_command((*commands)[i], &args, &infile, &outfile, &append);
        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                fprintf(stderr, "cd: missing argument\n");
            } else if (chdir(args[1]) != 0) {
                perror("cd");
            }
            free(args);
            continue;
        }

        pids[i] = fork();
        if (pids[i] == 0) { // Child process
            if (i > 0) {
                dup2(pipes[i - 1][0], STDIN_FILENO);
                close(pipes[i - 1][0]);
            }
            if (i < num_commands - 1) {
                dup2(pipes[i][1], STDOUT_FILENO);
                close(pipes[i][1]);
            }
            for (int j = 0; j < num_commands - 1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            if (infile) {
                int fd = open(infile, O_RDONLY);
                if (fd == -1) { perror("open infile"); exit(EXIT_FAILURE); }
                dup2(fd, STDIN_FILENO);
                close(fd);
            }
            if (outfile) {
                int fd = open(outfile, O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC), 0644);
                if (fd == -1) { perror("open outfile"); exit(EXIT_FAILURE); }
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }
            execvp(args[0], args);
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        free(args);
    }

    for (int i = 0; i < num_commands - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    for (int i = 0; i < num_commands; i++) {
        waitpid(pids[i], NULL, 0);
    }
}

int main() {
    char *input = NULL;
    size_t input_size = 0;
    char **commands;
    int num_commands;

    while (1) {
        printf("Junwei's Shell> ");
        ssize_t nread = getline(&input, &input_size, stdin);
        if (nread == -1) break;

        input[strcspn(input, "\n")] = '\0';
        if (strcmp(input, "exit") == 0) break;

        parse_input(input, &commands, &num_commands);
        execute_pipeline(&commands, num_commands);

        for (int i = 0; i < num_commands; i++) {
            free(commands[i]);
        }
        free(commands);
    }

    free(input);
    printf("Exiting Junwei's Shell\n");
    return 0;
}
