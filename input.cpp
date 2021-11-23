#include <iostream>
#include <stdexcept>
#include "string.hpp"

#define CHUNK_SIZE 16
#define RETURN_CODE 10

void cp1251_to_utf8(char *out, const char *in) {
    static const char table[128*3+1] = {                 
        "\320\202 \320\203 \342\200\232\321\223 \342\200\236\342\200\246\342\200\240\342\200\241"
        "\342\202\254\342\200\260\320\211 \342\200\271\320\212 \320\214 \320\213 \320\217 "      
        "\321\222 \342\200\230\342\200\231\342\200\234\342\200\235\342\200\242\342\200\223\342\200\224"
        "   \342\204\242\321\231 \342\200\272\321\232 \321\234 \321\233 \321\237 "                     
        "\302\240 \320\216 \321\236 \320\210 \302\244 \322\220 \302\246 \302\247 "                     
        "\320\201 \302\251 \320\204 \302\253 \302\254 \302\255 \302\256 \320\207 "                     
        "\302\260 \302\261 \320\206 \321\226 \322\221 \302\265 \302\266 \302\267 "
        "\321\221 \342\204\226\321\224 \302\273 \321\230 \320\205 \321\225 \321\227 "
        "\320\220 \320\221 \320\222 \320\223 \320\224 \320\225 \320\226 \320\227 "
        "\320\230 \320\231 \320\232 \320\233 \320\234 \320\235 \320\236 \320\237 "
        "\320\240 \320\241 \320\242 \320\243 \320\244 \320\245 \320\246 \320\247 "
        "\320\250 \320\251 \320\252 \320\253 \320\254 \320\255 \320\256 \320\257 "
        "\320\260 \320\261 \320\262 \320\263 \320\264 \320\265 \320\266 \320\267 "
        "\320\270 \320\271 \320\272 \320\273 \320\274 \320\275 \320\276 \320\277 "
        "\321\200 \321\201 \321\202 \321\203 \321\204 \321\205 \321\206 \321\207 "
        "\321\210 \321\211 \321\212 \321\213 \321\214 \321\215 \321\216 \321\217 "
    };
    while (*in != '\0' )
        if (*in & 0x80) {
            const char *p = &table[3 * (0x7f & *in++)];
            if (*p == ' ')
                continue;
            *out++ = *p++;
            *out++ = *p++;
            if (*p == ' ')
                continue;
            *out++ = *p++;
        }
        else
            *out++ = *in++;
    *out = 0;
}



char * raw(){
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

#ifdef WINDOWS
char * raw_input(){
  char * tmp_str = raw_input();
  char * _tmp  = tmp_str;
  int size = 0;
  while( _tmp++ )
    size++;
  char * str = (char *)malloc( sizeof(char) * size );
  cp1251_to_utf8( str, tmp_str );
  return str;
}
#else
char * raw_input(){
    return raw();
}

#endif


string str_input(){
  string s;
  s = raw_input();
  /*
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
  */
  return s;
}


bool isdigit( char c ){
  return ( c >= '0' && c <= '9' );
}

int64_t atoi( string s ){
  int64_t a = 0;
  int factor = 1;
  for( int i = 0; i < s.length(); i++ ){
    if( isdigit( s[ s.length() - 1 - i ] ) ){
      a += ( s[ s.length() - 1 - i ] - '0' ) * factor;
      factor *= 10;
    }else{
      if( s[ s.length() - 1 - i ] == '-' ){
        a *= -1;
      }
    }
  }
  return a;
}


int64_t int_input(){
  string s;
  s = str_input().c_str();
  s.strip();
  int64_t num = atoi( s );
  return num;
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



