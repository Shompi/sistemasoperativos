#include <stdio.h>
#include <stdlib.h>

int main() {

  int* pointer = (int*) 0x7fffbc2c02a0;

  printf("%i", *(pointer));

  return 0;
}