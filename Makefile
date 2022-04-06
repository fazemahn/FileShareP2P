index: pdu.o index.o
	gcc -o index pdu.o index.o
pdu.o: pdu.c
	gcc -Wall -c pdu.c
index.o: index.c
	gcc -Wall -c index.c
node: pdu.o node.o
	gcc -o node pdu.o node.o
node.o: node.c
	gcc -Wall -c node.c
clean:
	rm *.o index node

