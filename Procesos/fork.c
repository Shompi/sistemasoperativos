#include <unistd.h>
#include <stdio.h>

int main() {
	pid_t pid_hijo;
	pid_hijo = fork();
	/* Si fork() crea el proceso correctamente, retorna dos valores dependiendo del proceso que se está ejecutando.
	En el proceso padre retorna el pid del nuevo proceso, esté será el proceso hijo y es una replica exacta del proceso padre.
	En el proceso hijo retorna 0.
	*/
	if(pid_hijo > 0) { // Si pid_hijo es mayor que 0, significa que estamos en el proceso padre
		printf("%d: Soy el padre y mi hijo es %d\n", getpid(), pid_hijo);
	}else if(pid_hijo == 0) { // Si pid_hijo es 0, significa que estamos en el proceso hijo
		printf("%d: Soy el hijo y mi padre es %d\n", getpid(), getppid()); // getpid() obtiene pid del proceso. getppid() obtiene el pid del padre
	}else if(pid_hijo == -1) { // Si pid_hijo es -1, significa que el proceso no fue creado
		printf("%d: Error al crear proceso\n", getpid());
	}
	sleep(10);
	return 0;
}
