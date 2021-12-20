#include <iostream>
#include "string.hpp"
#include "list.hpp"
#include "input.hpp"
#include "value.hpp"
#include "table.hpp"
#include <stdexcept>

bool is_keyword( string w ){
  string keywords("SELECT AS FROM WHERE HAVING DESC");
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
    //std::cout << '#' << keys[i].c_str() << '#' << std::endl;
    //std::cout <<  keys.find( w ) << ' ' << w.c_str() << std::endl;
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
      string _tmp_str("");
      for( int k = w.find("(") + 1; k < w.find(")"); k++ )
        _tmp_str += w[k];
      _tmp_str.strip();
      list< string > _tmp_list = _tmp_str.split(',');
      _tmp_str = _tmp_list[ _tmp_list.length() - 1 ];
      _tmp_str.strip();
      bool is_num = true;
      for( int i = 0; i < _tmp_str.length(); i++ )
        if( !( ( _tmp_str[i] <= '9' && _tmp_str[i] >= '0' ) || _tmp_str[i] == '-' )  )
          is_num = false;
      if( _tmp_list.length() > 1 && is_num ){
        int num = string_to_int( _tmp_str );
        for( int i = 0; i < obj.length(); i++ )
          if( obj[i] == num )
            res++;
      }else{
        res = obj.length();
      }
    break;}
    case -1:{
      std::runtime_error( "Undefinded agregat funcion" );
    break;}
  }
  return res;
}

float compute_func( list<value> obj, string w ){
  float res = 0;
  switch( obj[0].get_type() ){
    case Type::INT:{
      list<int> list;
      for( int i = 0; i < obj.length(); i++ ){
        list.add( obj[i].get_int() );
      }
      res = compute_func( list, w );
    break;}
    case Type::ARRAY:{
      list<int> list, _tmp_list;
      for( int i = 0; i < obj.length(); i++ ){
        _tmp_list = obj[i].get_array();
        for( int j = 0; j < _tmp_list.length(); j++ ){
          list.add( _tmp_list[j]  );
        }
      }
      res = compute_func( list, w );
    break;}
    case Type::STRING:{
      std::runtime_error( "Agregat funcion not supported for string" );
    break;}

  }
  return res;
}

float compute_func( list< list<value> > obj, string w ){
  float res = 0;
  switch( obj[0][0].get_type() ){
    case Type::INT:{
      list<int> list;
      for( int i = 0; i < obj.length(); i++ )
        for( int j = 0; j < obj[i].length(); j++ )
          list.add( obj[i][j].get_int() );
      res = compute_func( list, w );
    break;}
    case Type::ARRAY:{
      list<int> list, _tmp_list;
      for( int i = 0; i < obj.length(); i++ )
        for( int j = 0; j < obj[i].length(); j++ ){
          _tmp_list = obj[i][j].get_array();
          for( int k = 0; k < _tmp_list.length(); k++ )
            list.add( _tmp_list[k] );
        }
      res = compute_func( list, w );
    break;}
    case Type::STRING:{
      std::runtime_error( "Agregat funcion not supported for string" );
    break;}
  }
  return res;
}

bool is_func( string w ){
  return ( ( w.find( "MIN" ) == 0 || w.find( "MAX" ) == 0 || w.find( "AVG" ) == 0 || w.find( "SUM" ) == 0 || w.find( "COUNT" ) == 0 ) && w.find( "(" ) != -1 && w.find( ")" ) != -1 );
}

bool is_list_value( list<value> ){ return true; }
bool is_list_value( value ){ return false; }


int get_int( list<value> ){ 
  std::runtime_error("Can't get int of list"); 
  return 0; 
}
int get_int( value v ){
  return v.get_int();  
}


string get_string( list<value> ){ 
  string s("");
  std::runtime_error("Can't get string of list"); 
  return s;
}
string get_string( value v ){
  return v.get_string();  
}


template <typename T>
list< list<T>> filter(  list<list<T>> objs, list<string> fields, list<Type::Type>types, string f ){
  list< list< T > > result; list< T > _tmp_l;
  for( int i = 0; i < objs[0].length(); i++ )
    result.add( _tmp_l );
  ////std::cout << "OBJ " << objs << std::endl;
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
  //std::cout << " args are " << args << std::endl;
  for( int i = 0; i < ( args.length() + 1 ) / 2; i++ ){
    equasion_res.add( false );
    sep = 0;
    _tmp_vals.clear();
    _tmp_typs.clear();
    val[0] = "";
    val[1] = "";
    _tmp_typs.add( Type::NONE );
    _tmp_typs.add( Type::NONE );
    typs.add(_tmp_typs);

    list< string > compare_operators = string ("<> <= >= < > =").split();
    for( int j = 0; j < compare_operators.length() && !sep; j++ ){
      if( args[i*2].find( compare_operators[j] ) != -1 ){
        sep = args[i*2].find( compare_operators[j] );
        oper = j + 1;
        for( int k = 0; k < sep; k++ )
          val[0]+=args[i*2][k];
        for( int k = sep + compare_operators[j].length(); k < args[i*2].size()+1; k++ )
          val[1]+=args[i*2][k];
      }
    }
    val[0].strip(); val[1].strip();

    //std::cout << "DEBUG1:!" << val[0] << "! !" << val[1] << "! " << opers << std::endl;
    //std::cout << "DEBUG1:!" << val[0] << "! !" << val[1] << "! " << opers << std::endl;
    for( int j = 0; j < 2; j++ ){
    //std::cout << "HERE STILL OK1" << val[j] << std::endl;
      bool is_num = true;
      for( int k = 0; k < val[j].length(); k++ )
        if(  !( ( val[j][k] <= '9' && val[j][k] >= '0' ) || val[j][k] == '-' ) ) 
          is_num = false;
      if( is_num ){
        typs[i][j] = Type::INT;
      }else if( is_func( val[j] ) ){
        typs[i][j] = Type::INT;
    //std::cout << "HERE STILL OK2 with" << val[i] << std::endl;
      }else if( val[j][0] == '\'' && val[j][-1] == '\'' ){
        typs[i][j] = Type::STRING;
      }else{
        //std::cout << fields << std::endl;
        //std::cout << val[j] << std::endl;
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
    //std::cout << typs << " <--- " << std::endl;
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

    //std::cout << "DEBUG: " << val[0] << " with type " << typs[i][0] << " op " << opers << " and " << val[1] << " with type " << typs[i][1] << std::endl;
  }
  for( int I = 0; I < objs.length(); I++ ){
    for( int i = 0; i < ( args.length() + 1 ) / 2; i++ ){
    ////std::cout << "HERE OK at obj " << I << ' ' << i << std::endl;
      switch( typs[i][0] ){
        case Type::INT:{
          int _vals[2];
          for( int j = 0; j < 2; j++ ){
          //std::cout << "DEBUG3 GET INT VALUE:" << vals[i] << std::endl;
            bool is_num = true;
            for( int k = 0; k < vals[i][j].length(); k++ )
              if( !( ( val[j][k] <= '9' && val[j][k] >= '0' ) || val[j][k] == '-' )  )
                is_num = false;
            //std::cout << "HERE STILL OK WITH " << i << ' ' << j << ' ' << is_num <<  std::endl;
            if( is_num ){
              _vals[j] = string_to_int( vals[i][j] );
            }else if( is_func( vals[i][j] ) ){
              string _tmp_str("");
              for( int k = vals[i][j].find("(") + 1; k < vals[i][j].find(")"); k++ )
                _tmp_str += vals[i][j][k];
              _tmp_str.strip();

              list< string > _tmp_list = _tmp_str.split(',');
              list< T > _tmp_val;
              //list<list< value >> _tmp_val_list;
              bool _is_list_value = false;
              for( int k = 0; k < _tmp_list.length(); k++ ){
                _tmp_list[k].strip();
                int id = fields.find( _tmp_list[k] );
                bool _is_num = true;
                for( int l = 0; l < _tmp_list[k].length(); l++ )
                  if( !( ( val[j][k] <= '9' && val[j][k] >= '0' ) || val[j][k] == '-' ))
                    _is_num = false;
                if( !( k == _tmp_list.length() - 1 && _is_num ) ){
                  _is_list_value =  is_list_value( objs[id][I] );
                _tmp_val.add( objs[I][id] );
                }
              }
                _vals[j] = compute_func( _tmp_val, vals[i][j] );
          }else{
            int id = fields.find( vals[i][j] );
            bool _is_list_value =  is_list_value( objs[I][id] );
            if( _is_list_value ){
              string error(" Can't compare group of INT ");
              error += vals[i][j];
              error += " in equasion ";
              error += args[i*2];
              std::runtime_error( error.c_str() );
            }else{
              _vals[j] = get_int( objs[I][id] );
            }
          }
        }
        //std::cout << "DEBUG4: vals are " << _vals[0] << ' ' << _vals[1] <<  std::endl;
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
          if( !( opers[i] == 1 || opers[i] == 6 ) )
            throw std::runtime_error( "wrong type of comarsion for string" );
          list<string> _vals;
          T _t;
          for( int j = 0; j < 2; j++ ){
            string *t = new string("");
            if( vals[i][j][0] == '\'' && vals[i][j][-1] == '\'' ){
              for( int k = 1; k < vals[i][j].size() - 1; k++ )
                (*t) += vals[i][j][k];
            }else{
              int id = fields.find( vals[i][j] );
              _t =  objs[I][id];
              if( ! is_list_value( _t ) ){
                (*t) = get_string( _t ).c_str();
              }else{
                string error(" Can't compare group of STRING ");
                error += vals[i][j];
                error += " in equasion ";
                error += args[i*2];
                std::runtime_error( error.c_str() );
              }
            }
            _vals.add( (*t));
          }
          ////std::cout << _vals << ' ' << I << std::endl;

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
    res = equasion_res[0];
    for( int i = 0; i < ( ( args.length() - 1 ) / 2 ); i++ ){
      if( args[i*2+1] == "AND" )
        res = res && equasion_res[i+1];
      if( args[i*2+1] == "OR" )
        res = res || equasion_res[i+1];
    }
    ////std::cout << args[1] << ":RES " << res  << ' ' << equasion_res << ' ' << I << std::endl;
    if( res ){
      _tmp_l.clear();
      for( int i = 0; i < objs[0].length(); i++ ){
        result[i].add( objs[I][i] );
      }
    }
  }
  return result;

}
//throw std::runtime_error("value is not an int");



table sql( list<table> db, string rq ){

  list< list< value > > rs;

  string tmp_rq = rq;

  list< string > tokens = rq.split();

  string _cols;
  string bufer("");
  list<string> cols; list<string> expanded_cols;
  int agregat_func = 0;
  bool is_top = false; int top_num = 0;
  bool agregat_in_select = false; bool is_select = false;
  list<string> tname; bool is_from = false;
  string where_expr(""); bool is_where = false;
  string group_expr(""); bool is_group_by = false;
  string having_expr(""); bool is_having = false;
  string order_expr(""); list<string> order; bool is_order_by = false; bool is_desc = false;
  string name_buf(""), func_buf("");
      

  for( int i = 0; i < tokens.length(); i++ ){
    if( ( tokens[i] == "GROUP" || tokens[i] == "ORDER" ) && tokens[i+1] == "BY" ){
      tokens[i] += " ";
      tokens[i] += tokens[i+1];
      tokens.remove(i+1);
    }
    //std::cout << i << ' ' << tokens[i].c_str() << std::endl;
  }

  int i = 0;
  if( tokens[i] == "SELECT"  ){
    if( tokens[i+1] == "TOP" ){
      i+=2;
      bool is_num = true;
      for( int j = 0; j < tokens[i].length(); j++ )
        if( !( ( tokens[i][j] <= '9' && tokens[i][j] >= '0' ) || tokens[i][j] == '-' )  )
          is_num = false;     
      if( is_num ){
        is_top = true;
        top_num = string_to_int( tokens[i] );
      }else{
        i-=2; 
      
      }
    }

    
    do{
      i++;
      
      //std::cout << "token is " << tokens[i] << "agfunc+ is " << agregat_func << std::endl;
      agregat_func += tokens[i].count('(');
      //std::cout << "token is " << tokens[i] << "agfunc+ is " << agregat_func << std::endl;
      
      if( agregat_func == 0 ){
        name_buf += ' ';
        name_buf += tokens[i];
      }else{
        func_buf += tokens[i];
        func_buf += ' ';
        agregat_in_select = true;
      }

      agregat_func -= tokens[i].count(')');
      
      //std::cout << '!' << tokens[i] <<  "! #" << name_buf << "# func_cout is " << agregat_func << ' ' << is_keyword( tokens[i+1] ) << std::endl;
      //std::cout << '!' << tokens[i] <<  "! #" << func_buf << "# func_cout is " << agregat_func << ' ' << is_keyword( tokens[i+1] ) << std::endl;

      if( agregat_func == 0 ){
        name_buf += func_buf;
        func_buf = ""; 
        name_buf.strip();
        //std::cout << "name_buf !" << name_buf << "! " << ( name_buf[-1] == ',' ) << std::endl;
        if( name_buf[-1] == ','  ){
          name_buf[-1] = '\0';
          name_buf.strip(); 
          cols.add( name_buf );
          name_buf = "";
        }else if ( is_keyword( tokens[i+1] ) ){
          name_buf.strip(); 
          cols.add( name_buf );
        }
      }


    }while( !is_keyword( tokens[i+1] ) );
    name_buf = ""; func_buf = "";
    is_select = true;
    //std::cout << "cols buf " << func_buf << std::endl;
    //std::cout << "cols buf " << name_buf << std::endl;
    //std::cout << "cols are " << cols << std::endl;

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
      is_from = true;
    }

    //std::cout << tname << std::endl;

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
      is_where = true;
    }

    //std::cout << where_expr << std::endl;

    if( tokens[i] == "GROUP BY" ){
      do{
        i++;
        //if( is_binary_operator( tokens[i] ) ){
        //  group_expr += " ";
        //  group_expr += tokens[i];
        //}else{
          group_expr += " ";
          group_expr += tokens[i];
        //}
      }while( ( !is_keyword( tokens[i+1] ) && i+1 < tokens.length() ) );

      is_group_by = true;
      //std::cout << ( group_expr.split(',') ) << std::endl;
      i++;
      if( tokens[i] == "HAVING" ){
        do{
          i++;
          if( is_binary_operator( tokens[i] ) ){
            having_expr += ";";
            having_expr += tokens[i];
            having_expr += ";";
          }else{
            having_expr += " ";
            having_expr += tokens[i];
          }
        }while( ( !is_keyword( tokens[i+1] ) &&  i+1 < tokens.length() ) );
        i++;
        //std::cout << having_expr.c_str() <<  std::endl;
        is_having = true;
      }

    }

    if( tokens[i] == "ORDER BY" ){
      do{
      i++;
      
      agregat_func += tokens[i].count('(');
      
      if( agregat_func == 0 ){
        name_buf += ' ';
        name_buf += tokens[i];
      }else{
        func_buf += tokens[i];
        func_buf += ' ';
      }
      agregat_func -= tokens[i].count(')');
      if( agregat_func == 0 ){
        name_buf += func_buf;
        func_buf = ""; 
        name_buf.strip();
        if( name_buf[-1] == ','  ){
          name_buf[-1] = '\0';
          name_buf.strip(); 
          order.add( name_buf );
          name_buf = "";
        }else if ( is_keyword( tokens[i+1] ) || (i+1 >= tokens.length() ) ){
          name_buf.strip(); 
          order.add( name_buf );
        }
      }
      

      }while( i + 1 < tokens.length() && !is_keyword( tokens[i+1] )  );

      i++;
      is_order_by = true;

      if( tokens[i] == "DESC" ){
        i++;
        is_desc = true;  
      }
    }
  }else{
    //std::cout << tokens[0].c_str() << " not found" << std::endl;
  }

  //std::cout << cols << std::endl;
  // edit this later
  table &t = db[0];
  list<Type::Type> typs; list<Type::Type> _tmp_type;
  list<string> flds; list<string> _tmp_flds;
  list<list<value>> data; list<list<value>> _tmp_data;
  for( int i = 0; i < db.length(); i++ ){
    if( db[i].name == tname[0] ){
      _tmp_type = db[i].types;
      for( int j = 0; j < _tmp_type.length(); j++ )
        typs.add( _tmp_type[j] );
      _tmp_flds = db[i].fields;
      for( int j = 0; j < _tmp_flds.length(); j++ )
        flds.add( _tmp_flds[j] );
      _tmp_data = db[i].objects;
      for( int j = 0; j < _tmp_data.length(); j++ )
        data.add( _tmp_data[j] );
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

  //std::cout << expanded_cols << std::endl;

  rs = data;//t.getCols( expanded_cols );

  //std::cout << rs << std::endl;

  if( is_where ){
    list<list<value>> __rs;
    list<value> ___rs;
    __rs = filter( rs, flds, typs, where_expr );
    rs.clear();
    for( int i = 0; i < __rs[0].length(); i++ ){
      ___rs.clear();
      for( int j = 0; j < __rs.length(); j++ ){
          ___rs.add( __rs[j][i] );
      }
      rs.add( ___rs );
    }
    //std::cout << "Filtered " << rs << std::endl;
  }

  if( is_group_by ){
    list< value > uniq;
    list< list< list< value >>> temp_rs;
    list< list< value >> _temp_rs;
    list< value > __temp_rs;
    for( int i = 0; i < rs[0].length(); i++ )
      _temp_rs.add( __temp_rs );
    //list< value > __temp_rs;
    //std::cout << '!' << group_expr <<  '!' << std::endl;
    group_expr.strip();
    int id = flds.find(group_expr);
    //std::cout << group_expr << " in " << expanded_cols << std::endl;
    //std::cout << "HERE STILL OK" << ' ' << id << std::endl;
    for ( int i = 0; i < rs.length(); i++ ){
      if( uniq.find( rs[i][id] ) == -1 ){
    //std::cout << "HERE STILL OK with " << rs[i][id] << std::endl;
        uniq.add( rs[i][id] );
        temp_rs.add( _temp_rs );
      }
    }
    //std::cout << "empy " << temp_rs << std::endl;
    //std::cout << "uniq is " << uniq << std::endl;
    for( int i = 0; i < uniq.length(); i++ ){
      for( int j = 0; j < rs.length(); j++ ){
        for( int k = 0; k < rs[i].length(); k++ ){
          if( uniq[i] == rs[j][id] ){
            if( !(j < 1 && k == id ) )
              temp_rs[i][k].add( rs[j][k] );
            //std::cout << rs[j][k] << " ";
          }
        }
          //std::cout << std::endl;
      }
    }
    //std::cout << "full is " << temp_rs << std::endl;
    //std::cout << "Len of temp_rs" << temp_rs[0].length() << std::endl;
    //std::cout << '!' << group_expr <<  '!' <<  agregat_in_select << std::endl;
    if( is_having ){
      //std::cout << "ASDASDASDASDASDASDASD" << std::endl;
      //std::cout << having_expr << std::endl;
      list<list<list<value>>> __temp_rs;
      list<list<value>> ___temp_rs;
      __temp_rs = filter( temp_rs, flds, typs, having_expr );
      temp_rs.clear();
      for( int i = 0; i < __temp_rs[0].length(); i++ ){
        ___temp_rs.clear();
        for( int j = 0; j < __temp_rs.length(); j++ ){
           ___temp_rs.add( __temp_rs[j][i] ); 
        }
        temp_rs.add( ___temp_rs );
      }
    }
   



    if( is_order_by ){
      for( int i = 0; i < order.length(); i++ ){
        for( int j = 0; j < temp_rs.length(); j++ ){
          int min_id = j;
          for( int u = j + 1; u < temp_rs.length(); u++ ){
            list< int > indexes;
            indexes.add( u );
            indexes.add( min_id );
            list< value > ab_val;
            for( int o = 0; o < indexes.length(); o++ ){
              if( is_func( order[i] ) ){
                string _tmp_str("");       
                for( int k = order[i].find("(") + 1; k < order[i].find(")"); k++ ){
                  _tmp_str += order[i][k]; 
                }
                _tmp_str.strip();
                list< string > _tmp_list = _tmp_str.split(',');
                list< list <value> > _tmp_val;
                for( int k = 0; k < _tmp_list.length(); k++ ){
                  _tmp_list[k].strip();
                  bool _is_num = true;
                  for( int l = 0; l < _tmp_list[k].length(); l++ )
                    if( !( ( _tmp_list[k][l] <= '9' && _tmp_list[k][l] >= '0' ) || _tmp_list[k][l] == '-' )  )
                      _is_num = false;
                  if( !( k == _tmp_list.length() - 1 && _is_num ) ){
                    int id = flds.find( _tmp_list[k] );
                    _tmp_val.add( temp_rs[ indexes[o] ][ id ] );   
                  
                  }

                }
                int64_t *num = new int64_t( compute_func( _tmp_val, order[i] ) );
                value v( *num );
                ab_val.add( v );
                  
              }else{
                if( order[i] == group_expr ){
                  int id = flds.find( order[i] );
                  ab_val.add( temp_rs[ indexes[o] ][ id ][0] );
                }else{
                  string error( "can't get filed " );
                  error += order[i];
                  error += " as ordering item";
                  std::runtime_error( error.c_str() ); 
                }
              
              }
            

            if( ab_val[0].get_type() != ab_val[1].get_type() ){
              string error("can't compare type"); 
              error += '0' + ab_val[0].get_type();
              error += " with ";
              error += '0' + ab_val[1].get_type();
              std::runtime_error( error.c_str() );
            }

            bool res = false;

            switch( ab_val[0].get_type() ){
              case Type::INT:{
                if( is_desc )
                res = ab_val[0].get_int() > ab_val[1].get_int();
                else
                res = ab_val[0].get_int() < ab_val[1].get_int();
              break;} 
              case Type::STRING:{
                if( is_desc )
                res = ab_val[0].get_string() > ab_val[1].get_string();
                else
                res = ab_val[0].get_string() < ab_val[1].get_string();
              break;} 
              case Type::ARRAY:{
                std::runtime_error("can't compare arrays");
              break;} 

            }

            if( res )
              min_id = u;
            
            }
          if( min_id != j ){
          
            temp_rs.swap( j, min_id );
          
          }

            } 
          
          }
        
        }

      }
    
    list<value> __rs;
    rs.clear(); value empy_value;
    for( int i = 0; i < temp_rs.length(); i++ ){
      __rs.clear();
      for( int j = 0; j < expanded_cols.length(); j++ ){
        __rs.add(empy_value);
      }
      rs.add( __rs );
    }
    //std::cout << "HERE STILL OK WITH " << rs << std::endl;
    
    for( int i = 0; i < temp_rs.length(); i++ ){
      //_temp_obj.clear();
      for( int j = 0; j < expanded_cols.length(); j++ ){
        if( is_func( expanded_cols[j] ) ){
          string _tmp_str("");
          for( int k = expanded_cols[j].find("(") + 1; k < cols[j].find(")"); k++ ){
            _tmp_str += expanded_cols[j][k]; 
          }
          _tmp_str.strip();
          list< string > _tmp_list = _tmp_str.split(',');
          list< list<value> > _tmp_val;
          //std::cout << "tmp_LIST " << _tmp_list << std::endl;
          for( int k = 0; k < _tmp_list.length(); k++ ){
            _tmp_list[k].strip();
            int id = flds.find( _tmp_list[k] ); 
            bool _is_num = true;
            for( int l = 0; l < _tmp_list[k].length(); l++ )
              if( ! ( ( _tmp_list[k][l] <= '9' && _tmp_list[k][l] >= '0' ) || _tmp_list[k][l] == '-' ) ) 
                _is_num = false;
            //std::cout << "NUM IS " << _is_num << " for #" << _tmp_list[k] << "# " << id  << << "for f"std::endl;
            if( !( k == _tmp_list.length() - 1 && _is_num ) ){
              _tmp_val.add( temp_rs[i][id] );
              //std::cout << "temp_rs "<< i << ' ' << id << ' ' << temp_rs[id][i] << std::endl; 
            }
               
          }
          int64_t *num = new int64_t(  compute_func( _tmp_val, expanded_cols[j] ));
          rs[i][j].set_value( *num );
        }else{
          if( expanded_cols[j] == group_expr ){
            int id = flds.find( expanded_cols[j] ); 
            rs[i][j] = temp_rs[i][id][0];
          }else{
            string error("Cant get field ");
            error += expanded_cols[j];
            error += " while grouping by ";
            error += group_expr;
            std::runtime_error( error.c_str() );
          }
        }
      }
    }

    //std::cout << "OBJ IS " << rs << std::endl;
    
  }else{
    
    if( is_order_by ){
      for( int i = 0; i < order.length(); i++ ){
        //std::cout << order[i] << std::endl;  
        
        for( int j = 0; j < rs.length(); j++ ){
          int min_id = j;
          for( int u = j + 1 ; u < rs.length(); u++ ){
            list< int > indexes;
            indexes.add( u );
            indexes.add( min_id );
            list<value> ab_val;
            //std::cout << "Indexes " << indexes << std::endl;

            for ( int o = 0; o < indexes.length(); o++ ){
              if( is_func( order[i] ) ){
                //std::cout << "Function " << order[i] << std::endl;
                string _tmp_str("");
                for( int k = order[i].find("(") + 1; k < order[i].find(")"); k++ ){
                  _tmp_str += order[i][k]; 
                }

                _tmp_str.strip();

                list< string > _tmp_list = _tmp_str.split(',');

                list< value > _tmp_val;

                for( int k = 0; k < _tmp_list.length(); k++ ){
                  _tmp_list[k].strip();

                  bool _is_num = true;
                  for( int l = 0; l < _tmp_list[k].length(); l++ )
                    if( ! ( ( _tmp_list[k][l] <= '9' && _tmp_list[k][l] >= '0' ) || _tmp_list[k][l] == '-' ) ) 
                      _is_num = false;
                  if( !( k == _tmp_list.length() - 1 && _is_num ) ){
                    int id = flds.find( _tmp_list[k] );
                    if( typs[id] != Type::ARRAY ){
                      string error("cant get agregat funcion if field ");
                      error += _tmp_list[k];
                      error += " in equasion ";
                      error += cols[j];
                      std::runtime_error( error.c_str() );
                    }
                    _tmp_val.add( rs[indexes[o]][id] );
                  }
                }
                int64_t *num = new int64_t(  compute_func( _tmp_val, order[i] ));
                //std::cout << " FUNC RES " << *num << std::endl;
                value v( *num );
                ab_val.add( v );

              }else{
                //std::cout << "Field " << order[i] << std::endl;
                int id = flds.find( order[i] );
                //std::cout << "Find " << order[i] << " as " << id << std::endl;
                ab_val.add( rs[indexes[o]][id] );

              }
              //std::cout << "AB_VAL " << ab_val << " For indexes " << indexes << std::endl;

              

            }
            
            //std::cout << "ab_value are " << ab_val << std::endl;

            if( ab_val[0].get_type() != ab_val[1].get_type() ){
              string error("can't compare type"); 
              error += '0' + ab_val[0].get_type();
              error += " with ";
              error += '0' + ab_val[1].get_type();
              std::runtime_error( error.c_str() );
            }

            bool res = false;

            switch( ab_val[0].get_type() ){
              case Type::INT:{
                if( is_desc )
                res = ab_val[0].get_int() > ab_val[1].get_int();
                else
                res = ab_val[0].get_int() < ab_val[1].get_int();
              break;} 
              case Type::STRING:{
                if( is_desc )
                res = ab_val[0].get_string() > ab_val[1].get_string();
                else
                res = ab_val[0].get_string() < ab_val[1].get_string();
              break;} 
              case Type::ARRAY:{
                std::runtime_error("can't compare arrays");
              break;} 
            
            }

            if( res )
              min_id = u;
          
          }
          if( min_id != j ){
            //std::cout << "swapping " << j << " and " << min_id << std::endl;
            rs.swap( j, min_id ); 
          }
        }
      }
    }


    list<list<value>> res_rs;
    list<value> __res_rs;
    value empty_value;
    for( int i = 0; i < expanded_cols.length(); i++ )
      __res_rs.add(empty_value);
    for( int i = 0; i < rs.length(); i++ )
      res_rs.add( __res_rs ); 
    //std::cout << "rs " << rs.length() << std::endl;
    for( int i = 0; i < rs.length(); i++ ){
      for( int j = 0; j < expanded_cols.length(); j++ ){
        if( is_func( expanded_cols[j] ) ){
          string _tmp_str("");
          for( int k = expanded_cols[j].find("(") + 1; k < expanded_cols[j].find(")"); k++ ){
            _tmp_str += expanded_cols[j][k]; 
          }
          _tmp_str.strip();
          list< string > _tmp_list = _tmp_str.split(',');
          list< value > _tmp_val;
          //std::cout << "tmp_LIST " << _tmp_list << std::endl;
          for( int k = 0; k < _tmp_list.length(); k++ ){
            _tmp_list[k].strip();

            bool _is_num = true;
            for( int l = 0; l < _tmp_list[k].length(); l++ )
              if( ! ( ( _tmp_list[k][l] <= '9' && _tmp_list[k][l] >= '0' ) || _tmp_list[k][l] == '-' ) ) 
                _is_num = false;
            if( !( k == _tmp_list.length() - 1 && _is_num ) ){
              int id = flds.find( _tmp_list[k] );
              if( typs[id] != Type::ARRAY ){
                string error("cant get agregat funcion if field ");
                error += _tmp_list[k];
                error += " in equasion ";
                error += expanded_cols[j];
                std::runtime_error( error.c_str() );
              }
              _tmp_val.add( rs[i][id] );
            }
          }
          int64_t *num = new int64_t(  compute_func( _tmp_val, expanded_cols[j] ));
          res_rs[i][j].set_value( *num );

        }else{
          int id = flds.find( expanded_cols[j] );
          res_rs[i][j] =  rs[i][id];
        }
      }
    }
    rs = res_rs;
  }





  //std::cout << "cols are " << cols << std::endl;
  for( int i = 0; i < cols.length(); i++ ){
    //std::cout << '!' << cols[i] << '!' << ' '; 
  }
  //std::cout << std::endl;

  //std::cout << "OUTPUT" << std::endl;
  if( is_top ){
    if( rs.length() > top_num ){
      for( int i = 0; i <= rs.length() - top_num; i++ ){
        rs.remove( rs.length() - 1 );
      }
    }
  }
  
  list< string > _flds;
  list< Type::Type > _typs;
  for( int i = 0; i < expanded_cols.length(); i++ ){
    _flds.add( expanded_cols[i] );
    _typs.add( rs[0][i].get_type() );
  }
  table _t;
  _t.objects = rs;
  _t.fields = _flds;
  _t.types = _typs;

  return _t;

}
