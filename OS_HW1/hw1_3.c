#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_LINE 80

int main(void){
	char *arg[MAX_LINE/2+1]; /*command line arguments*/
	int should_run = 1; /*flag to determine when to exit program*/

	while(should_run){
		printf("osh>");
		fflush(stdout);
		// memset(arg, 0, sizeof(arg));
		/**
		* your code!
		* After reading user input, the step are:
		* (1) fork a child process using fork()
		* (2) the child process will invoke execvp()
		*/

		char inputBuffer[MAX_LINE]; //store input
		read(STDIN_FILENO, inputBuffer, MAX_LINE); //read input and store;

		char *split = strtok(inputBuffer, " "); //split input
		int now = 0;

		while(split != NULL){
			arg[now++] = split;
			char *index;
			if ((index = strchr(arg[now-1], '\n')) != NULL) {
				*index = '\0';
			}
			split = strtok(NULL, " ");
		}
		if(!strcmp(arg[0], "exit")){
			should_run = 0; //if the input is "exit" than cahnge the flag;
			continue;
		}

		arg[now] = NULL;

		pid_t pid = fork(); //create child process to run execvp;
		if(pid == 0){
			if(execvp(arg[0], arg) < 0){
				printf("Execvp Error. You input an invalid command!");
				exit(1);
			}
		}else if(pid > 0){
			wait(NULL); //parent process wait;
		}else{
			printf("Fork Error.");
			exit(1);
		}
	}
	return 0;
}


