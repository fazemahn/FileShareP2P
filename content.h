#ifndef CONT_UNIT
#define CONT_UNIT
struct content{
    char owner [10];
    char cname [10];
    char cdata[255];
    unsigned short int port;
    struct content * next;
};
struct content* findContent(struct content* head, char* key);
#endif