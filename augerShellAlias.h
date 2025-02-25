/*
  Author: Emily Probin and Ruairidh Blair
  Stage 7: Alias Header File
  Description: Header file for alias functionality in the shell.
*/

#ifndef AUGERSHELLALIAS_H
#define AUGERSHELLALIAS_H

#define MAX_ALIAS_LENGTH 512
#define MAX_ALIASES 10

typedef struct {
    char name[MAX_ALIAS_LENGTH];
    char command[MAX_ALIAS_LENGTH];
} Alias;

// Function prototypes
void add_alias(char* name, char* command);
void remove_alias(char* name);
void print_aliases();
char* invoke_alias(char* input);

#endif
