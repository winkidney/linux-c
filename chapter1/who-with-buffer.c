/* who-with-buffer.c - who with buffered reads
 *      - surpresses epty records
 *      - formats time nicely
 *      -buffers input (using utmplib)
 *
 */
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>
#include <utmp.h>

#define SHOWHOST

void show_info(struct utmp *);

int main(int argc, char * argv[]){
    struct utmp * utbufp,   /*holds pointer to next rec*/
                * utmp_next();    /*returns pointer to next*/
    if ( utmp_open( UTMP_FILE ) == -1){
        perror( UTMP_FILE );
        exit(1);
    }
    while( ( utbufp = utmp_next() ) != ((struct utmp * ) NULL))
        show_info(utbufp);
    utmp_close();
    return 0;
}



/*
 * show_info()
 * displays contents of the utmp struct in human readable form
 * *note* these sizes should not be hardwired
 */

void show_info(struct utmp *utbufp){
    if (utbufp->ut_type != USER_PROCESS )
        return;
    printf("% -8.8s", utbufp->ut_name);     /*the logname */
    printf(" ");
    printf("% -8.8s",utbufp->ut_line);      /* the tty*/
    printf(" ");
    printf("%12.12s", ctime(&utbufp->ut_time));       /* login time */
    printf(" ");
    #ifdef SHOWHOST
    printf("( %s )", utbufp->ut_host);
    #endif
    printf("\n");   
}

