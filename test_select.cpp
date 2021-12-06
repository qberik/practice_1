#include <iostream>
#include "menu.hpp"
#include "input.hpp"
#include "type.hpp"
#include "table.hpp"
#include "list.hpp"
#include "value.hpp"
#include "string.hpp"
#include "select.cpp"

int main(){

  table t;
  string table_name("Ученики");
  t.set_name( table_name );
 
  list< Type::Type > tp;
  list< string > fl;
  
  string p1("Фамилия");        fl.add(p1); tp.add( Type::STRING );
  string p2("Имя");            fl.add(p2); tp.add( Type::STRING );
  string p3("Отчество");       fl.add(p3); tp.add( Type::STRING );
  string p4("Год рождения");   fl.add(p4); tp.add( Type::INT );
  string p5("Курс");           fl.add(p5); tp.add( Type::STRING );
  string p6("Оценки");         fl.add(p6); tp.add( Type::ARRAY );

  t.set_fields( fl );
  t.set_types( tp );

  list<value> _obj;
  string _o1("Иванов");         value o1( _o1 ); _obj.add(o1);
  string _o2("Иван");           value o2( _o2 ); _obj.add(o2);
  string _o3("Иванович");       value o3( _o3 ); _obj.add(o3);
  int    _o4 = 2000;            value o4( _o4 ); _obj.add(o4);
  string _o5("ИУК4-12Б");       value o5( _o5 ); _obj.add(o5);
  list<int> _o6; _o6.add(-2); _o6.add(-1); _o6.add(0); _o6.add(1); _o6.add(2);
  value o6( _o6 ); _obj.add(o6);

  list<value> __obj;
  string __o1("Добровольский");   value vo1( __o1 ); __obj.add(vo1);
  string __o2("Андрей");          value vo2( __o2 ); __obj.add(vo2);
  string __o3("Денисович");       value vo3( __o3 ); __obj.add(vo3);
  int    __o4 = 2004;             value vo4( __o4 ); __obj.add(vo4);
  string __o5("ИУК4-12Б");        value vo5( __o5 ); __obj.add(vo5);
  list<int> __o6; __o6.add(-4); __o6.add(-2); __o6.add(0); __o6.add(2); __o6.add(4);
  value vo6( __o6 ); __obj.add(vo6);

  list<value> ___obj;
  string ___o1("Морозов");   value vvo1( ___o1 ); ___obj.add(vvo1);
  string ___o2("Дмитрий");          value vvo2( ___o2 ); ___obj.add(vvo2);
  string ___o3("Александрович");       value vvo3( ___o3 ); ___obj.add(vvo3);
  int    ___o4 = 2002;             value vvo4( ___o4 ); ___obj.add(vvo4);
  string ___o5("ИУК4-12Б");        value vvo5( ___o5 ); ___obj.add(vvo5);
  list<int> ___o6; ___o6.add(123); ___o6.add(-2); ___o6.add(0); ___o6.add(2); ___o6.add(-123);
  value vvo6( ___o6 ); ___obj.add(vvo6);

  /*

  */

  t.add( _obj );
  t.add( __obj );
  t.add( ___obj );
  //t.add( _obj );
  
  list< table > db;
  db.add( t );

  string s("SELECT a, AVG( b) , SUM(c ), *, C, C, B FROM A, B , C , *, * WHERE SOME <= SUM(AVG(COL )) AND COL > AVG( SOME_ANOTER_COL) GROUP BY SOME_COOL < AVG( A ), A < B AND B >= C OR A == C HAVING C <= SUM( A) ORDER BY B, A , C" );
  s = "SELECT * FROM Ученики WHERE Имя = 'Андрей' ";

  sql( db, s );

  return 0;
}
