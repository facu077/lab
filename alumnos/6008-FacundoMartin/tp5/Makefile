CC = gcc
CFLAGS = -g -Wall -pthread 
TARGETS = web

all: $(TARGETS)

web: server.c service.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)


clean:
	rm -f $(TARGETS) *.o *~

