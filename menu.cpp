#include "menu.hpp"
#include <iostream>

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
