#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

#include <sys/types.h>
#include <sys/sem.h>

void *crear_memoria_compartida(size_t tamano);

void crearMensaje(char *memory)
{
  srand(getpid());
  int i;
  //Maximo largo del mensaje, 24 caracteres.

  for (i = 0; i < 24; i++)
  {
    memory[i] = (rand() % (125 - 33 + 1)) + 33;
  }
  memory[i] = '\0'; // El ultimo caracter de la cadena lo asignamos al caracter nulo
}

struct sembuf p = {0, -1, SEM_UNDO};
struct sembuf v = {0, 1, SEM_UNDO};

int main()
{
  int num_proc = 0;

  printf("Ingrese el numero de procesos: ");
  scanf("%i", &num_proc);

  // Creamos el arreglo de semáforos y obtenemos su id
  int semid = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);

  if (semid < 0)
  {
    // No se pudo obtener el arreglo de semáforos.
    perror("semget");
    exit(1);
  }

  if (semctl(semid, 0, SETVAL, 1) < 0)
  {
    perror("semctl");
    exit(1);
  }

  char *shared_memory = (char *)crear_memoria_compartida(128); //crear memoria compartida
  strcpy(shared_memory, "Primer mensaje\0");

  int i = 0;

  // Creamos n hijos
  for (i = 0; i < num_proc; i++)
  {
    if (fork() == 0)
    {
      // Procesos hijos
      do
      {

        // Se reservan los recursos para lectura
        /*         if (semop(semid, &p, 1) < 0)
        {
          perror("semop p");
          exit(1);
        } */

        // Leemos el mensaje en el hijo desde la memoria compartida
        printf("Proceso %i LEE: %s\n", getpid(), shared_memory);

        usleep(600000);
        // Libreamos los recursos y aumentamos el contador del semáforo
        /*         if (semop(semid, &v, 1) < 0)
        {
          perror("semop v");
          exit(1);
        } */

        // Se reservan los recursos para escritura
        /*         if (semop(semid, &p, 1) < 0)
        {
          perror("semop p");
          exit(1);
        } */

        // Escribimos un mensaje al azar
        crearMensaje(shared_memory);

        printf("Proceso %i ESCRIBE: %s\n", getpid(), shared_memory);

        usleep(600000);
        // Libreamos los recursos y aumentamos el contador del semáforo
        /*         if (semop(semid, &v, 1) < 0)
        {
          perror("semop v");
          exit(1);
        } */
      } while (1);
    }
  }
  wait(NULL);
  printf("Ejecucion finalizada.\n");
  exit(0);
}

// Codigo base
void *crear_memoria_compartida(size_t tamano)
{
  int protection = PROT_READ | PROT_WRITE;                  // Se define que el arreglo a crear tenga permisos de lectura y escritura.
  int visibility = MAP_SHARED | MAP_ANONYMOUS;              // Se define que el arreglo se cree en un segmento de datos compartidos y no esté respaldado a ningún descriptor (fd)
  return mmap(NULL, tamano, protection, visibility, -1, 0); // mmap es similar a malloc, pero con opciones avanzadas de memoria.
}