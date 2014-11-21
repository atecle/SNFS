target: clientapp

clientapp: client.o clientSNFS.o
	gcc -Wall  -o $@  client.o  clientSNFS.o

client.o: client.c
	gcc -Wall  -c client.c

clientSNFS.o: clientSNFS.c
	gcc -Wall  -c clientSNFS.c

clean: 
	rm *.o
	rm clientapp
