#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char *argv_ls[] = { "ls", 0 };
static char *argv_wc[] = { "wc", 0 };
static char **cmds[]   = { argv_ls, argv_wc };

int main(void)
{
    int n_commands = 2;
    int pipefd[2];
	int i = 0;
    pipe(&pipefd[0]);   // Error check!

    fflush(stdout);
    for (i = 0; i < n_commands; i++)
    {
        int pid = fork();

        if (pid == 0)
        {
            int command_no = i;
            int prev_pipe = ((command_no - 1) % 2) * 2;
            int current_pipe = (command_no % 2) * 2;
            printf("cmd %d: prev pipe %d, curr pipe %d\n", i, prev_pipe, current_pipe);
            fflush(stdout);

            // If current command is the first command, close the
            // read end, else read from the last command's pipe
            if (command_no == 0)
            {
                close(pipefd[0]);
            }
            else
            {
                dup2(pipefd[prev_pipe], 0);
                close(pipefd[current_pipe]);  // Line 40
            }

            // If current command is the last command, close the
            // write end, else write to the pipe
            if (command_no == n_commands - 1)
                close(pipefd[current_pipe + 1]);  // Line 46
            else
                dup2(pipefd[current_pipe + 1], 1);

            execvp(cmds[i][0], cmds[i]);
            fprintf(stderr, "Failed to exec: %s (%d: %s)\n", cmds[i][0], errno, strerror(errno));
            _exit(1);
        }
    }

    return 0;
}
