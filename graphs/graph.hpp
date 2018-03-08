
#include <set>
#include <stack>
#include <vector>

#include <iostream>

#ifndef GRAPHS_HPP
#define GRAPHS_HPP

class Graph {

   private:
      std::vector< std::set<int> > adjacency;

   public:
      Graph( size_t n ) { adjacency = std::vector< std::set<int> >(n); }
      void addEdge( const int, const int );
      void addDirectedEdge( const int, const int );
      bool isPath( const int, const int );
      void print();
};

#endif

