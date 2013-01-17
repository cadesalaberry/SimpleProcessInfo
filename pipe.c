#include <stdlib.h>			// Standard Library.
#include <unistd.h>			// Needed to get PID of a process.
#include <stdio.h>			// Needed for I/O to stdout.
#include <sys/wait.h>		// Needed for wait().
#include <string.h>			// Needed for strlen().
#define BUFFER_SIZE 6969

int main(){
	
	int pipefd[2];
	int nBytesRead;														// Stores the number of bytes read in the pipe
	pid_t childPid;														// Stores the PID of the child
	char * cmdChild[] = {"ls", 0};										// Stores the command to be exec by the child
	char   bufferR[BUFFER_SIZE];										// Used as the read pipe buffer
	
	if(pipe(pipefd) < 0){
		fprintf(stderr, "Error while creating the pipe.");
	}
	switch (childPid = fork()){
	
			case -1:{
				printf("\nforking %d failed\n", getppid());
				break;
			}
			case  0:{
				
				close(pipefd[0]);										// Closes the input of the pipe
				printf("I am da child #%d and I execute ", getpid());
				printf("\"ls\".\n");
				printf("I am writing it to the output of the pipe.\n");

				dup2(pipefd[1], 1);										// Makes stdin redirect to the pipe
				
				execvp(cmdChild[0], cmdChild);							// executes the command as the child
                //write(pipefd[1], cmdChild[0], (strlen(cmdChild[0])+1));	// Writes the output on the out of the pipe
				exit(0);
				break;
			}
			default:{
				wait(NULL);
				
				close(pipefd[1]);											// Closes the output of the pipe
				printf("Back to da parent #%d.\n", getpid());
                nBytesRead = read(pipefd[0], bufferR, sizeof(bufferR));	// Reads what is in the pipe
                printf("Received %d bytes: %s", nBytesRead, bufferR);
                
                
				break;
			}
		}
	return 0;
}
