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
  
  string s;
  std::cout << "Введи что-то 1 раз" << std::endl;
  s = raw_input();
  std::cout << "Сейчас попробую вывести" << std::endl;
  std::cout << s.c_str() << std::endl;
  std::cout << "А сейчас выведу цифровые коды" << std::endl;
  for( int i = 0; s[i] != '\0'; i++ ){
    std::cout << (int)s[i] << ' '; 
  }
  std::cout << std::endl;

  return 0;
}
