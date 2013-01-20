#include <stdlib.h>			// Standard Library.
#include <unistd.h>			// Needed to get PID of a process.
#include <stdio.h>			// Needed for I/O to stdout.
#include <sys/wait.h>		// Needed for wait().
#include <string.h>			// Needed for strlen().

/**
 * Deals with the forking stuff.
 */ 
int spawn (char** theArgs){
	
	pid_t childPid;
		
	switch (childPid = fork()){
		case -1:{
			printf("\nforking %d failed\n", getppid());
			break;
		}
		case  0:{
			printf("Spawning child #%d, launching: \"", getpid());
			printf("%s\"\n", theArgs[0]);

			execvp(theArgs[0], theArgs);
			printf("Error found. Aborting...\n");
			exit(-1);
			break;
		}
		default:{
			wait(NULL);
			printf("Back to da parent #%d.\n", getpid());
			break;
		}
	}
	return 0;
}
int main(){

	char sInput[69];
	char * fromKeyboard[69];
	int i = 0;
	
	do{
		printf("\nHey, I am process #%d\n", getpid());

		printf("What command do you want to execute ? ");
		
		if (fgets(sInput, sizeof sInput, stdin) != NULL){
		
			//Creates an array of word from the input string.
			fromKeyboard[0] = strtok(sInput, " \n");
			do { fromKeyboard[++i] = strtok(NULL, " \n");
			} while(fromKeyboard[i] != NULL);
			
			spawn(fromKeyboard);
		}
	} while(0);
	
	return 0;
}






