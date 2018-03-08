
#include <iostream>
#include <vector>
#include <set>
#include <numeric>


std::vector<int> range( const int start, const int end ) {
   /*Returns a vector of all integers [start, end].*/

   std::vector<int> v(end - start + 1);
   std::iota( v.begin(), v.end(), start );

   return v;
}


std::set<int> primesRange( const int n ) {
   /*Returns all primes in the range 1 to n.*/

   std::vector<int> v = range( 2, n );
   std::set<int> possible( v.begin(), v.end() );
   std::set<int> primes;

   for (auto &i : possible) {

      primes.insert(i);

      for ( int k = i; k <= n; k += i ) {
         possible.erase(k);
      }
   }

   return primes;
}


int main( int argc, char** argv ){

   std::set<int> primes = primesRange( 1000000 );

   for ( auto &i : primes ) {
      std::cout << i << std::endl;
   }

   return 0;
}

