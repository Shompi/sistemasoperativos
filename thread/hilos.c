#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int sumatotal = 0;

void suma()
{
  pthread_t id = pthread_self();

  for (int i = 0; i < 5; i++)
  {
    sumatotal = sumatotal + i;
    printf("Hilo 0x%x: %d\n", (unsigned int)id, i); // pthread_self equivalente a getpid, obtiene el id del hilo
    usleep(99000);
  }
}


int main()
{
  pthread_t th1, th2;
  pthread_create(&th1, NULL, (void *)suma, (void *)NULL); // Creación del hilo
  pthread_create(&th2, NULL, (void *)suma, (void *)NULL);

  pthread_join(th1, NULL); // Ejecución del hilo
  pthread_join(th2, NULL);

  printf("Resultado final: %i\n", sumatotal);
  printf("Hilos finalizados\n");

  return 0;
}
