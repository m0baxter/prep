
#ifndef NODE_HPP
#define NODE_HPP

template<class T>
class Node {

   private:
      T data;
      std::shared_ptr< Node<T> > next;

   public:
      Node( T, std::shared_ptr< Node<T> > );
      std::shared_ptr< Node<T> > getNext();
      void setNext( std::shared_ptr< Node<T> > );
      T getData();
      void setData( T );
};

template<class T>
Node<T>::Node( T d, std::shared_ptr< Node<T> > n ) {

   data = d;
   next = n;
}

template<class T>
std::shared_ptr< Node<T> > Node<T>::getNext() {
   return next;
}

template<class T>
T Node<T>::getData() {
   return data;
}

template<class T>
void Node<T>::setNext( std::shared_ptr< Node<T> > n ) {
   next = n;
}

template<class T>
void Node<T>::setData( T a ) {
   data = a;
}

#endif

