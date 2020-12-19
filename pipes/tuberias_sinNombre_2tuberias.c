#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

    int fd1[2];
    int fd2[2];
    int resultado;
    pid_t hijo;

    resultado = pipe(fd1);
    pipe(fd2);

    if(resultado < 0) {
        perror("Error al crear pipe\n");
        exit(1);
    }

    hijo = fork();

    if(hijo < 0) {
        perror("Error al crear proceso\n");
        exit(1);
    }
    int n = 0;
    char *mensaje;

    mensaje = (char *) malloc(sizeof(char)*140);

    if(hijo == 0) {
        while(1){
            close(fd1[0]);
            close(fd2[1]);

            if(read(fd2[0],mensaje,sizeof(mensaje)) > 0) {
                printf("El padre dijo: %s\n",mensaje);
            }
            printf("El hijo manda: ");
            fgets(mensaje,140,stdin);

            write(fd1[1],mensaje,sizeof(mensaje));

        }
    }else {
        while(1) {
            close(fd1[1]);
            close(fd2[0]);
            printf("El padre manda: ");
            fgets(mensaje,140,stdin);

            write(fd2[1],mensaje,sizeof(mensaje));

            if(read(fd1[0],mensaje,sizeof(mensaje)) > 0) {
                printf("El hijo escribe: %s\n",mensaje);
            }

        }
    }

    return 0;
}