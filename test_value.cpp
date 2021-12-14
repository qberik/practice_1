#include "list.hpp"
#include "value.hpp"
#include "stdlib.h"
#include <iostream>

int main(){


  list<value> lv;
  value *v = new value[10];
  //int *num = new int[10];
  //int64_t *num = (int64_t*)malloc( sizeof(int64_t) * 10 );
  //for( int i = 0; i < 10; i++ ){
  //  *(num+i) = i; 
  //}
  for( int i = 0; i < 10; i++ ){
    int64_t *num = new int64_t(i);
    value v ( *num );
    lv.add( v );
    //lv.add( *(v+i) );
  }
  /*
  for( int i = 0; i < 10; i++ ){
    lv[i].set_value( *num ); 
  }*/

  //std::cout << v << std::endl;
  //std::cout << v << std::endl;
  std::cout << &lv[0].get_int() << std::endl;
  std::cout << &lv[1].get_int() << std::endl;
  std::cout << &lv[0] << std::endl;
  std::cout << &lv[1] << std::endl;

  std::cout << lv << std::endl;

  value *v1 = new value( 10 );

  lv[0] = *v1 ;

  std::cout << lv << std::endl;

  value *v2 = new value( 12 );

  lv[1] = *v2 ;

  std::cout << lv << std::endl;

  std::cout << &lv[0].get_int() << std::endl;
  std::cout << &lv[1].get_int() << std::endl;

  return 0;
}
