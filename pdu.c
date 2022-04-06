#include "pdu.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
pdu create(char type, char *data){
    pdu unit = malloc(sizeof(struct PDU));
    memset(unit->data, 0, 100);
    strcpy(unit->data, data);
    unit->type = type;
    return unit;
};
pdur create_r(char* peerName, char* contentName, unsigned short int portnum){
    struct PDUr * unit = malloc(sizeof(struct PDUr));
    unit->type_r = 'r';
    memset(unit->nulladdr, 0, sizeof(unit->nulladdr));
    unit->port_num = portnum;
    strcpy(unit->p_name, peerName);
    strcpy(unit->c_name, contentName);
    return unit;
};
void destroy(pdu unit){
    free(unit);
};
void printpdu(pdu unit){
    printf("The type is: %c and the data is: ", unit->type);
    char *l = unit->data;
    while(*l!='\0')
        printf("%c", *l++);
    printf("\n");
};
void printpdu_r(pdur unit){
    printf("The type is: %c, port is %d\n", unit->type_r, unit->port_num);
    char *p = unit->p_name;
    char *c = unit->c_name;
    printf("The peer name is: ");
    while(*p!='\0')
        printf("%c", *p++);
    printf("\n");
    printf("The content name is: \n");
    while(*c!='\0')
        printf("%c", *c++);
    printf("\n");
};