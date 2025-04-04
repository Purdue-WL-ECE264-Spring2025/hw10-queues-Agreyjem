#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) { 
	struct list_node *node = (struct list_node *)malloc(sizeof(struct list_node));
	if(node != NULL){
	node->value = value;
	node->next = NULL;
	}
	return node; }

void insert_at_head(struct linked_list *list, size_t value) {
	struct list_node *temp = (struct list_node*)malloc(sizeof(struct list_node));
	temp->next = (struct list_node*)malloc(sizeof(struct list_node));
	if(temp == NULL){
		return;
	}
	temp->value = value;
	temp->next = list->head;
	list->head = temp;
}

void insert_at_tail(struct linked_list *list, size_t value) {
        struct list_node *temp = (struct list_node*)malloc(sizeof(struct list_node));
        if(temp == NULL){
                return;
        }

	temp->value = value;
	temp->next = NULL;

	if(list->head == NULL){
		list->head = temp;
		return;
	}
	struct list_node *current = list->head;
	while(current->next != NULL){
		current = current->next;
	}
	current->next = temp;

}

size_t remove_from_head(struct linked_list *list) {
	if(list->head == NULL){
		return 0;
	}
	struct list_node *temp = list->head;
	size_t val = temp->value;
	list->head = temp-> next;
	free(temp);
       	       return val; }

size_t remove_from_tail(struct linked_list *list) { 
	if(list->head == NULL){
		return 0;
	}
	if(list->head->next == NULL){
	size_t val = list->head->value;
	free(list->head);
	list->head = NULL;
	return val;
	}
	struct list_node *temp = list->head;
	while(temp->next->next !=NULL){
		temp= temp->next;
	}
	size_t val = temp->next->value;
	free(temp->next);
	temp->next = NULL;
	return val; }

void free_list(struct linked_list list) {
	struct linked_list *current  = &list;
	struct list_node *next;

	while(current != NULL){
		next = current->head->next;
		free(current->head);
		current->head= next;
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
