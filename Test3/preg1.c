#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

int CTRLZ = 0; //(SIGTSTP)
int CTRLC = 0; //(SIGINT)

void sigint_handler()
{
  CTRLZ = 0;
  CTRLC += 1;
  printf("CTRL C: %i\n", CTRLC);
}

void sigtstp_handler()
{
  CTRLC = 0;
  CTRLZ += 1;
  printf("CTRL Z: %i\n", CTRLZ);
}

int main(int argc, char const *argv[])
{
  int status;
  pid_t idhijo = fork();

  //Si hubo un error al crear el hijo.
  if (idhijo == -1)
    return -1;

  if (idhijo == 0)
  {
    //Proceso hijo debe estar en bucle infinito
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);
    while (1)
    {
      if (CTRLZ == 3)
        exit(1);
      if (CTRLC == 3)
        exit(2);
    };
  }
  else
  {
    //Proceso padre

    //Se programa para que ignore las señales de INTERRUPT y STOP.
    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);

    int s, exitstatus;
    printf("Presione CTRL+Z o CTRL+C 3 veces consecutivas para terminar el proceso.\n");
    //Esperamos a que el hijo termine.
    wait(&s);

    //Valor de status del hijo
    //1 : El proceso terminó por CTRL + Z (SIGTSTP);
    //2 : El proceso terminó por CTRL + C (SIGINT);
    exitstatus = WEXITSTATUS(s);
    if (exitstatus == 1)
      printf("El proceso hijo finalizo por SIGTSTP (CTRL + Z)\n");

    if (exitstatus == 2)
      printf("El proceso hijo finalizo por SIGINT (CTRL + C)\n");

    printf("Ambos procesos han finalizado.\n");
  }
  return 0;
}
