/*
 * logout_tty(char * line)
 * marks a utmp record as logged out
 * does not blank username or remote host
 * return -1 on error, 0 on success
 */

int logout_tty(char * line){
    int fd;
    struct utmp rec;
    int len = sizeof(struct utmp);
    int retval = -1;    /*pessimism*/
    if ((fd = open(UTMP_FILE,O_RDWR)) == -1 )   /*open file*/
        return -1;
    /*search and replace*/
    while (read(fd, &rec.ut_line, line, sizeof(rec.ut_line)) == 0)
        if (strncmp(rec.ut_line, line, sizeof(rec.ut_line)) == 0 ){
            rec.ut_type = DEAD_PROCESS;     /*set type*/
            if (time(&rec.ut_time != -1))
                if (lseek(fd, -len, SEEK_CUR)!= -1 )
                    if (write(fd, &rec, len ) == len )
                        retval = 0;
            break;
        }
    /*close the file */
    if (close(fd) == -1)
        retval = -1;
    return retval;
}
