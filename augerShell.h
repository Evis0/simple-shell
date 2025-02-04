void run_shell();
void launch_child(char *command, char** argv);
char* get_path();
void unit_tests();
int tokenisation(char* input, char** tokenArray, char* delim);
int compare_arrays(char** array1, char** array2);