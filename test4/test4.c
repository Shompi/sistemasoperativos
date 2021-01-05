#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/sem.h>

void *crear_memoria_compartida(size_t tamano);

char *crearMensaje()
{

  int i;
  char *mensaje = malloc(sizeof(char) * 8); //Maximo largo del mensaje, 9 caracteres.

  for (i = 0; i < 9; i++)
  {
    mensaje[i] = (rand() % (126 - 33 + 1)) + 33;
  }
  mensaje[i] = '\0'; // El ultimo caracter de la cadena lo asignamos al caracter nulo
  return (mensaje);
}

union semun
{
  int val;
  struct semid_ds *buf;
  unsigned short *array;
};

struct sembuf p = {0, -1, SEM_UNDO};
struct sembuf v = {0, 1, SEM_UNDO};

int main()
{

  // Creamos el arreglo de semáforos y obtenemos su id
  int semid = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);

  char *mensaje = NULL;
  //union semun sem_union;

  if (semid < 0)
  {
    // No se pudo obtener el arreglo de semáforos.
    perror("semget");
    exit(1);
  }

  //sem_union.val = 1;

  if (semctl(semid, 0, SETVAL, 1) < 0)
  {
    perror("semctl");
    exit(1);
  }

  char *shared_memory = crear_memoria_compartida(128); //crear memoria compartida
  int i = 0;

  // Creamos 10 hijos
  for (i = 0; i < 10; i++)
  {
    if (fork() == 0)
    {
      // Dormimos al hijo un segundo
      sleep(1);

      // Toma los recursos
      if (semop(semid, &p, 1) < 0)
      {
        perror("semop p");
        exit(13);
      }

      // Leemos el mensaje en el hijo
      printf("(Hijo %i - ID: %i) LEE: %s", i + 1, getpid(), shared_memory);

      // Libreamos los recursos y aumentamos el contador del semáforo
      if (semop(semid, &v, 1) < 0)
      {
        perror("semop v");
        exit(14);
      }

      printf("\n");
      exit(0);
    }
    else
    {

      // Reservamos los recursos
      if (semop(semid, &p, 1) < 0)
      {
        perror("semop p");
        exit(13);
      }

      // Creamos un mensaje al azar de 9 caracteres (contando el caracter nulo);
      mensaje = crearMensaje();

      // Copiamos el mensaje en la memoria compartida
      memcpy(shared_memory, mensaje, sizeof(mensaje));

      // Dormimos al proceso 2 segundos
      sleep(2);

      // Liberamos los recursos
      if (semop(semid, &v, 1) < 0)
      {
        perror("semop v");
        exit(14);
      }
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