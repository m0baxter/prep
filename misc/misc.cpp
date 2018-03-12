
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>

#include <array>
#include "misc.hpp"


unsigned int numberOfOnes( unsigned int a ) {
   /*Counts the number of bits set to 1 in the integer a.*/

   int count = 0;

   while (a != 0) {
      count += a % 2;
      a >>= 1;
   }

   return count;
}


double sqrt( const double a ) {
   /*Approximates the square root of a.*/

   if ( a < 0.0 ) {
      return std::nan("");
   }


   double start, end;

   if ( a < 1.0 ) {
      start = 0.0;
      end = 1.0;
   }
   else {
      start = 1.0;
      end = a;
   }

   double root = (end + start) / 2;

   int i = 0;

   while ( std::fabs( end - start )/2 > 1.0E-10 and i < 100 ) {

      if ( (root*root - a) > 0 ) {
         end = root;
      }
      else if ( (root*root - a) <= 0 ) {
         start = root;
      }

      root = (end + start) / 2;
      ++i;
   }

   return root;
}


int findDup( const std::vector<int> list ) {

   std::vector<int> vec = list;
   std::sort(vec.begin(), vec.end() );

   int prev = vec.front();

   for ( auto i = vec.begin() + 1; i != vec.end(); ++i ) {
      if ( *i == prev ) {
         return prev;
      }

      prev = *i;
   }
}

bool intersect( std::pair<int,int> a, std::pair<int,int> b ) {

   return a.first <= b.second && b.first <= a.second;
}

std::vector< std::pair<int,int>> mergeIntervals( std::vector< std::pair<int, int> > list, std::pair<int, int> interval ) {
   /**/

   std::pair<int,int> tmp = interval;
   std::vector< std::pair<int,int> > merged;


   for ( auto itr = list.begin(); itr != list.end(); ++itr) {
      if ( intersect( *itr, tmp ) ) {
         tmp = std::make_pair( std::min( itr->first, tmp.first), std::max( itr->second, tmp.second) );

         if (itr+1 == list.end() ) {
            merged.push_back(tmp);
         }
      }
      else {
         if ( itr->second < tmp.first ) {
            merged.push_back(*itr);
         }
         else {
            if ( itr+1 == list.end() ) {
               merged.push_back(tmp);
               merged.push_back(*itr);
            }
         }
      }
   }

   return merged;
}


int main() {

   std::vector< std::pair<int,int> > vec = { std::make_pair(1, 5), std::make_pair(10, 15), std::make_pair(20, 25), std::make_pair(30, 200) };
   std::vector< std::pair<int,int> > merged = mergeIntervals( vec, std::make_pair(12,27) );

   for (auto &ran : merged ) {
      std::cout << ran.first << "   " << ran.second << std::endl;
   }


   std::array< std::array<int, 2>, 2> A = { {{1,1},{0,1}} };
   std::array< std::array<int, 2>, 2> B = { {{1,1},{1,1}} };

   std::array< std::array<int, 2>, 2> C = multiply<int, 2, 2, 2>(A,B);

   for (int i = 0; i < 2; ++i ) {
      for (int j = 0; j < 2; ++j ) {
         std::cout << C[i][j] << std::endl;
      }
   }

   return 0;
}

