
#ifndef INHERIT_TESTS_HPP
#define INHERIT_TESTS_HPP

#include <iostream>

class BaseClass {
   private:
      int x;

   protected:
      int y;

   public:
      int z;
      BaseClass() { int x; int y; int z; };
      BaseClass( const int a, const int b, const int c ) { x = a; y = b; z = c; };
};

class FirstChildPublic : public BaseClass {
   /*
    * x: not accessible
    * y: protected
    * z: public
    *
    * */

   private:
   protected:
   public:
      void printPublic() { std::cout << pub << std::endl; };
      //void printPrivate() { std::cout << priv << std::endl; }; //Not allowed.
      void printP() { std::cout << prot << std::endl; };
};

class FirstChildProtected : protected BaseClass {
   /*
    * x: not accessible
    * y: protected
    * z: protected
    *
    * */

   private:
   protected:
   public:
      void printPublic() { std::cout << pub << std::endl; };
      //void printPrivate() { std::cout << priv << std::endl; }; //Not allowed.
      void printP() { std::cout << prot << std::endl; };
};

class FirstChildPrivate : private BaseClass {
   /*
    * x: not accessible
    * y: private
    * z: private
    *
    * */

   private:
   protected:
   public:
      void printPublic() { std::cout << pub << std::endl; };
      //void printPrivate() { std::cout << priv << std::endl; }; //Not allowed.
      void printP() { std::cout << prot << std::endl; };
};

#endif

