
#include <cstdlib>
#include <algorithm>

#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

template<class T>
class Node {

   private:
      Node<T>* rChild;
      Node<T>* lChild;
      T val;

   public:
      Node();
      Node( const T );
      T getVal() { return val; };
      Node<T>* getLeft() { return lChild; };
      Node<T>* getRight() { return rChild; };
      void setLeft( Node<T>* n) { lChild = n; };
      void setRight( Node<T>* n) { rChild = n; };
};

template<class T>
Node<T>::Node() {

   rChild = nullptr;
   lChild = nullptr;
}

template<class T>
Node<T>::Node( const T v ) {

   val = v;
   rChild = nullptr;
   lChild = nullptr;
}


template<class T>
class Tree {

   private:
      Node<T>* root;

   public:
      Tree() { root = nullptr; };
      Tree( Node<T>* node ) { root = node; };
      void insert( const T );
      void remove( const T );
      bool isIn( const T );
      size_t height();
      void inorder();
      void postorder();
      void preorder();
      bool isBalanced();
      Node<T>* getPointer( T );
      Node<T>* getRoot()  { return root; };
      Node<T>* getLeft()  { return root->getLeft(); };
      Node<T>* getRight() { return root->getRight(); };
};

template<class T>
void Tree<T>::insert( const T val ) {

   Node<T>* newNode = new Node<T>( val );

   if (root == nullptr) {
      root = newNode;
   }
   else {

      if ( val > root->getVal() ) {
         if (root->getRight() == nullptr) {
            root->setRight( newNode );
         }
         else {
            Tree<T>( root->getRight() ).insert(val);
         }
      }
      else if ( val < root->getVal() ) {
         if (root->getLeft() == nullptr) {
            root->setLeft( newNode );
         }
         else {
            Tree<T>( root->getLeft() ).insert(val);
         }
      }
   }
}

template<class T>
bool Tree<T>::isIn( const T v ) {
   if ( root == nullptr ) {
      return false;
   }
   else{
      if ( v > root->getVal() ) {
         return Tree<T>( root->getRight() ).isIn(v);
      }
      else if ( v < root->getVal() ) {
         return Tree<T>( root->getLeft() ).isIn(v);
      }
      else {
         return true;
      }
   }
}

template<class T>
size_t Tree<T>::height() {

   if (root == nullptr){
      return 0;
   }
   else {
      return 1 + std::max( Tree<T>(root->getLeft()).height() , Tree<T>(root->getRight()).height() );
   }
}

template<class T>
void Tree<T>::preorder() {

   if ( root == nullptr ) {
      return;
   }

   std::cout << root->getVal() << std::endl;  //Vist node.
   Tree<T>( root->getLeft() ).preorder();     //Deal with left.
   Tree<T>( root->getRight() ).preorder();    //Deal with right.
}

template<class T>
void Tree<T>::inorder() {

   if ( root == nullptr ) {
      return;
   }

   Tree<T>( root->getLeft() ).inorder();      //Deal with left.
   std::cout << root->getVal() << std::endl;  //Vist node.
   Tree<T>( root->getRight() ).inorder();     //Deal with right.
}

template<class T>
void Tree<T>::postorder() {

   if ( root == nullptr ) {
      return;
   }

   Tree<T>( root->getLeft() ).postorder();    //Deal with left.
   Tree<T>( root->getRight() ).postorder();   //Deal with right.
   std::cout << root->getVal() << std::endl;  //Vist node.
}

template<class T>
bool Tree<T>::isBalanced() {

   if ( root == nullptr ) {
      return true;
   }
   else {
      Tree<T> left = Tree<T>( root->getLeft() );
      Tree<T> right = Tree<T>( root->getRight() );

      return left.isBalanced() && right.isBalanced() && ( std::abs( (int) (left.height() - right.height()) ) <= 1);
   }
}


template<class T>
Node<T>* Tree<T>::getPointer( T val ) {

   Node<T> *res = nullptr;

   if ( root != nullptr ) {

      if ( res != nullptr ) {
         return res;
      }
      if (val == root->getVal() ){
         return root;
      }

      if( root->getLeft() != nullptr ) {
         res = Tree<T>( root->getLeft() ).getPointer( val );
      }

      if ( root->getRight() != nullptr ) {
         res = Tree<T>( root->getRight() ).getPointer( val );
      }
   }

   return res;
}

#endif

