index: pdu.o index.o
	gcc -o index pdu.o index.o
pdu.o: pdu.c
	gcc -Wall -c pdu.c
index.o: index.c
	gcc -Wall -c index.c
clean:
	rm *.o index

