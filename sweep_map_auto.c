#include"mine.h"
#include"link_ds.h"
typedef struct {
	int row;
	int col;
	int opt;
	}opts;
link_ds* analysis(minemap * minem);
static int game(link_ds* optarr,const minemap* minem);
static int openf(int row,int col,const minemap* minem);
static int counts = 0;
int sweep_map(minemap * minem){

	int rows = minem->rows;
	int cols = minem->cols;
	//char *p_mine = minem->p_mine;
	int mine = minem->mine;
	int result = 0;
	counts = rows*cols - mine;
	link_ds* optarr = NULL;
	while(!result){
	
		optarr = analysis(minem);
		printf("optarr:%p\n",optarr);
		result = game(optarr,minem);
		printf("counts:%d\n",counts);
		print_map(minem);

	}//end while
	
	fcleararr();

	return result;
}

int game(link_ds* optarr,const minemap* minem){
	printf("game begin...\n");
	//int rows = minem->rows;
	int cols = minem->cols;
    char *pt_mine = NULL;
	//int mine = minem->mine;
	for(unit* temp = optarr->head->p_next;temp != optarr->tail;temp = temp->p_next){
	
		int row = ((opts*)(temp->p_data))->row;
		int col = ((opts*)(temp->p_data))->col;
		int opt = ((opts*)(temp->p_data))->opt;
        
        printf("row:%d,col:%d,opt:%d\n",row,col,opt);
		pt_mine = minem->p_mine + row * cols + col;
		printf("mine is %d\n",*pt_mine);
		switch(opt){

			case 1:
			if(*pt_mine & 1){
				printf("BOOM...\n");	
				return  -1;
			}else{

				if(*pt_mine & 2)break;
			
				*pt_mine |= 2;
				if((--counts) <= 0) return 1;

				if(!(*pt_mine>>4)){
				
					if(openf(row,col,minem)){
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
	
	}//end for
	printf("game ending\n");
	return 0;
}

int openf(int row,int col,const minemap* minem){

	int rows = minem->rows;
	int cols = minem->cols;
	char *p_mine = minem->p_mine;
	//int mine = minem->mine;
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
				
			       		if(openf(loopr,loopc,minem)){
						return 1;
					}
			
				}//end if
			}//end if
		}//end for loopc
	}//end for

	return 0;
}
