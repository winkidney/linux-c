/* sigdemo3.c
 * purpose : show answers to signal questions
 * question1 : does the handler stay in effect after a signal arrives?
 * question2 : what if a signalX arrives while handling signalX?
 * question3 : what if a signalX arrives while handling signalY?
 * question4 : what happens to read() when a signal arrives?
 */

#include <stdio.h>
#include <signal.h>

#define INPUTLEN 100

main(int argc, char *argv[]){
    void inthandler(int);
    void quithandler(int);
    char input[INPUTLEN];
    int nchars;

    signal(SIGINT, inthandler);
    signal(SIGQUIT, quithandler);

    do{
        printf("\nType a message\n");
        nchars = read(0, input, (INPUTLEN-1));      /*read chars from file descripter
                                                      the '0' stands for tty devices*/
        if (nchars == -1)
            perror("read returned an error!\n");
        else{
            input[nchars] = '\0';
            printf("You typed: %s ", input);
        }
    }while( strcmp( input, "quit", 4) != 0);
}

void inthandler(int s ){
    printf("Received singal %d..waiting\n", s);
    sleep(2);
    printf("leaving inthandler\n");
}

void quithandler(int s){
    printf("Received signal %d..waiting\n",s);
    sleep(3);
    printf("Leaving quithandler \n");
}

 
