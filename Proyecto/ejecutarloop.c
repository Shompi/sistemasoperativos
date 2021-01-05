#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
int main(int argc, char const *argv[])
{

  long int cantidad_procesos = strtol(argv[1], NULL, 10);
  printf("%li\n", cantidad_procesos);

  int i;

  for (i = 0; i < cantidad_procesos; i++)
  {

    if (fork() == 0)
    {
      execlp("./loop", "loop", NULL);
    }
  }
  printf("Esperando a que terminen los hijos.\n");
  wait(NULL);
  printf("Los hijos han terminado.\n");
  return 0;
}
