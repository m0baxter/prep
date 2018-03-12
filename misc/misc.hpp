
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

#endif

