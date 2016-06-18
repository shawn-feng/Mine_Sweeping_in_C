#ifndef MINE_H
#define MINE_H

#include<stdio.h>
#include<stdlib.h>
#define OPEN 1
#define FLAG 2
#define CANL 3
typedef struct{

	int rows;
	int cols;
	char *p_mine;
	int mine;
}minemap;
void mine_map(const minemap * minem);
void print_map(const minemap * minem);
int sweep_map(const minemap * minem);
int result(int condition);
#endif
