#include <iostream>
#include "list.hpp"
#include "string.hpp"

//using namespace std;
//
#define cout std::cout
#define endl std::endl

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



  list<string> l;
  string st("A");
  l.add( st );
  st = "B";
  l.add( st );

  cout << "# len fo list " << l.length() << "#" << endl;
  cout << "# Show list #" << endl;

  for( int i = 0; i < l.length(); i++ ){
    cout << i << " index, element " << l[i].c_str() << endl; 
  }

  string fnd( "C" );
  cout << "find \"C\" at " << l.find( fnd ) << endl;

  return 0;
}
