#include <stdio.h>
#include <unistd.h>

int main() {
	int id;
	id = fork();
  
  printf("%d", id);

	if(id == 0) {
		fork();
	}
	sleep(10);
	return 0;
}
