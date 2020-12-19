#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
  //Multiplicación de matrices.
  int Af, Ac, Bf, Bc;

  printf("Ingrese las dimensiones de la matriz A: ");
  scanf("%i %i", &Af, Ac);

  printf("Ingrese las dimensiones de la matriz B: ");
  scanf("%i %i", &Bf, &Bc);

  int A[Af][Ac];
  int B[Bf][Bc];

  
  return 0;
}
