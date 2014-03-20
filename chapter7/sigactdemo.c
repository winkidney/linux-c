/* sigactdemo.c
 *              purpose : shows use of sigaction()
 *              feature : blocks^\ while handling ^C
 *                      does not reset ^C handler, so two kill
 *
 */
 
#include <stdio.h>
#include <signal.h>
#define  INPUTLEN 100

main(){
    struct sigaction newhandler;
    sigset_t blocked;
    void inthandler();
    char x[INPUTLEN];

    /*load these two members first */

    newhandler.sa_handler = inthandler;

    newhandler.sa_flags = SA_RESETHAND|SA_RESTART;
    printf("%d ,%d ,%d\n", SA_RESETHAND,SA_RESTART,SA_RESETHAND|SA_RESTART);
    /* then bulid the list of blocked signals */

    sigemptyset(&blocked);

    sigaddset(&blocked, SIGQUIT);
    newhandler.sa_mask = blocked;
    
    if (sigaction(SIGINT, &newhandler, NULL) == -1)
        perror("sigaction");
    else
        while(1){
            fgets(x, INPUTLEN,stdin);
            printf("input: %s", x);
        }
}

void inthandler(int s){
    
    printf("Called with signal %d\n", s);
    sleep(s);
    printf("done handlinnng signal %d\n", s);
}

            

