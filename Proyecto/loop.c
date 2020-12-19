/*
 * ¡¡NO MODIFICAR ESTE CÓDIGO!!
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main() {
	u_int8_t hasta; // Variable sin signo de 1 byte
	srand(time(NULL));
	hasta = (rand() % 16) + 1; // Entre 1 a 15 segundos
	for(int i = 0 ; i <= hasta ; i++) {
		printf("Soy el proceso %d\n", getpid());
		sleep(1);
	}
	return 0;
}
