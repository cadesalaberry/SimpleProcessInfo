// Standard Library.
#include <stdlib.h>

// Needed to get PID of a process.
//#include <unistd.h>

// Needed for I/O to stdout.
#include <stdio.h>

#include <string.h>

/****************************************
 *              ABOUT PID.              *
 ****************************************/

// Always successfully returns process ID of caller.
//pid_t getpid(void);

// Always successfully returns proces ID of parent of caller.
//pid_t getppid(void);

/****************************************
 *      ABOUT ENVIRONEMNT VARIABLES.    *
 ****************************************/

// Returns string of env. var. of process "name". (or NULL)
//char *getenv(const char *name);

// Returns accordingly: 0=SUCESS, 1=ERROR
//int setenv(const char *name, const char *value, int overwrite); 

// Returns accordingly: 0=SUCESS, 1=ERROR
//int unsetenv(const char *name);

char ** arrayFromString(char * string);

int main(){

	pid_t childPid;
	pid_t parentPid;
	char sInput[69];
	char * theArgs[69];
	int i = 1;
		
	do{
		
		printf("\nHey, I am process #%d\n", getpid());
		printf("1) What command do you want to execute ? ");
		
		//FROM KEYBOARD:
		//fscanf(stdin, "%s %s", theArgs[0], theArgs[1]);

		//theArgs[0] = strtok(sInput, " ");
		//for(i = 1; theArgs[i-1] != NULL; i++){
			//i++;
		//	theArgs[i] = strtok(NULL, " ");
		//} //while (theArgs[i] != NULL);

		theArgs[0] = "ls"; theArgs[1] = "-l";
		printf("Passing: %s %s\n", theArgs[0], theArgs[1]);
		
		switch (childPid = fork()){
	
			case -1:{
				printf("\nforking %d failed\n", getppid());
				break;
			}
			case  0:{
				printf("I am da child #%d and I am executing: \"", getpid());
				printf("%s\"\n", theArgs[0]);
				exit(execvp(theArgs[0], theArgs));

				break;
			}
			default:{
				wait(NULL);
				printf("Back to da parent #%d.\n", getpid());
				break;
			}
		}
		
		wait();
	} while(0);
}

char ** arrayFromString(char * string){

	char * array[69];
	char* token = strtok( string, " " );
	int i = 0;

	for(i = 0; token != NULL && i < 69; token = strotok( NULL, " ")){
	    array[ i ] = token;
	    ++i;
	}
	
	return array;
}





