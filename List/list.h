#include <stdbool.h>

typedef struct list list_t;


list_t *l_create();
//data in nodes free user
void l_delete(list_t *l);

void l_push(list_t *l, void *data);

void l_for_each(list_t *l, void (*f_do)(void *data));

bool l_node_delete(list_t *l, void* s_data,
					bool (*f_compare)(void* data1,void *data2));
