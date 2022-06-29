# Variables definition
CC=gcc
CFLAGS=-Wall -pedantic 
LDFLAGS= 
OPTION=-lcrypto -lssl

# Rules
all: HashCheck clean

HashCheck: HashCheck.o
	$(CC) $(CFLAGS) $< -o $@ $(OPTION)

makedepend:
	makedepend *.c -Y

clean:
	rm *.o

.PHONY: clean all makedepend


