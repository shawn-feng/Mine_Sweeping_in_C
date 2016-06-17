#include"mine.h"

static int open(int row,int col,const minemap * minem);
static int counts = 0;
int sweep_map(const minemap * minem){

	int rows = minem->rows;
	int cols = minem->cols;
	int mine = minem->mine;
	char *p_mine = minem->p_mine;
	
	int result = 0;
	int row = 0,col = 0,operator = 0;
	char * pt_mine = NULL;
	counts = rows*cols - mine;
	while(!result){
	
		printf("row,col,operator:1->open,2->flag,3->cancel\n");
		scanf("%*[^\n]%*c");
		scanf("%d,%d,%d",&row,&col,&operator);
		row--;col--;
		pt_mine = p_mine + cols * row + col;
		switch(operator){
		
			case 1:
			if(*pt_mine & 1){
			
				result = -1;
			}else{

				if(*pt_mine & 2)continue;
			
				*pt_mine |= 2;
				if((--counts) <= 0) result =  1;

				if(!(*pt_mine>>4)){
				
					if(open(row,col,minem)){
						result = 1;
					}
				
				}
			}
			break;

			case 2:
			*pt_mine |= 4;
			break;

			case 3:
			break;

			default:
			break;
		
		}//end switch

		printf("counts:%d\n",counts);
		print_map(minem);

	}//end while


	return result;
}

int open(int row,int col,const minemap* minem){

	int rows = minem->rows;
	int cols = minem->cols;
	int mine = minem->mine;
	char *p_mine = minem->p_mine;
	for(int loopr = row - 1;loopr <= row + 1;loopr++){
	
		if(loopr < 0 ||loopr >= rows)continue;

		for(int loopc = col -1;loopc <= col + 1;loopc++){
		
			if(loopc < 0||loopc >=cols)continue;
			
			char * pt_mine = p_mine + cols*loopr + loopc;

			if(*pt_mine & 2){
			
				continue;
			}else{
			
				*pt_mine |= 2;

				if((--counts)<=0) return 1;

				if(!(*pt_mine >> 4)){
				
			       		if(open(loopr,loopc,minem)){
						return 1;
					}
			
				}//end if
			}//end if
		}//end for loopc
	}//end for

	return 0;
}
