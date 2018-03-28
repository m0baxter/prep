
#ifndef MYQUEUE_HPP
#define MYQUEUE_HPP

#include <vector>

template<class T>
class MyQueue {

   private:
      std::vector<T> front, back;

   public:
      void add( const T a ) { back.push_back(a); };
      T pop();
      size_t size() { return front.size() + back.size(); };
      bool empty() { return front.empty() and back.empty(); };
};

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

#endif

