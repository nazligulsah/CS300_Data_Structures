//
//  stack.cpp
//  cs300
//
//  Created by Gülşah Önen on 25.03.2021.
//

#ifndef stack_h
#define stack_h
#include <vector>
#include <iostream>
using namespace std;
template<class T>         // template for struct
struct StackNode
{
  T x_coordinate;
  T y_coordinate; // int should be T
  bool *visited;
  bool *has_pawn;

  StackNode<T>(){
    x_coordinate = 1;
    y_coordinate = 1;
  }
};
template <class T>
       class Stack
       {
         public:
           Stack( );

           bool isEmpty( ) const;
           bool isFull( ) const;
           const T & top( ) const;

           void makeEmpty( );
           void pop( );
           void push( const T & x );
           T topAndPop( );

         private:
           vector<T> theArray;
           int  topOfStack;
       };


#endif /* stack_h */

template <class T>
Stack<T>::Stack(  )
 {
    topOfStack = -1;
}
template <class T>
bool Stack<T>::isEmpty( ) const
 {
    return topOfStack == -1;
}
template <class T>
bool Stack<T>::isFull( ) const
{
      return topOfStack == theArray.size( )-1;
}
template <class T>
void Stack<T>::makeEmpty( )
{
      topOfStack =-1;
}
template <class T>
const T & Stack<T>::top( ) const
{
      if ( isEmpty( ) )
          cout << "empty" << endl;
      return theArray[ topOfStack ];
}
template <class T>
void Stack<T>::pop( )
{
      if ( isEmpty( ) )
          cout << "empty" << endl;
      topOfStack --;
}
template <class T>
void Stack<T>::push( const T & x )
{
     if ( isFull( ) )
         cout << "full" << endl;
     theArray[++topOfStack ] = x;
}
template <class T>
T Stack<T>::topAndPop( )
{
     if ( isEmpty( ))
         cout << "empty" << endl;
     return theArray[topOfStack--];
}





