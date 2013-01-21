#include <stdlib.h>			// Standard Library.
#include <unistd.h>			// Needed to get PID of a process.
#include <stdio.h>			// Needed for I/O to stdout.
#include <sys/wait.h>		// Needed for wait().
#include <string.h>			// Needed for strlen().

int main(){
	
	int pipefd[2];
	pid_t childPid;
	char * cmdChild[] = {"ls", 0};
	char * cmdParent[] = {"wc", "-l", 0};
	
	if(pipe(pipefd) < 0){
		fprintf(stderr, "Error while creating the pipe.\n");
		
	} else {
		switch (childPid = fork()){
			case -1:{
				printf("\nForking %d failed.\n", getppid());
				break;
			}
			case  0:{
				// Closes the input of the pipe for it is not used.
				close(pipefd[0]);
				
				printf("I am da child #%d and I execute ", getpid());
				printf("\"ls\".\n");
				printf("I am writing it to the output of the pipe.\n");
				
				// Makes stdin redirect to the pipe.
				dup2(pipefd[1], 1);
				
				execvp(cmdChild[0], cmdChild);
				printf("Error found. Aborting...\n");
				exit(-1);
				break;
			}
			default:{
				// Waits for the child to be done.
				wait(NULL);
				
				// Closes the output of the pipe for it is not used.
				close(pipefd[1]);
		
				printf("Back to da parent #%d.\n", getpid()); printf(
				"The command \"wc\" has counted the following "); 
				printf("number of lines:\n");					
				
				/* If no FILE argument is specified,
				 * wc will use the stdin as input.
				 * Thus we redirect the pipe to stdin
				 */
				 dup2(pipefd[0],0);
			
				execvp(cmdParent[0], cmdParent);
				printf("Error found. Aborting...\n");
				exit(-1);
				break;
			}
		}
	}
	return -1;
}
