#include <iostream>
#include "string.hpp"
#include "list.hpp"
#include "input.hpp"
#include "value.hpp"
#include "table.hpp"


bool is_keyword( string w ){
  string keywords("SELECT FROM WHERE GROUP BY HAVING AND OR");
  return ( keywords.split().find( w ) != -1 );
}



list< list< value > > sql( table &t, string rq ){

  list< list< value > > rs; 

  string tmp_rq = rq;
 
  list< string > tokens = rq.split();

  string _cols;
  string cols("");

  for( int i = 0; i < tokens.length(); i++ ){
    std::cout << tokens[i].c_str() << std::endl;
  }
  
  if( tokens[0] == "SELECT"  ){
    int i = 0;
    
    do{
      i++;
      cols += tokens[i];
      if( tokens[i] == "," )
        cols += " ";
      std::cout << cols.c_str() << ' ' << i << std::endl;
      std::cout << cols[-1] << std::endl;
      std::cout << "###" << ( tokens[i+1] == ",") << std::endl;
      std::cout << "###" << (tokens[i][-1] == ',') << std::endl;
    }while( tokens[i][-1] != ',' or tokens[i+1] != "," );
    
    
    


  }else{
    std::cout << tokens[0].c_str() << " not found" << std::endl;
  }





  return rs;

}
























int main(){

  
  table t;
  string tn("Ученики");
  t.set_name( tn );
  bool table_was_created = false;
  
  list< Type > tp;
  list< string > fl;
  
  string p1("Фамилия");        fl.add(p1); tp.add( STRING );
  string p2("Имя");            fl.add(p2); tp.add( STRING );
  string p3("Отчество");       fl.add(p3); tp.add( STRING );
  string p4("Год рождения");   fl.add(p4); tp.add( INT );
  string p5("Курс");           fl.add(p5); tp.add( STRING );
  string p6("Оценки");         fl.add(p6); tp.add( ARRAY );

  t.set_fields( fl );
  t.set_types( tp );
  table_was_created = true;

  list<value> _obj;
  string _o1("Иванов");         value o1( _o1 ); _obj.add(o1);
  string _o2("Иван");           value o2( _o2 ); _obj.add(o2);
  string _o3("Иванович");       value o3( _o3 ); _obj.add(o3);
  int    _o4 = 2000;            value o4( _o4 ); _obj.add(o4);
  string _o5("ИУК4-12Б");       value o5( _o5 ); _obj.add(o5);
  list<int> _o6; _o6.add(-2); _o6.add(-1); _o6.add(0); _o6.add(1); _o6.add(2);
  value o6( _o6 ); _obj.add(o6);

  t.add( _obj );

  string rq("SELECT Имя , Курс, Оценки FROM Ученики");
  list< list< value > > rs;

  rs = sql( t, rq );


  return 0;
}
