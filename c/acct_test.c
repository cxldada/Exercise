#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void) {
	pid_t pid;

	if((pid = fork()) < 0) {
		printf("fork error\n");
		exit(1);
	} else if (pid != 0) { // parent
		sleep(2);
		exit(2);
	}

	if((pid = fork()) < 0) {
		printf("fork error\n");
		exit(3);
	} else if (pid != 0) { // first child
		sleep(4);
		abort();
	}

	if((pid = fork()) < 0) {
		printf("fork error\n");
		exit(5);
	} else if (pid != 0) { // second child
		execl("/bin/dd","dd","if=/etc/passwd","of=/dev/null",NULL);
		exit(7);
	}

	if((pid = fork()) < 0) {
		printf("fork error\n");
		exit(8);
	} else if (pid != 0) { // third child
		sleep(8);
		exit(0);
	}

	sleep(6);
	kill(getpid(),SIGKILL);
	exit(6);
}
