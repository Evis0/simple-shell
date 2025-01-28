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
  // char delim[8] = {' ', '\t', '|', '<', '>', '&', ';'};
  int goFlag = 1;

  while(goFlag){
    printf("> ");
    if(!fgets(input,512,stdin)){
      printf("\n");
      break;
    } if(strcmp(input,"exit")){
      printf("%s, %d",input,strcmp(input,"exit"));
      break;
    }
    
  }
}
