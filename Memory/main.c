#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  int *pointer = malloc(sizeof(int));

  printf("Asignada memoria desde [%p]\n", pointer);
  *(pointer) = 5;
  sleep(30);
  free(pointer);
  printf("Execution terminated.\n");
  return 0;
}
