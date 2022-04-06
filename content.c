#include "content.h"
#include <stdio.h>
#include <string.h>
struct content* findContent(struct content* head, char* key) {

   //start from the first link
   struct content* current = head;

   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   
   while(strcmp(current->cdata, key)!=0) {
	
      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //go to next link
         current = current->next;
      }
   }      
	
   //if data found, return the current Link
   return current;
}