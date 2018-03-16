
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

template<class T, int n>
int getFirst( std::array<T,n> data, T val, int start, int end ) {

   if ( start > end ) {
      return -1;
   }
   else { 
      int s = start;
      int e = end;
      int check = (start + end)/2;

      if ( data[check] == val ) {
         if ( (check > 0 and data[check - 1]) or (check == 0) ) {
            return check;
         }
         e = check - 1;
      }
      else if ( data[check] > val ) {
         e = check - 1;
      }
      else{
         s = check + 1;
      }

      return getFirst<T,n>( data, val, s, e );
   }
}

template<class T, int n>
int getLast( std::array<T,n> data, T val, int start, int end ) {

   if ( start > end ) {
      return -1;
   }
   else { 
      int check = (start + end)/2;
      int s =start;
      int e = end;

      if ( data[check] == val ) {
         if ( (check < n - 1 and data[check + 1] != val ) or (check == n - 1) ) {
            return check;
         }
         start = check + 1;
      }
      else if ( data[check] > val ) {
         end = check - 1;
      }
      else{
         start = check + 1;
      }

      return getLast<T,n>( data, val, start, end );
   }
}

template<class T, int n>
int countVal( std::array<T,n> data, T val ) {

   int first = getFirst<T,n>( data, val, 0, n - 1 );
   int last  = getLast<T,n>(  data, val, 0, n - 1 );

   if ( (first > -1) and (last > -1) ) {
      return last - first + 1;
   }
   else{
      return 0;
   }
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

