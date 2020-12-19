#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void multiplicarPorEscalar(int f, int c, int matrix[][c], int escalar)
{
  int i, j;
  for (i = 0; i < f; i++)
  {
    for (j = 0; j < c; j++)
    {
      matrix[i][j] = matrix[i][j] * escalar;
    }
  }
}

void llenarMatriz(int f, int c, int matrix[][c])
{
  int i, j;
  for (i = 0; i < f; i++)
  {
    for (j = 0; j < c; j++)
    {
      matrix[i][j] = rand() % 10;
    }
  }
}

void imprimirMatriz(int f, int c, int matrix[][c])
{
  int i, j;
  for (i = 0; i < f; i++)
  {
    for (j = 0; j < c; j++)
    {
      printf("[%i]", matrix[i][j]);
    }
    printf("\n");
  }
}

void sumarMatrices(int f, int c, int matrix1[][c], int matrix2[][c])
{
  int i, j;
  for (i = 0; i < f; i++)
  {
    for (j = 0; j < c; j++)
    {
      matrix2[i][j] = matrix2[i][j] + matrix1[i][j];
    }
  }
}

void inversoAditivo(int f, int c, int matrix[][c])
{
  int i, j;
  int matrizInversa[f][c];
  for (i = 0; i < f; i++)
  {
    for (j = 0; j < c; j++)
    {
      matrizInversa[i][j] = matrix[i][j] * -1;
    }
  }
  printf("Matriz Inversa Aditiva:\n");
  imprimirMatriz(f, c, matrizInversa);
  sumarMatrices(f, c, matrizInversa, matrix);
  imprimirMatriz(f, c, matrix);
}

int main(int argc, char const *argv[])
{
  srand(time(NULL));
  int filas = 3, cols = 3;
  int matrix[filas][cols];
  int escalar;
  llenarMatriz(filas, cols, matrix);
  imprimirMatriz(filas, cols, matrix);
 /*  printf("Ingrese el valor del escalar para multiplicar la matriz: ");
  scanf("%i", &escalar);

  multiplicarPorEscalar(filas, cols, matrix, escalar); */
  // inversoAditivo(filas, cols, matrix);
  return 0;
}