#include <stdio.h>

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

int chequear_fallo(int *marcos, int cant_marcos, int referencia)
{
  int i;

  // Primero chequear si la referencia ya está en algun marco de página
  for (i = 0; i < cant_marcos; i++)
  {
    if (marcos[i] == referencia)
      return 0; // No se hace ningun cambio, no hay fallo.
  }

  // Si la referencia no está en el marco
  return 1;
}

void ejecutar_fifo(int *referencias, int cant_referencias, int cant_marcos)
{
  int orden_de_entrada[cant_marcos];
  int marcos[cant_marcos];
  int fallos = 0;
  // Inicializamos ambos arreglos con valores -1
  inicializar_marcos(marcos, cant_marcos);
  inicializar_marcos(orden_de_entrada, cant_marcos);

  int i, j, cambio, referencia_actual;

  int primera_referencia = 0; // Indice que indicará cual es la primera referencia que entró.

  for (i = 0; i < cant_marcos; i++)
  {
    marcos[i] = referencias[i];
    orden_de_entrada[i] = referencias[i];
    fallos++;
    imprimir_marcos(marcos, cant_marcos, 1, referencias[i]); // Todas las primeras inserciones lanzan un fallo.
  }

  for (j = i; j < cant_referencias; j++)
  {
    referencia_actual = referencias[j];
    cambio = chequear_fallo(marcos, cant_marcos, referencia_actual); // 1 se hizo un cambio, 0 no se cambió nada.

    if (cambio == 1)
    {
      // Se genera un fallo.
      fallos++;
      // Tomamos el primer marco que se ingresó y le cambiamos el valor.
      marcos[primera_referencia] = referencia_actual;
      imprimir_marcos(marcos, cant_marcos, 1, referencia_actual);
      // Aumentamos nuestro contador en 1
      primera_referencia++;

      // Si nos escapamos del marco reiniciamos el contador.
      if (primera_referencia >= cant_marcos)
        primera_referencia = 0;
    }
    else
    {
      imprimir_marcos(marcos, cant_marcos, 0, referencia_actual);
    }
  }

  calcular_tasa_fallos(fallos, cant_referencias);
}

int main(int argc, char const *argv[])
{

  int cant_referencias, referencia = 0, i = 0, cant_marcos = 0;
  do
  {
    printf("Ingrese la cantidad de referencias que va a ingresar: ");
    scanf("%i", &cant_referencias);

    if (cant_referencias <= 0)
      printf("Error: Debe ingresar un numero entero mayor que 0.\n");

  } while (cant_referencias <= 0);

  do
  {
    printf("Ingrese el numero de marcos de pagina: ");
    scanf("%i", &cant_marcos);

    if (cant_marcos <= 0)
      printf("El numero de marcos de pagina debe ser mayor que 0.");

  } while (cant_marcos <= 0);

  int referencias[cant_referencias];

  for (i = 0; i < cant_referencias; i++)
  {
    do
    {
      printf("Ingrese el valor de la referencia %i: ", i + 1);
      scanf("%i", &referencia);

      if (referencia < 0)
        printf("El valor de la referencia debe ser igual o mayor que 0.\n");

    } while (referencia < 0);

    // Ingresamos la referencia al array de referencias.
    referencias[i] = referencia;
  }

  printf("EJECUTANDO ALGORITMO FIFO\n");
  ejecutar_fifo(referencias, cant_referencias, cant_marcos);

  return 0;
}
