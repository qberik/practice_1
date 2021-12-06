#ifndef INPUT_H
#define INPUT_H
#include "string.hpp"


void cp1251_to_utf8(char *, const char *);

int atoi( string );

char * raw_input();

string str_input( );

int64_t int_input();

list<int> arr_input();



#endif
