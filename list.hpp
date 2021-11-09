#ifndef LIST_H
#define LIST_H
/* Односвязный список, где
 * каждый элемент указывает
 * на предыдущий */
// TODO
// - написать деструктор, а то память течёт

template <typename T>
struct Frame{
   T data;
   Frame<T>* prev; 
};

template <typename T>
class list {
  public:
    list();


    int length() const;
    
    void add( T value );
    void insert( int pos, T value );


    int find( T value );
    T& operator[]( int pos ) const;

    void remove( int pos );

    bool operator==( list<T>& );
   
    void clear(); 
    list<T> operator=( const list<T>& );

  private:
  
    int size;
    Frame<T>* head;

};

#include "list.cpp"
#endif
