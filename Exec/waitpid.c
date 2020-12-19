#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
	pid_t id;
	if((id = fork()) == 0) {
		printf("PID1: %d\n", getpid());
		sleep(8);
		return 8;
	}else {
		if(fork() > 0) {
			int status;
			//waitpid(0, &status, 0);
			waitpid(id, &status, 0);
			if(WIFEXITED(status)) {
				printf("El proceso hijo retorno valor %d\n", WEXITSTATUS(status));
			}
			if(WIFSIGNALED(status)) {
				printf("El proceso hijo termino con señal %d\n", WTERMSIG(status));
			}
		}else {
			printf("PID2: %d\n", getpid());
			sleep(5);
			return 3;
		}
	}
}
