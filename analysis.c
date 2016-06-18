#include"mine.h"
#include"link_ds.h"

typedef struct {

	int row;
	int col;
	int opt;
}opts;

typedef struct {

	int row;
	int col;
}point;


static void*group_index[7][7] = {NULL};
static void *optarr= NULL;
static int optn = 0;
void* analysis(mindmap * minem){

	int rows = minem->rows;
	int cols = minem->cols;
	int mine = minem->mine;
	char* p_mine = minem->p_mine;
	
	if(optarr){
	
		clean(optarr);
	}

}

void scan_mine(mindmap *minem){

	int rows = minem->rows;
	int cols = minem->cols;
	char* p_mine = minem->p_mine;

	for(int loopr = 0;loopr < rows;loopr++){
	
		for(int loopc = 0;loopc < cols;loopc++){
			
			char *pt_mine = p_mine + loopr*cols + loopc;
			if(*pt_mine & 2){
			
				int minec = pt_mine>>4;	
				switch(minec){
				
					case 0:case 8:
					break;
					case 1:
					mine_group(minem,loopr,loopc,1);
					break;
					case 2:
					mine_group(minem,loopr,loopc,2);
					break;
					case 3:
					mine_group(minem,loopr,loopc,3);
					break;
					case 4:
					mine_group(minem,loopr,loopc,4);
					break;
					case 5:
					mine_group(minem,loopr,loopc,5);
					break;
					case 6:
					mine_group(minem,loopr,loopc,6);
					break;
					case 7:
					mine_group(minem,loopr,loopc,7);
					break;
					default:
					break;
				
				}//end switch
			
			}//end if
		
		
		}//end for loopc
	
	}//end for loopr




}//end scan_mine

int mine_group(mindmap *minem,int row,int col,int mine){

	int rows = minem->rows;
	int cols = minem->cols;
	char* p_mine = minem->p_mine;
	int closem = 0;
	int flagm = 0;	
	point *p = calloc(8,sizeof(point));
	for(loopr = row - 1;loopr <= row + 1;loopr++){
	
		if(loopr<0 || loopr >=rows)continue;
		for(loopc = col-1;loopc <=col+1;loopc++){
		
			if(loopc<0 || loopc>=cols)continue;
			
			switch(*(p_mine + loopr*cols +loopc) & 6){
			
				case 4:
				flagm++;
				break;

				case 0:
				p[closem].row = loopr+1;
				p[closem].col = loopc+1;
				closem++;
				break;

				default:
				break;
			}
		}
	}//end for loopr

	if(flagm < mine && closem > (mine-flagm)){
		
		unit* u_index = NULL;
		unit* newu = NULL;
		int new_m = mine - flagm;
		int new_c = closem;
		
		resolve(unit* newu,int* new_m,int* new_c){
		
		if(u_index = group_index[new_m][new_c]){
		
			newu = insert_back(p,u_index);
		}else{
			group_index[mine-flagm][closem] = init_link();
		}
	}else if(flagm <  mine && closem == (mine-flagm)){
		
		for(int loop = 0;loop < closem;loop++){
		
			optadd(p[loop].row,p[loop].col,FLAG);
		}
		
	}else if(flagm == mine && closem){
		
		for(int loop = 0;loop < closem;loop++){
		
			optadd(p[loop].row,p[loop].col,OPEN);
		}
		
	}
	return 0;

}

int optadd(int row ,int col,int opt){

	opts *u_p = malloc(sizeof(opts));
	u_p->row = row-1;
	u_p->col = col-1;
	u_p->opt = opt;
	
	
	if(optarr == NULL){
	
		optarr = init_link();
	}else{
	
		insert_back(u_p,optarr->head);
	}

	return 0;

}


int resolve(unit* newu,int* new_m,int* new_c){
	
	unit* start = NULL;
	unit* find = NULL;
	switch(*new_c){
		case 2:
		return -1;
		break;

		case 3:
		return onebyone(1,2,new_m,new_c,newu);
		break;

		case 4:
		case 5:
		case 6:
		case 7:
		if(!onebyone(2,3,new_m,new_c,newu))break;
		if(!onebyone(1,3,new_m,new_c,newu))break;
		if(!onebyone(1,2,new_m,new_c,newu))break;
		default:
		break;
	
	}//end switch
	
	return ;
}
int onebyone(int mine,int close,int* new_m,int* new_c,unit *newu){

	unit* start = (unit*)group_index[mine][close];
	unit* find = find_data(start,newu->p_data,compare);
	if(!find)return -1;
	subset(find,newu);
	if(*new_m -= mine){
		
		*new_c -= close;
		if(*new_c == *new_m){
			point (*p)[8] = (point(*)[])(newu->p_data);
			for(int loop = 0;loop < 8;loop++){
			
				if(p[loop].row){
				
					optadd(p[loop].row,p[loop].col,FLAG);
				}
			
			}//end for
			return 1;
		
		}else if(*new_c > *new_m){
			
			 resolve(newu,new_m,new_c);
		}
	}else{
			point (*p)[8] = (point(*)[])(newu->p_data);
			for(int loop = 0;loop < 8;loop++){
			
				if(p[loop].row){
				
					optadd(p[loop].row,p[loop].col,OPEN);
				}
			
			}//end for
			return 1;
	}

}//end onebyone
int compare(void* dat1,void* dat2){
	
	point (*p1)[8] = (point(*)[])dat1;
	point (*p2)[8] = (point(*)[])dat2;
	int result = 1;
	for(int loop1 = 0;loop1 < 8;loop1++){
	
		for(int loop2 = 0;loop2 <8;loop2++){
		
			if(p1[loop1].row == p2[loop2].row && p2[loop2].col == p1[loop1].col){
				
				result = 0;
				break;
			}else{
			
				result = 1;
			}
		}
		if(result)return 1;
	
	}
	return 0;
}

unit* subset(unit* finded,unit* father){

	point (*fed)[8] = (point(*)[])(finded->p_data);
	point (*fa)[8] = (point(*)[])(father->p_data);

	
	for(int loop1 = 0;loop1 < 8;loop1++){
	
		if(fed[loop1].row == 0)continue;
		for(int loop2 = 0;loop2 <8;loop2++){
			if(fa[loop2].row == 0)continue;
			if(fed[loop1].row == fa[loop2].row && fa[loop2].col == fed[loop1].col){
				fa[loop2].col = 0;
				fa[loop2].row = 0;
				break;
			}
		}
	
	}//end for loop1
	return father;
}
