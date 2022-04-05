#include "pdu.h"
#include <stdlib.h>
#include <stdio.h>
pdu create(char type, char *data){
    pdu unit = malloc(sizeof(struct PDU));
    unit->data = data;
    unit->type = type;
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
