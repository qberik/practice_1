#ifndef STRING_HPP
#define STRING_HPP
#include <cstddef>
#include "list.hpp"
#include <ostream>



class string{
  public:
    string();
    string( const char * );
    string( string& );
    ~string();
    
    std::size_t length() const;
    std::size_t size() const;

    void strip( char separator = ' ' );

    list<string> split( char separator = ' ' );

    const char * c_str() const;

    std::size_t find( const char * ) const;
    std::size_t find( const string ) const;

    int count ( char chr ) const;

    char& operator[]( const int  ); 

    friend std::ostream& operator<< (std::ostream& out, string& str); 

    //string& operator[]( const std::size_t );
    string& operator=( const char * );
    string& operator=( string & );
    string& operator+( char );
    string& operator+( const char * );
    string& operator+( string & );
    string& operator+=( char );
    string& operator+=( const char * );
    string& operator+=( string & );


    bool operator<( const string& ); bool operator<( const char * );
    bool operator>( const string& ); bool operator>( const char * );
    bool operator==( const string& ); bool operator==( const char * );
    bool operator!=( const string& ); bool operator!=( const char * );
    bool operator<=( const string& ); bool operator<=( const char * );
    bool operator>=( const string& ); bool operator>=( const char * );

    char * string_ptr;
    std::size_t capacity;

  private:

};

#endif
