#include"mine.h"
#include"link_ds.h"
#include<time.h>
typedef struct {

	int row;
	int col;
	int opt;
}opts;

typedef struct {

	int row;
	int col;
}point;

void*group_index[9][9] = {NULL};
static link_ds *optarr= NULL;
static int scant = 0;
void scan_mine(minemap *minem);
int mine_group(minemap *minem,int row,int col,int mine);
int optadd(int row ,int col,int opt);
int resolve(unit* newu,int* new_m,int* new_c);
int onebyone(int mine,int close,int* new_m,int* new_c,unit *newu);
int compare(void* dat1,void* dat2);
void fcleararr();
unit* subset(unit* finded,unit* father);

link_ds* analysis(minemap * minem){
    
    if(scant > 6){
        
        printf("Have scan 5 times without opt,Now ramdon a point\n");
        int row = 0;
        int col = 0;
        
        do {
            row = rand()%(minem->rows);
            col = rand()%(minem->cols);
        }while(*(minem->p_mine + minem->cols * row + col) & 6);
        optadd(row+1, col+1, OPEN);
        scant = 0;
        return optarr;
    }
	
    if(!optarr){
        
        optadd(1, 1, OPEN);
	
	}else{
        
		clean_unit(optarr);
		scan_mine(minem);
	}
	return optarr;

}

void scan_mine(minemap *minem){

    printf("scan_mine begin...\n");
	int rows = minem->rows;
	int cols = minem->cols;
	char* p_mine = minem->p_mine;

	for(int loopr = 0;loopr < rows;loopr++){
	
		for(int loopc = 0;loopc < cols;loopc++){
			
			char *pt_mine = p_mine + loopr*cols + loopc;
			if(*pt_mine & 2){
			
				int minec = (*pt_mine)>>4;	
				switch(minec){
				
					case 0:case 8:
					break;
					case 1:
                        if(mine_group(minem,loopr,loopc,1))return;
					break;
					case 2:
                        if(mine_group(minem,loopr,loopc,2))return;
					break;
					case 3:
                        if(mine_group(minem,loopr,loopc,3))return;
					break;
					case 4:
                        if(mine_group(minem,loopr,loopc,4))return;
					break;
					case 5:
                        if(mine_group(minem,loopr,loopc,5))return;
					break;
					case 6:
                        if(mine_group(minem,loopr,loopc,6))return;
					break;
					case 7:
                        if(mine_group(minem,loopr,loopc,7))return;
					break;
					default:
					break;
				
				}//end switch
			
			}//end if
		
		
		}//end for loopc
	
	}//end for loopr

    scant++;
    printf("scan_mine ending no opt,scant :%d\n",scant);

}//end scan_mine

int mine_group(minemap *minem,int row,int col,int mine){

	int rows = minem->rows;
	int cols = minem->cols;
	char* p_mine = minem->p_mine;
	int closem = 0;
	int flagm = 0;	
	point *p = calloc(8,sizeof(point));
	for(int loopr = row - 1;loopr <= row + 1;loopr++){
	
		if(loopr<0 || loopr >=rows)continue;
		for(int loopc = col-1;loopc <=col+1;loopc++){
		
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
		
		int new_m = mine - flagm;
		int new_c = closem;
        unit * newu = calloc(1,sizeof(unit));
        newu->p_data = p;
        if(!resolve(newu,&new_m,&new_c)){free(newu);newu = NULL;return 1;}
		if(group_index[new_m][new_c]){
		
            if(find_data(group_index[new_m][new_c],newu->p_data,compare)){
                free(newu);newu = NULL;
            }else{
                insert_unit_back(newu, ((link_ds*)group_index[new_m][new_c])->head);
            }
		}else{
			group_index[new_m][new_c] = init_link();
            insert_unit_back(newu, ((link_ds*)group_index[new_m][new_c])->head);
		}
	}else if(flagm <  mine && closem == (mine-flagm)){
		
		for(int loop = 0;loop < closem;loop++){
		
			optadd(p[loop].row,p[loop].col,FLAG);
		}
        return 1;
		
	}else if(flagm == mine && closem){
		
		for(int loop = 0;loop < closem;loop++){
		
			optadd(p[loop].row,p[loop].col,OPEN);
		}
        
        return 1;
	}
    
    return 0;
}

int optadd(int row ,int col,int opt){

	opts *u_p = malloc(sizeof(opts));
	u_p->row = row-1;
	u_p->col = col-1;
	u_p->opt = opt;
	
	
	if(optarr == NULL)optarr = init_link();
	
		insert_back(u_p,optarr->head);
	return 0;
}


int resolve(unit* newu,int* new_m,int* new_c){
	
	
	int result = 0;
	switch(*new_c){
		case 2:
		return -1;
		break;

		case 3:
		result = onebyone(1,2,new_m,new_c,newu);
		break;

		case 4:
		case 5:
		case 6:
		case 7:
        case 8:
		if(!(result = onebyone(2,3,new_m,new_c,newu)))break;
		if(!(result = onebyone(1,3,new_m,new_c,newu)))break;
		if(!(result = onebyone(1,2,new_m,new_c,newu)))break;
		default:
		break;
	
	}//end switch
	
	return result;
}
int onebyone(int mine,int close,int* new_m,int* new_c,unit *newu){

	if(*new_m < mine || *new_c <= close)return -1;
    if(!group_index[mine][close])return -1;

	unit* find = find_data((link_ds*)group_index[mine][close],newu->p_data,compare);
	if(!find)return -1;
	subset(find,newu);
	if(*new_m -= mine){
		
		*new_c -= close;
		if(*new_c == *new_m){
			point (*p)[8] = (point(*)[])(newu->p_data);
			for(int loop = 0;loop < 8;loop++){
			
				if((*p+loop)->row){
				
					optadd((*p+loop)->row,(*p+loop)->col,FLAG);
				}
			
			}//end for
			return 0;
		
		}else if(*new_c > *new_m){
			
			return  resolve(newu,new_m,new_c);
		}
	}else{
			point (*p)[8] = (point(*)[])(newu->p_data);
			for(int loop = 0;loop < 8;loop++){
			
				if((*p+loop)->row){
				
					optadd((*p+loop)->row,(*p+loop)->col,OPEN);
				}
			
			}//end for
			return 0;
	}
    
    return -1;

}//end onebyone
int compare(void* dat1,void* dat2){
	
	point (*p1)[8] = (point(*)[])dat1;
	point (*p2)[8] = (point(*)[])dat2;
	int result = 1;
	for(int loop1 = 0;loop1 < 8;loop1++){
	
		for(int loop2 = 0;loop2 <8;loop2++){
		
			if((*p1+loop1)->row == (*p2+loop2)->row && (*p2+loop2)->col == (*p1+loop1)->col){
				
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
	
		if((*fed+loop1)->row == 0)continue;
		for(int loop2 = 0;loop2 <8;loop2++){
			if((*fa+loop2)->row == 0)continue;
			if((*fed+loop1)->row == (*fa+loop2)->row && (*fa+loop2)->col == (*fed+loop1)->col){
				(*fa+loop2)->col = 0;
				(*fa+loop2)->row = 0;
				break;
			}
		}
	
	}//end for loop1
	return father;
}

void fcleararr(){
	printf("cleararr begin..\n");
	for(int loopr = 0;loopr < 7;loopr++){
	
		for(int loopc = 0;loopc < 7;loopc++){
		
			if(group_index[loopr][loopc]){
			
				clean((link_ds*)group_index[loopr][loopc]);
                free(group_index[loopr][loopc]);
                group_index[loopr][loopc] = NULL;
			}
		}
	}
	return;
}
