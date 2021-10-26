#ifndef HASH24_H
#define HASH24_H

#include <string>

// Helper class for calculating hash values using universal randomly selected hash functions.
class Hash24 {

private:
   // some prime numbers of suitable size
   static long const prime1 = 16890581L ;   // prime number ~ 2^24 = 16777216
   static long const prime2 = 17027399L ;   // larger prime ~ 2^24 = 16777216

   // random values for the hash function
   unsigned long random_a ;
   unsigned long random_b ;
   unsigned long random_c ;

public:
    Hash24();
    Hash24(unsigned long rand_a, unsigned long rand_b, unsigned long rand_c);
    int hash(unsigned long x);
    int hash(std::string str);
    void dump();
};

#endif
