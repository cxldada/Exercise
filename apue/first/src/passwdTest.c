#include "../include/apue.h"
#include <pwd.h>
#include <grp.h>
#include <shadow.h>
#include <stddef.h>
#include <string.h>

void ptr_passwd(struct passwd *pwbuf)
{
    printf("user name: %s\n", pwbuf->pw_name);
    printf("pass word: %s\n", pwbuf->pw_passwd);
    printf("uid: %d\n", pwbuf->pw_uid);
    printf("gid: %d\n", pwbuf->pw_gid);
    printf("gecos: %s\n", pwbuf->pw_gecos);
    printf("dir: %s\n", pwbuf->pw_dir);
    printf("shell: %s\n", pwbuf->pw_shell);
    printf("\n");
}

void forPasswd()
{
    uid_t uid;
    char *name;
    struct passwd *pwbuf;

    printf("myself passwd info:\n");
    uid = getuid();
    if ((pwbuf = getpwuid(uid)) == NULL)
        err_sys("getpwuid error");
    ptr_passwd(pwbuf);

    name = getlogin();
    if ((pwbuf = getpwnam(name)) == NULL)
        err_sys("getpwuid error");
    ptr_passwd(pwbuf);

    printf("loop /etc/passwd content:\n");

    setpwent();
    int i = 1;
    while ((pwbuf = getpwent()) != NULL)
    {
        printf("------- %d -------\n", i);
        ptr_passwd(pwbuf);
        i++;
    }
    endpwent();
}

void ptr_spasswd(struct spwd *pwp)
{
    printf("login name: %s\n", pwp->sp_namp);
    printf("pass word: %s\n", pwp->sp_pwdp);
    printf("Date of last change: %ld\n", pwp->sp_lstchg);
    printf("Minimum number of days between changes: %ld\n", pwp->sp_min);
    printf("Maximum number of days between changes: %ld\n", pwp->sp_max);
    printf("Number of days to warn user to change the password: %ld\n", pwp->sp_warn);
    printf("Number of days the account may be inactive: %ld\n", pwp->sp_inact);
    printf("Number of days since 1970-01-01 until account expires: %ld\n", pwp->sp_expire);
    printf("Reserved: %ld\n", pwp->sp_flag);
    printf("\n");
}

void loopSPasswd()
{
    struct spwd *pwp;
    char *name;
    printf("myself shadow passwd info:\n");
    name = getlogin();
    if ((pwp = getspnam(name)) == NULL)
        err_sys("getspnam error");
    ptr_spasswd(pwp);

    printf("start loop\n");
    int i = i;
    setspent();
    while ((pwp = getspent()) != NULL)
    {
        printf("------- %d -------\n", i);
        ptr_spasswd(pwp);
        i++;
    }
    endspent();
}

void ptr_group(struct group *gp)
{
    int i;

    printf("group name: %s\n", gp->gr_name);
    printf("group passwd: %s\n", gp->gr_passwd);
    printf("gid: %d\n", gp->gr_gid);

    i = 0;
    while (gp->gr_mem[i] != NULL)
    {
        printf("%d member name: %s\n", i + 1, gp->gr_mem[i]);
    }
    printf("\n");
}

void groupInfo()
{
    gid_t gid;
    struct group *gp;

    gid = getgid();
    if ((gp = getgrgid(gid)) == NULL)
        err_sys("getgrgid error");
    ptr_group(gp);
}

void fushugroupInfo()
{
    int i;
    int gidsize = getgroups(0,NULL);
    gid_t gidlist[gidsize];
    if ((gidsize = getgroups(gidsize, gidlist)) < 0)
        err_sys("getgroups error");

    for (i = 0; i < gidsize; i++)
    {
        printf("%d ", gidlist[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    // forPasswd();
    // loopSPasswd();
    // groupInfo();
    fushugroupInfo();
    return 0;
}
