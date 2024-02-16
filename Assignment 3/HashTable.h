#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include "myStructs.h"
using namespace std;


/* Hash Table header was taken by the lecture slides. */

template <class HashedObj>
class HashTable
{
    public:
		 /*
          Internal method to test if a positive number is prime.
          Not an efficient algorithm.
         */
        bool isPrime( int n )
        {
            if ( n == 2 || n == 3 )
                return true;

            if ( n == 1 || n % 2 == 0 )
                return false;

            for ( int i = 3; i * i <= n; i += 2 )
                 if ( n % i == 0 )
                     return false;

            return true;
        }

		 /*
         Internal method to return a prime number 
		 at least as large as n.  Assumes n > 0.
        */
        int nextPrime( int n )
        {
              if ( n % 2 == 0 )
                  n++;

              for ( ; ! isPrime( n ); n += 2 )
                   ;

              return n;
        }

		int hash (const WordItem & x, int tableSize) const
		{ 
			string key= x.word;
			int hashVal = 0;
  
			for (int i = 0; i < key.length();i++) 
				hashVal = 37 * hashVal + key[ i ];

			hashVal = hashVal % tableSize;

			if (hashVal < 0) 
				hashVal = hashVal + tableSize;

			return(hashVal);
		}
		explicit HashTable( const HashedObj & notFound, int size = 101 );
		HashTable( const HashTable & rhs )
				: ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
					harray( rhs.harray ), currentSize( rhs.currentSize ) { }

		const HashedObj & find( const HashedObj & x ) const;

		void makeEmpty() {}
		void insert( const HashedObj & x );
		void remove( const HashedObj & x );

		const HashTable & operator=( const HashTable & rhs );

		int sizeReturner(){ 
			int s = currentSize;
			return s;
		}
		int arrSize(){
			return harray.size();
		}		
	private:
		struct HashEntry
		{
			 HashedObj element;
			 string info;

			 HashEntry( const HashedObj & e = HashedObj( ), string i = "EMPTY" ) : element( e ), info( i ) {}
		};           
		vector<HashEntry> harray;
		int currentSize;
		const HashedObj ITEM_NOT_FOUND;
		bool isActive( int currentPos ) const;
		int findPos( const HashedObj & x ) const;
		void rehash();
 };
#endif