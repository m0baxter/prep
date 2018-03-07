
#include <iostream>
#include <vector>
#include "myQueue.hpp"

int main() {

   std::vector<int> v = {0,1,2,3,4,5,6,7,8};

   MyQueue<int> q;

   for (auto &i : v) {
      q.add(i);
   }

   for (int k = 0; k < 9; ++k) {
      q.add(k);
      std::cout << q.pop() << std::endl;
      std::cout << q.pop() << std::endl;
   }

   return 0;
}

