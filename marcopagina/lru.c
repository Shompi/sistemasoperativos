#include <stdio.h>

int buscar_posicion(int *tiempos, int cant_marcos)
{
  int i, min = tiempos[0], p = 0;

  for (i = 1; i < cant_marcos; ++i)
  {
    if (tiempos[i] < min)
    {
      min = tiempos[i];
      p = i;
    }
  }

  return p;
}

void imprimir_marcos(int *marcos, int cant_marcos, int fallo, int referencia)
{

  int i;
  printf("Ref: %i - ", referencia);

  for (i = 0; i < cant_marcos; i++)
  {
    if (marcos[i] != -1)
      printf("[%i]", marcos[i]);
    else
      printf("[ ]");
  }

  if (fallo)
    printf("\t// Fallo.");
  else
    printf("\t// No hay fallo.");

  printf("\n");
}

void inicializar_marcos(int *marcos, int cant_marcos)
{
  int i;
  for (i = 0; i < cant_marcos; i++)
    marcos[i] = -1; // Significa que el marco está libre.
}

void calcular_tasa_fallos(int fallos, int cant_referencias)
{
  printf("\nTotal de fallos: %i / %i", fallos, cant_referencias);

  float tasa = (float)fallos / (float)cant_referencias;
  printf("\nTasa de fallos: %1.f%c\n", tasa * 100, 37);

  float rendimiento = (1.0 - tasa) * 100;
  printf("Rendimiento: %1.f%c\n", rendimiento, 37);
}

void ejecutar_LRU(int *referencias, int *marcos, int cant_referencias, int cant_marcos)
{

  int contador = 0;
  int tiempos[cant_marcos];
  int chequeo_a, cambio;
  int i = 0, j = 0, posicion, fallos = 0;

  for (i = 0; i < cant_referencias; ++i)
  {
    chequeo_a = 1;
    cambio = 1;

    for (j = 0; j < cant_marcos; ++j)
    {
      // Si la referencia ya existe en un marco de página
      if (marcos[j] == referencias[i])
      {
        contador++;
        tiempos[j] = contador;
        chequeo_a = 0;
        cambio = 0;
        break;
      }
    }

    if (chequeo_a == 1)
    {
      for (j = 0; j < cant_marcos; ++j)
      {
        if (marcos[j] == -1)
        {
          contador++;
          fallos++;
          marcos[j] = referencias[i];
          tiempos[j] = contador;
          cambio = 0;
          break;
        }
      }
    }

    if (cambio == 1)
    {
      posicion = buscar_posicion(tiempos, cant_marcos);
      contador++;
      fallos++;
      marcos[posicion] = referencias[i];
      tiempos[posicion] = contador;
    }
    if (cambio == 1 || chequeo_a == 1)
      imprimir_marcos(marcos, cant_marcos, 1, referencias[i]);
    else
      imprimir_marcos(marcos, cant_marcos, 0, referencias[i]);
  }

  calcular_tasa_fallos(fallos, cant_referencias);
}

int main()
{
  int cant_marcos, cant_referencias, referencia = 0;

  do
  {
    printf("Cantidad de referencias: ");
    scanf("%i", &cant_referencias);
    if (cant_referencias <= 0)
      printf("ERROR: Debe ingresar al menos 1 referencia.\n");
  } while (cant_referencias <= 0);

  int referencias[cant_referencias];

  do
  {
    printf("Ingrese el numero de marcos ");
    scanf("%i", &cant_marcos);
    if (cant_marcos <= 0)
      printf("ERROR: La cantidad de marcos debe ser igual o mayor que 1.\n");
  } while (cant_marcos <= 0);

  int marcos[cant_marcos];

  int i;
  for (i = 0; i < cant_referencias; ++i)
  {
    do
    {
      printf("Ingrese el valor de la referencia %i: ", i + 1);
      scanf("%i", &referencia);

      if (referencia < 0)
        printf("El valor de la referencia debe ser igual o mayor que 0.\n");

    } while (referencia < 0);

    referencias[i] = referencia;
  }

  inicializar_marcos(marcos, cant_marcos);
  printf("\nEJECUTANDO ALGORITMO LRU\n");
  ejecutar_LRU(referencias, marcos, cant_referencias, cant_marcos);
  return 0;
}