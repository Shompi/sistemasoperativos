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

  //Se programa para que ignore las señales de INTERRUPT y STOP.
  signal(SIGINT, SIG_IGN);
  signal(SIGTSTP, SIG_IGN);

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
