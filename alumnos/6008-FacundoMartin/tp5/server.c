#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h> /* inet_aton */
#include <netdb.h>
#include <string.h>

#include "service.h"


void *atender_cliente(void *arg)
{
	int conn = (long)arg;
	service(conn);
	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	struct sockaddr_in direccion = {};
	int sockfd, conn;
	pthread_t tid;
	//printf("hola?");
 	sockfd = socket(PF_INET, SOCK_STREAM, 0);

	if (sockfd == -1) { 
		perror("socket()");
		exit(EXIT_FAILURE); 
	}

	/* ADDR. FAMILY */
	direccion.sin_family= AF_INET;
	/* PORT */
	//direccion.sin_port = htons(5001);
	direccion.sin_port = htons(9000);
	/* ADDRESS */
	inet_pton(AF_INET, "127.0.0.1", &direccion.sin_addr);
	
	if (bind(sockfd, (struct sockaddr *) &direccion , sizeof (direccion)) < 0) { 
		perror("bind()");
		exit(EXIT_FAILURE); 
	}

	if (listen(sockfd, 5) < 0) { 
		perror("listen()");
		exit(EXIT_FAILURE); 
	}

	while ( (conn = accept(sockfd, NULL, 0)) > 0) {
		if(pthread_create(&tid, NULL, atender_cliente, (void*)(long)conn) != 0){
			printf("error al crear el hilo\n");
			return -1;
		}
		pthread_join(tid,NULL);
		close(conn);
	}

	return 0;	
}

