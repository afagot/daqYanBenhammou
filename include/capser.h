#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h>

int initport(int fd);
int writeport(int fd, char *chars);
int readport(int fd, char *result);
int getbaud(int fd);
