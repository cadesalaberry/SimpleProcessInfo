// Standard Library.
#include <stdlib.h>

// Needed to get PID of a process.
#include <unistd.h>
#include <string.h>
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
int addValueToFieldInFile(char * field, FILE * file, char * buffer);
extern char ** environ;

int main() {

	  // Gets the program signature.
	  pid_t pid = getpid();
	  pid_t ppid = getppid();

	  FILE * file;
	  char * pPath;
	  char report[6969];
	  char * field;
	  char * buffer;
	  
	  // Gets the path the the status file.
	  sprintf(pPath, "/proc/%d/status", pid);

	  file = fopen(pPath, "r");
	  if (file != NULL) {
			printf("Reading: %s\n", pPath);

			//strcat(report, addValueToFieldInFile("Name:", file));

			addValueToFieldInFile("Name:", file, buffer);
			printf("%s", buffer);
			// Get the values in there
			fclose(file);
	  } else {
			printf("Failed while opening: %s\n", pPath);
	  }

	  //  is the way to go for concatenation.
	  //fprintf(pPath, "/proc/%d", getpid());

	  printf("\n\n========================================\n");
	  printf("Running process #%d", pid);
	  printf(" with parent #%d\n", ppid);
	  printf("%s", report);
	  printf("\n========================================\n\n");

}

int addValueToFieldInFile(char * field, FILE * file, char * buffer) {

	  buffer = malloc(sizeof (char)* 6969);
	   while (!feof(file)) {
			
			fscanf(file, "%s", buffer);
			
			printf("Looking at: %s\n", buffer);
			//exit(1);
			if (strcmp(buffer, field) == 0) {
				  strcat(field, " ");
				  fscanf(file, "%s", buffer);
				  return 1;
			}
	  }
	  return -1;
}
