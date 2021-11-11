#include "menu.hpp"
#include <iostream>
#include <cmath>

#include "string.hpp"
#include "list.hpp"

#define cout std::cout
#define endl std::endl


void print_menu(){
  cout << "      База Данных Version 1.0   " << endl;
  cout << "    Создал: Чузов М. Ю. ИУК12-Б " << endl;
  cout << "                                " << endl;
  cout << "       1. Создать таблицу       " << endl;
  cout << "       2. Вывести таблицу       " << endl;
  cout << "       3. Добавить запись       " << endl;
  cout << "       4. Изменить запись       " << endl;
  cout << "       5. Удалить запись        " << endl;
  cout << "       6. Выйти из программы    " << endl;
  cout << "                                " << endl;
  cout << "     Введите номер пункта > ";
  
}

void item1_stage1(){
  cout << "                                  " << endl;
  cout << "  Введите имя поля и задайте тип  " << endl;
  cout << "  или нажмите Enter для завершения" << endl;
  cout << "                                  " << endl;

}



void print_center( int64_t num, int width ){
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
    cout << num;
  }else{
    int space = width - len;
    int left = floor( space / 2.0 );
    int right = ceil( space / 2.0 );
    for( int i = 0; i < left; i++ ){
      cout << ' ';
    }
    cout << num;
    for( int i = 0; i < right; i++ ){
      cout << ' ';
    }
  }

}

void print_center( string str, int width ){
  int len = str.length();

  if( len > width ){
    cout << str.c_str();
  }else{
    int space = width - len;
    int left = floor( space / 2.0 );
    int right = ceil( space / 2.0 );

    for( int i = 0; i < left; i++ ){
      cout << ' ';
    }
    cout << str.c_str();
    for( int i = 0; i < right; i++ ){
      cout << ' ';
    }
  }

}
