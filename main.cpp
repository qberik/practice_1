#if defined(_WIN64) || defined(_WIN32)
    #define WINDOWS
#else
    #define LINUX
#endif
//#include <iostream>
#include "menu.hpp"
#include "input.hpp"
#include "type.hpp"
#include "table.hpp"
#include "list.hpp"
#include "value.hpp"
#include "string.hpp"
#ifdef WINDOWS
  #include <windows.h>
#endif

int main(){
  #ifdef WINDOWS
    SetConsoleOutputCP(CP_UTF8);
  #endif 
  bool exit = false;

  table t;
  string table_name("Ученики");
  t.set_name( table_name );
  bool table_was_created = false;
  
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


  list< Type::Type > _t;
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
            std::cout << "  Введите имя поля или Enter > ";
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
            std::cout << "  Type::INT Type::STRING Type::INT_Type::ARRAY " << std::endl;
            std::cout << "  Введите тип > ";
            _s = str_input().c_str();
            if( _s == "Type::INT" ){
              _t.add( Type::INT );
              valid = true;
            }
            if( _s == "Type::STRING" ){
              _t.add( Type::STRING );
              valid = true;
            }
            if( _s == "Type::INT_Type::ARRAY" ){
              _t.add( Type::ARRAY );
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
           
          list<int>width;
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
                  }break;
                case Type::STRING:
                  len = t.objects[i][j].get_string().length();
                  break;
                case Type::ARRAY:
                  list<int> arr_tmp = t.objects[i][j].get_array();
                  for( int i = 0; i < arr_tmp.length(); i++ ){
                    int num = arr_tmp[i];
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
                  break;
              

              }
              if( len > width[j] )
                width[j] = len;
            }
          }

          /* табличка должна выглядить как-то так
           ╔════════╤═══╗
           ║LONGBRUH│ A ║
           ╟────────┼───╢
           ║  BRUH1 │ABC║
           ╟────────┼───╢
           ║  BRUH2 │ C ║
           ╚════════╧═══╝ 
          */

          std::cout << "╔";
          for( int i = 0; i < col; i++ ){
            for( int j = 0; j < width[i]; j++ ){
              std::cout << "═";
            } 
            std::cout <<  ( ( i + 1 == col ) ? "╗" : "╤" ) ;
          }
          std::cout << std::endl;
          
          std::cout << "║";
          for( int i = 0; i < col; i++ ){
            print_center( t.fields[i], width[i] );
            std::cout << ( ( i + 1 == col ) ? "║" : "│" );
          }
          std::cout << std::endl;

          value val;
          for( int i = 0; i < t.objects.length(); i++ ){
            std::cout << "╟";
            for( int i = 0; i < col; i++ ){
              for( int j = 0; j < width[i]; j++ ){
                std::cout << "─";
              } 
              std::cout <<  ( ( i + 1 == col ) ? "╢" : "┼" ) ;
            }
            std::cout << std::endl;

            std::cout << "║";
            for( int j = 0; j < t.fields.length(); j++ ){
              val = t.objects[i][j];
              switch( val.get_type() ){
                case Type::INT:
                  print_center( val.get_int(), width[j] );
                  break;
                case Type::STRING:
                  print_center( val.get_string(), width[j] );
                  break;
                case Type::ARRAY:
                  print_center( val.get_array(), width[j] );
                  break;
              
              }
              std::cout << ( ( j + 1 == col ) ? "║" : "│" );
            }
            std::cout << std::endl;

          }

          std::cout << "╚";
          for( int i = 0; i < col; i++ ){
            for( int j = 0; j < width[i]; j++ ){
              std::cout << "═";
            } 
            std::cout <<  ( ( i + 1 == col ) ? "╝" : "╧" ) ;
          }
          std::cout << std::endl;

        
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
            case Type::INT:
              _s = "Int";
              break;
            case Type::STRING:
              _s = "String";
              break;
            case Type::ARRAY:
              _s = "Array";
              break;
          }
          std::cout << "  Тип поля " << _s.c_str() << std::endl;

        value *v;
        switch( t.types[i] ){
          case Type::INT:{
            int64_t *int_tmp = new int64_t;
            std::cout << "  Введите число > ";
            *int_tmp = int_input();
            v = new value( *int_tmp );
            }break;
          case Type::STRING:{
            string *str = new string();
            std::cout << "  Введите строку > ";
            _s = str_input().c_str();
            *str = _s;
            v = new value( *str );
            }break;
          case Type::ARRAY:{
            std::cout << "  Введите числа через пробел > ";
            list<int> *arr_tmp = new list<int>;
            *arr_tmp = arr_input();
            v = new value( *arr_tmp );
            }break;
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
