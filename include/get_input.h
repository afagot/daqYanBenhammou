/*****************************************************
  file : get_input.h

  prototypes for get_input functions

  970122 J.O.Petersen + M.Joos 
  990210 HP Beck  added ReadCard functionality
********************************************************/

#ifndef _GET_INPUT_H
#define _GET_INPUT_H

#ifdef __cplusplus
extern "C" {
#endif

int getdec(void);
unsigned int gethex(void);
int getdecd(int defa);
unsigned int gethexd(unsigned int defa);
char getfstchar(void);
void getstrd(char* a, char* defa);

int ReadCard_int (char* filename, char* tag, int nr, int* i) ;
int ReadCard_uint(char* filename, char* tag, int nr, unsigned int* u) ;
int ReadCard_str (char* filename, char* tag, int nr, char* c) ;

#ifdef __cplusplus
}
#endif

#endif

