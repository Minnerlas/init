#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "init.h"

#ifdef DBG
# define dbgprint(x) nprintf x
#else
# define dbgprint(x) do {} while (0)
#endif

#define DUZ 100
#define POCDUZ 8

char delm[] = " \n\t";
char ulcmd[DUZ];

void oslobodi_argv(char **argv){
	int i;
	for(i = 0; argv[i]; i++)
		free(argv[i]);
	free(argv);
}

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

//void *

int main(int argc, char **argv) {
	uid_t euid;

	euid = geteuid();

	//if(euid != 0)
	//	printf("%s can only be run as root\n", *argv), exit(1);
	

	FILE *init_rc;

	init_rc = fopen(SERVISI, "r");

	while(fgets(ulcmd, DUZ, init_rc)) {

		if(*ulcmd == '\n')
			continue;

		char **child_argv = obrada_argv(ulcmd, DUZ);

		printf("%s \n", child_argv[0]);
		//execve(child_argv[0], child_argv, NULL);

		oslobodi_argv(child_argv);
	}

	fclose(init_rc);

}
