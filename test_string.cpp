#if defined(_WIN64) || defined(_WIN32)
    #define WINDOWS
#else
    #define LINUX
#endif

#include <iostream>
#include "string.hpp"
#include "list.hpp"
#include "input.hpp"

#ifdef WINDOWS
  #include <windows.h>
#endif

int main(){
  #ifdef WINDOWS
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(1251);
    std::cout << "WIN" << std::endl;
  #endif 
  
  string s1;

  string s2;

  std::cout << "Введи что-то 2 раза" << std::endl;
  s1 = raw_input();

  s2 = str_input().c_str();

  std::cout << "Сейчас попробую вывести" << std::endl;
  std::cout << s1.c_str() << std::endl;

  std::cout << s2.c_str() << std::endl;

  return 0;
}
