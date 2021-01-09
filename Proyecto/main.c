#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

struct ProcesoFIFO
{
  id_t id;
};
struct ProcesoRR
{
  id_t id;
};
struct ProcesoPNE
{
  id_t id;
  id_t prioridad;
};

// Funciones
int validar_parametros(int argc, char **argv)
{

  // Recordar que argv[0] es el nombre del programa.
  // fifo
  if (strcmp(argv[1], "-F") == 0 && argc == 3)
    return 1;
  // round robin con quantum
  if (strcmp(argv[1], "-R") == 0 && strcmp(argv[3], "-Q") == 0 && argc == 5)
    return 2;
  // Prioridad no expulsivo
  if (strcmp(argv[1], "-P") == 0 && strcmp(argv[3], "-p") == 0)
    return 3;
  else
    return 0;
};

void FIFO(int argc, char **argv)
{
  printf("\tEl proceso padre comienza su ejecucion\n");
  int cant_procesos = atoi(argv[2]);

  struct ProcesoFIFO procesos[cant_procesos];

  int i;
  // Creamos los procesos
  for (i = 0; i < cant_procesos; i++)
  {
    procesos[i].id = fork();

    if (procesos[i].id == 0)
    {

      kill(getpid(), SIGSTOP); // Pausamos al hijo con sgstop
      execl("loop", "loop", (char *)NULL);
    }
  }
  sleep(1);

  int estado;

  for (i = 0; i < cant_procesos; i++)
  {
    printf("\t\tEl Proceso %d se esta ejecutando\n", procesos[i].id);
    kill(procesos[i].id, SIGCONT); // Enviamos señal al proceso hijo para que continue su ejecucion
    wait(&estado);                 // Esperamos a que finalice
    printf("\t\tEl                 Proceso %d ha finalizado\n", procesos[i].id);
  }
  printf("\tHan finalizado todos los procesos.\nnEjecucion finalizada.\n");
};

void prioridadNoExp(argc, **argv)
{
  /*Aun no implementado*/

}

void roundRobin(int argc, char **argv)
{
  printf("\tCOMIENZA EJECUCION ROUND ROBIN\n");
  int cant_procesos = atoi(argv[2]);
  int quantum = atoi(argv[4]);
  int q_restante;
  int i;
  struct ProcesoRR procesos[cant_procesos];

  for (i = 0; i < cant_procesos; i++)
  {
    procesos[i].id = fork();

    if (procesos[i].id == 0)
    {
      execl("loop", "loop", (char *)NULL); // Permutamos a loop
    }
    else
    {
      printf("\t\tID del proceso creado: %i\n", procesos[i].id);
      kill(procesos[i].id, SIGSTOP); // Dejamos al hijo en estado detenido
    }
  }
  sleep(1);

  int estado;

  for (i = 0; i < cant_procesos; i++)
  {
    for (q_restante = quantum; q_restante > 0; q_restante--)
    {

      printf("\nENTRA -> el proceso %i\n", getpid());
      kill(procesos[i].id, SIGCONT);

      if (q_restante)
        continue;
      else
      {
        kill(procesos[i].id, SIGSTOP);
        printf("\nSALE <- proceso %i", getpid());
      }
    }
    sleep(1);
    }

    wait(&estado);
    printf("\tEl proceso padre finaliza su ejecucion\n");
}

void imprimir_uso()
{
  printf("Como usar este programa:\n");
  printf("Argumentos:\n");
  printf("\tFIFO: -F [num_procesos]");
  printf("\n\tRound Robin: -R [num_procesos] -Q [quantum]");
  printf("\n\tPrioridades no Expulsivo: -P [num_procesos] -p [prioridad1 prioridad2 ... prioridadn\n");
}

int main(int argc, char **argv)
{
  // Si el programa se inicia sin argumentos
  if (argc == 1)
  {
    imprimir_uso();
    return 0;
  }

  // Entero sin signo de 8 bits.
  u_int8_t valido = validar_parametros(argc, argv);

  switch (valido)
  {
  case 0:
    imprimir_uso();
    break;
  case 1:
    printf("FIFO\n");
    FIFO(argc, argv);
    break;
  case 2:
    printf("Round Robin\n");
    roundRobin(argc, argv);
    break;
  case 3:
    printf("Prioridades no Expulsivo.\n");
    prioridadNoExp(argc, argv);
    break;
  }
  printf("Programa finalizado\n");
  return 0;
}