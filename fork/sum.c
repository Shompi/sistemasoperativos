#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{

  int val1, val2;

  printf("Ingrese 2 numeros para sumar: ");
  scanf("%i %i", &val1, &val2);

  printf("El resultado es: %i\n", val1 + val2);
  return 0;
}
