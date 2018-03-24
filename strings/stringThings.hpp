
#include <string>
#include <sstream>

#ifndef STRINGTHINGS_HPP
#define STRINGTHINGS_HPP

template<class T>
T fromString( std::string s ) {

   std::stringstream ss;
   T out;

   ss << s;
   ss >> out;

   return out;
}

template<class T>
std::string toString( T val ) {

   std::stringstream ss;
   std::string s;

   ss << val;
   ss >> s;

   return s;
}

#endif

