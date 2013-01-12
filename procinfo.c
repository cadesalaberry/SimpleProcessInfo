// Standard Library.
#include <stdlib.h>

// Needed to get PID of a process.
#include <unistd.h>

// Needed for I/O to stdout.
#include <stdio.h>

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

int main(){
	
	printf("\n\n========================================\n");
	printf("Running process #%d", getpid());
	printf(" with parent #%d\n", getppid());

	FILE * pFile;
	char * pName;
	char * pPath;
	
	// sprintf(); is the way to go for concatenation.
	//fprintf(pPath, "/proc/%d", getpid());

	pFile = fopen (pPath,"r");

	if (pFile != NULL) {
		fscanf(pFile, "Name:\t%[^\n]\n", *pName);
		printf("%s", &pName);		
		fclose (pFile);
	} else {	
		printf("Failed while opening: /proc\n");	
	}
	
	printf("\n========================================\n\n");
	
}






