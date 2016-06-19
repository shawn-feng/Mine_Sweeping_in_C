#include"mine.h"
#include<time.h>
void mine_map(const minemap * minem){

	int rows = minem->rows;
	int cols = minem->cols;
	int mine = minem->mine;
	char *p_mine = minem->p_mine;
	printf("mine_map beginning\n");
	srand((unsigned int)time(0));
	
	int row = 0, col = 0;

	for(int loop = 0;loop < mine; loop++){
	
		row = rand()%rows;
		col = rand()%cols;

		if(!(*(p_mine + cols * row + col)&1)){
		
			*(p_mine + cols * row + col) |= 1;
			
			for(int loopr = row-1;loopr <= row + 1;loopr++){
			
				if(loopr < 0 || loopr >= rows)continue;

				for(int loopc = col -1;loopc <= col + 1;loopc++){
				
					if(loopc < 0 || loopc >= cols)continue;
					if(!(*(p_mine + cols * loopr + loopc) & 1)){
					
						*(p_mine + cols * loopr + loopc) += 16;
					}
				}
			
			}
		}else{

			loop--;
		}
	}

	printf("mine_map ending\n");
    print_open(minem);

	return ;
}
