#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

	pid_t pid;
	if((pid = fork) == 0)
		execl();
	int status;
	waitpid(pid, &status, 0);

	puts("TESTTEST\n");
}
