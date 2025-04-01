#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) { return NULL; }

void insert_at_head(struct linked_list *list, size_t value) {
	struct linked_list *temp = (struct linked_list*)malloc(sizeof(struct linked_list));
	temp->head = (struct list_node*)malloc(sizeof(struct list_node));
	temp->head->value = value;
	temp->head->next = list->head;
	list = temp;
	free_list(*temp);
}

void insert_at_tail(struct linked_list *list, size_t value) {
	struct linked_list *temp = (struct linked_list*)malloc(sizeof(struct linked_list));
	temp->head = (struct list_node*)malloc(sizeof(struct list_node));
	temp->head->value = value;
	struct linked_list *evenMoreTemp = list;
	while(evenMoreTemp->head->next != NULL)
	{
		evenMoreTemp->head = evenMoreTemp->head->next;
	}
	evenMoreTemp->head->next = temp->head;

}

size_t remove_from_head(struct linked_list *list) {
       size_t val = list->head->value;
	list->head = list->head->next; 
       	       return val; }

size_t remove_from_tail(struct linked_list *list) { 
	struct linked_list *temp = list;
	size_t val;
	while(temp->head->next !=NULL){
		temp->head = temp->head->next;
	}
	val = temp->head->next->value;
	temp->head->next = NULL;
	return val; }

void free_list(struct linked_list list) {
	struct linked_list temp;
	while(list.head != NULL){
		temp = list;
		list.head = list.head->next;
		free(temp.head);
	}

}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
