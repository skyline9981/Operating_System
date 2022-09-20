#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int status;
	printf("Main Process ID : %d.\n", getpid());
	pid_t pid;

	pid = fork(); // fork 1

	if(pid < 0){
		printf("Failed1\n");
		exit(1);
	
	}else if(pid == 0){
		printf("Fork 1. I'm the child %d, my parent is %d.\n", getpid(), getppid());
		
		pid = fork(); // fork 4;
		
		if(pid < 0){
			printf("Failed4\n");
			exit(1);
		
		}else if(pid == 0){
			printf("Fork 4. I'm the child %d, my parent is %d.\n", getpid(), getppid());
			
			pid = fork(); // fork 5;

			if(pid < 0){
				printf("Failed5\n");
				exit(1);
			}else if(pid == 0){
				printf("Fork 5. I'm the child %d, my parent is %d.\n", getpid(), getppid());
			}else{
				wait(NULL);
			}
		}else{
			wait(NULL);
		}
	}else{
		pid = fork();// fork 2;

		if(pid < 0){
			printf("Failed2\n");
			exit(1);
		
		}else if(pid == 0){
			printf("Fork 2. I'm the child %d, my parent is %d.\n", getpid(), getppid());
		
		}else{
			wait(NULL);
		
		}
		pid = fork(); // fork 3;
		if(pid < 0){
			printf("Failed3\n");
			exit(1);
		
		}else if(pid == 0){
			printf("Fork 3. I'm the child %d, my parent is %d.\n", getpid(), getppid());
		
		}else{
			wait(NULL);
		
		}
	}

	return 0;
}