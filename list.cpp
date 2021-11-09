#include <iostream>

template <typename T>
list<T>::list(){
  size = 0;
  head = nullptr;
}



template <typename T>
int list<T>::length() const{
  return size;
}


template <typename T>
void list<T>::add( T value ){
  Frame<T> *f = new Frame<T>();
  f -> data = value;
  f -> prev = head;
  head = f;
  size += 1;
}


template <typename T>
void list<T>::insert( int pos, T value ){
  Frame<T> *tmp = head;
  int endpos = size - pos - 1;
  for( int i = 0; i < endpos; i++ ){
    tmp = tmp -> prev;    
  } 

  Frame<T> *f = new Frame<T>();
  f -> data = value;
  f -> prev = tmp -> prev;
  tmp -> prev = f;

  size += 1;
}

template <typename T>
int list<T>::find( T value ){
  int index = -1;
  Frame<T> *f = head;
  for( int i = 0; i < size; i++ ){
    if( f -> data == value )
      index = i;
    f = f -> prev;
  }
  index = size - index - 1;
  return index;
}

template <typename T>
T& list<T>::operator[]( int pos ) const{

  pos = size - pos - 1;
  Frame<T> *f = head;
  for( int i = 0; i < pos; i++ ){
    f = f -> prev;    
  }
  return f -> data;
}


template <typename T>
void list<T>::remove( int pos ){
  if( pos == size - 1 ){
    // тут утечка памяти
    // надо потом поправить
    head = head -> prev;
  }else{
    pos = size - pos - 2;
    Frame<T> *f = head, *tmp;
    for( int i = 0; i < pos; i++ ){
      f = f -> prev; 
    }
    // тут кстати тоже 
    f -> prev = f -> prev -> prev;
  }
    size -= 1;
}



template <typename T>
bool list<T>::operator==( list<T>& other ){
  if( list<T>::length() != other.length() )
    return false;

  bool eq = true;
  for( int i = 0; i < list<T>::length(); i++ ){
    if( list<T>::operator[](i) != other[i] )
     eq = false; 
  }
  return eq;
}




template <typename T>
void list<T>::clear(){
  // Здесь нужно очищать память
  size = 0;
  head = nullptr;
}

template <typename T>
list<T> list<T>::operator=( const list<T>& other ){
  if( this != &other ){
    list<T>::clear();
    for( int i = 0; i < other.length(); i++ ){
      list<T>::add( other[i] );
    } 
  }
  return *this;
}

