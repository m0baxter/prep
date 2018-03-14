
#include <set>
#include <vector>

#ifndef GRAPH_HPP
#define GRAPH_HPP

class Graph {

   private:
      std::vector< std::set<int> > adjacency;

   public:
      Graph( size_t n ) { adjacency = std::vector< std::set<int> >(n); }
      void addEdge( const int, const int );
      void addDirectedEdge( const int, const int );
      bool isPath( const int, const int );
      bool hasLoop( const int );
      void print();
};

#endif

