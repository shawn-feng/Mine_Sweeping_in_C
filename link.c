
#include"link_ds.h"

void init_link(struct link_ds* p_link){

	p_link->head = calloc(1,sizeof(unit));
	p_link->tail = calloc(1,sizeof(unit));

	p_link->head->p_next = p_link->tail;
	p_link->tail->p_last = p_link->head;
	return;
}

unit* insert_back(void *p_data,unit *p_p){

	unit *newu = NULL;
	newu = malloc(sizeof(unit));
	newu->p_data = p_data;
	newu->p_next = p_p->p_next;
	p_p->p_next->p_last = newu;
	newu->p_last = p_p;
	p_p->p_next = newu;
	return newu;
}

void delete(unit *p_d){

	p_d->p_last->p_next = p_d->p_next;
	p_d->p_next->p_last = p_d->p_last;
	free(p_d);
	p_d = NULL;
}

void clean(struct link_ds* p_link){

	unit* p_d = NULL;
	for(p_d = p_link->head;p_d->p_next != p_link->tail;){
	
		unit* temp = p_d->p_next;
		delete(p_d);
		p_d = temp;
	}
	delete(p_d);
	delete(p_link->tail);
	return ;
}
