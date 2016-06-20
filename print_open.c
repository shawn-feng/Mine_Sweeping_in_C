#include"mine.h"

void print_open(const minemap * minem){
    
    int rows = minem->rows;
    int cols = minem->cols;
    int mine = minem->mine;
    char *p_mine = minem->p_mine;
    
    for(int i = 0; i <= cols; i++){
        
        printf("%2d",i);
    }
    
    printf("\n");
    
    printf(" 1");
    for(int loop = 0;loop < rows * cols; loop++){
        
        
        switch(*(p_mine + loop) & 1){
                
            case 0:
                printf("%2d",*(p_mine + loop) >> 4);
                break;
                
            case 1:
                printf(" *");
                break;
                
            default:
                break;
        }
        
        if(!((loop + 1)%cols)){
            
            printf("\n");
            if((loop+1)/cols < rows)
                printf("%2d",(loop + 1)/cols + 1);
        }
    }
    
    return  ;
}
