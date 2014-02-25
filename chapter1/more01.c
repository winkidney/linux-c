/*this is a program that does what the "more" command can do .
 *more01.c
 */
#include<stdio.h>
#define PAGELEN 24
#define LINELEN 512
//int exit();     //如果没有这个声明，那么gcc编译将会产生警告，因为第一次遇到使用exit函数的时候却未发现声明？
/*如果有上面这行，gcc将会产生和内建函数冲突的警告，所以索性还是不要理会吧 = =以后再来看个究竟。*/
void do_more(FILE *);
int see_more();

int main(int argc, char *argv[]){
    FILE *fp;
    if (argc == 1)
        do_more(stdin);
    else
        while(--argc)
            if ( (fp = fopen(*++argv,"r")) != NULL ){
                    do_more( fp );
                    fclose( fp );
            }
            else
                exit(1);
    return 0;
}

void do_more( FILE * fp){
    char line[LINELEN];
    int num_of_lines = 0;
    int see_more(),reply;
    while (fgets( line, LINELEN, fp)){  /*more input*/
        if (num_of_lines == PAGELEN){   /*full screen?*/
            reply = see_more();
            if (reply == 0)
                break;
            num_of_lines -= reply;  /*reset count*/
        }
        if (fputs(line, stdout) == EOF)
            exit(1);
        num_of_lines++;
    }
}


int see_more(){
    int c;
    printf("\033[7m more?\033[m");
    while( (c=getchar()) != EOF ){
        if ( c == 'q' )
            return 0;
        if ( c == ' ' )
            return PAGELEN;
        if ( c == '\n' )
            return 1;
    }
    return 0;
}

