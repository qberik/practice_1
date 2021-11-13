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


bool isdigit( char c ){
  return ( c >= '0' && c <= '9' );
}

int atoi( string s ){
  int a = 0;
  int factor = 1;
  for( int i = 0; i < s.length(); i++ ){
    if( isdigit( s[ s.length() - 1 - i ] ) ){
      a += ( s[ s.length() - 1 - i ] - '0' ) * factor;
      factor *= 10;
    }
  }
  return a;
}


list<int> arr_input(){

  string s;
  s = str_input().c_str();
  list <string> list_str = s.split();
  list <int> list_int;
  for( int i = 0; i < list_str.length(); i++ ){
    list_int.add( atoi( list_str[i] ) );
  }
  return list_int;
}



