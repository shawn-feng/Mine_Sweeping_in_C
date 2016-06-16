#ifndef MINE_H
#define MINE_H

#include<stdio.h>
#include<stdlib.h>
void mine_map(char * p_mine,int row,int col,int mine);
void print_map(char * p_mine,int row ,int col ,int mine);
int sweep_map(char * p_mine,int row ,int col,int mine);
int result(int condition);

#endif
