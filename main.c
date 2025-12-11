#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "header.h"

char command[100];
char* tokens[10];
int count, pip = 0;
int i[10];
char* piped_tokens[20][20];

void input_token(){

		pip = 0;
		int y = 0;

		//input command	
		fgets(command, sizeof(command), stdin);           
		command[strcspn(command, "\n")] = 0;
		
		//tokenisation of the input command
		count = 0;
		char* token = strtok(command, " ");              

		while (token != NULL && count < 10) {

			if (strcmp(token, "|") == 0) {
				i[y] = count;
				y = y + 1;
            	pip++;
        	}
			tokens[count++] = token;       
			token = strtok(NULL, " ");    
		}
		tokens[count] = NULL;
}

void cd(){

		if (tokens[1] == NULL) {
			chdir(getenv("HOME"));
		} else {
			// Change to the specified directory
			if (chdir(tokens[1]) != 0) {
				perror("cd failed");
			}
		}
		//continue;   // Skip fork(), go back to loop
}

void pid(){

	pid_t pid = fork();

	if (pid == 0) {
		
		execvp(tokens[0], tokens);
		perror("exec failed");  
		exit(1);
	} else {
		
		wait(NULL);
	}
}

void pippe(){

	int cmd = 0;
    int arg = 0;

    for (int t = 0; tokens[t] != NULL; t++) {

        if (strcmp(tokens[t], "|") == 0) {
            piped_tokens[cmd][arg] = NULL;
            cmd++;
            arg = 0;
        }
        else {
            piped_tokens[cmd][arg++] = tokens[t];
        }
    }

    piped_tokens[cmd][arg] = NULL;

	int cmd_count = cmd + 1; // number of commands

    int oldfd = 0; // input for next process
    int fd[2];

    for (int c = 0; c < cmd_count; c++) {

        pipe(fd);
        pid_t pid = fork();

        if (pid == 0) {  // child

            dup2(oldfd, STDIN_FILENO); // previous pipe input

            if (c < cmd_count - 1) {
                dup2(fd[1], STDOUT_FILENO); // next pipe output
            }

            close(fd[0]); // close unused read end

            execvp(piped_tokens[c][0], piped_tokens[c]);
            perror("exec failed");
            exit(1);
        }

        // parent
        wait(NULL);
        close(fd[1]);  // close write end
        oldfd = fd[0];  // next command reads from this pipe
    }

}

int main() {

	while (1){
		char cwd[50];

   		if (getcwd(cwd, sizeof(cwd)) !=NULL){
			printf("%s> ", cwd);
		}
		else{return 1;}

		input_token();
		
		if (strcmp(tokens[0], "cd") == 0) {
			cd();
		}
		
		else if (strcmp(tokens[0], "help") == 0){
			commands();
			return 0;
		}

		else if (pip != 0){
			pippe();
		}

		else {
			pid();
		}
	}
	return 0;
}