
#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <memory>
#include <tuple>
#include <utility>
#include "node.hpp"

template<class T>
class LinkedList {

   private:
      std::shared_ptr< Node<T> > head, tail;

   public:

      LinkedList() {
         head = nullptr;
         tail = nullptr;
      }

      void insertHead( T val ) {

         std::shared_ptr< Node<T> > newNode(new Node<T>(val, nullptr) );

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

         std::shared_ptr< Node<T> > newNode( new Node<T>(val, nullptr) );

         if ( tail == nullptr ) {
            head = newNode;
            tail = newNode;
         }
         else {
            tail -> setNext(newNode);
            tail = newNode;
         }
      }

      std::shared_ptr< Node<T> > begin() {
         return head;
      }

      std::shared_ptr< Node<T> > end() {
         return tail->getNext();
      }

      bool isEmpty() {
         return (head == nullptr && tail == nullptr);
      }

      bool isSingle() {
         return head == tail;
      }

      size_t size(){

         std::shared_ptr< Node<T> >n = head; //this -> begin();
         size_t len = 0;

         while (n != nullptr) {
            len++;
            n = n -> getNext();
         }

         return len;
      }

      T element( int k ) {

         std::shared_ptr< Node<T> > n = head;

         for (int i = 0; i < k; ++i) {
            n = n->getNext();
         }
         return n->getData();
      }

      std::shared_ptr< Node<T> > nodeAt( int k ) {

         std::shared_ptr< Node<T> > n = head;

         for (int i = 0; i < k; ++i) {
            n = n->getNext();
         }
         return n;
      }

      bool hasLoop() {
         /*Detects the presence of a loop. This can never happend with this implementation...*/

         std::shared_ptr< Node<T> > single = head;
         std::shared_ptr< Node<T> > dooble = head;

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
   std::shared_ptr< Node<T> > node = list.begin();

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

   std::shared_ptr< Node<T> > n = list.begin();

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

   std::shared_ptr< Node<T> > n1 = l1.begin();
   std::shared_ptr< Node<T> > n2 = l2.begin();

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
      return merge( mergeSort( split.first ), mergeSort( split.second ) );
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
      std::shared_ptr< Node<T> > n = sList.begin();

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

template<class T>
LinkedList<T> quickSort( LinkedList<T> list ) {
   /*Performs a quick sort on list.*/

   if ( list.isEmpty() ) {
      return LinkedList<T>();
   }
   else {
      std::tuple< LinkedList<T>, LinkedList<T>, LinkedList<T> > p = partition( list );

      LinkedList<T> lo    = std::get<0>(p);
      LinkedList<T> pivot = std::get<1>(p);
      LinkedList<T> hi    = std::get<2>(p);

      //return join( join( quickSort(lo), pivot), quickSort(hi) );
      return quickSort(lo) + pivot + quickSort(hi);
   }
}

template<class T>
std::tuple< LinkedList<T>, LinkedList<T>, LinkedList<T> > partition( LinkedList<T> list ) {
   /*Partitions the list into pivot, elements lower than pivot, and those higher than pivot.*/

   if ( list.size() == 0 ) {
      return std::make_tuple( LinkedList<T>(), LinkedList<T>(), LinkedList<T>() );
   }
   else if ( list.size() == 1 ) {

      LinkedList<T> pivot;
      pivot.insertTail( list.element(0) );

      return std::make_tuple( LinkedList<T>(), pivot, LinkedList<T>() );
   }
   else {

      T p = list.element(0);

      LinkedList<T> pivot;
      LinkedList<T> lo;
      LinkedList<T> hi;

      for ( int i = 0; i < list.size(); ++i ) {

         T val = list.element(i);

         if ( val < p ) {
            lo.insertTail(val);
         }
         else if ( val > p ) {
            hi.insertTail(val);
         }
         else if ( val == p ) {
            pivot.insertTail(val);
         }
      }

      return std::make_tuple( lo, pivot, hi );
   }
}

template<class T>
LinkedList<T> operator+( LinkedList<T> l1, LinkedList<T> l2 ) {

   LinkedList<T> res;

   for ( int i =0; i < l1.size(); ++i ) {

      res.insertTail( l1.element(i) );
   }

   for ( int i =0; i < l2.size(); ++i ) {

      res.insertTail( l2.element(i) );
   }

   return res;
}

#endif

