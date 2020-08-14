#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define RADNI_FOLDER "./run/"
#define SERVISI "./init.rc"
#define SOCK_PUT "echo_socket"

#define DUZ 100

char ulcmd[DUZ];

int main() {

	FILE *init_rc;

	init_rc = fopen(SERVISI, "r");
	fclose();

	printf("Hello\n");
}
