#ifndef TABLE_HPP
#define TABLE_HPP
#include "type.hpp"
#include "list.hpp"
#include "value.hpp"
#include "string.hpp"



class table{

  public:
    table();

    void set_name( string );
    void set_fields( list< string > );
    void set_types( list< Type::Type > );
    void add( list<value> object );
    void edit( int id, list<value> new_obj );
    void remove( int id );

    int find( list<value> object );

    list<value> getCol( int );
    list<value> getCol( string );
    list< list< value > > getCols( list< int > );
    list< list< value > > getCols( list< string > );

    list< value > getRow( int );
    list< list< value > > getRows( list< int > );
    


    list< list< value > > objects;
    string name;
    list< string > fields;
    list< Type::Type > types;

};
#endif
