
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <memory>

#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

template<class T>
class Node {

   private:
      std::shared_ptr< Node<T> > rChild;
      std::shared_ptr< Node<T> > lChild;
      T val;

   public:
      Node();
      Node( const T );
      T getVal() { return val; };
      std::shared_ptr< Node<T> > getLeft() { return lChild; };
      std::shared_ptr< Node<T> > getRight() { return rChild; };
      void setLeft( std::shared_ptr< Node<T> > n) { lChild = n; };
      void setRight( std::shared_ptr< Node<T> > n) { rChild = n; };
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
      std::shared_ptr< Node<T> > root;

   public:
      Tree() { root = nullptr; };
      Tree( std::shared_ptr< Node<T> > node ) { root = node; };
      void insert( const T );
      void remove( const T );
      bool isIn( const T );
      size_t height();
      void inorder();
      void postorder();
      void preorder();
      bool isBalanced();
      std::shared_ptr< Node<T> > getPointer( T );
      std::shared_ptr< Node<T> > getRoot()  { return root; };
      std::shared_ptr< Node<T> > getLeft()  { return root->getLeft(); };
      std::shared_ptr< Node<T> > getRight() { return root->getRight(); };
      void print();
      std::shared_ptr< Node<T> > kthNode( int& );
};

template<class T>
void Tree<T>::insert( const T val ) {

   std::shared_ptr< Node<T> > newNode(new Node<T>( val ) );

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
std::shared_ptr< Node<T> > Tree<T>::getPointer( T val ) {

   std::shared_ptr< Node<T> > res = nullptr;

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

template<class T>
void Tree<T>::print() {

   std::queue< std::shared_ptr< Node<T> > > row;
   row.push(root);

   while ( !row.empty() ) {

      std::queue< std::shared_ptr< Node<T> > > next;

      while ( !row.empty() ) {

         std::shared_ptr< Node<T> > n = row.front();
         row.pop();

         if ( n != nullptr ) {
            std::cout << n->getVal() << "  ";
         }

         if ( n->getLeft() != nullptr ) {
            next.push( n->getLeft() );
         }
         if ( n->getRight() != nullptr ) {
            next.push( n->getRight() );
         }
      }

      std::cout << std::endl;

      row = next;
   }
}

template<class T>
std::shared_ptr< Node<T> > Tree<T>::kthNode( int &k ) {
   /*returns the kth node inorder.*/

   std::shared_ptr< Node<T> > res = nullptr;

   if ( root != nullptr ) {

      if( root->getLeft() != nullptr ) {
         res = Tree<T>( root->getLeft() ).kthNode( k );
      }

      if ( res == nullptr ) {
         if ( k == 0 ) {
            res = root;
         }

         k--;
      }

      if ( res == nullptr and ( root->getRight() != nullptr ) ) {
         res = Tree<T>( root->getRight() ).kthNode( k );
      }
   }

   return res;
}

#endif

