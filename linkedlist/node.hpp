
#ifndef NODE_HPP
#define NODE_HPP

template<class T>
class Node {

   private:
      T data;
      Node<T>* next;

   public:
      Node( T, Node<T>*);
      Node* getNext();
      void setNext( Node<T>* );
      T getData();
      void setData( T );
};

template<class T>
Node<T>::Node( T d, Node<T> *n ) {

   data = d;
   next = n;
}

template<class T>
Node<T>* Node<T>::getNext() {
   return next;
}

template<class T>
T Node<T>::getData() {
   return data;
}

template<class T>
void Node<T>::setNext( Node<T>* n ) {
   next = n;
}

template<class T>
void Node<T>::setData( T a ) {
   data = a;
}

#endif

