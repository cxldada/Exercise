#include "../include/apue.h"
#include <sys/time.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    time_t itime1;
    struct timespec spec;
    struct tm *timep;

    itime1 = time(NULL);
    printf("UNIX time: %d\n", itime1);

    if (clock_gettime(CLOCK_REALTIME, &spec) < 0)
        err_sys("clock_gettime error");
    printf("CLOCK_REALTIME: %ld,%ld\n", spec.tv_sec, spec.tv_nsec);

    if (clock_gettime(CLOCK_MONOTONIC, &spec) < 0)
        err_sys("clock_gettime error");
    printf("CLOCK_MONOTONIC: %ld,%ld\n", spec.tv_sec, spec.tv_nsec);

    if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &spec) < 0)
        err_sys("clock_gettime error");
    printf("CLOCK_PROCESS_CPUTIME_ID: %ld,%ld\n", spec.tv_sec, spec.tv_nsec);

    if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &spec) < 0)
        err_sys("clock_gettime error");
    printf("CLOCK_THREAD_CPUTIME_ID: %ld,%ld\n", spec.tv_sec, spec.tv_nsec);

    if ((timep = gmtime(&itime1)) == NULL)
        err_sys("gmtime error");
    printf("%0d-%0d-%0d %0d:%0d:%0d", timep->tm_year, timep->tm_mon,
           timep->tm_mday, timep->tm_hour, timep->tm_min, timep->tm_sec);

    if ((timep = localtime(&itime1)) == NULL)
        err_sys("gmtime error");
    printf("%0d-%0d-%0d %0d:%0d:%0d", timep->tm_year, timep->tm_mon,
           timep->tm_mday, timep->tm_hour, timep->tm_min, timep->tm_sec);

    return 0;
}
