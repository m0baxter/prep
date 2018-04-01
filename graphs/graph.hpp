
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <unordered_set>

class Graph{

   private:
      std::unordered_map<int, std::unordered_set<int> > adj;

   public:
      void addNode( const int );
      void addEdgeD( const int, const int );
      void addEdgeB( const int, const int );
      bool isPath( const int, const int );
      std::vector< std::unordered_set<int> > connectedComponents();
      bool connected() { return connectedComponents().size() <= 1; };
      std::vector<int> path(const int, const int );
      std::vector<int> shortestPath( const int, const int );
      void printPath( const int, const int );
      bool hasCycle();
      bool isTree();
};

#endif

