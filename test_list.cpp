#include <iostream>
#include "list.hpp"

using namespace std;

list< int > some_func(){
  list< int > x;
  x.add( 1 );
  x.add( 2 );
  x.add( 3 );
  return x;
}

int main(){
  list<int> a;

  list<int> q1;
  q1.add(0);
  q1.add(0);
  list<int> q2;
  q2.add(1);
  q2.add(0);


  a.add(0);
  a.add(1);
  a.add(2);
  a.add(3);
  a.add(4);
  a.add(6);

  a.insert( 5, 5 );

  a = a;
  a = q2;

  cout << "# len fo list " << a.length() << "#" << endl;
  cout << "# Show list #" << endl;

  for( int i = 0; i < a.length(); i++ ){
    cout << i << " index, element " << a[i] << endl; 
  }

  cout << "# find element in list #" << endl;
  int num = 1;
  cout << num << " in list on pos " << a.find( num ) << endl;

  a.remove(0);
  for( int i = 0; i < a.length(); i++ ){
    cout << i << " index, element " << a[i] << endl; 
  }

  cout << " q1 == q2 : " << ( q1 == q2 ) << endl;

  list<int> z;
  z = some_func();
  std::cout << z.length() << std::endl;
  for( int i = 0; i < z.length(); i++ ){
    std::cout << z[i] << std::endl;
  }
  return 0;
}
