#include<stdio.h>
//test c commandline arguments

int main(int argc, char *argv[]){
    int i;
    printf("this is the number of arguments : %d\n",argc);
    for(i=argc-1;i>0;i--)
        printf("this is argument that you've inputed:%s\n",argv[i]);
    return(0);    
}
