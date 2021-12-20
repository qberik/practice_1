#if defined(_WIN64) || defined(_WIN32)
    #define WINDOWS
#else
    #define LINUX
#endif
#include <iostream>
#include <stdexcept>
#include <fstream>
#include "menu.hpp"
#include "input.hpp"
#include "type.hpp"
#include "table.hpp"
#include "list.hpp"
#include "value.hpp"
#include "string.hpp"
#include "select.cpp"
#ifdef WINDOWS
  #include <windows.h>
#endif

#define SEPARATOR_FOR_BINARY_FILES '\a'


int main(){
  #ifdef WINDOWS
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(1251);
  #endif 

  list< table > db;
  int selected = -1;

  bool preset = true;
  if( preset ){
    string nam( "TAT" );

    list< string > fld;
    string f1("A"); fld.add(f1);
    string f2("B"); fld.add(f2);
    string f3("C"); fld.add(f3);
    
    list< Type::Type > typ;
    typ.add( Type::INT );
    typ.add( Type::STRING );
    typ.add( Type::ARRAY );

    table t;
    t.set_name( nam );
    t.set_fields( fld );
    t.set_types( typ );

    int64_t v_1 = 123; value v1( v_1 );
    string *v_2 = new string("SOME"); value v2( *v_2 );
    list< int > v_3;
    v_3.add( 1 ); v_3.add( 2 ); v_3.add( 3 ); v_3.add( 4 );
    value v3( v_3 );
    list< value > o1;
    o1.add( v1 );
    o1.add( v2 );
    o1.add( v3 );

    int64_t v_4 = -9876543210; value v4( v_4 );
    string *v_5 = new string("qwerty-12345"); value v5( *v_5 );
    list< int > v_6;
    v_6.add( -1 ); v_6.add( -2 ); v_6.add( -3 ); v_6.add( 400 );
    value v6 ( v_6 );
    list < value > o2;
    o2.add( v4 );
    o2.add( v5 );
    o2.add( v6 );

    t.add( o1 );
    t.add( o2 );

    db.add( t );
    selected = 1;

  
  }


  bool exit = false;
  bool menu = false;

  clean_screen();
  do{
    print_menu();
    int ch = int_input();
    clean_screen();
    switch( ch ){
      case 1:{
              do{
              print_menu1();
              int ch = int_input();
              clean_screen();
              switch( ch ){
                case 1:{
                        if( db.length() == 0 ){
                          std::cout << "     Нет созданных таблиц\n" << std::endl;  
                        }else{
                          std::cout << "     Создано " << db.length() << " таблиц" << std::endl;
                          for( int i = 0; i < db.length(); i++ )
                            std::cout << "     Нормер:" << i+1 << " Имя:" << db[i].name << " Поля:" << db[i].fields << std::endl;
                        
                        }
                break;}
                case 2:{
                        if( db.length() == 0 ){
                          std::cout << "     Нет созданных таблиц\n" << std::endl;  
                        }else{
                          std::cout << "     Введите номер таблицы > ";
                          int id = int_input() - 1;
                          std::cout << "     После какого поля вставить новое? " << std::endl; 
                          std::cout << "     По умолчанию в конец (" << db[id].fields.length()  << ")" << std::endl; 
                          std::cout << "     Введите позицию поля > ";
                          int pos = int_input();
                          
                          std::cout << "     Введите имя поля > ";
                          string name; name = str_input().c_str();
                          string str_type; Type::Type type;
                          bool valid = false; value default_value;
                          do{
                            std::cout << "     Доступные типы:" << std::endl;
                            std::cout << "     INT STRING INT_ARRAY " << std::endl;
                            std::cout << "     Введите тип поля > ";
                            str_type = str_input().c_str();
                            if( str_type == "INT" ){
                              type = Type::INT;
                              int64_t val = 0;
                              default_value.set_value( val );
                              valid = true;
                            }
                            if( str_type == "STRING" ){
                              type = Type::STRING;
                              string val( "" );
                              default_value.set_value( val );
                              valid = true;
                            }
                            if( str_type == "INT_ARRAY" ){
                              type = Type::ARRAY;
                              list<int> val;
                              default_value.set_value( val );
                              valid = true;
                            }
                          }while( !valid );

                          db[id].fields.insert( pos, name );
                          db[id].types.insert( pos, type );

                          std::cout << "     Установить значения по умолчанию? (Д/Н) > ";
                          string choose; choose = str_input().c_str(); 
                          if( choose == "Д" || choose == "д" || choose == "Y" || choose == "y" ){
                            for( int i = 0; i < db[id].objects.length(); i++ )
                              db[id].objects[i].insert( pos, default_value );
                          }
                          if( choose == "Н" || choose == "н" || choose == "N" || choose == "n" || choose == "" ){
                            value empty_value;
                            for( int i = 0; i < db[id].objects.length(); i++ )
                              db[id].objects[i].insert( pos, empty_value );
                          }
                        }
                break;}
                case 3:{
                        if( db.length() == 0 ){
                          std::cout << "     Нет созданных таблиц\n" << std::endl;  
                        }else{
                          std::cout << "     Введите номер таблицы > ";
                          int id = int_input() - 1;
                          std::cout << "     Поля таблицы" << std::endl;
                          if( db[id].fields.length() <= 1 ){
                            std::cout << "     У таблицы должно быть хотя бы поле " << std::endl;
                            std::cout << "     Удаление полей невозможно " << std::endl;
                          }else{
                            std::cout << "     " << db[id].fields;
                            std::cout << "     Какое поле удалить?" << std::endl;
                            std::cout << "     Введите позицию поля > ";
                            int pos = int_input() - 1;
                            db[id].fields.remove( pos );
                            db[id].types.remove( pos );
                            for( int i = 0; i < db[id].objects.length(); i++ )
                              db[id].objects[i].remove( pos );
                          }
                        }
                break;}
                case 4:{
                        std::cout << "     Введите имя таблицы > ";
                        bool end = false; 
                        int fields_count = 0;
                        list< string > table_fields;
                        list< Type::Type > table_types;
                        string name; name = str_input().c_str();
                        while ( !end ){
                          bool expr = true;
                          string name("");
                          do{
                            std::cout << "     Введите имя поля или Enter для конца ввода" << std::endl;
                            std::cout << std::endl;
                            std::cout << "     Введите имя поля > ";
                            name = str_input().c_str();
                            expr =  ( name == "" && fields_count == 0 );
                            if( name == "" && fields_count == 0 )
                              std::cout << "     Задайте хотя бы 1 поле" << std::endl;
                          }while( expr );

                          if( name != "" ){
                            bool valid = false;
                            Type::Type type;
                            do{
                              std::cout << "     Доступные типы:" << std::endl;
                              std::cout << "     INT STRING INT_ARRAY " << std::endl;
                              std::cout << "     Введите тип поля > ";
                              string str_type; str_type = str_input().c_str(); 
                              if( str_type == "INT" ){
                                type = Type::INT;
                                valid = true;
                              }
                              if( str_type == "STRING" ){
                                type = Type::STRING;
                                valid = true;
                              }
                              if( str_type == "INT_ARRAY" ){
                                type = Type::ARRAY;
                                valid = true;
                              }
                            }while( !valid );
                            table_fields.add( name );
                            table_types.add( type );
                            fields_count++;
                          }
                          end = ( name == "" );
                        }
                        table t;
                        t.set_name( name );
                        t.set_fields( table_fields );
                        t.set_types( table_types );
                        db.add( t );

                break;}
                case 5:{
                        if( db.length() == 0 ){
                          std::cout << "     Нет созданных таблиц\n" << std::endl;  
                        }else{
                          std::cout << "     Введите нормер таблицы > ";
                          int id = int_input() - 1;
                          db.remove( id );
                        }
                break;}
                case 6:{
                        if( db.length() == 0 ){
                          std::cout << "     Нет созданных таблиц\n" << std::endl;  
                        }else{
                          std::cout << "     Введите нормер таблицы > ";
                          int id = int_input() - 1;
                          selected = id;
                          std::cout << "     Выбрана таблица " << db[id].name << " Поля:" << db[id].fields << std::endl;
                          
                        }
                break;}
                case 0:{
                        menu = true;
                break;}
              }
              }while( !menu ); menu = false;
      break;}
      case 2:{
              if( db.length() == 0 ){
                std::cout << "     Не создано ни одной таблицы " << std::endl;
                std::cout << "     Создайте хотя бы одну таблицу в пункте меню 1" << std::endl;
              }else if( selected == -1 ){
                std::cout << "     Не выбрана ни одна таблица из имеющихся" << std::endl;
                std::cout << "     Выберете требуемую таблицу в пункте меню 1" << std::endl;
              }else{
                do{
                print_menu2();
                int ch = int_input();
                clean_screen();
                switch( ch ){
                  case 1:{
                          std::cout << std::endl;
                          std::cout << "     Введите имя файла > ";
                          string filename; filename = str_input().c_str();
                          std::ofstream file( filename.c_str() );
                          print_table( db[selected], file );
                          file.close();
                  break;}
                  case 2:{
                          std::cout << std::endl;
                          std::cout << "     Введите имя файла > ";
                          string filename; filename = str_input().c_str();
                          std::ofstream file( filename.c_str() );
                          write_table( db[selected], file );
                          file.close();
                  break;}
                  case 3:{
                          std::cout << std::endl;
                          std::cout << "     Введите имя файла > ";
                          string filename; filename = str_input().c_str();
                          std::ofstream file( filename.c_str() );
                          write_table( db[selected], file, SEPARATOR_FOR_BINARY_FILES );
                          file.close();
                  break;}
                  case 4:{
                          bool file_not_exist = false;
                          std::ifstream file; 
                          do{
                            if( file_not_exist )
                              std::cout << "     Такого файла не существует " << std::endl;
                            std::cout << std::endl;
                            std::cout << "     Введите имя файла > ";
                            string filename; filename = str_input().c_str();
                            file.open( filename.c_str() );
                            file_not_exist = file.fail();
                          }while( file_not_exist );
                          table t;
                          try{ t = load_table( file ); }catch( std::runtime_error& err ){
                            std::cout << err.what() << std::endl;
                          }
                          db.add( t );
                          file.close();
                  break;}
                  case 5:{
                          bool file_not_exist = false;
                          std::ifstream file; 
                          do{
                            if( file_not_exist )
                              std::cout << "     Такого файла не существует " << std::endl;
                            std::cout << std::endl;
                            std::cout << "     Введите имя файла > ";
                            string filename; filename = str_input().c_str();
                            file.open( filename.c_str() );
                            file_not_exist = file.fail();
                          }while( file_not_exist );
                          table t;
                          try{ t = load_table( file, SEPARATOR_FOR_BINARY_FILES ); }catch( std::runtime_error& err ){
                            std::cout << err.what() << std::endl;
                          }
                          db.add( t );
                          file.close();
                  break;}
                  case 6:{
                          bool file_not_exist = false;
                          std::ifstream file; 
                          do{
                            if( file_not_exist )
                              std::cout << "     Такого файла не существует " << std::endl;
                            std::cout << std::endl;
                            std::cout << "     Введите имя исходного файла > ";
                            string filename; filename = str_input().c_str();
                            file.open( filename.c_str() );
                            file_not_exist = file.fail();
                          }while( file_not_exist );
                          std::cout << "     Введите имя конечного файла > ";
                          string filename1; filename1 = str_input().c_str();
                          table t;
                          try{ t = load_table( file ); }catch( std::runtime_error& err ){
                            std::cout << err.what() << std::endl;
                          }
                          file.close();
                          std::ofstream file1( filename1.c_str(), std::ios::binary  );
                          write_table( t, file1, SEPARATOR_FOR_BINARY_FILES );
                          file1.close();
                  break;}
                  case 7:{
                          bool file_not_exist = false;
                          std::ifstream file; 
                          do{
                            if( file_not_exist )
                              std::cout << "     Такого файла не существует " << std::endl;
                            std::cout << std::endl;
                            std::cout << "     Введите имя исходного файла > ";
                            string filename; filename = str_input().c_str();
                            file.open( filename.c_str() );
                            file_not_exist = file.fail();
                          }while( file_not_exist );
                          std::cout << "     Введите имя конечного файла > ";
                          string filename1; filename1 = str_input().c_str();
                          table t;
                          try{ t = load_table( file, SEPARATOR_FOR_BINARY_FILES ); }catch( std::runtime_error& err ){
                            std::cout << err.what() << std::endl;
                          }
                          file.close();
                          std::ofstream file1( filename1.c_str() );
                          write_table( t, file1 );
                          file1.close();
                  break;}
                  case 0:{
                          menu = true;
                  break;}
                }
                }while( !menu ); menu = false;
              }
      break;}
      case 3:{
              print_table( db[selected] );
      break;}
      case 4:{
              do{
              print_menu4();
              int ch = int_input();
              clean_screen();
              switch( ch ){
                case 1:{
                        string rq; rq = "SELECT * FROM ";
                        rq += db[selected].name;
                        std::cout << "     Запрос по умолчанию: " << rq;
                        std::cout << std::endl;
                        std::cout << "     Результат" << std::endl;
                        table t;
                        try{ t = sql( db, rq );  }catch( std::runtime_error &err ){
                          std::cout << err.what() << std::endl;
                        }
                        print_table( t );
                break;}
                case 2:{
                        std::cout << "     Введите запрос > ";
                        string rq; rq = str_input().c_str();
                        std::cout << std::endl;
                        std::cout << "     Результат" << std::endl;
                        table t;
                        try{ t = sql( db, rq );  }catch( std::runtime_error &err ){
                          std::cout << err.what() << std::endl;
                        }
                        print_table( t );
                break;}
                case 0:{
                        menu = true;
                break;}
              }
              }while( !menu ); menu = false;
      break;}
      case 5:{
              do{
              print_menu5();
              int ch = int_input();
              clean_screen();
              switch( ch ){
                case 1:{
                        print_table( db[selected] );
                break;}
                case 2:{
                        list< value > obj;
                        for( int i = 0; i < db[selected].fields.length(); i++ ){
                          std::cout << "     Введите " << ( i + 1 ) << "-е поле объекта " << std::endl;
                          switch( db[selected].types[i] ){
                            case Type::INT:{
                                            std::cout << "     Тип поля Число" << std::endl;
                                            std::cout << "     Введите элемент > ";
                                            int64_t num = int_input();   
                                            value *v = new value( num );
                                            obj.add( *v );
                            break;} 
                            case Type::STRING:{
                                            std::cout << "     Тип поля Срока" << std::endl;
                                            std::cout << "     Введите элемент > ";
                                            string s; s = str_input().c_str();
                                            value *v = new value( s );
                                            obj.add( *v );
                            break;} 
                            case Type::ARRAY:{
                                            std::cout << "     Тип поля Массив\n     Вводите числа через пробел" << std::endl;
                                            std::cout << "     Введите элемент > ";
                                            list< int > arr = arr_input();
                                            value *v = new value( arr );
                                            obj.add( *v );
                            break;} 
                          }
                        }
                        db[selected].add( obj );
                break;}
                case 3:{
                        std::cout << "     Введите номер записи, который нужно заменить " << std::endl;
                        std::cout << std::endl;
                        std::cout << "     Номер записи > ";
                        int id = int_input() - 1;
                        list< value > obj;
                        for( int i = 0; i < db[selected].fields.length(); i++ ){
                          std::cout << "     Введите " << ( i + 1 ) << "-е поле нового объекта " << std::endl;
                          switch( db[selected].types[i] ){
                            case Type::INT:{
                                            std::cout << "     Тип поля Число" << std::endl;
                                            std::cout << "     Введите элемент > ";
                                            int64_t num = int_input();   
                                            value *v = new value( num );
                                            obj.add( *v );
                            break;} 
                            case Type::STRING:{
                                            std::cout << "     Тип поля Срока" << std::endl;
                                            std::cout << "     Введите элемент > ";
                                            string s; s = str_input().c_str();
                                            value *v = new value( s );
                                            obj.add( *v );
                            break;} 
                            case Type::ARRAY:{
                                            std::cout << "     Тип поля Массив\n     Вводите числа через пробел" << std::endl;
                                            std::cout << "     Введите элемент > ";
                                            list< int > arr = arr_input();
                                            value *v = new value( arr );
                                            obj.add( *v );
                            break;} 
                          }
                        }
                        db[selected].edit( id, obj );                         
                break;}
                case 4:{
                        std::cout << "     Введите номер записи, который нужно заменить " << std::endl;
                        std::cout << std::endl;
                        std::cout << "     Номер записи > ";
                        int id = int_input() - 1;
                        db[selected].remove( id );
                break;}
                case 5:{
                        std::cout << "     Таблица имеет поля" << std::endl;
                        std::cout << "     " << db[selected].fields << std::endl;
                        std::cout << "     Поля имеют типы" << std::endl;
                        std::cout << "     ";
                        for( int i = 0; i < db[selected].fields.length(); i++ ){
                          switch( db[selected].types[i] ){
                            case Type::INT:{
                                            std::cout << "число ";
                            break;}
                            case Type::STRING:{
                                            std::cout << "строка ";
                            break;}
                            case Type::ARRAY:{
                                            std::cout << "массив ";
                            break;}
                          }
                        }
                        std::cout << std::endl;
                        std::cout << "     Сортировка возможна по полям типов: число, строка " << std::endl;
                        std::cout << "     Введите номер поля > ";
                        int id = int_input() - 1;
                        std::cout << "     Сотрировать прямо или обратно > ";
                        string s; s = str_input().c_str();
                        bool rev = false;
                        if( s == "обратно" || s == "Обратно" ){
                          rev = true; 
                        }
                        string rq("SELECT * FROM ");
                        rq += db[selected].name;
                        rq += " ORDER BY ";
                        rq += db[selected].fields[id];
                        if( rev )
                          rq += " DESC";
                        table t;
                        try{ t = sql( db, rq );
                        db[selected] = t; }catch( std::runtime_error &err ){
                          std::cout << err.what() << std::endl;
                        }
                break;}
                case 0:{
                        menu = true;
                break;}
              }
              }while( !menu ); menu = false;
      break;}
      case 0:{
              exit = true;

      break;}
    
    
    }
  }while( !exit );
  return 0;
}
