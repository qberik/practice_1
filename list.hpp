#ifndef LIST_H
#define LIST_H
/* Односвязный список, где
 * каждый элемент указывает
 * на предыдущий */
// TODO
// - написать деструктор, а то память течёт
#include <ostream>

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
    void add( T value, int pos );
    void insert( int pos, T value );

    void swap( int from, int to );
    void sort( bool(*compare)( T, T ) );
    
    template <typename _T>
    friend std::ostream& operator<< (std::ostream& out, const list<_T>& );

    int find( T value );
    int find( bool (*condition)( T ) );
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
