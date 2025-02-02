	/*
  Author(s): Emily Probin and Ruairidh Blair
  Version: 0.1
  Date: 28/1/25
*/
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void driver();
void launch_child(char *command, char** argv);
char* get_path();

int main(){
  driver();
  return 0;
}

/*
	
*/
void driver(){
  char input[512];
  // This holds all of the delimiters for the strtok function
  char delim[8] = {' ', '\t', '|', '<', '>', '&', ';'};

  // This will alway run unless the break command is used
  while(1){
    printf("> ");
    // Check the user has not used control + d
    if(!fgets(input,512,stdin)){
      printf("\n");
      break;
    } 
    if(strcmp(input,"exit\n") == 0){
      break;
    }
	if(strcmp(input,"test\n") == 0){
	  char *args[] = {"python3", "--version", NULL}; 

      launch_child("python3", args);
      continue;
    }
	
    // Loop using the strtok function and stores each token in the tokenArray
    char *tokenArray[50];
    char *token = strtok(input,delim);
    //printf("%p\n", token);
    int i = 0;
    while(token){
      tokenArray[i] = token;
      token = strtok(NULL,delim);
      //printf("%p\n", token);
      i++;
    }
    // Set the next position in array to NULL to make it easier to loop through
    tokenArray[i] = NULL;
    /* 
    for (int i = 0; i<50; i++){
	    if (tokenArray[i] == NULL) {
		    break;
		}
		printf("%s\n", tokenArray[i]);
	}
	*/
	if(i > 0) {
		launch_child(tokenArray[0], tokenArray);
	}
	
  }
}

/*
	https://man7.org/linux/man-pages/man2/fork.2.html
	https://man7.org/linux/man-pages/man2/wait.2.html
*/
void launch_child(char *command, char** argv){
	pid_t PID = fork();
	
	if (PID == 0) {
		printf("I am in child\n");
		printf("Path is %s", get_path());
		
		// execute program
		execvp(command, argv);	// will return -1 or never return
		// will only return if exec failed
		printf("Exec failed! %s\n", strerror(errno));
		exit(-1);
		
	} else if (PID == -1) {
		printf("I am a childless parent\n");
		printf("Error in fork - errno = %i\n", errno);
	} else {
		wait(NULL);
		printf("Finished child process.\n");
	}
}

char* get_path(){
	char* path = getenv("PATH");
	printf("%s\n", path);
	if (path == NULL){
		printf("oh no\n");
	}
	return path;
}

