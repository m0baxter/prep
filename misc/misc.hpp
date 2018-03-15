
#include <array>

#ifndef MISC_HPP
#define MISC_HPP

template<class T, int m, int l, int n>

std::array< std::array<T, m>, n> multiply( std::array< std::array<T, m>, l> A, std::array< std::array<T, l>, m> B ) {

   std::array< std::array<T, m>, n> C;

   for ( int i = 0; i < m; ++i ) {
      for ( int j = 0; j < n;  ++j ) {
         C[i][j] = 0;
      }
   }

   for ( int i = 0; i < m; ++i ) {
      for ( int j = 0; j < n;  ++j ) {
         for ( int k = 0; k < l; ++k ) {
            C[i][j] += A[i][k]*B[k][j];
         }
      }
   }

   return C;
}


template<class T, int n>
bool find( std::array<T,n> data, T val ) {
   /*Performs a binary search to find val.*/

   int start = 0;
   int end = data.size();
   int check = (start + end)/2;

   while ( start != end - 1 ) {

      if ( val > data[check] ) {
         start = check;
      }
      else if ( val < data[check] ) {
         end = check;
      }
      else {
         return true;
      }

      check = (start + end)/2;
   }

   return false;
}


template<int n>
bool addTo( const int sum, const std::array<int, n> values ) {
   /*determines whether any two elements in values add to sum.*/

   for ( auto &i : values ) {
      if ( find<int, n>( values, sum - i ) ) {
         return true;
      }
   }

   return false;
}

#endif

