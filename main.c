#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "header.h"

int main() {

	char command[100];
	char* tokens[10];
	int count = 0;
	
	while (1){
		char cwd[50];

   		if (getcwd(cwd, sizeof(cwd)) !=NULL){
			printf("%s> ", cwd);
		}
		else{return 1;}

		//input command	
		fgets(command, sizeof(command), stdin);           
		command[strcspn(command, "\n")] = 0;
		
		//tokenisation of the input command
		count = 0;
		char* token = strtok(command, " ");              

		while (token != NULL && count < 10) {
			tokens[count++] = token;       
			token = strtok(NULL, " ");    
		}
		tokens[count] = NULL;

		if (strcmp(tokens[0], "cd") == 0) {

    // If no argument: go to HOME
			if (tokens[1] == NULL) {
				chdir(getenv("HOME"));
			} else {
				// Change to the specified directory
				if (chdir(tokens[1]) != 0) {
					perror("cd failed");
				}
			}

			continue;   // Skip fork(), go back to loop
		}

		//print all the tokens from the input command
		//int i = 0;
		//for (i; i < count; i = i + 1) {
		//	printf("%s", tokens[i]);	
		//}
		
		else if (strcmp(tokens[0], "help") == 0){
			commands();
		}

		else {
			pid_t pid = fork();

			if (pid == 0) {
				
				execvp(tokens[0], tokens);
				perror("exec failed");  
				exit(1);
			} else {
				
				wait(NULL);
			}
	}
	}
	return 0;
}