#include "HashTable.h"


using namespace std;


extern int uniqueWordCounter;

/* Hash Table implementation was taken by the lecture slides. */


/*
 Construct the hash table.
*/
template <class HashedObj>
HashTable<HashedObj>::HashTable( const HashedObj & notFound, int size ): ITEM_NOT_FOUND( notFound ), harray( nextPrime( size ) )
{
    makeEmpty( );
}


/*
Method that performs quadratic probing resolution.
Return the position where the search for x terminates.
*/
template <class HashedObj>
int HashTable<HashedObj>::findPos( const HashedObj & x ) const
{
        int collisionNum = 0;
        int currentPos = hash( x, harray.size() ); //48 current pos
		 
		
        while ( harray[currentPos].info != "EMPTY" && harray[currentPos].element != x )
        {
            currentPos += pow(++collisionNum, 2);//add the difference
			                             
            if ( currentPos >= harray.size() )              // perform the mod
                   currentPos = currentPos - harray.size();                // if necessary
        }
		
        return currentPos;
}

/*
Return true if currentPos exists and is active.
*/
template <class HashedObj>
bool HashTable<HashedObj>::isActive( int currentPos ) const
{
        return harray[ currentPos ].info == "ACTIVE";
}


/*
Remove item x from the hash table.
x has to be in the table
*/
template <class HashedObj>
void HashTable<HashedObj>::remove( const HashedObj & x )
{
        int currentPos = findPos( x );
        if ( isActive( currentPos ) )
            harray[ currentPos ].info = "DELETED";
}


/*
Find item x in the hash table.
Return the matching item, or ITEM_NOT_FOUND, if not found.
*/
template <class HashedObj>
const HashedObj & HashTable<HashedObj>::find( const HashedObj & x ) const
{
        int currentPos = findPos( x );
        if (isActive( currentPos )) 
            return harray[ currentPos ].element; 
 
        return   ITEM_NOT_FOUND;
}

/*
Insert item x into the hash table. If the item is
already present, then do nothing.
*/
template <class HashedObj>
void HashTable<HashedObj>::insert( const HashedObj & x )
{
	
        // Insert x as active
	
        int currentPos = findPos( x );
		
		
        if ( isActive( currentPos ) )
            return;
        harray[ currentPos ] = HashEntry( x, "ACTIVE" );
		

        // enlarge the hash table if necessary 
		//if ( ++currentSize >= harray.size() / 2 )
        int e = uniqueWordCounter;
        float loadFactor = 1/0.5;
		if ( ++e >= float(harray.size()) / loadFactor )
		{			
			rehash( );
		}
        
		
	
}

/*
Expand the hash table.
*/
template <class HashedObj>
void HashTable<HashedObj>::rehash( )
{

	int oldSize = harray.size();

    vector<HashEntry> oldharray = harray;

    // Create new double-sized, empty table
    harray.resize( nextPrime( 2 * oldharray.size( ) ) );
    for ( int j = 0; j < harray.size( ); j++ )
            harray[ j ].info = "EMPTY";


	int newSize = harray.size();

    // Copy table over
    int c = currentSize;
    currentSize = 0;
    for ( int i = 0; i < oldharray.size( ); i++ )
	{
        if ( oldharray[ i ].info == "ACTIVE" )
		{
				
                insert( oldharray[ i ].element );
		}
        
	}
    int h = uniqueWordCounter;
    h++;
	cout << "rehashed..."<<endl;	
	cout << "previous table size:"<<oldSize<< ", new table size: "<<newSize<< ", current unique word count "<< h<<","<<endl;
	cout << "current load factor: " << double(h)/newSize << endl;
}
