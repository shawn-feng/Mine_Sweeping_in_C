#include"mine.h"

int main(){

	int row ,col , mine;

	char *p_mine = NULL;

	char agine = '\0';
	
	printf("Welcome to Mine_Sweeping\n");

	do{
	
		printf("Please input row :");

		scanf("%d",&row);

		printf("Please input col :");

		scanf("%d",&col);

		printf("Please input number of mines:");

		scanf("%d",&mine);

		p_mine = (char*)calloc(row * col,sizeof(char));

		mine_map(p_mine,row,col,mine);


		print_map(p_mine,row,col,mine);

		if(sweep_map(p_mine,row,col,mine) ==1){
			printf("successful\n");
		}else{
		
			printf("fail\n");
		}

		printf("Play agine?(Y/N)");

		setbuf(stdin,NULL);
		scanf("%c",&agine);

		}while(agine == 'Y' || agine == 'y');

	free(p_mine);
	p_mine = NULL;


	return 0;
}


