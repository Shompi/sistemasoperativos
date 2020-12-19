#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{


  int fd[2];
  pid_t hijo;

  int r;

  r = pipe(fd);

  if (r < 0)
  {
    perror("Error al crear pipe\n");
    exit(1);
  }

  hijo = fork();
  int numero;

  if (hijo < 0)
  {
    perror("Error al crear proceso\n");
    exit(1);
  }
  if (hijo == 0)
  {
    close(fd[0]);
    printf("Proceso hijo: Escribir un numero > ");
    scanf("%d", &numero);
    write(fd[1], &numero, sizeof(int));
  }
  else
  {
    close(fd[1]);
    read(fd[0], &numero, sizeof(int));
    printf("Proceso padre: Leer el numero ingresado por el proceso hijo > %d\n", numero);
  }
  return 0;
}
