#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void imprimir_pid() {
	printf("PID: %d\n", getpid());
}

int main() {
	signal(SIGUSR1, imprimir_pid); // Programar señal
	signal(SIGINT, SIG_IGN); // Ignorar señal
	while(1);
	return 0;
}
