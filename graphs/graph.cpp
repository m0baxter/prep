
#include <iostream>
#include "graph.hpp"


void Graph::addEdge( const int source, const int destination ) {
   /*Creates an edge between vertices labeled by source and destination.*/

   adjacency.at(source).insert(destination);
   adjacency.at(destination).insert(source);
}

void Graph::addDirectedEdge( const int source, const int destination ) {
   /*Creates an edge between vertices labeled by source and destination.*/

   adjacency.at(source).insert(destination);
}

void Graph::print() {
   int i = 0;

   for (auto &adj : adjacency) {

         std::cout << "Node " << i << ": ";

      for (auto &node : adj){
         std::cout << node << "   ";
      }
      ++i;
      std::cout << std::endl;
   }
}

bool Graph::isPath( const int start, const int end ) {
   /*Find a path from start to end.*/

   std::stack<int> possible;
   possible.push(start);
   std::set<int> visited;

   while ( !possible.empty() ) {
      int node = possible.top();
      possible.pop();

      visited.insert(node);

      if (node == end) {
         return true;
      }
      else {
         for (auto &n : adjacency.at(node) ) {
            if ( !visited.count(n) ) {
               possible.push(n);
            }
         }
      }
   }

   return false;
}


int main() {

   Graph g(4);

   g.addEdge(0,1);
   g.addEdge(0,2);
   g.addEdge(1,2);

   std::cout << g.isPath(0, 3) << std::endl;

   return 0;
}

