//Compilar con: gcc -pthread -o [nombresalida] [nombreentrada];
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define arraySize 20

int globalArray[arraySize];

void mitadSuperior()
{
  int mitad = arraySize / 2;
  int i;
  for (i = mitad; i < arraySize; i++)
  {
    globalArray[i] = ((rand() % 10) + 1) + 10;
  }
}

void mitadInferior()
{
  int mitad = arraySize / 2;
  int i;
  for (i = 0; i < mitad; i++)
  {
    globalArray[i] = (rand() % 10) + 1;
  }
}

void imprimirArray()
{
  int i;
  for (i = 0; i < arraySize; i++)
  {
    printf("[%i]", globalArray[i]);
  }

  printf("\n");
}

int main(int argc, char const *argv[])
{
  srand(time(NULL));

  pthread_t th1, th2;
  pthread_create(&th1, NULL, (void *)mitadSuperior, (void *)NULL);
  pthread_create(&th2, NULL, (void *)mitadInferior, (void *)NULL);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  printf("Ambos hilos finalizaron.\n");
  imprimirArray();
  return 0;
}
