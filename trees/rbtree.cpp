
#include <iostream>
#include <vector>
#include "rbtree.hpp"


int main() {

   RBTree<int> tree;
   std::vector<int> v = {1,2,3,4,5,6,7};
   //std::vector<int> v = {7,6,5,4,3,2,1};

   for ( auto &i : v ) {
      tree.insert(i);
      std::cout << std::endl;
      //tree.preorder();
   }

   tree.preorder();

   return 0;
}

