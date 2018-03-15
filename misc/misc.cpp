
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
#include <array>
#include <random>
#include <ctime>
#include <map>

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


void fizzBang() {

   for ( int i = 1; i <= 100; ++i ) {
      bool mult5 = (i % 5 == 0);
      bool mult3 = (i % 3 == 0);

      if ( mult3 and mult5 ) {
         std::cout << "FizzBang" << std::endl;
      }
      else if ( mult3 ) {
         std::cout << "Fizz" << std::endl;
      }
      else if ( mult5 ) {
         std::cout << "Bang" << std::endl;
      }
      else {
         std::cout << i << std::endl;
      }
   }
}


void coinFlip() {

   std::mt19937 rnd( std::time(0));

   for (int i = 0; i < 10; ++i ) {
      std::cout << rnd( ) % 2 << std::endl;
   }
}

int diceRoll( const int numRolls ) {

   std::array<int, 7> counts = { 0, 0, 0, 0, 0, 0, 0 };
   std::mt19937 rnd( std::time(0));

   int i = 0;

   while ( i < numRolls ) {

      int c1 = rnd( ) % 2;
      int c2 = rnd( ) % 2;
      int c3 = rnd( ) % 2;

      int roll = 100 * c1 + 10 * c2 + c3;

      switch (roll) {
         case 1:
            counts[1] += 1;
            ++i;
            break;

         case 10:
            counts[2] += 1;
            ++i;
            break;

         case 11:
            counts[3] += 1;
            ++i;
            break;

         case 100:
            counts[4] += 1;
            ++i;
            break;

         case 101:
            counts[5] += 1;
            ++i;
            break;

         case 110:
            counts[6] += 1;
            ++i;
            break;

         default:
            break;
      }
   }

   for ( int j = 1; j < 7; ++j ) {
      std::cout << "Rolled: " << j << "  Fraction: " << (1.0*counts[j]/numRolls) << std::endl; 
   }
}


std::vector<int> duplicates( std::vector<int> data ) {
   /*Returns a list of dupliate items.*/

   std::map<int,int> counts;

   for (auto &i : data ) {

      if ( counts.count(i) ) {
         counts[i] += 1;
      }
      else {
         counts[i] = 1;
      }
   }

   std::vector<int> dups;

   for ( auto &pair : counts ) {
      if ( pair.second > 1 ) {
         dups.push_back( pair.first );
      }
   }

   return dups;
}


std::array< std::array<int, 2>, 2 > nthPower( std::array< std::array<int, 2>, 2 > A, int n ) {

   if (n == 1) {
      return A;
   }

   else if ( n % 2 == 0 ) {
      return multiply<int,2,2,2>( nthPower(A, n/2), nthPower(A, n/2) );
   }
   else if ( n % 2 == 1 ) {
      return multiply<int,2,2,2>( multiply<int,2,2,2>( nthPower(A, (n-1)/2), nthPower(A, (n-1)/2) ), A);
   }
}


int fibonacci( const int n ) {
   /*Calculates the nth fibonacci number*/

   std::array< std::array<int, 2>, 2 > unit {{{1,1}, {1,0}}};

   if (n == 0) {
      return 0;
   }
   else if ( n == 1 ){
      return 1;
   }
   else {
      return nthPower(unit, n - 1 )[0][0];
   }
}


int main() {

   std::vector<int> data = { 1, 3, 4, 1, 5, 8, 0, 2, 1, 3, 10, 0 };

   std::vector<int> dups = duplicates( data );

   for ( auto &i : dups ) {
      std::cout << i << std::endl;
   }

   for (int i = 0; i < 40; ++i ) {
      std::cout << fibonacci(i) << std::endl;
   }

   return 0;
}

