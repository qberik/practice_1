#ifndef STRING_HPP
#define STRING_HPP
#include <cstddef>
#include "list.hpp"



class string{
  public:
    string();
    string( const char * );
    string( string& );
    ~string();
    
    size_t length();

    void strip( char separator = ' ' );

    list<string> split( char separator = ' ' );

    const char * c_str();

    char& operator[]( const int  ); 

    //string& operator[]( const std::size_t );
    string& operator=( const char * );
    string& operator=( string & );
    string& operator+( const char * );
    string& operator+( string & );
    string& operator+=( const char * );
    string& operator+=( string & );


    bool operator<( string& ); bool operator<( const char * );
    bool operator>( string& ); bool operator>( const char * );
    bool operator==( string& ); bool operator==( const char * );
    bool operator!=( string& ); bool operator!=( const char * );
    bool operator<=( string& ); bool operator<=( const char * );
    bool operator>=( string& ); bool operator>=( const char * );

    char * string_ptr;
    std::size_t capacity;

  private:

};

#endif
