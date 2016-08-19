# Computación II: TP3: Comunicación entre procesos con memoria compartida. 

CC=gcc
LDLIBS=-pthread
CFLAGS=-g -Wall

tp3: tp3.o servicio.o
	$(CC) $(LDLIBS) $(CFLAGS) -o $@ $^ 

test: tp3
	cat file.txt | ./tp3
	sleep 2

clean:
	$(RM) tp3 *.o *~

