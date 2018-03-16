
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <locale>
#include "stringThings.hpp"


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


int numberOf( const int n, const int i ) {
   /*Counts the number of times i appears in the range 1...n*/

   int count = 0;
   char digit = fromString<char>( toString<int>(i) );

   for ( int j = 1; j <= n; ++j ) {
      std::string num = toString<int>(j);

      for ( auto &c : num ) {
         if (c == digit) {
            count += 1;
         }
      }
   }

   return count;
}


std::set< char > common( const std::string &s1, const std::string &s2 ) {
   /*Returns a set of common elements. in s1 and s2.*/

   std::string string1(s1.begin(), s1.end());
   std::string string2(s2.begin(), s2.end());
   
   std::vector<char> result(s1.size() + s2.size() );

   std::sort(string1.begin(), string1.end() );
   std::sort(string2.begin(), string2.end() );

   auto it = std::set_intersection( string1.begin(), string1.end(), string2.begin(), string2.end(), result.begin() );

   return std::set<char>(result.begin(), it);

}


void permutations( std::string str, std::string out ) {
   /*Prints all permutations of the string str.*/

   if ( str.size() == 0 ) {
      std::cout << out << std::endl; 
      return;
   }

   for ( int i = 0; i < str.size(); ++i ) {
      permutations( str.substr(1), out + str[0] );

      rotate( str.begin(), str.begin() + 1, str.end() );
   }
}

std::string deleteFrom( std::string s1, std::string s2 ) {
   /*Removes all of the characters in s1 from s2.*/

   std::set<char> remove( s1.begin(), s1.end() );
   std::string out = "";

   for ( char &c : s2 ) {
      std::cout << c << std::endl;
      if ( !remove.count(c) ) {
         out = out.insert( out.size(), 1, c);
      }
   }

   return out;
}

std::string keepFirst( std::string s ) {
   /*Removes duplicates from a string keeping the first occurences.*/

   std::string out = "";
   std::set<char> letters;

   for ( char &c : s ) {
      if ( !letters.count(c) ) {
         out = out.insert( out.size(), 1, c);
      }

      letters.insert(c);
   }

   return out;
}

bool areAnagrams( std::string s1, std::string s2 ) {
   /*Check if the tow strings are anagrams.*/

   if ( s1.size() != s2.size() ) {
      return false;
   }
   else {
      std::map<char, int> letters1;
      std::map<char, int> letters2;

      for ( int i = 0; i < s1.size(); ++i ) {
         char c1 = std::tolower( s1[i], std::locale());
         char c2 = std::tolower( s2[i], std::locale());

         if ( letters1.count( c1 ) ) {
            letters1[c1] += 1;
         }
         else {
            letters1[c1] = 1;
         }

         if ( letters2.count( c2 ) ) {
            letters1[c2] += 1;
         }
         else {
            letters2[c2] = 1;
         }
      }

      return letters1 == letters2;
   }
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

   std::string s1 = "this is words.";
   std::string s2 = "that is not.";
   auto res = common( s1, s2 );

   std::cout << s1 << "    " << s2 << std::endl;
   std::cout << std::string(res.begin(), res.end()) << std::endl;

   int i = fromString<int>("12");
   std::string s = toString<int>(32);

   std::cout << i << "   " << s << std::endl;

   std::cout << deleteFrom("aeiou", "we are students.")<< std::endl;
   std::cout << keepFirst("112012") << std::endl;
   std::cout << areAnagrams("Cat", "act") << std::endl;


   return 0;
}

