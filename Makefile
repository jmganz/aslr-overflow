CC = cc
CFLAGS = -Wall -fPIE -pie -fno-stack-protector -O0

#all: address client entropy printHidden server
all: client server entropy

address: address.c
client: client.c
entropy: entropy.c
printHidden: printHidden.c
server: server.c

clean: 
	rm -f *.o address client entropy printHidden server
