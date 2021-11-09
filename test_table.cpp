#include <iostream>
#include "type.hpp"
#include "table.hpp"
#include "list.hpp"
#include "value.hpp"
#include "string.hpp"


int main(){

  table t;
  
  string name( "Имя" );
  string cors( "Курс" );
  string vozr( "Возраст" );

  list<string> fld;
  fld.add( name );
  fld.add( cors );
  fld.add( vozr );

  list< Type > tp; 
  tp.add( STRING );
  tp.add( STRING );
  tp.add( INT );


  t.set_fields( fld );
  t.set_types( tp );

  string a_n ("Рома");
  string a_c ("ИУК6");
  value n( a_n );
  value c( a_c );
  list<value> obj;
  obj.add( n );
  obj.add( c );
  obj.add( 18 );
  
  string b_n("Вова");
  string b_c("ИУК2");
  value n1( b_n );
  value c1( b_c );
  list<value> obj1;
  obj1.add( n1 );
  obj1.add( c1 );
  obj1.add( 17 );
  
  t.add( obj );
  t.add( obj1 );

  int row = 1;
  string rq1( "Возраст" );
  string rq2( "Имя" );
  list< string > rq;
  rq.add(rq1);
  rq.add(rq2);
  //std::cout << t.getRow( row )[ 0 ].get_string().c_str() << std::endl;
  //std::cout << t.getRow( row )[ 1 ].get_string().c_str() << std::endl;
  //std::cout << t.getRow( row )[ 2 ].get_int() << std::endl;
  list< list<value> > rs;
  list< list< list<value> > > tmp;

  //std::cout << t.getCols( rq )[0][0].get_string() << std::endl;

  std::cout << t.getCols( rq )[1][0].get_string().c_str() << " " << t.getCols( rq )[0][0].get_int() << std::endl;
  std::cout << t.getCols( rq )[1][1].get_string().c_str() << " " << t.getCols( rq )[0][1].get_int() << std::endl;
  return 0;
}
