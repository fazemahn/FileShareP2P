#ifndef PROTO_UNIT
#define PROTO_UNIT
struct PDU{
    char type; 
    char data[100];
};
typedef struct PDU* pdu;
struct PDUr{
    char type_r;
    char p_name[10];
    char c_name[10];
    unsigned short int port_num;
    char nulladdr[77];
};
typedef struct PDUr* pdur;
pdur create_r(char* peerName, char* contentName, unsigned short int port);
pdu create(char type, char *data);
void destroy(pdu unit);
void printpdu(pdu unit);
void printpdu_r(pdur unit);
#endif