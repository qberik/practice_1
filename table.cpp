//#include <
#include "table.hpp"
#include "list.hpp"
#include "value.hpp"
#include "string.hpp"
#include "type.hpp"


table::table(){ }

void table::set_name( string nm ){
  name = nm;
}

void table::set_fields( list< string > fld ){
  fields = fld;
}

void table::set_types( list< Type::Type > tp ){
  types = tp;
}

void table::add( list<value> object ){
  for( int i = 0; i < object.length(); i ++ ){
    if( object[i].get_type() != types[i] )
      throw std::runtime_error("Wrong object value types");
  }
  objects.add( object );
}

void table::edit( int id, list<value> new_obj ){
  objects[id] = new_obj;
}

void table::remove( int id ){
  objects.remove( id );
}


list<value> table::getCol( int index ){
  list<value> col;
  for( int i = 0; i < objects.length(); i++ ){
    col.add( objects[i][index] );
  }
  return col;
}

list<value> table::getCol( string fld ){
  int index = fields.find( fld );
  return table::getCol( index );
}

list< list< value > > table::getCols( list< int > ids ){
  list< list<value> > cols;
  list<value> col;
  for( int i = 0; i < ids.length(); i++ ){
    cols.add( table::getCol( ids[i] ) );
  }
  return cols;
}

list< list< value > > table::getCols( list< string > flds ){
  list< int > ids;
  for( int i = 0; i < flds.length(); i++ ){
    ids.add( fields.find( flds[i] ) );  
  }
  return table::getCols( ids );
}


list< value > table::getRow( int id ){
  return objects[id];
}

list< list< value > > table::getRows( list<int> ids ){
  list< list< value > > obj;
  for( int i = 0; i < ids.length(); i++ ){
    obj.add( objects[ ids[i] ] );
  }
  return obj;
}
