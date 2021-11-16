#include <iostream>
#include "string.hpp"
#include "list.hpp"

int main(){
  
  string s("   Тестовая строка с пробелами в начале и в конце     ");
  string s1 = s;

  std::cout << s.c_str() << "# len is " << s.length() << std::endl;

  s1.strip();
  std::cout << "strip string " << s1.c_str() << " len is " << s1.length() << std::endl;

  list<string> l = s.split();
  std::cout << "split string" << std::endl;
  for( int i = 0; i < l.length(); i++ ){
    std::cout << l[i].c_str() <<  std::endl;
  }
  
  string st("ASD");

  std::cout << st[-1] << std::endl;
  std::cout << st[2] << std::endl;

  return 0;
}
