#include <stdlib.h>			// Standard Library.
#include <unistd.h>			// Needed to get PID of a process.
#include <stdio.h>			// Needed for I/O to stdout.
#include <fcntl.h>
#define MAX_N_BYTES_TO_READ 69


int randomizeArray(int * array){
	
	int i;
	for(i = 0; i < sizeof(array)/sizeof(int); i++)
	{
		// Cannot be used on all computers.
		//int x = arc4random();
		//array[i] = x;
	}
	return 0;
}

int writeArrayToFile(int * array, char * filename){
	
	int		fileD;
	ssize_t	bytesWritten;

	// Tries opening the file.
	fileD = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if(fileD < 0) {
		printf("Error opening the file.\n");
		return -1;
		
	} else {
		
		//Tries writing to the file.
		bytesWritten = write(fileD, array, MAX_N_BYTES_TO_READ);
		if(bytesWritten < 0) {
			printf("Error writing the file.\n");
			return -1;
		} else {
			printf("File written successfully.\n");
		}
	}
	return 0;
}

int readFileAtLocation(char * filename, int location){
	
	int		fileD;
	int		array[69];
	ssize_t	bytesRead;

	// Tries opening the file.
	fileD = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if(fileD < 0) {
		printf("Error opening the file.\n");
		return -1;
		
	} else {
		
		//Tries reading the file.
		bytesRead = read(fileD, array, MAX_N_BYTES_TO_READ);
		if(bytesRead < 0) {
			printf("Error reading the file.\n");
			return -1;
		} else {
			int i;
			for (i = 0; i < 69; i++){
				printf("%i", array[i]);
			}
		}
	}
	return 0;
	
}

int main(){
	
	int		array[] = {0,1,2,3,4,5,6,7,8,9};
	
	writeArrayToFile(array, "the_array");
	readFileAtLocation("the_array", 2);
	return 0;
}

