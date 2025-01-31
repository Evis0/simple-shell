/*
  Author(s): Emily Probin and Ruairidh Blair
  Version: 0.1
  Date: 28/1/25
*/

#include <stdio.h>
#include <string.h>

void driver();

int main(){
  driver();
  return 0;
}

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
    } if(strcmp(input,"exit\n") == 0){
      break;
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
