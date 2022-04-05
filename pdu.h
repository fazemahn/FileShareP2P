#ifndef PROTO_UNIT
#define PROTO_UNIT
struct PDU{
    char type; 
    char * data;
};
typedef struct PDU* pdu;
pdu create(char type, char *data);
void destroy(pdu unit);
void printpdu(pdu unit);
#endif