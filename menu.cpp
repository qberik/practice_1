#if defined(_WIN64) || defined(_WIN32)
    #define WINDOWS
#else
    #define LINUX
#endif

#include "menu.hpp"
#include <iostream>
#include <cmath>

#include "input.hpp"
#include "string.hpp"
#include "list.hpp"

#include "table.hpp"
#include <ostream>
#include <stdexcept>

#define cout std::cout
#define endl std::endl




void clean_screen(){
  #ifdef WINDOWS
  system( "cls" );
  #endif 
  #ifdef LINUX
  system( "clear" );
  #endif
}

void print_menu(){
  cout << "      База Данных Version 1.0   " << endl;
  cout << "    Создал: Чузов М. Ю. ИУК12-Б " << endl;
  cout << "                                " << endl;
  cout << "     1. Управление таблицами    " << endl;
  cout << "     2. Работа с файлами        " << endl;
  cout << "     3. Вывести таблицу         " << endl;
  cout << "     4. Создание запроса        " << endl;
  cout << "     5. Изменение таблицы       " << endl;
  cout << "     0. Выйти из программы      " << endl;
  cout << "                                " << endl;
  cout << "     Введите номер пункта > ";
  
}

void print_menu1(){
  cout << "                                " << endl;
  cout << "     1. Список таблиц           " << endl;
  cout << "     2. Добавление полей        " << endl;
  cout << "     3. Удаление полей          " << endl;
  cout << "     4. Создание таблицы        " << endl;
  cout << "     5. Удаление таблицы        " << endl;
  cout << "     6. Выбор рабочей таблицы   " << endl;
  cout << "     0. Главное меню            " << endl;
  cout << "                                " << endl;
  cout << "     Введите номер пункта > ";
}

void print_menu2(){
  cout << "                                                   " << endl;
  cout << "     1. Печать таблицы в файл                      " << endl;
  cout << "     2. Вывести таблицу в текстовый файл           " << endl;
  cout << "     3. Вывести таблицу в бинарный файл            " << endl;
  cout << "     4. Загрузить таблицу из текстого файла        " << endl;
  cout << "     5. Загрузить таблицу из бинарного файла       " << endl;
  cout << "     6. Конвертировать текстового в бинарный файл  " << endl;
  cout << "     7. Конвертировать бинарный в текстовый файл   " << endl;
  cout << "     0. Главное меню                               " << endl;
  cout << "                                                   " << endl;
  cout << "     Введите номер пункта > ";
}

void print_menu4(){
  cout << "                                      " << endl;
  cout << "     1. Выполнить запрос по умолчанию " << endl;
  cout << "     2. Создать свой запрос           " << endl;
  cout << "     0. Главное меню                  " << endl;
  cout << "                                      " << endl;
  cout << "     Введите номер пункта > "; 

}

void print_menu5(){
  cout << "                                " << endl;
  cout << "     1. Выбрать таблицу         " << endl;
  cout << "     2. Довабить запись         " << endl;
  cout << "     3. Изменить запись         " << endl;
  cout << "     4. Удалить запись          " << endl;
  cout << "     5. Сортировка записей      " << endl;
  cout << "     0. Главное меню            " << endl;
  cout << "                                " << endl;
  cout << "     Введите номер пункта > ";
}

void item1_stage1(){
  cout << "                                  " << endl;
  cout << "  Введите имя поля и задайте тип  " << endl;
  cout << "  или нажмите Enter для завершения" << endl;
  cout << "                                  " << endl;

}




table load_table( std::istream &in, char sep ){
  
  string s(""); 
  char ch;
  while( EOF != ( ch = in.get() ) ){
    s += ch;
    //cout << ch << endl;
  }

  list< string > tokens = s.split( sep ); // << endl;
  int index = 0;
  string DBS = tokens[index++];
  if ( DBS != "DBS")
    throw std::runtime_error("     Неверный файл базы данных");
  int col = string_to_int( tokens[index++] );
  string name = tokens[index++];
  list< string > flds;
  list< Type::Type > typs;
  for( int i = 0; i < col; i++ )
    flds.add( tokens[index++] );
  for( int i = 0; i < col; i++ )
    typs.add( static_cast<Type::Type> ( string_to_int( tokens[index++] ) ) );

  list< list< value > > objs;
  while( index < tokens.length() ){
    list< value > obj;
    for( int i = 0; i < col; i++ ){
      obj.clear();
      switch( typs[i] ){
        case Type::INT:{
          int64_t num = string_to_int( tokens[index++] );
          value v( num );
          obj.add( v );    
        break;} 
        case Type::STRING:{
          string *str = new string( tokens[index++].c_str() );
        break;} 
        case Type::ARRAY:{
          list< int > *arr = new list< int >;
          string val( tokens[index++].c_str() );
          string unbracked("");
          for ( int j = 1; j < val.length() - 1; j++ )
            unbracked += val[j];
          list< string > vals = unbracked.split(',');
          for( int j = 0; j < vals.length(); j++ )
            arr->add( string_to_int( vals[j] ) );
          value v( *arr );
          obj.add( v );
        break;} 
      }
    }
    objs.add(obj);
  }

  /*
  cout << col << endl;
  cout << name << endl;
  cout << flds << endl;
  cout << typs << endl;
  cout << objs << endl;
  */
  table t;
  t.name = name;
  t.fields = flds;
  t.types = typs;
  t.objects = objs;
  return t;
}




void write_table( table &t , std::ostream & out , char sep ){
  out << "DBS" << sep;

  int col = t.fields.length();
  out << col << sep;
  out << t.name << sep;

  for( int i = 0; i < col; i++ )
    out << t.fields[i] << sep;
  
  for( int i = 0; i < col; i++ )
    out << t.types[i] << sep;

  for( int i = 0; i < t.objects.length(); i++ )
    for( int j = 0; j < col; j++ )
      out << t.objects[i][j] << sep;

}



void print_table( table &t, std::ostream & out ){

  int col = t.fields.length();
  
  list < int > width;
  for( int i = 0; i < col; i++ ){
    width.add( t.fields[i].length() ); 
  }
  
  for( int i = 0; i < t.objects.length(); i++ ){
    for( int j = 0; j < col; j++ ){
      int len = 0;
      switch( t.objects[i][j].get_type() ){
        case Type::INT:{
                        int64_t num = t.objects[i][j].get_int();
                        while( num ){
                          len++;
                          num /= 10;
                        }
                        if( t.objects[i][j].get_int() == 0 ){
                        len = 1;
                        }
                        if( t.objects[i][j].get_int() < 0 ){
                          len += 1;
                        }
        break;} 
        case Type::STRING:{
                        len = t.objects[i][j].get_string().length();
        break;} 
        case Type::ARRAY:{
                        list<int> arr_tmp = t.objects[i][j].get_array();
                        for( int k = 0; k < arr_tmp.length(); k++ ){
                          int num = arr_tmp[k];
                          int _num = num;
                          len++;
                          while( _num ){
                            len++;
                            _num/=10;
                          }
                          if ( num == 0 )
                            len++;
                          if ( num <  0 )
                            len++;
                        }
                        len--;
        break;} 
        case Type::NONE:{
                        len = 4;
        break;} 
      
      }
      if( len > width[j] )
        width[j] = len;
    } 
  }
  

  out << "╔";
  for( int i = 0; i < col; i++ ){
    for( int j = 0; j < width[i]; j++ ){
      out << "═";
    } 
    out <<  ( ( i + 1 == col ) ? "╗" : "╤" ) ;
  }
  out << endl;
  
  out << "║";
  for( int i = 0; i < col; i++ ){
    print_center( t.fields[i], width[i], out );
    out << ( ( i + 1 == col ) ? "║" : "│" );
  }
  out << endl;

  value val;
  for( int i = 0; i < t.objects.length(); i++ ){
    out << "╟";
    for( int i = 0; i < col; i++ ){
      for( int j = 0; j < width[i]; j++ ){
        out << "─";
      } 
      out <<  ( ( i + 1 == col ) ? "╢" : "┼" ) ;
    }
    out << endl;

    out << "║";
    for( int j = 0; j < t.fields.length(); j++ ){
      val = t.objects[i][j];
      switch( val.get_type() ){
        case Type::INT:
          print_center( val.get_int(), width[j], out );
          break;
        case Type::STRING:
          print_center( val.get_string(), width[j], out );
          break;
        case Type::ARRAY:
          print_center( val.get_array(), width[j], out );
          break;
      
      }
      out << ( ( j + 1 == col ) ? "║" : "│" );
    }
    out << endl;

  }

  out << "╚";
  for( int i = 0; i < col; i++ ){
    for( int j = 0; j < width[i]; j++ ){
      out << "═";
    } 
    out <<  ( ( i + 1 == col ) ? "╝" : "╧" ) ;
  }
  out << endl;



}


void print_center( int64_t num, int width, std::ostream & out  ){
  int len = 0;
  int64_t _num = num;
  while( _num ){
    len++;
    _num /= 10;
  }
  if ( num == 0 )
    len = 1;
  if ( num < 0 )
    len++;
  
    
  if( len > width ){
    out << num;
  }else{
    int space = width - len;
    int left = floor( space / 2.0 );
    int right = ceil( space / 2.0 );
    for( int i = 0; i < left; i++ ){
      out << ' ';
    }
    out << num;
    for( int i = 0; i < right; i++ ){
      out << ' ';
    }
  }

}

void print_center( string str, int width, std::ostream & out  ){
  int len = str.length();

  if( len > width ){
    out << str.c_str();
  }else{
    int space = width - len;
    int left = floor( space / 2.0 );
    int right = ceil( space / 2.0 );

    for( int i = 0; i < left; i++ ){
      out << ' ';
    }
    out << str.c_str();
    for( int i = 0; i < right; i++ ){
      out << ' ';
    }
  }

}

void print_center( list<int> l, int width, std::ostream & out  ) {
  int len = 0;
  for( int i = 0; i < l.length(); i++ ){
    int num = l[i];
    int _num = num;
    len++;
    while( _num ){
      _num/=10;
      len++;
    }
    if( num == 0 )
      len += 1;
    if( num <  0 )
      len += 1;
  }
  if( l.length() != 0 )
    len--; // without last space

  if( len > width ){
    for( int i = 0; i < width; i++ )
      out << "#";
  }else{
    int space = width - len;
    int left = floor( space / 2.0 );
    int right = ceil( space / 2.0 );

    for( int i = 0; i < left; i++ ){
      out << ' ';
    }
    for( int i = 0; i < l.length() - 1; i++ ){
      out << l[i] << ' '; 
    }
    if( l.length() > 0 )
      out << l[l.length()-1];
    for( int i = 0; i < right; i++ ){
      out << ' ';
    }
  }

}









