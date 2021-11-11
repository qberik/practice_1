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

bool comp( int a, int b ){
  return a < b;
}

int main(){
  list<int> a;

  a.add(4);
  a.add(4);
  a.add(3);
  a.add(2);
  a.add(1);

  a = a;

  cout << "# len fo list " << a.length() << "#" << endl;
  cout << "# Show list #" << endl;
  for( int i = 0; i < a.length(); i++ ){
    cout << i << " index, element " << a[i] << endl; 
  }
  

  a.sort( &comp );


  cout << "# Show sorted list #" << endl;
  for( int i = 0; i < a.length(); i++ ){
    cout << i << " index, element " << a[i] << endl; 
  }

  return 0;
}
