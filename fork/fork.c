#include <unistd.h>
#include <stdio.h>

int main()
{
  int status;

  if (status = execl("./sum", "sum") == -1)
    printf("Error on exec.\n");
  
  return 0;
}
