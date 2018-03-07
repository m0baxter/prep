
#include <iostream>
#include <vector>
#include "linkedList.hpp"


int main() {

   std::vector<int> vals = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

   LinkedList<int> list;

   for ( auto &i : vals) {
      list.insertTail(i);
   }

   std::cout << "Properly constructed linked list:  " << list.hasLoop() << std::endl;

   //Add a loop:
   Node<int>* n1 = list.nodeAt(16);
   Node<int>* n2 = list.nodeAt(5);
   n1->setNext(n2);

   std::cout << "Linked list with a loop added by hand:  " << list.hasLoop() << std::endl;

   return 0;
}

