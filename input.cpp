#include <iostream>
#include <stdexcept>
#include "string.hpp"

#define CHUNK_SIZE 16
#define RETURN_CODE 10

char * raw_input(){
  char * a = (char*)calloc( CHUNK_SIZE ,sizeof(char) );
  if( a == nullptr )
    throw std::runtime_error("failed to allocate memory ");

  int max_len = CHUNK_SIZE;
  int k; char c;
  char i = 0;
  k = 1;
  while (k > 0)
  {
      c = getchar();
      if ( i >= max_len ){
        char * tmp = a;
        a = (char*)realloc( a ,max_len + CHUNK_SIZE );
        if( a == nullptr )
          throw std::runtime_error("failed to allocate memory ");
        max_len += CHUNK_SIZE;
      }
      if (c != '\n' && i < max_len ) a[i++] = c;
      else a[i] = k = 0;
  } 
  return a;
}

string str_input(){
  string s("");
  bool newline = false;
  char c;
  int i = 0;
  while( !newline ){
    c = getchar();
    if( c != '\n' ){
      s[i] = c;
      i++;
    }else{
      newline = true;
    } 
  }
  return s;
}

int64_t int_input(){
  int64_t num;
  std::cin >> num;
  std::cin.ignore();
  return num;
}



