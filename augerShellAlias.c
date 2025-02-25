/*
  Author: Emily Probin and Ruairidh Blair
  Stage 7: Alias Functionality
  Description: Implements alias support for the shell.
*/

#include "augerShellAlias.h"
#include <stdio.h>
#include <string.h>

Alias alias_list[MAX_ALIASES];
int alias_count = 0;

// Adds or updates an alias
void add_alias(char* name, char* command) {
    for (int i = 0; i < alias_count; i++) {
        if (strcmp(alias_list[i].name, name) == 0) {
            strcpy(alias_list[i].command, command);
            printf("Updated alias: %s -> %s\n", name, command);
            return;
        }
    }

    if (alias_count >= MAX_ALIASES) {
        printf("ERROR! Maximum number of aliases reached.\n");
        return;
    }

    strcpy(alias_list[alias_count].name, name);
    strcpy(alias_list[alias_count].command, command);
    alias_count++;
}

// Removes an alias by shifting elements
void remove_alias(char* name) {
    for (int i = 0; i < alias_count; i++) {
        if (strcmp(alias_list[i].name, name) == 0) {
            for (int j = i; j < alias_count - 1; j++) {
                alias_list[j] = alias_list[j + 1];
            }
            alias_count--;
            printf("Alias '%s' removed.\n", name);
            return;
        }
    }
    printf("ERROR! Alias '%s' not found.\n", name);
}

// Prints all stored aliases
void print_aliases() {
    if (alias_count == 0) {
        printf("No aliases set.\n");
        return;
    }
    for (int i = 0; i < alias_count; i++) {
        printf("%s='%s'\n", alias_list[i].name, alias_list[i].command);
    }
}

// Invokes aliases before execution
char* invoke_alias(char* input) {
    static char expanded[MAX_ALIAS_LENGTH];
    char temp[MAX_ALIAS_LENGTH];
    strcpy(temp, input);

    char* first_token = strtok(temp, " ");
    for (int i = 0; i < alias_count; i++) {
        if (strcmp(alias_list[i].name, first_token) == 0) {
            snprintf(expanded, sizeof(expanded), "%s%s", alias_list[i].command, input + strlen(first_token));
            return expanded;
        }
    }
    return input;
}
