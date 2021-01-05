// TRABAJO DE SISTEMAS OPERATIVOS
// GRUPO 10: BAYRON REYES Y JAVIER GONZALEZ
//
// LIBRERIAS PRECARGADAS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
// 

struct ProcesoFIFO{ 
	id_t id; 
};
struct ProcesoRR{ 
	id_t id; 
};
struct ProcesoPNE{ 
	id_t id;
	id_t prioridad; 
};


// Funciones
int evaluaParametros(int argc, char** argv);
void FIFO(int argc, char** argv);
void roundRobin(int argc, char** argv);
void prioridadNoExp(int argc, char** argv);
//
// FUNCION PRINCIPAL 
int main(int argc, char** argv){
	printf("Programa iniciado\n\a");
	switch(evaluaParametros(argc, argv)){
		case 0: // ERROR DE PARAMETROS DE ENTRADA 
			printf("ERROR: Parametros erroneamente ingresados\n");
			break;
		case 1: // FIFO
			printf("Se utilizarà el algoritmo FIFO\n");
			FIFO(argc, argv);
			break;
		case 2: // ROUND ROBIN
			printf("Se utilizarà el algoritmo Round Robin\n");
			roundRobin(argc, argv);
			break;
		case 3: // PRIORIDADES NO EXPULSIVO
			printf("Se utilizarà el algoritmo de Prioridades no expulsivo\n");
			prioridadNoExp(argc, argv);
			break;
	}
	printf("Programa finalizado\n\a");
	return 0;
};
//
// FUNCION PARA EVALUAR QUE ALGORITMO UTILIZAR
int evaluaParametros(int argc, char** argv){
	// RETORNA 1 SI SE UTILIZARA EL ALGORITMO FIFO
	if(strcmp(argv[1], "-F") == 0 && argc == 3) return 1; 
	// RETORNA 2 SI SE UTILIZARA EL ALGORITMO ROUND ROBIN
	if(strcmp(argv[1], "-R") == 0 && strcmp(argv[3], "-Q") == 0 && argc == 5) return 2; 
	// RETORNA 3 SI SE UTILIZARA EL ALGORITMO DE PRIORIDADES NO EXPULSIVO
	if(strcmp(argv[1], "-P") == 0 && strcmp(argv[3], "-p") == 0 && argc == 7) return 3;
	// RETORNA 0 EN EL CASO DE QUE LOS PARAMETROS SEAN INCORRECTOS 
	else return 0; 
};
//
// PLANIFICACION MEDIANTE EL ALGORITMO FIFO
void FIFO(int argc, char** argv){
	printf("\tEl proceso padre comienza su ejecucion\n"); // INICIO DE LA EJECUCION DEL PROCESO PADRE
	struct ProcesoFIFO procesos[atoi(argv[2])]; // CREA LA ESTRUCTURA DEFINIDA PARA EL PROCESO DE PLANIFICACION
	// CREA LOS PROCESOS PARA EJECUTAR EL ALGORITMO
	for(int i = 0; i < atoi(argv[2]); i++){
		procesos[i].id = fork(); // CREA UN PROCESO Y ALMACENA SU ID EN UN ARREGLO DE TIPO PROCESOFIFO
		if(procesos[i].id == 0){ // EJECUTA EL PROCESOFIFO
			printf("\t\tID del proceso hijo: %d\n", getpid()); // MUESTRA LA ID DEL PROCESO HIJO POR PANTALLA    
			kill(getpid(), SIGSTOP);   // PAUSA LA EJECUCION DEL PROCESO HIJO
			execl("loop", "loop", (char *) NULL); // UTILIZA LA CLASE LA FUNCION LOOP, DE EL PROGRAMA LOOP.C
		}
	}
	sleep(1); // ESPERA UN MOMENTO ENTRE LA CREACION DE PROCESOS Y LA PLANIFICACION DE ESTOS
	int estado; // VARIABLE AUXILIAR DE ESTADO RELACIONADO A LOS PROCESOS HIJO UTIL PARA LA PLANIFICACION
	// PLANIFICACION MEDIANTE EL ALGORITMO FIFO
	for(int i = 0; i < atoi(argv[2]); i++){
		printf("\t\tEl proceso hijo (id: %d) comienza su ejecucion\n", procesos[i].id); // INICIO DE EJECUCION DE UN PROCESO HIJO
		kill(procesos[i].id, SIGCONT);  // ENVIA LA SEÑAL AL PROCESO HIJO PARA QUE CONTINUE CON SU EJECUCION
		wait(&estado); // WAIT HASTA QUE EL PROCESO HIJO TERMINA SU EJECUCION
		printf("\t\tEl proceso hijo (id: %d) finaliza su ejecucion\n", procesos[i].id ); // FIN DE EJECUCION DE UN PROCESO HIJO
	}
	printf("\tEl proceso padre finaliza su ejecucion\n"); // INICIO DE LA EJECUCION DEL PROCESO PADRE
};
//
// PLANIFICACION MEDIANTE EL ALGORITMO ROUND ROBIN
void roundRobin(int argc, char** argv){
	printf("\tEl proceso padre comienza su ejecucion\n"); // INICIO DE LA EJECUCION DEL PROCESO PADRE
	struct ProcesoRR procesos[atoi(argv[2])]; // CREA LA ESTRUCTURA DEFINIDA PARA EL PROCESO DE PLANIFICACION
	// CREA LOS PROCESOS PARA EJECUTAR EL ALGORITMO
	for(int i = 0; i < atoi(argv[2]); i++){
		procesos[i].id = fork(); // CREA UN PROCESO Y ALMACENA SU ID EN UN ARREGLO DE TIPO PROCESOFIFO
		if(procesos[i].id == 0){ // EJECUTA EL PROCESOFIFO
			printf("\t\tID del proceso hijo: %d\n", getpid()); // MUESTRA LA ID DEL PROCESO HIJO POR PANTALLA    
			kill(getpid(), SIGSTOP);   // PAUSA LA EJECUCION DEL PROCESO HIJO
			execl("loop", "loop", (char *) NULL); // UTILIZA LA CLASE LA FUNCION LOOP, DE EL PROGRAMA LOOP.C
		}
	}
	sleep(1); // ESPERA UN MOMENTO ENTRE LA CREACION DE PROCESOS Y LA PLANIFICACION DE ESTOS
	int estado = 0; // VARIABLE AUXILIAR DE ESTADO RELACIONADO A LOS PROCESOS HIJO UTIL PARA LA PLANIFICACION
	int senal; // VARIABLE AUXILIAR DE ESTADO DE LA SEÑAL ENVIADA AL PROCESO
	signal(SIGCHLD, SIG_IGN); // IGNORA LAS SEÑALES DE LOS PROCESOS HIJO
	while(estado == 0){
		estado = 1;
		for(int i = 0; i < atoi(argv[2]); i++){
			senal = kill(procesos[i].id, 0);
			if(senal == 0){ 
				printf("\t\tEl proceso hijo (id: %d) comienza su ejecucion\n", procesos[i].id);
				kill(procesos[i].id, SIGCONT);
				sleep(atoi(argv[4]));
				kill(procesos[i].id, SIGSTOP);
				senal = kill(procesos[i].id, 0);
				if(senal == 0){ //!strcmp(errno,ESRCH
					printf("\t\tEl proceso hijo (id: %d) pausa su ejecucion\n", procesos[i].id);
					estado = 0; //No estado
				}
				else printf("\t\tEl proceso hijo (id: %d) finaliza su ejecucion\n", procesos[i].id);
			}
		}
	}
	printf("\tEl proceso padre finaliza su ejecucion\n"); // INICIO DE LA EJECUCION DEL PROCESO PADRE
};
//
// PLANIFICACION MEDIANTE EL ALGORITMO DE PRIORIDADES NO EXPULSIVO
void prioridadNoExp(int argc, char** argv){
	printf("\tEl proceso padre comienza su ejecucion\n"); // INICIO DE LA EJECUCION DEL PROCESO PADRE
	printf("\t\tAlgoritmo no implementado\n");
	printf("\tEl proceso padre finaliza su ejecucion\n"); // INICIO DE LA EJECUCION DEL PROCESO PADRE
};