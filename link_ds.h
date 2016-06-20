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
	struct link_ds* (*init_link)(void);
	unit* (*insert_back)(void*,unit*);
	void(*del)(unit*);
	void(*clean)(struct link_ds*);

}link_ds;
void insert_unit_back(unit* newu,unit *p_p);
int count(link_ds*);
void* getdata(link_ds*,int);
struct link_ds* init_link(void);
unit* insert_back(void *p_data,unit *p_p);
void del(unit *p_d);
void clean(struct link_ds* p_link);
void clean_unit(struct link_ds* p_link);
unit* find_data(link_ds*,void* dat ,int(*compare)(void*,void*));

#endif
