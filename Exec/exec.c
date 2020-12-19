#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	//execlp("ls", "ls", "-a", "-l" ,(char *) NULL);
	execlp("ls", "ls", (char *) NULL);
	printf("Ha fallado la permutacion\n");
	return 0;
}
