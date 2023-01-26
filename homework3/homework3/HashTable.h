//
//  Header.h
//  homework3
//
//  Created by Gülşah Önen on 7.05.2021.
//

#include <iostream>
#include<string>
#include<vector>

using namespace std;

template <class Object>
class List;     // Incomplete declaration.

template <class Object>
class ListItr;     // Incomplete declaration.

template <class Object>
class ListNode
{
    ListNode( const Object & theElement = Object( ), ListNode * n = NULL )
            : element( theElement ), next( n ) { }  // Constructor

    Object   element;
    ListNode *next;

    friend class List<Object>;
    friend class ListItr<Object>;
};

template <class Object>
class ListItr
{
public:
    ListItr( ) : current( NULL ) { }
    bool isPastEnd( ) const
    {   return current == NULL;   }
    void advance( )
    {   if ( ! isPastEnd( ) )   current = current->next;   }
    const Object & retrieve( ) const
    {   if ( isPastEnd( ) ) {
            Object i;
            return i;
    }
        return current->element;    }

private:
    ListNode<Object> *current;    // Current position

    ListItr( ListNode<Object> *theNode )
            : current( theNode ) { }

    friend class List<Object>;    // Grant access to constructor
};

template <class Object>
class List
{
public:
    List( );
    List( const List & rhs );
    ~List( );
    bool isEmpty( ) const;
    void makeEmpty( );
    ListItr<Object> zeroth( ) const;
    ListItr<Object> first( ) ;
    void insert( const Object & x, const ListItr<Object> & p );
    ListItr<Object> find(  Object & x ) const;
    ListItr<Object> findPrevious( const Object & x ) const;
    void remove( const Object & x );

    const List & operator=( const List & rhs );

private:
    ListNode<Object> *header;
};

template <class Object>
List<Object>::List( )
{
    header = new ListNode<Object>;
}
template <class Object>
bool List<Object>::isEmpty( ) const
{
    // see if the header points to NULL
    return header->next == NULL;
}
template <class Object>
void List<Object>::insert( const Object & x, const ListItr<Object> & p )
{
    if ( p.current != NULL )
        p.current->next = new ListNode<Object>( x, p.current->next );
}
template <class Object>
ListItr<Object> List<Object>::find( Object & x ) const
{
    ListNode<Object> *itr = header->next; // Initialize

    while ( itr != NULL && (itr->element).name != x.name )
        itr = itr->next;

    return ListItr<Object>( itr );
}
template <class Object>
ListItr<Object> List<Object>::findPrevious(const Object & x ) const
{
    ListNode<Object> *itr = header;

    while ( itr->next!= NULL && (itr->next->element).name!= x.name )
        itr = itr->next;

    return ListItr<Object>( itr );
}

template <class Object>
void List<Object>::remove(const Object & x ) {
    ListItr<Object> p = findPrevious(x); // Locate previous of x, if any

    if (p.current->next != NULL) {
        ListNode<Object> *oldNode = p.current->next;
        p.current->next = p.current->next->next;  // Bypass deleted node
        delete oldNode;
    }
}

template <class Object>
       ListItr<Object> List<Object>::zeroth( ) const
       {
           return ListItr<Object>( header );
       }

template <class Object>
           ListItr<Object> List<Object>::first( )
           {
                  return ListItr<Object>( header->next );
           }
template <class Object>
        void List<Object>::makeEmpty( )
        {
               while ( ! isEmpty( ) )
                      remove( first( ).retrieve( ) );
        }

template <class Object>
       List<Object>::~List( )
       {
             makeEmpty( );  // Get rid of all list nodes
             delete header;  // then get rid of the header
       }

template <class Object>
        void printList( const List<Object> & theList )
        {
             if ( theList.isEmpty( ) )
                cout << "Empty list" << endl;
             else
             {
                 ListItr<Object> itr = theList.first( );
                 for ( ; ! itr.isPastEnd( ); itr.advance( ) )
                      cout << itr.retrieve( ) << " ";
             }
             cout << endl;
        }


template <class Object>
       const List<Object> & List<Object>::operator=( const List<Object> & rhs )
       {
           if ( this != &rhs )
           {
                 makeEmpty( );

                 ListItr<Object> ritr = rhs.first( );
                 ListItr<Object> itr = zeroth( );
                 for (  ;  ! ritr.isPastEnd( ); ritr.advance( ), itr.advance( ) )
                       insert( ritr.retrieve( ), itr );
            }
            return *this;
       }


    template <class HashedObj>
class HashTable
{
public:
    HashTable( const HashedObj & notFound,
               int size = 101 );
    HashTable( const HashTable & rhs )
            : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
              theLists( rhs.theLists ) { }

    const HashedObj & find( const HashedObj & x ) const;

    void makeEmpty( );
    void insert(  HashedObj & x );
    void remove( const HashedObj & x );

    const HashTable & operator=( const HashTable & rhs);

private:
    vector<List<HashedObj> > theLists;
    // The array of Lists
    const HashedObj ITEM_NOT_FOUND;
};

int hash( const string & key, int tableSize );
int hash( int key, int tableSize );

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
int nextPrime( int n )
{
    if ( n % 2 == 0 )
        n++;

    for ( ; ! isPrime( n ); n += 2 )
        ;

    return n;
}



template <class HashedObj>
HashTable<HashedObj>::HashTable(
        const HashedObj & notFound, int size )
        : ITEM_NOT_FOUND( notFound ), theLists( nextPrime( size ) )
{
}
template <class HashedObj>
void HashTable<HashedObj>::makeEmpty( )
{
    for( int i = 0; i < theLists.size( ); i++ )
        theLists[ i ].makeEmpty( );
    // destroy the lists but not the vector!
}
template <class HashedObj>
void HashTable<HashedObj>::insert(HashedObj & x )
{
    // hash the given object and locate the list it should be on
    
    List<HashedObj> & whichList = theLists[hashed( x, theLists.size( ) ) ];

    // locate the object in the list (using List’s find)
    ListItr<HashedObj> itr = whichList.find( x );
    // insert the new item at the head of the list if not found!
    if ( itr.isPastEnd( ) )
        whichList.insert( x, whichList.zeroth( ) );
}

template <class HashedObj>
void HashTable<HashedObj>::remove( const HashedObj & x )
{
    // remove from the appropriate list
    theLists[ ::hash( x, theLists.size( ) ) ].remove( x );
}
template <class HashedObj>
const HashedObj & HashTable<HashedObj>::
find( const HashedObj & x ) const
{
    ListItr<HashedObj> itr;
    // locate the approriate list and search there
    itr = theLists[ ::hash( x, theLists.size( ) ) ].find( x );
    // retrieve from the located position
    if ( itr.isPastEnd( ) )
        return ITEM_NOT_FOUND;

    return itr.retrieve( );
}

