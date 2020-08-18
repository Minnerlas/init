#ifndef INIT_H
#define INIT_H

#define PREFIKS "/init"
#define INITSV_PUT (PREFIKS "/build/initsv")
#define RADNI_FOLDER PREFIKS "/run/"
#define SERVISI (PREFIKS "/init.rc")
#define SOCK_PUT "echo_socket"

enum komanda {
	NISTA,
	UBIJ
};

#endif /* INIT_H */
