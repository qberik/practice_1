#ifndef VALUE_HPP
#define VALUE_HPP
#include "string.hpp"
#include "type.hpp"
#include "list.hpp"

class value{

  public:
    value();
    value( const int& );
    value( string &str );
    value( list<int>& );

    void set_value( int& );
    void set_value( string& );
    void set_value( list<int>& );
    Type get_type();

    int& get_int();
    string& get_string();
    list<int>& get_array();

    bool operator==( value& ); 
    bool operator!=( value& ); 

  //private:
    Type type;

    union{
      int * int_ptr;
      string * string_ptr;
      list<int> * array_ptr;
    } data;
};

#endif
