#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "init.h"

#define DUZ 100

int main(int argc, char **argv) {
	if(argc < 3)
		exit(0);
	int s, t, len;
	struct sockaddr_un remote;
	char str[DUZ];
	char *socket_put = malloc(sizeof(*socket) * (strlen(RADNI_FOLDER) + strlen(argv[2] + 1)));
	*socket_put = 0;
	strcpy(socket_put, RADNI_FOLDER);
	strcat(socket_put, argv[2]);

	if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	printf("Trying to connect...\n");

	remote.sun_family = AF_UNIX;
	strcpy(remote.sun_path, socket_put);
	len = strlen(remote.sun_path) + sizeof(remote.sun_family);
	if (connect(s, (struct sockaddr *)&remote, len) == -1) {
		perror("connect");
		exit(1);
	}

	printf("Connected.\n");

	strncpy(str, argv[1], DUZ);

	if (send(s, str, strlen(str), 0) == -1) {
		perror("send");
		exit(1);
	}

	if ((t=recv(s, str, 100, 0)) > 0) {
		str[t] = '\0';
		printf("echo> %s", str);
	} else {
		if (t < 0) perror("recv");
		else printf("Server closed connection\n");
		exit(1);
	}

	close(s);

	return 0;
}
