
#include <utility>
#include "node.hpp"

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

template<class T>
class LinkedList {

   private:
      Node<T> *head, *tail;

   public:
      ~LinkedList() {

         if ( !hasLoop() ) {
            Node<T> *current = head;
            
            while ( current != nullptr ) {
               Node<T> *next = current->getNext();
               
               delete current;
               current = next;
            }
            head = nullptr;
            tail = nullptr;
         }
      };

      LinkedList() {
         head = nullptr;
         tail = nullptr;
      }

      void insertHead( T val ) {

         Node<T>* newNode = new Node<T>(val, nullptr);
         newNode->setData(val);

         if ( head == nullptr ){
            head = newNode;
            tail = newNode;
         }
         else {
            newNode -> setNext( head );
            head = newNode;
         }
      }

      void insertTail( T val ) {
         
         Node<T>* newNode = new Node<T>(val, nullptr);

         if ( tail == nullptr ) {
            head = newNode;
            tail = newNode;
         }
         else {
            tail -> setNext(newNode);
            tail = newNode;
         }
      }

      Node<T>* begin() {
         return head;
      }

      Node<T>* end() {
         return tail->getNext();
      }

      bool isEmpty() {
         return (head == nullptr && tail == nullptr);
      }

      bool isSingle() {
         return head == tail;
      }

      size_t size(){

         Node<T>* n = this -> begin();
         size_t len = 0;

         while (n != nullptr) {
            len++;
            n = n -> getNext();
         }

         return len;
      }

      T element( int k ) {

         Node<T>* n = head;

         for (int i = 0; i < k; ++i) {
            n = n->getNext();
         }
         return n->getData();
      }

      Node<T>* nodeAt( int k ) {

         Node<T>* n = head;

         for (int i = 0; i < k; ++i) {
            n = n->getNext();
         }
         return n;
      }

      bool hasLoop() {
         /*Detects the presence of a loop. This can never happend with this implementation...*/

         Node<T>* single = head;
         Node<T>* dooble = head;

         if (dooble != nullptr) {
            dooble = dooble->getNext();
         }

         while (dooble != nullptr) {

            if (single == dooble) {
               return true;
            }
            else {
               dooble = dooble->getNext();     //advance once (safe).
               if (dooble != nullptr) {        //check if you can advance again.
                  dooble = dooble->getNext();  //Advance a second time.
               }
            }

            single = single -> getNext();
         }

         return false;
      }
};

template<class T>
std::pair< LinkedList<T>, LinkedList<T> > splitList( LinkedList<T> list ) {
   /*Splits list into two, approximate, halves.*/

   LinkedList<T> first, second;

   int n = list.size();
   Node<T>* node = list.begin();

   for (int i = 0; i < n; ++i) {

      if ( i < n/2 ) {
         first.insertTail( node -> getData() );
      }
      else {
         second.insertTail( node -> getData() );
      }

      node = node -> getNext();
   }

   return std::make_pair( first, second );
}

template<class T>
LinkedList<T> reverseList( LinkedList<T> list ) {
   /*Reverses the list.*/

   LinkedList<T> rev;

   Node<T>* n = list.begin();

   while (n != nullptr) {
      rev.insertHead( n->getData() );
      n = n -> getNext();
   }

   return rev;
}

template<class T>
LinkedList<T> merge( LinkedList<T> l1, LinkedList<T> l2 ) {
   /*Merges the two sorted lists.*/

   LinkedList<T> merged;

   Node<T>* n1 = l1.begin();
   Node<T>* n2 = l2.begin();

   int len1 = l1.size();
   int len2 = l2.size();

   int i1 = 0;
   int i2 = 0;

   while (  (i1 < len1) || (i2 < len2 ) ) {

      if (i1 == len1) {
         merged.insertTail( n2->getData() );
         n2 = n2 -> getNext();
         ++i2;
      }
      else if (i2 == len2) {
         merged.insertTail( n1->getData() );
         n1 = n1 -> getNext();
         ++i1;
      }
      else {
         int v1 = n1 -> getData();
         int v2 = n2 -> getData();

         if (v1 < v2) {
            merged.insertTail( v1 );
            n1 = n1 -> getNext();
            ++i1;
         }
         else {
            merged.insertTail( v2 );
            n2 = n2 -> getNext();
            ++i2;
         }
      }
   }

   return merged;
}

template<class T>
LinkedList<T> mergeSort( LinkedList<T> list ) {
   /*Sorts list using merge sort.*/

   if ( list.isEmpty() ) {
      return LinkedList<T>();
   }
   else if ( list.isSingle() ) {
      LinkedList<T> res;
      res.insertTail( list.begin() -> getData() );
      return res;
   }
   else {
      std::pair< LinkedList<T>, LinkedList<T> > split = splitList(list);
      return merge( mergeSort( split.first  ), mergeSort( split.second ) );
   }
}

template<class T>
LinkedList<T> removeDups( LinkedList<T> list ) {
   /*Retruns a linked list free of duplicates.*/

   LinkedList<T> res;

   if ( list.isEmpty() ) {
      return res;
   }
   else {
      LinkedList<T> sList = mergeSort(list);
      Node<T>* n = sList.begin();

      T prv = n -> getData();
      res.insertTail( prv );

      n = n -> getNext();

      while ( n != nullptr ) {

         T val = n->getData();

         if ( val != prv ) {
            res.insertTail( val );
         }

         prv = val;
         n = n->getNext();
      }

      return res;
   }
}

#endif

