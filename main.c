#include"mine.h"

int main(){

	minemap minem = {};

	char again = '\0';
	
	printf("Welcome to Mine_Sweeping\n");

	do{
	
		printf("Please input row :");

		scanf("%d",&(minem.rows));

		printf("Please input col :");

		scanf("%d",&(minem.cols));

		printf("Please input number of mines:");

		scanf("%d",&(minem.mine));

        minem.p_mine = (char*)calloc(minem.rows * minem.cols,1);
        printf("p_mine:%p\n",minem.p_mine);

		mine_map(&minem);


		print_map(&minem);

		if(sweep_map(&minem) ==1){
			printf("successful\n");
		}else{
		
			printf("fail\n");
		}
        free(minem.p_mine);
        minem.p_mine = NULL;

		printf("Play agine?(Y/N)");

		setbuf(stdin,NULL);
		scanf("%c",&again);

		}while(again == 'Y' || again == 'y');

	


	return 0;
}


