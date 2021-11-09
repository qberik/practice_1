#include <iostream>
#include "string.hpp"

int main(){

  string s("Привет123");

  for( int i = 0; i < s.length(); i++ ){
    std::cout << s[i] << std::endl;
  }

  return 0;
}
