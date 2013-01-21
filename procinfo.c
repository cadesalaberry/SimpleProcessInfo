#include <stdlib.h>			// Standard Library.
#include <unistd.h>			// Needed to get PID of a process.
#include <stdio.h>			// Needed for I/O to stdout.
#include <sys/wait.h>		// Needed for wait().
#include <string.h>			// Needed for strlen().

// Gets the environnement variables.
extern char ** environ;

int main() {

	int    i = 0;
	FILE * file;
	char   temp[6969];
	char   pPath[69];
	char * values[69];
	char * fields[] = {"Name:", "State:", "VmStk:",
						"voluntary_ctxt_switches:",
						"nonvoluntary_ctxt_switches:"};  

	printf("Running process #%d", getpid());
	printf(" with parent #%d\n" , getppid());
	
	// Gets the path the the status file.
	sprintf(pPath, "/proc/%d/status", getpid());

	// Tries opening the file.
	file = fopen(pPath, "r");
	if (file != NULL) {
		
		printf("Reading file: %s\n", pPath);
		while (!feof(file)) {
			
			// Gets the next word in the file.
			fscanf(file, "%s", temp);
			
			for (i = 0; i < 5; i++){
				
				// Checks if it is one of the desired field.
				if(strcmp(temp, fields[i]) == 0){
					
					fscanf(file, "%s", temp);
					values[i] = temp;
					printf("%s\t\t\t\t%s\n", fields[i], values[i]);
				}
			}
		}
		fclose(file);
		
	} else {
		printf("Failed while opening: %s\n", pPath);
	}
	
	printf("Environment variables:\n"); 
	i = 0; while(environ[i]){ printf("%s\n", environ[i++]); }
	
	return 0;
}

