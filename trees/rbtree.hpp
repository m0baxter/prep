
#include <string>
#include <iostream>
#include <algorithm>

#ifndef RBTREE_HPP
#define RBTREE_HPP

enum class Colour { Black, Red };

std::string toString( Colour c ) {
   switch (c) {
      case Colour::Red:
         return "Red";
         break;
      case Colour::Black:
         return "Black";
         break;
   }
}


template<class T>
class RBTree;

template<class T>
class Node {

   private:
      T data;
      Node<T> *parent, *lChild, *rChild;
      Colour c;
      void leftArrange( Node<T>*, Node<T>*, Node<T>*, Node<T>*, Node<T>*, Node<T>*, Node<T>* );
      void rightArrange( Node<T>*, Node<T>*, Node<T>*, Node<T>*, Node<T>*, Node<T>*, Node<T>* );

   public:
      Node();
      Node( const T );
      bool isRightChild();
      bool isLeftChild();

   friend class RBTree<T>;
};


template<class T>
class RBTree {

   private:
      Node<T>* root;
      RBTree( Node<T>* node ) { root = node; }; //Root may not be Black.
      void blacken() { root -> c = Colour::Black; };
      void ins( const T );
      void balance();

   public:
      RBTree() { root = nullptr; };
      void insert( const T );
      int height();
      bool isBalanced();
      void preorder();
};


template<class T>
Node<T>::Node() {

   parent = nullptr;
   lChild = nullptr;
   rChild = nullptr;
   c = Colour::Red;
}

template<class T>
Node<T>::Node( const T val) {

   data = val;
   parent = nullptr;
   lChild = nullptr;
   rChild = nullptr;
   c = Colour::Red;
}

template<class T>
bool Node<T>::isRightChild() {

   if ( parent == nullptr ) {
      return false;
   }
   else {
      return parent->rChild == this;
   }
}

template<class T>
bool Node<T>::isLeftChild() {

   if ( parent == nullptr ) {
      return false;
   }
   else {
      return parent->lChild == this;
   }
}

template<class T>
void RBTree<T>::insert( const T v ) {

   this->ins( v );
   this->blacken();
}

template<class T>
void RBTree<T>::ins( const T val ) {

   Node<T>* newNode = new Node<T>( val );

   if (root == nullptr) {
      root = newNode;
   }
   else {

      if ( val > root->data ) {
         if ( root-> rChild == nullptr) {
            root -> rChild = newNode;
            newNode -> parent = root;
         }
         else {
            RBTree<T> right = RBTree<T>( root->rChild );
            right.ins(val);
            right.balance();
         }
      }
      else if ( val < root -> data ) {
         if ( root -> lChild == nullptr ) {
            root -> lChild = newNode;
            newNode -> parent = root;
         }
         else {
            RBTree<T> left = RBTree<T>( root -> lChild );
            left.ins(val);
            left.balance();
         }
      }
   }
}

template<class T>
void RBTree<T>::balance() {

   if ( root -> parent != nullptr) {

      if ( root->lChild != nullptr and root->lChild->c == Colour::Red and root->lChild->lChild != nullptr and root->lChild->lChild->c == Colour::Red ) {
         Node<T>* z = root;
         Node<T>* y = z -> lChild;
         Node<T>* x = y -> lChild;
         Node<T>* a = x -> lChild;
         Node<T>* b = x -> rChild;
         Node<T>* c = y -> rChild;
         Node<T>* d = z -> rChild;

         Node<T>().leftArrange(x, y, z, a, b, c, d);

         root = y;
         RBTree<T>(x).blacken();
         RBTree<T>(z).blacken();

         std::cout << "case 1:" << std::endl;
         RBTree<T>(y).preorder();
      }
      else if ( root->lChild != nullptr and root->lChild->c == Colour::Red and root->lChild->rChild != nullptr and root->lChild->rChild->c == Colour::Red ) {
         Node<T>* z = root;
         Node<T>* x = z -> lChild;
         Node<T>* y = x -> rChild;
         Node<T>* a = x -> rChild;
         Node<T>* b = y -> lChild;
         Node<T>* c = y -> rChild;
         Node<T>* d = z -> rChild;

         Node<T>().leftArrange(x, y, z, a, b, c, d);

         root = y;
         RBTree<T>(x).blacken();
         RBTree<T>(z).blacken();

         std::cout << "case 2:" << std::endl;
         RBTree<T>(y).preorder();
      }
      else if ( root->rChild != nullptr and root->rChild->c == Colour::Red and root->rChild->lChild != nullptr and root->rChild->lChild->c == Colour::Red ) {
         Node<T>* x = root;
         Node<T>* z = x -> rChild;
         Node<T>* y = z -> lChild;
         Node<T>* a = x -> lChild;
         Node<T>* b = y -> lChild;
         Node<T>* c = y -> rChild;
         Node<T>* d = z -> rChild;

         Node<T>().rightArrange(x, y, z, a, b, c, d);

         root = y;
         RBTree<T>(z).blacken();
         RBTree<T>(x).blacken();

         std::cout << "case 3:" << std::endl;
         RBTree<T>(y).preorder();
      }
      else if ( root->rChild != nullptr and root->rChild->c == Colour::Red and root->rChild->rChild != nullptr and root->rChild->rChild->c == Colour::Red ) {
         Node<T>* x = root;
         Node<T>* y = x -> rChild;
         Node<T>* z = y -> rChild;
         Node<T>* a = x -> lChild;
         Node<T>* b = y -> lChild;
         Node<T>* c = z -> lChild;
         Node<T>* d = z -> rChild;

         Node<T>().rightArrange(x, y, z, a, b, c, d);

         root = y;
         RBTree<T>(z).blacken();
         RBTree<T>(x).blacken();
         
         std::cout << "case 4:" << std::endl;
         RBTree<T>(y).preorder();
      }
   }
}

template<class T>
void Node<T>::leftArrange( Node<T>* x, Node<T>* y, Node<T>* z, Node<T>* a, Node<T>* b, Node<T>* c, Node<T>* d ) {

    if ( z->isRightChild() ) {
      z->parent->rChild = y;
   }
   else if ( z->isLeftChild() ) {
      z->parent->lChild = y;
   }
  
   y -> parent = z -> parent;
   y -> lChild = x;
   y -> rChild = z;
   
   x -> parent = y;
   x -> lChild = a;
   x -> rChild = b;
   
   z -> parent = y;
   z -> lChild = c;
   z -> rChild = d;

   if ( a != nullptr ) {
      a -> parent = x;
   }
   if ( b != nullptr ) {
      b -> parent = x;
   }
   if ( c != nullptr ) {
      c -> parent = z;
   }
   if ( d != nullptr ) {
      d -> parent = z;
   }
}

template<class T>
void Node<T>::rightArrange( Node<T>* x, Node<T>* y, Node<T>* z, Node<T>* a, Node<T>* b, Node<T>* c, Node<T>* d ) {

   if ( x->isRightChild() ) {
      x->parent->rChild = y;
   }
   else if ( x->isLeftChild() ) {
      x->parent->lChild = y;
   }
   
   y -> parent = x -> parent;
   y -> lChild = x;
   y -> rChild = z;
   
   x -> parent = y;
   x -> lChild = a;
   x -> rChild = b;
   
   z -> parent = y;
   z -> lChild = c;
   z -> rChild = d;

   if ( a != nullptr ) {
      a -> parent = x;
   }
   if ( b != nullptr ) {
      b -> parent = x;
   }
   if ( c != nullptr ) {
      c -> parent = z;
   }
   if ( d != nullptr ) {
      d -> parent = z;
   }
}

template<class T>
int RBTree<T>::height() {

   if (root == nullptr){
      return 0;
   }
   else {
      return 1 + std::max( RBTree<T>( root->lChild ).height(), RBTree<T>( root->rChild ).height() );
   }
}

template<class T>
bool RBTree<T>::isBalanced() {

   if ( root == nullptr ) {
      return true;
   }
   else {
      RBTree<T> left  = RBTree<T>( root->lChild );
      RBTree<T> right = RBTree<T>( root->rChild );

      return left.isBalanced() && right.isBalanced() && ( std::abs( (left.height() - right.height()) ) <= 1);
   }
}

template<class T>
void RBTree<T>::preorder() {

   if ( root == nullptr ) {
      return;
   }

   std::cout << root->data << "  " << toString(root->c) << std::endl;  //Vist node.
   RBTree<T>( root->lChild ).preorder();                    //Deal with left.
   RBTree<T>( root->rChild ).preorder();                     //Deal with right.
}

#endif

