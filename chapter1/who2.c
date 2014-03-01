/*who1.c - a first version of the who command
 *         open, read UPMP file ,and show results.
 *
 */
#include<stdio.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>

#define SHOWHOST    /*include remote machine on output*/

int main(int argc, char * argv){
    struct utmp current_record;     /*read info into here*/
    int utmpfd;     /*file descriptor*/
    int reclen = sizeof(current_record);

    if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1){
        perror( UTMP_FILE );    /*UTMP_FILE is in utmp.h*/
        exit(1);
    }
    while( read(utmpfd, &current_record, reclen) == reclen )
        show_info(&current_record);
    close(utmpfd);
    return 0;   /*went ok*/
}

/*
 * show_info()
 * displays contents of the utmp struct in human readable form
 * *note* these sizes should not be hardwired
 */

show_info(struct utmp *utbufp){
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

