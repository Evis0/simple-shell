/*
  Author(s): Emily Probin and Ruairidh Blair
  Version: 0.2
  Date: 28/1/25
*/
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "augerShell.h"


#define MAX_TOKENS 50
#define MAX_INPUT_LENGTH 512
#define PATH_MAX 4096



/*
	Author: Emily Probin and Ruairidh Blair 
	Description: starts the run_shell function and returns 0 after
*/
int main(){
	const char* original_path = get_path();
	
	static char original_wd[PATH_MAX];
	getcwd(original_wd, PATH_MAX);
	
	//printf("%s\n", original_wd);
	int chdir_return = chdir(getenv("HOME"));
	if (chdir_return == -1) {
		printf("ERROR! Change directory to HOME failed: %s\n", strerror(errno));
	}
	//printf("%s\n", getcwd());
	
	//unit_tests();
	run_shell();

	setenv("PATH", original_path, 0);
	//printf("%s \n\n%s", original_path, get_path());

	// probably don't need to do this
	chdir_return = chdir(original_wd);
	if (chdir_return == -1) {
		printf("ERROR! Change directory to original failed: %s\n", strerror(errno));
	}
	
	
	return 0;
}

/*
	Author: Ruairidh Blair and Emily Probin
	Description: Tokenises the input into an array of strings, using set delimiters
*/
int tokenisation(char* input, char** tokenArray, char* delim) {
	// Loop using the strtok function and stores each token in the tokenArray
    char *token = strtok(input,delim);
    //printf("%p\n", token);
    int i = 0;
    while(token && i<MAX_TOKENS){
      tokenArray[i] = token;
      token = strtok(NULL,delim);
      //printf("%p\n", token);
      i++;
    }
    if (i > MAX_TOKENS) {
		printf("Tokens have exceeded limit of 50. The first 50 tokens have been considered.");
	}
    // Set the next position in array to NULL to make it easier to loop through
    tokenArray[i] = NULL;
    
    /*
    for (int j = 0; j<MAX_TOKENS; j++){
	    if (tokenArray[j] == NULL) {
		    break;
		}
		printf("%s\n", tokenArray[i]);
	}
	*/
	
	return i;
}



/*
	Author: Emily Probin and Ruairidh Blair
	Description: Runs the shell, takes input, lunches child processes
*/
void run_shell(){
	
	
  char input[MAX_INPUT_LENGTH];

  // This holds all of the delimiters for the strtok function
  char delim[9] = {' ', '\t', '|', '<', '>', '&', ';', '\n', 0};

  // This will alway run unless the break command is used
  while(1){
    printf("> ");
    // Check the user has not used control + d
    if(!fgets(input,MAX_INPUT_LENGTH,stdin)){
      printf("\n");
      break;
    } 
   	fflush(stdin);
   	
	if(strcmp(input, "\n") == 0){
		continue;
	}

    if(strcmp(input,"exit\n") == 0){
      break;
    }
	
    // Loop using the strtok function and stores each token in the tokenArray
    char *tokenArray[MAX_TOKENS+1];
    int i = tokenisation(input, tokenArray, delim);
	
	
	
	if(strcmp(tokenArray[0],"getpath") == 0){
      char* path = get_path();
      printf("The path is  %s\n", path);
      continue;
    }
	if (strcmp(tokenArray[0], "setpath") == 0){
		if (i>2) {
			printf("Too many parameters\n");
			continue;
		}
		if (i == 1){
			printf("Not enough parameters, must include path you want to set\n");
			continue;
		}
		set_path(tokenArray[1]);
		continue;
	}
	if (strcmp(tokenArray[0], "cd") == 0) {
		int iserror = 0;
		if (i>2) {
			printf("Too many parameters\n");
			continue;
		}
		if (i==1) {
			iserror = chdir(getenv("HOME"));
			if (iserror) {
				printf("ERROR! cd failed: %s\n", strerror(errno));
			}
			continue;
		}
		iserror = chdir(tokenArray[1]);
		if (iserror) {
			printf("ERROR! cd failed: %s: %s\n", strerror(errno), tokenArray[1]);
		}
		continue;
		}
	if (i > 0) {
		launch_child(tokenArray[0], tokenArray);
	}
	
	
  }
}

/*
	Author: Emily Probin
	Date: 31/1/25
	Description: Launches child process. Child process runs the program and passes the arguments, if that
	fails then it exits the program. If the parent is childless it sends an error message. The parent process
	waits for the child process before returning to the main shell.
	https://man7.org/linux/man-pages/man2/fork.2.html
	https://man7.org/linux/man-pages/man2/wait.2.html
*/
void launch_child(char *command, char** argv){
	pid_t PID = fork();
	
	if (PID == 0) {
		//printf("I am in child\n");
		//printf("Path is %s", get_path());
		
		// execute program
		execvp(command, argv);	// will return -1 or never return
		// will only return if exec failed
		printf("ERROR! %s failed: %s\n", command, strerror(errno));
		
		exit(-1);
		
	} else if (PID == -1) {
		//printf("I am a childless parent\n");
		printf("Error in fork - errno = %i\n", errno);
	} else {
		wait(NULL);
		//printf("Finished child process.\n");
	}
}

/*
	Author: Emily Probin
	Date: 31/1/25 
	Description: Gets the path and returns it (string). Using the getenv function.
*/
char* get_path(){
	char* path = getenv("PATH");
	//printf("%s\n", path);
	if (path == NULL){
		printf("Failed to get path.\n");
	}
	return path;
}

/*
	Author: Emily Probin
	Date: 4/2/25
	Description: Sets the path and returns 1 for success and 0 for failure
*/
int set_path(char* value){
	
	int result = setenv("PATH", value, 1);
	if (result) {
		printf("ERROR! Set path failed: %s\n", strerror(errno));
		return 0;
	}
	return 1;
}


/*
	Author: Emily Probin
	Date: 31/1/25 
	Description: Little helper function to compare 2 arrays of strings and return 1 if they are the same 
	and 0 if they arent
*/
int compare_arrays(char** array1, char** array2){
	
	while (*array1 != NULL && *array2 != NULL) {
		// https://www.programiz.com/c-programming/library-function/string.h/strcmp
		if (strcmp(*array1, *array2)){
			return 0;
		}
		array1++;
		array2++;
	}
	if (*array1 == NULL && *array2 == NULL){
		return 1;
	}
	return 0;
}


/*
	Author: Emily Probin
	Date: 2/2/25 
	Description: Test to see if the tokenisation function is working
*/
void unit_tests() {
	char delim[9] = {' ', '\t', '|', '<', '>', '&', ';', '\n', 0};

	char* out1[MAX_TOKENS] = {0};
	char *tokenArray[MAX_TOKENS+1];
	out1[0] = "python3";
	out1[1] = "--version";
	char input[MAX_INPUT_LENGTH];
	strcpy(input, "python3 --version\n");	// strtok modifies ..

	tokenisation(input, tokenArray, delim);
	if (compare_arrays(tokenArray, out1)){
		printf("passed test 1\n");
	}
	else {
		printf("failed test 1\n");
	}
}
