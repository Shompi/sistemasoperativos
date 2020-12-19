#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	pid_t id;
  
	if((id = fork()) == 0) {
		//for(int i = 0 ; i < 999999 ; i++){}
		printf("PID: %d\n", getpid());
		sleep(5);
		return 30;
	}else {
		int status;
		wait(&status);
		if(WIFEXITED(status)) {
			printf("El proceso hijo retorno valor %d\n", WEXITSTATUS(status));
		}
		if(WIFSIGNALED(status)) {
			printf("El proceso hijo termino con señal %d\n", WTERMSIG(status));
		}
	}
	return 0;
}