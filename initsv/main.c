#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "init.h"

#define DBG

#ifdef DBG
# define dbgprintf(x) printf x
#else
# define dbgprintf(x)
#endif

#define DUZ 200

int kraj = 0;
pid_t pid = 0;

const char delim[] = "/ \n\t";

typedef void (*sighandler_t)(int);

static void sigint_handler(int signum) {
	if(signum != SIGINT)
		exit(1);

	kraj = 1;
	kill(pid, SIGINT);
}

void *server(void *arg){
	unsigned int s, s2;
	struct sockaddr_un local, remote;
	int len, radi = 1, t;
	char buf[DUZ], *prg = arg;

	if((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket"); //TODO
		exit(1);
	}

	local.sun_family = AF_UNIX;  // local is declared before socket()
	strcpy(local.sun_path, RADNI_FOLDER);
	strcat(local.sun_path, prg);
	unlink(local.sun_path);
	len = strlen(local.sun_path) + sizeof(local.sun_family);

	if(bind(s, (struct sockaddr *)&local, len) == -1) {
		perror("bind");
		exit(1);
	}

	if(listen(s, 1) == -1) {
		perror("listen");
		exit(1);
	}

	while(radi) {
		if((s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1) {
			perror("accept");
			exit(1);
		}

		if(len = recv(s2, &buf, DUZ, 0)) {
			dbgprintf(("buf: %s\n", buf));
			char *t = malloc(sizeof(*t) * DUZ);
			*t = 0;

			if(!strncmp("stat", buf, 4)) {
				snprintf(t, DUZ, "pid: %d", pid);
			} else if(!strncmp("kill", buf, 4)) {
				kraj = 1;
				kill(pid, SIGINT);
			} else
				strcpy(t, "Ovo je test");

			send(s2, t, strlen(t), 0);
			close(s2);
			free(t);
		}

	}

	kraj = 1;
	kill(pid, SIGINT);

	return NULL;
}

int main(int argc, char **argv, char **envp) {
	if(argc<2)
		exit(1);

	signal(SIGINT, sigint_handler);
	printf("%s %s\n", argv[0], argv[1]);
	char *prg, *t2 = NULL;



	prg = malloc(sizeof(*prg) * (strlen(argv[1]) + strlen(SVDIR)+1));

	*prg = 0;

	strcpy(prg, SVDIR);
	strcat(prg, argv[1]);

	pthread_t server_tred;
	int iret = 0;
	int wstatus = 0;


	iret = pthread_create(&server_tred, NULL, server, argv[1]);


	while(!kraj) {
		if((pid = fork()) == 0)
			execve(prg, argv + 1, envp), exit(1);
		sleep(3);
		while(!waitpid(pid, &wstatus, 0));
	}

	free(prg);
}
