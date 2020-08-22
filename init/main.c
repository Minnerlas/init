#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/un.h>

#include "init.h"

#ifdef DBG
# define dbgprintf(x) printf x
#else
# define dbgprint(x) do {} while (0)
#endif

#define DUZ 100
#define POCDUZ 8

const char delm[] = " \n\t";
char ulcmd[DUZ];

void oslobodi_argv(char **argv){
	int i;
	for(i = 0; argv[i]; i++)
		free(argv[i]);
	free(argv);
}

char *env[] = {
	"PATH=/init/build:/usr/bin:usr/sbin:/bin:/sbin",
	NULL
};

char **obrada_argv(char *ul, int duz) {
	char **argv = malloc(sizeof(*argv) * (POCDUZ + 1));
	int i, fd;
	for(i = 0; i<POCDUZ; i++)
		argv[i] = NULL;
	int argc = 0, stvduz = POCDUZ;
	argv[argc] = NULL;
	char *prg;

	char *tok = strtok(ul, delm);
	if((tok[0] == '.') && (tok[1] == '/')) {
		prg = strdup(tok);
		dbgprint((1, "prg(./): %s\n", prg));
	} else {
		prg = malloc(sizeof(*prg) * (strlen(tok) + 1));
		*prg = 0;
		strcat(prg, tok);
		dbgprint((1, "prg: %s\n", prg));
	}
	if(1){

		while(tok) {
			argv[argc++] = strdup(tok);
			argv[argc] = NULL;
			if(argc == stvduz) {
				stvduz *= 2;
				char **t = malloc(sizeof(*t) * (stvduz + 1));
				for(i = 0; i<= argc; i++)
					t[i] = argv[i];
				free(argv);
				argv = t;
			}

			dbgprint((1, "%s\n", tok));
			tok = strtok(NULL, delm);
		}

		free(prg);
		return argv;
	} 

	/*================= KRAJ =================*/

	for(i = 0; i<argc; i++)
		free(argv[i]);
	free(argv);
	free(prg);

	return NULL;
}

int pokreni(char **argv, char **envp) {
	size_t duz = 0;
	int i;
	pid_t pid;
	for(i = 0; argv[i]; i++);
	duz = i;
	//printf("duz %d\n", duz);
	char **t = malloc(sizeof(*t)*(duz + 2));
	t[0] = strdup(INITSV);
	for(i = 0; i < duz + 1; i++)
		t[i+1] = argv[i];

	free(argv);
	argv = t;
	if(!(pid = fork()))
		execve(INITSV_PUT, argv, envp);
	oslobodi_argv(argv);
}

int main(int argc, char **argv, char **envp) {

	uid_t euid;

	euid = geteuid();

	//if(euid != 0)
	//	printf("%s can only be run as root\n", *argv), exit(1);

	int duz1, duz2, ukduz, i;
	for(duz1 = 0; envp[duz1]; duz1++);
	for(duz2 = 0; env[duz2]; duz2++);
	ukduz = duz1+duz2;


	char **t = malloc(sizeof(*t) * (ukduz + 1));

	for(i = 0; i<duz1; i++)
		t[i] = envp[i];

	for(i = 0; i<duz2; i++)
		t[duz1+i] = env[i];

	t[ukduz] = NULL;
	
	//signal(SIGCHLD, SIG_IGN);

	FILE *init_rc;

	init_rc = fopen(SERVISI, "r");

	pid_t pid;

	if(!(pid = fork()))
		execve(PREFIKS "/start.sh", NULL, envp);

	waitpid(pid, NULL, 0);

	while(fgets(ulcmd, DUZ, init_rc)) {

		if(*ulcmd == '\n' || *ulcmd == '#')
			continue;

		char **child_argv = obrada_argv(ulcmd, DUZ);

		printf("%s \n", child_argv[0]);
		pokreni(child_argv, t);
		//execve(child_argv[0], child_argv, NULL);
		printf("TEST");

	}

	free(t);
	fclose(init_rc);
	for(;;)
		wait(NULL);
}
