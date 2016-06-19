
#include"link_ds.h"

link_ds* init_link(void){

	link_ds *p_link = malloc(sizeof(link_ds));
	p_link->head = calloc(1,sizeof(unit));
	p_link->tail = calloc(1,sizeof(unit));

	p_link->head->p_next = p_link->tail;
	p_link->tail->p_last = p_link->head;
	return p_link;
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

void del(unit *p_d){

	p_d->p_last->p_next = p_d->p_next;
	p_d->p_next->p_last = p_d->p_last;
	if(p_d->p_data)free(p_d->p_data);
	p_d->p_data = NULL;
	free(p_d);
	p_d = NULL;
}

void clean(struct link_ds* p_link){

	unit* p_d = NULL;
	for(p_d = p_link->head->p_next;p_d != p_link->tail;){
	
		unit* temp = p_d->p_next;
		del(p_d);
		p_d = temp;
	}
	free(p_link->head);
	free(p_link->tail);
	p_link->head = NULL;
	p_link->tail = NULL;
	return ;
}

unit* find_data(link_ds* start,void* dat,int(*compare)(void*,void*)){

	unit* temp = NULL;
	for(temp = start->head->p_next;temp != start->tail;temp = temp->p_next){
	
		if(compare(temp->p_data,dat)){
			continue;
		}else{
			return temp;
		}
	}

	return NULL;
}

int count(link_ds* lds){
	
	int num = 0;
	for(unit* temp = lds->head->p_next;temp != lds->tail;temp = temp->p_next){
	
		num++;
	}
	return num;
}

void* getdata(link_ds* lds,int index){

	int num = 0;
	for(unit* temp = lds->head->p_next;temp!=lds->tail;temp = temp->p_next){
	
		num++;
		if(num == index){
		
			return temp->p_data;
		}
	}
	return NULL;
}
