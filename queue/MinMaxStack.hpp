
#include <vector>

#ifndef MIMMAXSTACK_HPP
#define MINMAXSTACK_HPP

template<class T>
class MinMaxStack {

   private:
      std::vector<T> data;
      std::vector<T> mins;
      std::vector<T> maxs;

   public:
      void push( T );
      T pop();
      T min() { return mins.back(); };
      T max() { return maxs.back(); };
      size_t size() { return data.size(); };
      bool empty() { return data.empty(); };
};

template<class T>
void MinMaxStack<T>::push( T a ) {

   data.push_back(a);

   if ( mins.empty() ) {
      mins.push_back(a);
   }
   else if ( a <= mins.back() ) {
      mins.push_back(a);
   }

   if ( maxs.empty() ) {
      maxs.push_back(a);
   }
   else if ( a >= maxs.back() ) {
      maxs.push_back(a);
   }
}

template<class T>
T MinMaxStack<T>::pop() {

   T val = data.back();
   data.pop_back();

   if ( val == mins.back() ) {
      mins.pop_back();
   }

   if ( val == maxs.back() ) {
      maxs.pop_back();
   }

   return val;
}

#endif

