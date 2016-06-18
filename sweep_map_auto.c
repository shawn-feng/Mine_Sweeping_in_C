#include"mine.h"

typedef struct {
	int row;
	int col;
	int opt;
	}opts;

static int game(opts* optarr[],const minemap* minem);
static int open(int row,int col,const minemap* minem);
static int counts = 0;
int sweep_map(const minemap * minem){

	int rows = minem->rows;
	int cols = minem->cols;
	char *p_mine = minem->p_mine;
	int mine = minem->mine;
	int result = 0;
	counts = rows*cols - mine;
	opts* optarr[10] = {NULL};
	while(!result){
	
		
		result = game(optarr,minem);
		printf("counts:%d\n",counts);
		print_map(minem);

	}//end while


	return result;
}

int game(opts* optarr[],const minemap* minem){

	int rows = minem->rows;
	int cols = minem->cols;
	char *p_mine = minem->p_mine;
	int mine = minem->mine;
	for(int loop = 0;(optarr + loop) != NULL;loop++){
	
		int row = (optarr+loop)->row;
		int col = (optarr+loop)->col;
		int opt = (optarr+loop)->opt;
		
		char * pt_mine = p_mine + row * cols + col;
		switch(opt){

			case 1:
			if(*pt_mine & 1){
			
				return  -1;
			}else{

				if(*pt_mine & 2)continue;
			
				*pt_mine |= 2;
				if((--counts) <= 0) result =  1;

				if(!(*pt_mine>>4)){
				
					if(open(row,col,minem)){
						return 1;
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
	
	}
	return 0;
}

int open(int row,int col,const minemap* minem){

	int rows = minem->rows;
	int cols = minem->cols;
	char *p_mine = minem->p_mine;
	int mine = minem->mine;
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
