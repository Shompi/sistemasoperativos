#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
	if(fork() == 0) {
		printf("Finalizo!!\n");
		return 0;
		//exit(0);
	}else {
		int status;
		sleep(3);
		wait(&status);
		printf("Obtengo la salida del hijo\n");
		sleep(3);
	}
	return 0;
}
