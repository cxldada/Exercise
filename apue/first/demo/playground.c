#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <termios.h>
#include <signal.h>
#include <pthread.h>

#define MAXLINE 1024

void log_doit(const char *format, va_list ap)
{
	char buf[MAXLINE];
	vsnprintf(buf, MAXLINE - 1, format, ap);
	strcat(buf, "\n");
	fflush(stdout);
	fputs(buf, stderr);
	fflush(NULL);
}

void log_err(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	log_doit(format, ap);
	va_end(ap);
	exit(1);
}

void log_wring(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	log_doit(format, ap);
	va_end(ap);
}

void stdioTest(int argc, char *argv[])
{
	FILE *pf;
	if ((pf = fopen(argv[1], "r+")) == NULL)
		log_err("use: a.out <pathname>");

	char buf[MAXLINE];
	if (fgets(buf, MAXLINE, stdin) != NULL)
	{
		if (fputs(buf, pf) < 0)
			log_wring("write date to file error");
		else
			log_err("write error");
	}
	else
	{
		log_err("read error");
	}
	fflush(stdin);
	fflush(pf);

	long li_pos = ftell(pf);
	printf("io seek = %ld\n", li_pos);

	fseek(pf, -2l, SEEK_CUR);
	li_pos = ftell(pf);
	printf("io seek = %ld\n", li_pos);
	if (fgets(buf, MAXLINE, stdin) != NULL)
	{
		if (fputs(buf, pf) < 0)
			log_wring("write date to file error");
		else
			log_err("write error");
	}
	else
	{
		log_err("read error");
	}

	li_pos = ftell(pf);
	printf("io seek = %ld\n", li_pos);
	fclose(pf);
}

void formatioText(int argc, char *argv[])
{
	FILE *file;
	int fd;
	char buf[MAXLINE];
	int a = 100000000;
	printf("%#x\n", a);
	if ((file = fopen(argv[1], "r+")) == NULL)
		log_err("fopen error");
	if ((fd = open(argv[1], O_RDWR | O_APPEND)) < 0)
		log_err("open error");

	fprintf(file, "%#x\n", a);
	fclose(file);
	dprintf(fd, "%#o\n", a);
	close(fd);
	snprintf(buf, MAXLINE, "%.2f", 100.12345);

	printf("%s\n", buf);
}

void binIOTest(int argc, char *argv[])
{
	if (argc < 2)
		log_err("use: a.out <pathname>");

	FILE *fp;
	if ((fp = fopen(argv[1], "r+")) == NULL)
		log_err("fopen error");

	struct stTemp
	{
		char b;
		float c;
		int d;
	} a;
	a.b = 'c';
	a.c = 123.123;
	a.d = 1;

	int fs[10];
	int i;
	for (i = 0; i < 10; i++)
	{
		time_t t = time(NULL);
		srand(t + i);
		fs[i] = rand();
	}
	if (fwrite(fs, sizeof(int), 10, fp) != 10)
		if (ferror(fp))
			log_wring("fwrite error");

	rewind(fp);

	int resfs[10];
	struct stTemp res[4];
	if (fread(resfs, sizeof(int), 10, fp) != 10)
		if (ferror(fp))
			log_wring("fread error");

	for (i = 0; i < 10; i++)
	{
		printf("id:%d  content: %d\n", i, resfs[i]);
	}
	fclose(fp);
}

extern char **environ;

void environmentTest(int argc, char *argv[])
{
	int i;
	char *value;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("environ[%d]: %s\n", i, environ[i]);
	}

	if ((value = getenv("PATH")) == NULL)
		log_wring("getenv error");
	else
		printf("PATH value = %s\n", value);

	if (putenv("ENVTEST=cxldada,niubi") != 0)
		log_wring("putenv error");
	if ((value = getenv("ENVTEST")) == NULL)
		log_wring("getenv error");
	else
		printf("ENVTEST value = %s\n", value);

	if (setenv("ENVTEST", "cxl,niubi", 1) < 0)
		log_wring("setenv error");
	if ((value = getenv("ENVTEST")) == NULL)
		log_wring("getenv error");
	else
		printf("ENVTEST value = %s\n", value);

	if (unsetenv("ENVTEST") < 0)
		log_wring("unsetenv");
	if ((value = getenv("ENVTEST")) == NULL)
		log_wring("getenv error");
	else
		printf("ENVTEST value = %s\n", value);
}

void allocTest(int argc, char *argv[])
{
	int *iarr = malloc(sizeof(int) * 10);
	if (iarr == NULL)
		log_wring("malloc error");

	if ((iarr = realloc(iarr, sizeof(int) * 100)) == NULL)
		log_wring("realloc error");

	free(iarr);

	struct x
	{
		int a;
		char b;
		double c;
	};

	struct x *xarr;
	if ((xarr = calloc(10, sizeof(struct x))) == NULL)
		log_wring("calloc error");
	free(xarr);
}

void errnoTest()
{
	printf("%s\n",strerror(1));
	perror("haha");
}

void setidTest()
{
	uid_t uid, euid;
	gid_t gid, egid;
	uid = getuid();
	gid = getgid();
	euid = geteuid();
	egid = getegid();

	printf("before change:\n");
	printf("uid: %d, gid: %d, euid: %d, egid: %d\n",
		   uid, gid, euid, egid);
	if(setuid(500) < 0)
		log_wring("setuid error");
	if(setgid(500) < 0)
		log_wring("setgid error");
	uid = getuid();
	gid = getgid();
	euid = geteuid();
	egid = getegid();
	printf("after setuid:\n");
	printf("uid: %d, gid: %d, euid: %d, egid: %d\n",
		   uid, gid, euid, egid);

	if(setreuid(500,500) < 0)
		log_wring("setreuid error");
	if(setregid(500,500) < 0)
		log_wring("setregid error");
	uid = getuid();
	gid = getgid();
	euid = geteuid();
	egid = getegid();
	printf("after setreuid:\n");
	printf("uid: %d, gid: %d, euid: %d, egid: %d\n",
		   uid, gid, euid, egid);

	if(seteuid(500) < 0)
		log_wring("seteuid error");
	if(setegid(500) < 0)
		log_wring("setegid error");
	uid = getuid();
	gid = getgid();
	euid = geteuid();
	egid = getegid();
	printf("after seteuid:\n");
	printf("uid: %d, gid: %d, euid: %d, egid: %d\n",
		   uid, gid, euid, egid);
}

void sidTest()
{
	int fd = 0;
	pid_t pgid, sid;

	// if ((fd = open("/dev/pts/1", O_RDWR)) < 0)
		// log_err("open error");

	if((pgid = tcgetpgrp(fd)) < 0)
		log_wring("open error");
	printf("tcgetpgrp pgid = %d\n", pgid);

	if((sid = tcgetsid(fd)) < 0)
		log_wring("tcgetsid error");
	printf("tcgetsid sid = %d\n", sid);

	close(fd);
}

void psignalTest()
{
	char *strsig;
	int i;

	for(i = 0;i <= SIGUNUSED;i ++)
	{
		// psignal(i,NULL);
		strsig = strsignal(i);
		printf("signal [%d] info: %s\n", i, strsig);
	}
}

void *th_fn1(void *arg)
{
	printf("starting thread 1\n");
	while(1)
	{
	}
}

void *th_fn2(void *arg)
{
	if(arg != NULL)
	{
		printf("starting thread 2\n");
		pthread_t tid1 = (pthread_t)arg;
		printf("thread 2 printf tid1 = %ld\n", (unsigned long)tid1);
		pthread_cancel(tid1);
	}
	printf("exiting thread 2\n");
	pthread_exit((void *)2);
}

void pthreadcancelTest()
{
	pthread_t tid1, tid2;
	int err;

	err = pthread_create(&tid1, NULL, th_fn1, NULL);
	if (err != 0)
		log_wring("create thread 1 error");

	err = pthread_create(&tid2, NULL, th_fn2, (void *)tid1);
	if (err != 0)
		log_wring("create thread 2 error");

	sleep(10);
}

int main(int argc, char *argv[])
{
	// stdioTest(argc, argv);
	// formatioText(argc, argv);
	// binIOTest(argc, argv);
	// environmentTest(argc, argv);
	// allocTest(argc, argv);
	// errnoTest();
	// setidTest();
	// sidTest();
	// psignalTest();
	// pthreadcancelTest();
	return 0;
}