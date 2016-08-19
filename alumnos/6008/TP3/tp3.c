/*
 * Computación II: TP3: Comunicación entre procesos con memoria compartida.
 */

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/types.h>

#include "servicio.h"
#define SIZE 2048

int main(int argc, char **argv)
{
	sem_t *ptr;
	int *palabras,*total,cont;
	palabras = malloc(16*sizeof(int));
	total = malloc(16*sizeof(int));
	char *pch;
	int *words;

	memset(total,0,16*sizeof(int));	
	//Memoria compartida para el semaforo y la lectura del archivo
	ptr = mmap(NULL,sizeof(sem_t)+SIZE,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
	//Memoria compartida para los datos procesados
	words = mmap(NULL,16*sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);

	sem_init(ptr,1,1);
	if(fork()==0){ //Hijo
		sem_wait(ptr);
		pch = strtok (ptr+sizeof(sem_t),"\n");
		while (pch != NULL){
			palabras = contar(pch);
			for(cont=0;cont<16;cont++){
				total[cont]=total[cont]+palabras[cont];
			}
			pch = strtok (NULL, "\n");
		}
		for(cont=0;cont<16;cont++){
			words[cont]=total[cont];
			
		}
		sem_post(ptr);
		return 0;
	}
	//Padre
	sem_wait(ptr);
	read(STDIN_FILENO, ptr+sizeof(sem_t), SIZE);
	sem_post(ptr);
	
	wait(NULL);
	for(cont=0;cont<16;cont++){
		total[cont]=words[cont];
	}
	mostrar(total);	
		
	return 0;
}
