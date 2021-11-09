//#include <iostream>
#include "menu.hpp"
#include "input.hpp"
#include "type.hpp"
#include "table.hpp"
#include "list.hpp"
#include "value.hpp"
#include "string.hpp"


int main(){
 
  bool exit = false;

  table t;

  bool table_was_created = false;
  
  list< Type > tp;
  list< string > f;
  
  string p1("Фамилия");        f.add(p1); tp.add( STRING );
  string p2("Имя");            f.add(p2); tp.add( STRING );
  string p3("Отчество");       f.add(p3); tp.add( STRING );
  string p4("Год рождения");   f.add(p4); tp.add( INT );
  string p5("Курс");           f.add(p5); tp.add( STRING );
  string p6("Оценки");         f.add(p6); tp.add( STRING );

  t.set_fields( f );
  t.set_types( tp );
  table_was_created = true;


  list< Type > _t;
  list< string > _f;
  string _s;

  do{
    print_menu();
    switch( int_input() ){
      case 1:{
        item1_stage1();
        int end = -1;
        _t.clear();
        _f.clear();

        while ( end != 1 ){
          bool valid = false; 
          do{
            std::cout << std::endl;
            std::cout << "  Введите имя поля или Enter >";
            _s = str_input().c_str();
            if( _s == "" ){
              if( end == -1 ){
                std::cout << "  Задайте хотя-бы 1 поле" << std::endl;
              }else{

                std::cout << std::endl;
                end = 1;
              }
            }else{
              valid = true;
            }
          }while( !valid  && end != 1 );
          if( end != 1 ){
          
          _f.add( _s );
          valid = false;
          do{
            std::cout << std::endl;
            std::cout << "  Доступные типы:" << std::endl;
            std::cout << "  INT STRING INT_ARRAY " << std::endl;
            std::cout << "  Введите тип > ";
            _s = str_input().c_str();
            if( _s == "INT" ){
              _t.add( INT );
              valid = true;
            }
            if( _s == "STRING" ){
              _t.add( STRING );
              valid = true;
            }
            if( _s == "INT_ARRAY" ){
              _t.add( ARRAY );
              valid = true;
            }
          }while( !valid );

          if( end = -1 )
            end = 0;
          }
        }
        t.set_fields( _f );
        t.set_types( _t );
        table_was_created = true;

      }break;
      case 2:{
        // ВЫВОД
        if( table_was_created ){
          int col = t.fields.length();
          /* 
          list<int>width;
          for( int i = 0; i < col; i++ ){
            width.add( t.fields[i].length() ); 
          }
          std::cout << "+";
          for( int i = 0; i < col; i++ ){
            for( int j = 0; j < width[i]; j++ ){
              std::cout << "-";
            } 
            std::cout << "+";
          }
          */
          std::cout << std::endl;
          std::cout << "|";
          for( int i = 0; i < col; i++ ){
            std::cout << t.fields[i].c_str() << "|";
          }
          std::cout << std::endl;
          value val;
          for( int i = 0; i < t.objects.length(); i++ ){
            std::cout << "|";
            for( int j = 0; j < t.fields.length(); j++ ){
              val = t.objects[i][j];
              switch( val.get_type() ){
                case INT:
                  std::cout << val.get_int();
                  break;
                case STRING:
                  std::cout << val.get_string().c_str();
                  break;
                case ARRAY:
                  break;
              
              }
              std::cout << "|";
            }
            std::cout << std::endl;
          }


        
        }else{
          std::cout << "\n  Сначала создадите таблицу\n" << std::endl;
        }

        }break;

      case 3:{
        // Добавление записи
        list< value > *obj = new list< value >();
        for( int i = 0; i < t.fields.length(); i++ ){
          std::cout << std::endl;
          std::cout << "  Имя поля " << t.fields[i].c_str() << std::endl;
          switch( t.types[i] ){
            case INT:
              _s = "Int";
              break;
            case STRING:
              _s = "String";
              break;
            case ARRAY:
              _s = "Array";
              break;
          }
          std::cout << "  Тип поля " << _s.c_str() << std::endl;

        value *v;
        switch( t.types[i] ){
          case INT:
            std::cout << "  Введите число > ";
            v = new value( int_input() );
            break;
          case STRING:{
            string *str = new string();
            std::cout << "  Введите строку > ";
            _s = str_input().c_str();
            *str = _s;
            v = new value( *str );
            }break;
          case ARRAY:
            //v = new value( int_input() );
            break;
        }

        obj->add( *v );

        }
          t.add( *obj ); 
          std::cout << std::endl;
        }break;
      case 6:
        exit = true;
        break;

    }
  }while( !exit );



  return 0;
}
