#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

	char command[100];
	char* tokens[10];
	int count = 0;
	
	while (1){
		//input command	
		printf("> ");
		fgets(command, sizeof(command), stdin);           
		command[strcspn(command, "\n")] = 0;
		
		//tokenisation of the input command
		char* token = strtok(command, " ");              

		while (token != NULL && count < 10) {
			tokens[count++] = token;       
			token = strtok(NULL, " ");    
		}
		tokens[count] = NULL;

		//print all the tokens from the input command
		//int i = 0;
		//for (i; i < count; i = i + 1) {
		//	printf("%s", tokens[i]);	
		//}

		pid_t pid = fork();

		if (pid == 0) {
			
			execvp(tokens[0], tokens);
			perror("exec failed");  
			exit(1);
		} else {
			
			wait(NULL);
		}

	}
	return 0;
}