
#include <iostream>
#include <vector>
#include <unordered_set>
#include "graph.hpp"

void Graph::addNode( const int n ) {
   /*Adds a node to the graph.*/

   if ( !adj.count(n) ) {
      adj[n] = std::unordered_set<int>();
   }
}

void Graph::addEdgeD( const int src, const int dst ) {
   /*Add a directed esdge between dst and src nodes.*/

   adj[src].insert(dst);
}

void Graph::addEdgeB( const int src, const int dst ) {
   /*Add a bodirectional edge between the two nodes.*/

   adj[src].insert(dst);
   adj[dst].insert(src);
}

bool Graph::isPath( const int start, const int end ) {
   /*Determines whether a path exists between nodes start and end.*/

   std::unordered_set<int> visited = { start };
   std::stack<int> possible( { start } ); //or: std::queue<int> possible( { start } );

   while ( !possible.empty() ) {

      int next = possible.top(); //or: int next = possible.front();
      possible.pop();
      visited.insert(next);

      for ( auto &n : adj[next] ) {

         if ( n == end ) {
            return true;
         }
         if ( !visited.count(n) ) {
            possible.push(n);
         }
      }
   }

   return false;
}

std::vector< std::unordered_set<int> > Graph::connectedComponents() {

   std::vector< std::unordered_set<int> > components;
   std::unordered_set<int> visited;

   for ( auto &p : adj ) {

      int node = p.first;

      if ( !visited.count(node) ) {
         
         visited.insert(node);

         std::unordered_set<int> reachable = { node };
         std::queue<int> possible( {node} );

         while ( !possible.empty() ) {

            int next = possible.front();
            possible.pop();

            visited.insert( next );
            reachable.insert( next );

            for ( auto &n : adj[next] ) {
               if ( !visited.count(n) ) {
                  possible.push( n );
               }
            }
         }

         components.push_back( reachable );
      }
   }

   return components;
}

std::vector<int> Graph::path( const int start, const int end ) {
   /*Returns a path from start to end. If no path exists returns an empty vector.*/

   std::stack<int> possible;
   std::vector<int> path;
   std::unordered_set<int> visited = { start };

   int node = start;

   while ( node != end ) {
      
      bool foundUnvisited = false;

      for ( auto &n : adj[node] ) {
         if ( !visited.count(n) ) {
            path.push_back(node);
            visited.insert(n);
            node = n;
            foundUnvisited = true;
            break;
         }
      }

      if ( !foundUnvisited ) {
         if ( path.empty() ) {
            return path;
         }

         node = path.back();
         path.pop_back();
      }
   }

   path.push_back( end );

   return path;
}

std::vector<int> Graph::shortestPath( const int start, const int end ) {
   /*Finds a shortest path between two nodes.*/

   std::queue< std::vector<int> > paths;
   paths.push( {start} );
   int shortest = adj.size() + 1;
   std::vector<int> shortPath;

   while ( !paths.empty() ) {

      std::vector<int> path = paths.front();
      paths.pop();

      int node = path.back();

      for ( auto &n : adj[node] ) {

         std::vector<int> p = path;
         p.push_back(n);

         if ( p.size() <= shortest ) {
            if ( n == end ) {
               std::cout << "Shortest: " << p.size() << std::endl;
               shortest = p.size();
               shortPath = p;
            }

            paths.push(p);
         }
      }
   }

   return shortPath;
}

int main() {

   Graph g;

   g.addNode(1);
   g.addNode(2);
   g.addNode(3);
   g.addNode(4);
   g.addNode(5);
   g.addNode(6);
   g.addNode(7);
   g.addNode(8);

   g.addEdgeB( 1, 2);
   g.addEdgeB( 1, 3);
   g.addEdgeB( 1, 7);
   g.addEdgeB( 2, 3);
   g.addEdgeB( 3, 4);
   g.addEdgeB( 3, 6);
   g.addEdgeB( 3, 5);
   g.addEdgeB( 5, 4);
   g.addEdgeB( 5, 6);
   g.addEdgeB( 4, 6);
   g.addEdgeB( 6, 7);

   std::vector<int> path = g.shortestPath( 1, 7 );

   if ( path.empty() ) {
      std::cout << "No path." << std::endl;
   }
   else {
      for ( int i = 0; i < path.size() - 1; ++i ) {
         std::cout << path[i] << " -> ";
      }
      
      std::cout << path[ path.size() - 1 ] << std::endl;
   }

   return 0;
}

