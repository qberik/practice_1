#include <iostream>
#include "string.hpp"
#include "list.hpp"
#include "input.hpp"
#include "value.hpp"
#include "table.hpp"
#include <stdexcept>

bool is_keyword( string w ){
  string keywords("SELECT FROM WHERE HAVING");
  list<string> keys = keywords.split();
  keywords = "GROUP BY";
  keys.add( keywords );
  keywords = "ORDER BY";
  keys.add( keywords );
  return ( keys.find( w ) != -1 );
}

bool is_binary_operator( string w ){
  string keywords("AND OR NOT");
  list<string> keys = keywords.split();
  /*
  for( int i = 0; i < keys.length(); i++ ){
    std::cout << '#' << keys[i].c_str() << '#' << std::endl;
    std::cout <<  keys.find( w ) << ' ' << w.c_str() << std::endl;
  } */
  return ( keywords.split().find( w ) != -1 );
}

float compute_func( list<int> obj, string w ){
  int var = -1;
  if( w.find( "(" ) != -1 && w.find( ")" ) != -1 ){
    if( w.find( "MIN" ) == 0 ){ var = 1; }
    if( w.find( "MAX" ) == 0 ){ var = 2; }
    if( w.find( "AVG" ) == 0 ){ var = 3; }
    if( w.find( "SUM" ) == 0 ){ var = 4; }
    if( w.find( "COUNT" ) == 0 ){ var = 5; }
  }
  float res = 0;
  switch( var ){
    case 1:{
      res = obj[0];
      for( int i = 0; i < obj.length(); i++ )
        if ( obj[i] < res )
          res = obj[i];
    break;}
    case 2:{
      res = obj[0];
      for( int i = 0; i < obj.length(); i++ )
        if ( obj[i] > res )
          res = obj[i];
    break;}
    case 3:{
      res = obj[0];
      for( int i = 0; i < obj.length(); i++ )
        res += obj[i];
      res /= static_cast<float>( obj.length() );
    break;}
    case 4:{
      for( int i = 0; i < obj.length(); i++ )
        res += obj[i];
    break;}
    case 5:{
      res = obj.length();
    break;}
    case -1:{
      std::runtime_error( "Undefinded agregat funcion" );
    break;}
  }
  return res;
}

bool is_func( string w ){
  return ( ( w.find( "MIN" ) == 0 || w.find( "MAX" ) == 0 || w.find( "AVG" ) == 0 || w.find( "SUM" ) == 0 || w.find( "COUNT" ) == 0 ) && w.find( "(" ) != -1 && w.find( ")" ) != -1 );
}

list< list<value>> filter(  list<list<value>> objs, list<string> fields, list<Type::Type>types, string f ){
  list< list< value > > result; list<value> _tmp_l;
  for( int i = 0; i < objs.length(); i++ )
    result.add( _tmp_l );
  //std::cout << "OBJ " << objs << std::endl;
  list<string> args = f.split(';');
  for( int i = 0; i < args.length(); i++ ){
    args[i].strip(); 
  }
  string tmp("");
  list<bool> equasion_res; bool res;
  int oper = 0; int sep = 0; list<int> opers; 
  list<string> val; string s1(""); val.add(s1); val.add(s1);
  list< list< string> > vals; list< string > _tmp_vals;
  list< list<Type::Type> > typs; list<Type::Type> _tmp_typs;
  std::cout << "args are " << args << std::endl;
  for( int i = 0; i < ( args.length() + 1 ) / 2; i++ ){ 
    equasion_res.add( false );
    _tmp_vals.clear();
    _tmp_typs.clear();
    val[0] = "";
    val[1] = "";
    _tmp_typs.add( Type::NONE );
    _tmp_typs.add( Type::NONE );
    typs.add(_tmp_typs);
    tmp = "<>"; if( args[i*2].find(tmp) != -1 ){sep = args[i*2].find(tmp);oper = 1; for(int j = 0;j < sep; j++ ) val[0]+=args[i*2][j];  for(int j = sep + 2; j < args[i*2].size()+1; j++ ) val[1]+=args[i*2][j]; }
    tmp = "<="; if( args[i*2].find(tmp) != -1 ){sep = args[i*2].find(tmp);oper = 2; for(int j = 0;j < sep; j++ ) val[0]+=args[i*2][j];  for(int j = sep + 2; j < args[i*2].size()+1; j++ ) val[1]+=args[i*2][j]; }
    tmp = ">="; if( args[i*2].find(tmp) != -1 ){sep = args[i*2].find(tmp);oper = 3; for(int j = 0;j < sep; j++ ) val[0]+=args[i*2][j];  for(int j = sep + 2; j < args[i*2].size()+1; j++ ) val[1]+=args[i*2][j]; }
    tmp = "<";  if( args[i*2].find(tmp) != -1 ){sep = args[i*2].find(tmp);oper = 4; for(int j = 0;j < sep; j++ ) val[0]+=args[i*2][j];  for(int j = sep + 1; j < args[i*2].size()+1; j++ ) val[1]+=args[i*2][j]; }
    tmp = ">";  if( args[i*2].find(tmp) != -1 ){sep = args[i*2].find(tmp);oper = 5; for(int j = 0;j < sep; j++ ) val[0]+=args[i*2][j];  for(int j = sep + 1; j < args[i*2].size()+1; j++ ) val[1]+=args[i*2][j]; }
    tmp = "=";  if( args[i*2].find(tmp) != -1 ){sep = args[i*2].find(tmp);oper = 6; for(int j = 0;j < sep; j++ ) val[0]+=args[i*2][j];  for(int j = sep + 1; j < args[i*2].size()+1; j++ ) val[1]+=args[i*2][j]; }
    val[0].strip(); val[1].strip();
    for( int j = 0; j < 2; j++ ){
      bool is_num = true;
      for( int k = 0; k < val[j].length(); k++ )
        if( val[j][k] > '9' or val[j][k] < '0' )
          is_num = false;
      if( is_num ){
        typs[i][j] = Type::INT;
      }else if( is_func( val[j] ) ){
        typs[i][j] = Type::INT;
      }else if( val[j][0] == '\'' && val[j][-1] == '\'' ){  
        typs[i][j] = Type::STRING;
      }else{
        int id = fields.find( val[j] );
        if ( id == -1 ){
          string error("undefindex indefecator ");
          error += val[j];
          error += " in expression "; 
          error += f;
          throw std::runtime_error( error.c_str()  );
        }else{
          typs[i][j] = types[id];
        }
      }
    }
    if( typs[i][0] != typs[i][1] ){
      string error("wrong type of expression ");
      error += val[0];
      error += " and ";
      error += val[1];
      throw std::runtime_error( error.c_str()  );
    }
    _tmp_vals.add( val[0] );
    _tmp_vals.add( val[1] );
    vals.add( _tmp_vals );

    opers.add( oper );

    //std::cout << val[0] << " with type " << typs[i][0] << " op " << opers << " and " << val[1] << " with type " << typs[i][1] << std::endl;
  }
  for( int I = 0; I < objs[0].length(); I++ ){
    for( int i = 0; i < ( args.length() + 1 ) / 2; i++ ){
    //std::cout << "HERE OK at obj " << I << ' ' << i << std::endl;
      switch( typs[i][0] ){
        case Type::INT:{
          int _vals[2];
          for( int j = 0; j < 2; j++ ){
              bool is_num = true;
              for( int k = 0; k < vals[i][j].length(); k++ )
                if( vals[i][j][k] > '9' or vals[i][j][k] < '0' )
                  is_num = false;
              if( is_num ){
                _vals[j] = atoi( vals[i][j] );
            }else if( is_func( vals[i][j] ) ){
              string _tmp_str("");
              for( int k = vals[i][j].find("(") + 1; k < vals[i][j].find(")"); k++ )
                _tmp_str += vals[i][j][k];
              _tmp_str.strip();
              int id = fields.find( _tmp_str );
              //std::cout << id << ' ' << _tmp_str << std::endl;
              //std::cout << I << ' ' << i << "Here" << std::endl;
              _vals[j] = compute_func( objs[id][I].get_array(), vals[i][j] );
              //asdasd 
              //typs[i][j] = Type::INT;
            }else{
              int id = fields.find( vals[i][j] );
              //std::cout << id << ' ' <<  objs[I][id].get_type() << std::endl;
              //std::cout << id << ' ' <<  objs[id][I].get_type() << std::endl;
              //std::cout << id << ' ' <<  objs[id][I].get_string() << std::endl;
              _vals[j] = objs[id][I].get_int();
            }
          }
          //std::cout << _vals[0] << ' ' << _vals[1] << std::endl;

          switch( opers[i] ){
            case 1: {
              equasion_res[i] = _vals[0] != _vals[1];
            break;}
            case 2: {
              equasion_res[i] = _vals[0] <= _vals[1];
            break;}
            case 3: {
              equasion_res[i] = _vals[0] >= _vals[1];
            break;}
            case 4: {
              equasion_res[i] = _vals[0] < _vals[1];
            break;}
            case 5: {
              equasion_res[i] = _vals[0] > _vals[1];
            break;}
            case 6: {
              equasion_res[i] = _vals[0] == _vals[1];
            break;}
              

          }
        break;}
        case Type::STRING:{
          if( !( opers[i] == 1 or opers[i] == 6 ) )
            throw std::runtime_error( "wrong type of comarsion for string" );
          list<string> _vals; 
          for( int j = 0; j < 2; j++ ){
            string *t = new string("");
            if( vals[i][j][0] == '\'' && vals[i][j][-1] == '\'' ){
              for( int k = 1; k < vals[i][j].size() - 1; k++ )
                (*t) += vals[i][j][k];
            }else{
              int id = fields.find( vals[i][j] );
              (*t) = objs[id][I].get_string();
            }
            _vals.add( (*t));
          }
          std::cout << _vals << ' ' << I << std::endl;

          switch( opers[i] ){
            case 1: {
              equasion_res[i] = _vals[0] != _vals[1];
            break;}
            case 6: {
              equasion_res[i] = _vals[0] == _vals[1];
            break;}
          }

        break;}
        default:
          throw std::runtime_error( "undefined type of exression" );
      
      }
    }
    //std::cout << equasion_res << ' ' << I << std::endl;
    res = equasion_res[0];
    for( int i = 1; i < ( args.length() - 1 ) / 2; i++ ){
      if( args[i*2+1] == "AND" )
        res = res && equasion_res[i];
      if( args[i*2+1] == "OR" )
        res = res || equasion_res[i];
    }
    if( res ){
      _tmp_l.clear();
      for( int i = 0; i < objs.length(); i++ ){
        result[i].add( objs[i][I] );
      } 
    }
  }
  return result;

}
//throw std::runtime_error("value is not an int");
list< list< value > > sql( list<table> db, string rq ){

  list< list< value > > rs; 

  string tmp_rq = rq;
 
  list< string > tokens = rq.split();

  string _cols;
  string bufer("");
  list<string> cols; list<string> expanded_cols; 
  int agregat_func = 0; 
  bool agregat_in_select = false;
  list<string> tname; 
  string where_expr("");
  string group_expr("");
  string having_expr("");
  string order_expr("");

  for( int i = 0; i < tokens.length(); i++ ){
    if( ( tokens[i] == "GROUP" || tokens[i] == "ORDER" ) && tokens[i+1] == "BY" ){
      tokens[i] += " ";
      tokens[i] += tokens[i+1];
      tokens.remove(i+1);
    }
    std::cout << i << ' ' << tokens[i].c_str() << std::endl;
  }
  
  int i = 0;
  if( tokens[i] == "SELECT"  ){
    do{
      i++;
      agregat_func += tokens[i].count('(');

      if( tokens[i] != "," && agregat_func == 0 ){
        cols.add( tokens[i] );
        if( tokens[i][-1] == ',' )
          cols[cols.length()-1][-1] = '\0';
      }

      agregat_func -= tokens[i].count(')');

      if( agregat_func != 0 ){
        agregat_in_select = true;
        bufer += tokens[i];
      }else{
        if(bufer != ""){
          bufer += tokens[i];
          cols.add( bufer );
          if( bufer[-1] == ',' )
            cols[cols.length()-1][-1] = '\0';         
          bufer = "";
        }
      }    
    }while(  tokens[i][-1] == ',' || tokens[i+1] == "," || agregat_func != 0 );

    std::cout << cols << std::endl;

    i++;
    if( tokens[i] == "FROM" ){
      do{
      i++;
      if( tokens[i] != ","){
        tname.add( tokens[i] );
        if( tokens[i][-1] == ',' )
          tname[tname.length()][-1] = '\0';
      }
      }while( ( tokens[i][-1] == ',' || tokens[i+1] == "," ) );
      i++;
    }

    std::cout << tname << std::endl;

    if( tokens[i] == "WHERE" ){
      do{
        i++;

        if( is_binary_operator( tokens[i] ) ){
          where_expr += ";";
          where_expr += tokens[i];
          where_expr += ";";
        }else{
          where_expr += " ";
          where_expr += tokens[i];
        }



      }while( ( !is_keyword( tokens[i+1] ) && i+1 < tokens.length() ) );
      i++;
    }
      
    std::cout << where_expr << std::endl;

    if( tokens[i] == "GROUP BY" ){
      do{
        i++;
        if( is_binary_operator( tokens[i] ) ){
          group_expr += " ";
          group_expr += tokens[i];
          group_expr += " ";
        }else{
          group_expr += tokens[i];
        }
      }while( ( !is_keyword( tokens[i+1] ) && i+1 < tokens.length() ) );

      std::cout << ( group_expr.split(',') ) << std::endl;
      i++;
      if( tokens[i] == "HAVING" ){
        do{
          i++;
          if( is_binary_operator( tokens[i] ) ){
            having_expr += " ";
            having_expr += tokens[i];
            having_expr += " ";
          }else{
            having_expr += tokens[i];
          }
        }while( ( !is_keyword( tokens[i+1] ) &&  i+1 < tokens.length() ) );
        i++;
        std::cout << having_expr.c_str() <<  std::endl;
      }
        
    }

    if( tokens[i] == "ORDER BY" ){
      do{
      i++;
      if( tokens[i] != ","){
        order_expr += tokens[i];
        if( tokens[i][-1] == ',' )
          order_expr[-1] = '\0';
      }
      std::cout << '#' << order_expr.c_str() << ' ' << i << std::endl;
      }while( ( tokens[i][-1] == ',' || tokens[i+1] == "," ) );
      i++;
    }

    
  }else{
    std::cout << tokens[0].c_str() << " not found" << std::endl;
  }
  
  table &t = db[0];
  for( int i = 0; i < db.length(); i++ ){
    if( db[i].name == tname[0] ){
      t = db[i];
    }
  }

  list<string> _tmp;
  for( int i = 0; i <  cols.length(); i++ ){
    if( cols[i] == "*" ){
      for( int j = 0; j < t.fields.length(); j++ ){
        expanded_cols.add( t.fields[j] );
      }
    }else{
      expanded_cols.add( cols[i] );
    }
  }

  rs = t.getCols( expanded_cols );
  std::cout << filter( rs, expanded_cols, t.types, where_expr ) << std::endl;
  std::cout << expanded_cols << std::endl; 
  std::cout << rs << std::endl;
  

  return rs;

}







