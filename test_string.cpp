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
  /*
  #ifdef WINDOWS
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(1251);
    std::cout << "WIN" << std::endl;
  #endif 
 
  char str[] = { -12, -5, -30 };

  char str2[100];

  cp1251_to_utf8( str2, str );

  std::cout << str2 << std::endl;

  for( int i = 0; str2[i] != '\0'; i++ ){
    std::cout << (int)str2[i] << ' '; 
  }
  std::cout << std::endl;

  */
  list<string> s;
  string str("SOME");
  s.add(str);
  s.add(str);
  s[0][0] = 's';
  s[1] += '_';
  std::cout << "I print " << s[0].find("OM") << " AND " << s[1] << std::endl;

  string test("");
  std::cout << "Len of empty string is " << test.length() << std::endl;
  return 0;
}
