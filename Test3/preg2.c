#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

float suma(int a, int b)
{
  return a + b;
}

float resta(int a, int b)
{
  return a - b;
}

float division(int a, int b)
{
  return a / b;
}

float multiplicacion(int a, int b)
{
  return a * b;
}

int main()
{
  char args[] = {"20\n10\n30\n"};

  int numero;

  sscanf(args, "%i", &numero);

  printf("%i\n", numero + 10);
  return 0;
}