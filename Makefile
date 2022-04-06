testindex: pdu.o content.o time_server.o
	gcc -o index pdu.o content.o time_server.o
testnode: pdu.o content.o time_client.o
	gcc -o node pdu.o content.o time_client.o
index: pdu.o content.o index.o
	gcc -o index pdu.o content.o index.o
pdu.o: pdu.c
	gcc -Wall -c pdu.c
index.o: index.c
	gcc -Wall -c index.c
node: pdu.o content.o node.o
	gcc -o node pdu.o content.o node.o
node.o: node.c
	gcc -Wall -c node.c
content.o: content.c
	gcc -Wall -c content.c 

time_server.o: time_server.c
	gcc -Wall -c time_server.c 
time_client.o: time_client.c
	gcc -Wall -c time_client.c 
clean:
	rm *.o index node

