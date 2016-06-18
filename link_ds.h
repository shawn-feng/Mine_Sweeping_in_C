#ifndef LINK_DS_H
#define LINK_DS_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
typedef struct unit {

	void* p_data;
	struct unit* p_next;
	struct unit* p_last;

}unit;

typedef struct link_ds{

	unit* head;
	unit* tail;
	void(*init_link)(struct link_ds *);
	unit* (*insert_back)(void*,unit*);
	void(*delete)(unit*);
	void(*clean)(struct link_ds*);

}link_ds;
void init_link(struct link_ds* p_link);
unit* insert_back(void *p_data,unit *p_p);
void delete(unit *p_d);
void clean(struct link_ds* p_link);


#endif
