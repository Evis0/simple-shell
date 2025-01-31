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
void launch_child();
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
      launch_child();
      continue;
    }
	
    // Loop using the strtok function and stores each token in the tokenArray
    char *tokenArray[50];
    char *token;
    token = strtok(input,delim);
    int i = 0;
    while(token){
      tokenArray[i] = token;
      token = strtok(NULL,delim);
      i++;
    }
    // Set the next position in array to NULL to make it easier to loop through
    tokenArray[i] = NULL;
  }
}

/*
	https://man7.org/linux/man-pages/man2/fork.2.html
	https://man7.org/linux/man-pages/man2/wait.2.html
*/
void launch_child(){
	pid_t PID = fork();
	
	if (PID == 0) {
		printf("I am in child\n");
		exit(-1);
		// 
	}else if (PID == -1) {
		printf("I am a childless parent\n");
		printf("%i\n", errno);
	} else {
		wait(NULL);
		printf("Finished child process.\n");
	}
	get_path();
}

char* get_path(){
	char* path = getenv("PATH");
	printf("%s\n", path);
	if (path == NULL){
		printf("oh no\n");
	}
	return path;
}
