
#include <iostream>
#include <vector>
#include "MinMaxStack.hpp"


int main() {

   std::vector<int> vals = {1, 2, 4, 3, 1, 5, 7, 8, 9, 6};
   MinMaxStack<int> mmq;

   for ( auto &i : vals ) {
      mmq.push(i);
      std::cout << i << "  Min: " << mmq.min() << "  Max: " << mmq.max() << std::endl;
   }

   std::cout << std::endl;

   while ( not mmq.empty() ) {
      std::cout << "Min: " << mmq.min() << "  Max: " << mmq.max() << std::endl;
      std::cout << mmq.pop() << std::endl;
   }

   return 0;
}

