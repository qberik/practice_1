#include <iostream>
#include "string.hpp"

int main(){

  string s("Строка из тридцати двух символов");

  std::cout << s.c_str() << " len is " << s.length() << std::endl;
  
  return 0;
}
