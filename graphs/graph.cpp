
#include <iostream>
#include <stack>
#include <queue>
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
   std::stack<int> path;
   //possible.push(start);
   std::set<int> visited;

   int node = start;

   while ( node != end ) {

      std::cout << "Node: " <<  node << std::endl;

      bool foundUnvisited = false;
      for ( auto &n : adjacency.at(node) ) {
         if ( !visited.count(n) ) {
            path.push(node);
            visited.insert(n);
            node = n;
            foundUnvisited = true;
            break;
         }
      }
      if ( !foundUnvisited ) {
         if( path.empty() ) {
            return false; // empty route means no route found
         }
         node = path.top();
         path.pop();
      }
   }

   path.push( end );

   return true;
}

std::vector<int> Graph::path( const int start, const int end ) {
   /*Find a path from start to end.*/

   std::stack<int> possible;
   std::vector<int> path;
   std::set<int> visited = {start};

   int node = start;

   while ( node != end ) {

      bool foundUnvisited = false;

      for ( auto &n : adjacency.at(node) ) {
         if ( !visited.count(n) ) {
            path.push_back(node);
            visited.insert(n);
            node = n;
            foundUnvisited = true;
            break;
         }
      }
      if ( !foundUnvisited ) {
         if( path.empty() ) {
            return path; // empty route means no route found
         }
         node = path.back();
         path.pop_back();
      }
   }

   path.push_back( end );

   return path;
}

int main() {

   Graph g(5);

   g.addEdge(0,1);
   g.addEdge(1,2);
   g.addEdge(2,3);
   g.addEdge(3,0);
   g.addEdge(0,4);
   g.print();

   std::cout << std::endl;

   std::vector<int> path = g.path(4, 3);

   for ( auto &n : path ) {
      std::cout << n << std::endl;
   }

   return 0;
}

