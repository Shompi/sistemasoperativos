#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	printf("Ejemplo de proceso huerfano. \n");
	printf("Inicio del Proceso padre. PID=%d\n",getpid());
	if(fork() == 0){
		printf("Inicio proceso hijo. PID=%d, PPID=%d\n",getpid(),getppid());
		sleep(10);
		printf("El proceso queda huerfano. PID=%d, PPID=%d\n",getpid(),getppid());
	}
	else{
		printf("Continuacion proceso padre. PID=%d\n",getpid());
		sleep(5);
	}
	printf("Fin del proceso %d\n",getpid());
	return(0);
}
