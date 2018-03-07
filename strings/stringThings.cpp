
#include <iostream>
#include <string>
#include <set>
#include <algorithm>


bool allUnique( const std::string s ) {
   /*Determine if the string s contains all unique characters.*/

   std::set<char> unique( s.begin(), s.end() ); 

   return ( unique.size() == s.size() );
}


std::string revString( const std::string s ) {
   /*Reverse a string.*/

   std::string rev( s.rbegin(), s.rend() );

   return rev;
}


bool isPermutation( const std::string s1, const std::string s2 ) {
   /*Determine whether the two strings are permutations of eachother.*/

   if ( s1.size() == s2.size() ) {

      std::set<char> set1( s1.begin(), s1.end() );
      std::set<char> set2( s2.begin(), s2.end() );
      
      return ( set1 == set2 );
   }

   else {
      return false;
   }
}


std::string revWords( const std::string s ) {
   /*Returns a copy of the string s with the words reversed.*/

   std::string reversed = s;

   size_t pos = 0;
   size_t prev = 0;

   bool notFirst = false;

   while ( pos != std::string::npos ) {

      prev = pos;
      pos = s.find(" ", pos + 1);

      std::reverse( reversed.begin() + prev + notFirst, reversed.begin() + pos);

      notFirst = true;
   }

   std::reverse( reversed.begin() + prev +1 , reversed.end() );

   return reversed;
}


int main() {

   std::cout << allUnique("1234") << std::endl;
   std::cout << allUnique("1234123") << std::endl;

   std::cout << revString( "this" ) << std::endl;

   std::cout << isPermutation( "this", "tihs" ) << std::endl;
   std::cout << isPermutation( "this", "tis" ) << std::endl;
   std::cout << isPermutation( "this", "this" ) << std::endl;
   std::cout << isPermutation( "this", "thisthis" ) << std::endl;

   std::cout << revWords("This is a bunch of words") << std::endl;
   std::cout << true << std::endl;

   return 0;
}
