#include "list.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
	void *value;
	struct node *next;
}_node_t;

struct list {
	_node_t *head;
	_node_t *tail;
};

list_t *l_create()
{
	list_t *new_list = (list_t*)calloc(1, sizeof (list_t));
	new_list->head = new_list->tail = NULL;
	return new_list;
}

void l_delete(list_t *l)
{
	_node_t *current = l->head;
	while(current)
	{
		_node_t *next = current->next;
		free(current);
		current = next;
	}
	free(l);
}

void l_push(list_t *l, void *data)
{
	_node_t* new_node = (_node_t*)calloc(1, sizeof (_node_t));
	new_node->value = data;
	new_node->next = NULL;
	if (!l->head)
	{
		l->head = l->tail = new_node;
	}
	else
	{
		l->tail->next = new_node;
		l->tail = new_node;
	}
}

bool l_node_delete(list_t *l, void* s_data,
					bool (*f_compare)(void* data1,void *data2))
{
	_node_t *current = l->head;
	_node_t *prev = NULL;
	while (current)
	{
		if (f_compare && f_compare(current->value, s_data))
		{
			if (!prev)
				l->head = current->next;
			else
				prev->next = current->next;
			free(current);
			return true;
		}
		prev = current;
		current = current->next;
	}
	return false;
}

void *l_find(list_t *l, bool (*f_find)(void *data)) {
	_node_t *current = l->head;
	while (current)
	{
		if (f_find(current->value)) {
			return current->value;
		}
		current = current->next;
	}
	return NULL;
}

void l_for_each(list_t *l, void (*f_do)(void *data))
{
	_node_t *current = l->head;
	while (current)
	{
		f_do(current->value);
		current = current->next;
	}
}
