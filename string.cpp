#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <cmath>
#include <cwchar>
#include "string.hpp"
#include "list.hpp"

#include <iostream>

#define CHUNK_SIZE 16.0
#define ZERO_TERMINATOR '\0'

std::size_t len( const char * str ){
  return strlen( str ) + 1;
};


string::string(){
  string_ptr = nullptr;
  capacity = 0;
}

string::string( const char * str  ){

  std::size_t chunk_len = std::ceil( len( str )/ CHUNK_SIZE );
  capacity = chunk_len * CHUNK_SIZE;

  string_ptr = ( char * ) std::malloc( sizeof( char ) * chunk_len * CHUNK_SIZE );

  if (string_ptr  == nullptr)
    throw std::runtime_error("failed to allocate memory ");
  
  std::memset( string_ptr, ZERO_TERMINATOR, capacity );
  memcpy( string_ptr, str, len( str ));

}


string::string( string & str ){

  std::size_t chunk_len = std::ceil( len( str.c_str() ) / CHUNK_SIZE );
  capacity = chunk_len * CHUNK_SIZE;
  
  string_ptr = ( char * ) std::malloc( sizeof( char ) * chunk_len * CHUNK_SIZE );

  if (string_ptr == nullptr)
    throw std::runtime_error("failed to allocate memory ");
  std::memset( string_ptr, ZERO_TERMINATOR, capacity );
  memcpy( string_ptr, str.c_str(), len( str.c_str() ) ); 

}


string::~string(){

  free( string_ptr );

}


std::size_t string::length(){
  int count = 0;
  char *p = string_ptr;
  while (*p != 0)
  {
      if ((*p & 0x80) == 0 || (*p & 0xc0) == 0xc0)
          ++count;
      ++p;
  }
  return count;
}

void string::strip( char sep){
  int from = 0; 
  bool flag = true;
  int l = len( string_ptr ) - 1;
  for( int i = 0; i < l && flag; i++ ){
    if( *(string_ptr+i) == sep ){
      from++;  
    }else{
      flag = false; 
    }
  } 
  int to = l - 1;
  flag = true;
  for( int i = 0; i < l && flag; i++ ){
    if( *(string_ptr + (l - 1) - i ) == sep ){
      to--;
    }else{
      flag = false; 
    }
  }
  int clear = from + ( l - to );
  for( int i = 0; i < l - from; i++ ){
    string::operator[](i) = string::operator[](from + i);
  }
  for( int i = 0; i < clear; i++ ){
    string::operator[](l - i) = ZERO_TERMINATOR;
  }
  
}

list<string> string::split( char sep ){
  int l = len( string_ptr ) - 1;
  int it = 0;
  list<string> str_list;
  bool flag = false;
  string* tmp_str = nullptr;
  for( int i = 0; i < l; i++ ){
    if( *(string_ptr + i) != sep ){
      if( flag ){
        (*tmp_str)[ it++ ] = *( string_ptr + i);
      }else{
        if( tmp_str != nullptr ){
          str_list.add( *tmp_str );  
        }
        flag = true;
        tmp_str = new string;
        it = 0;
        (*tmp_str)[ it++ ] = *( string_ptr + i);
      }
    }else{
      flag = false;
    }
  }
  if( tmp_str != nullptr ){
    str_list.add( *tmp_str );  
  }
  return str_list;

}

const char * string::c_str(){
  return string_ptr;
}


char& string::operator[]( int index ){

  if( index < 0 )
    index = len( string_ptr ) - index;
    // привет питону siiing str("abc")[-1] == 'c'

  if( index + 1 >= capacity ){
    char * old_ptr = string_ptr;
    std::size_t new_capacity = CHUNK_SIZE * ( std::ceil( ( index + 2 ) / CHUNK_SIZE ) );
    string_ptr = (char *)std::realloc( string_ptr, new_capacity );
    if (string_ptr  == nullptr)
      throw std::runtime_error("failed to allocate memory ");
    //free( old_ptr );
    std::memset( string_ptr + capacity, ZERO_TERMINATOR, new_capacity - capacity );
    capacity = new_capacity;
  }
  return *( string_ptr + index );
}


string& string::operator=( const char * str ){
  std::size_t target_capacity = CHUNK_SIZE * ( std::ceil( ( len( str )  )/ CHUNK_SIZE ) );

  if( target_capacity > capacity  ){
    char * old_ptr = string_ptr;
    free( string_ptr );
    string_ptr = nullptr;
    string_ptr = (char *)std::malloc( target_capacity );
    if (string_ptr  == nullptr)
      throw std::runtime_error("failed to allocate memory ");
    //free( old_ptr );
    capacity = target_capacity;
  }
  std::memset( string_ptr, ZERO_TERMINATOR, capacity );
  memcpy( string_ptr, str, len( str ) );
  return *this;
}

string& string::operator=( string& str ){
  if ( this == &str) {
    return *this;
  }
  return string::operator=( str.c_str() );
}

string& string::operator+( const char * str ){
  std::size_t new_capacity = CHUNK_SIZE * ( std::ceil( ( len(string_ptr) + len(str) - 1 ) / CHUNK_SIZE  ) ); // 2 len - 1, cuz double \0 at end of strings
  
  if ( new_capacity > capacity ){
    char * old_str = string_ptr;
    string_ptr = (char*)std::malloc( new_capacity );
    if (string_ptr == nullptr)
      throw std::runtime_error("failed to allocate memory ");
    std::memset( string_ptr, ZERO_TERMINATOR, new_capacity );
    std::memcpy( string_ptr, old_str, len( old_str ) );
    free( old_str );
    //std::memcpy( old_str, string_ptr, len( old_str ) );

  }
  std::memcpy( string_ptr+ len(string_ptr) - 1 , str, len(str) ); // also 2 len - 1, cuz double \0 at end of strings

  capacity = new_capacity;
  return *this;
}

string& string::operator+( string&  str ){
  return string::operator+( str.c_str() );
}

string& string::operator+=( const char * str ){
  string::operator+( str );
  return *this;
}

string& string::operator+=( string& str ){
  string::operator+( str );
  return *this;
}

bool string::operator<( const char * str ){

  size_t length = std::min( len(string_ptr), len( str ) );

  int flag = -1; // undefined

  for ( int i = 0; i < length; i++){
    if( !(flag+1) ){
      if( string_ptr[i] == str[i] )
        continue;
      flag = (string_ptr[i] < str[i]);
    }
  }
  
  if( !(flag+1) )
    flag = (len( string_ptr ) > len( str ));

  return flag;
}

bool string::operator<( string& str ){
  return string::operator<( str.c_str() );
}

bool string::operator>( const char * str ){

  size_t length = std::min( len(string_ptr), len( str ) );

  int flag = -1; // undefined

  for ( int i = 0; i < length; i++){
    if( !(flag+1) ){
      if( string_ptr[i] == str[i] )
        continue;
      flag = (string_ptr[i] > str[i]);
    }
  }
  
  if( !(flag+1) )
    flag = (len( string_ptr ) < len( str ));

  return flag;
}

bool string::operator>( string& str ){
  return string::operator>( str.c_str() );
}

bool string::operator==( const char * str ){

  int flag = -1; //undefinded

  if( len(string_ptr) != len( str ) ){
    flag = 0;
  }

  if ( !(flag+1) ){
    size_t length = len(string_ptr);
    flag = 1;
    for( int i = 0; i < length; i++ ){
      if( string_ptr[i] != str[i] )
        flag = 0;
    }
  }

  return flag;
}

bool string::operator==( string& str ){
  return string::operator==( str.c_str() );
}

bool string::operator!=( const char * str ){
  return !( string::operator==( str ) );
}

bool string::operator!=( string& str ){
  return string::operator!=( str.c_str() );
}

bool string::operator<=( const char * str ){
  return ( string::operator<(str) || string::operator==(str) );
}

bool string::operator<=( string& str ){
  return string::operator<=( str.c_str() );
}

bool string::operator>=( const char * str ){
  return ( string::operator>(str) || string::operator==(str) );
}

bool string::operator>=( string& str ){
  return string::operator>=( str.c_str() );
}
