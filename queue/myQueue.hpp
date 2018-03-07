
#include <vector>

#ifndef MYQUEUE_HPP
#define MYQUEUE_HPP

template<class T>
class MyQueue {

   private:
      std::vector<T> front, back;

   public:
      void add( const T );
      T pop();
      size_t size();
};


template<class T>
void MyQueue<T>::add( const T a ) {
   /*Add an element to the back of the queue.*/

   back.push_back(a);
}

template<class T>
T MyQueue<T>::pop() {
   /*Remove the first element of the queue and remove it.*/

   if ( front.size() == 0 ){
      front = std::vector<T>( back.rbegin(), back.rend() );
      back = std::vector<T>();

      T val = front.back();
      front.pop_back();

      return val;
   }
   else {
      T val = front.back();
      front.pop_back();

      return val;
   }
}

template<class T>
size_t MyQueue<T>::size() {
   /*Returns the length of the queue.*/

   return front.size() + back.size();
}

#endif

