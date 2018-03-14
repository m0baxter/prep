
#include <iostream>
#include <vector>
#include "tree.hpp"


int main() {

   Tree<int> t;
   std::vector<int> v = { 4, 2, 6, 1, 3, 5, 7 };
   //std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7 };

   std::cout << "height: " << t.height() << std::endl;

   for ( auto &i : v ) {
      t.insert(i);
   }

   std::cout << "height: " << t.height() << std::endl;

   std::cout << "preorder:" << std::endl;
   t.preorder();
   std::cout << std::endl;

   std::cout << "inorder:" << std::endl;
   t.inorder();
   std::cout << std::endl;
   
   std::cout << "postorder:" << std::endl;
   t.postorder();
   std::cout << std::endl;

   std::cout << t.getPointer( 7 )->getVal() << std::endl;

   return 0;
}

