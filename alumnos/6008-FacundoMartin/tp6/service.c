#include "service.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>


int service(int sdc) {
	char buff[1024];
	char buffer[1024];
	char *token;
	char *estado = NULL;
	char metodo[8];
	int leido;
	char *http_header = "HTTP/1.0 200 Ok\r\nContent-Type: text/plain\r\n\r\n";

	leido = read(sdc, buff, sizeof buff);

	printf("El cliente me escribio %s \n", buff);

	strcpy(buffer,buff);
	token = strtok(buffer, " ");
	strcpy(metodo,token);

	if((token = strtok(NULL, " ")) == NULL){
		estado = "404 Not Found\n";
		write(sdc,estado,strlen(estado));
	}
	
	else if (!(strncmp(metodo,"GET",3) == 0)){
		estado = "405 METHOD NOT ALLOWED\n";
		write(sdc,estado,strlen(estado));
		}

	else{
		write(sdc, http_header, strlen(http_header)); 
		write(sdc, buff, leido);
	}
	
	close(sdc);
    return 0;
}

