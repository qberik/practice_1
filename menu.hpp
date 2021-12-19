#ifndef MENU_HPP
#define MENU_HPP
#include "string.hpp"
#include "list.hpp"
#include "table.hpp"
#include <iostream>

void print_menu( );
void print_menu1( );
void print_menu2( );
void print_menu4( );
void print_menu5( );
void item1_stage1();

void print_table( table &, std::ostream & = std::cout );

void write_table( table &, std::ostream & = std::cout , char = '\n');

table load_table( std::istream &, char = '\n' );

void clean_screen();

void print_center( int64_t, int width, std::ostream & = std::cout );
void print_center( string, int width, std::ostream & = std::cout);
void print_center( list<int>, int width, std::ostream & = std::cout );

#endif
