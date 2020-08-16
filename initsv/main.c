#include <stdio.h>
#include <unistd.h>

int kraj = 0;

int main(int argc, char **argv) {
	printf("%s %s\n", argv[0], argv[1]);
	while(!kraj) {
		execve(argv[1], argv + 1, NULL);
	}
}
