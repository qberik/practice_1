#include <stdexcept>
#include "value.hpp"
#include "list.hpp"
#include "string.hpp"
#include "type.hpp"

value::value( ){ }

value::value( const int64_t& int_ptr ): type(Type::INT) {
  data.int_ptr = & ( const_cast<int64_t&>(int_ptr) );
}

value::value( string& string_ptr ): type(Type::STRING) {
  data.string_ptr =  &string_ptr ;
}

value::value( list<int>& array_ptr ): type(Type::ARRAY){
  data.array_ptr = &array_ptr;
}


void value::set_value( int64_t& int_ptr ){
  type = Type::INT;
  data.int_ptr = & (const_cast<int64_t&>(int_ptr) );
}

void value::set_value( string& string_ptr ){
  type = Type::STRING;
  data.string_ptr = &string_ptr;
}

void value::set_value( list<int>& array_ptr ){
  type = Type::ARRAY;
  data.array_ptr = &array_ptr;
}


Type::Type value::get_type(){
  return type;
}


int64_t& value::get_int(){
  if(type != Type::INT)
    throw std::runtime_error("value is not an int");
  return *data.int_ptr;
}

string& value::get_string(){
  if(type != Type::STRING)
    throw std::runtime_error("value is not an string");
  return *data.string_ptr;
}

list<int>& value::get_array(){
  if(type != Type::ARRAY)
    throw std::runtime_error("value is not an array");
  return *data.array_ptr;
}


bool value::operator==( value& other){
  if ( value::get_type() != other.get_type() )
    return false;
  bool flag = false;
  switch(type){
    case Type::INT:
      flag = ( value::get_int() == other.get_int() );
      break;
    case Type::STRING:
      flag = ( value::get_string() == other.get_string() );
      break;
    case Type::ARRAY:
      flag = ( value::get_array() == other.get_array() );
      break;
    default:
      throw std::runtime_error("undefined value type in comparison");
  }
  return flag;
}

bool value::operator!=( value& other){
  return !value::operator==( other );
}
