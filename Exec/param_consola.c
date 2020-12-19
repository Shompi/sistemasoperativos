#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	for(int i = 0 ; i < argc ; i++) {
		printf("Parametro %d: %s\n", i, argv[i]);
	}
	return 0;
}
