#include "list.hpp"
#include "value.hpp"

int main(){

  value a( 2 );
  string bs("Bruh");
  value b( bs );
  string zs("Zruh");
  value z( zs );

  z.get_string()[0] = 'B';

  std::cout << ( z == b ) << std::endl;

  return 0;
}
