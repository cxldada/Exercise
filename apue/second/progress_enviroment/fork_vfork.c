#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int globalVal = 10;

int vfork_test()
{
   pid_t chpid;
    static int staticVal = 11;
    int normalVal = 12;

    if((chpid = vfork()) < 0)
    {
        printf("fork error\n");
        return 0;
    }
    else if(chpid == 0)
    {
        globalVal = 100;
        staticVal = 101;
        normalVal = 102;

        printf("global: %d,static: %d,normal: %d\n", globalVal, staticVal, normalVal);
        _exit(0);
    }

    printf("global: %d,static: %d,normal: %d\n", globalVal, staticVal, normalVal);
    return 0; 
}

int main(int argc, char const *argv[])
{
    vfork_test();
#if 0
    pid_t chpid;
    static int staticVal = 11;
    int normalVal = 12;

    if((chpid = fork()) < 0)
    {
        printf("fork error\n");
        return 0;
    }
    else if(chpid == 0)
    {
        globalVal = 100;
        staticVal = 101;
        normalVal = 102;

        printf("global: %d,static: %d,normal: %d\n", globalVal, staticVal, normalVal);
        return 0;
    }

    sleep(3);
    printf("global: %d,static: %d,normal: %d\n", globalVal, staticVal, normalVal);
#endif
    return 0;
}
