// here i will implement hash table, hash function and collision resolution using double hashing
//help me do it


#include <iostream>
#include <vector>   
#include <list>     
#include <algorithm>
#include <string>

#include <bits/stdc++.h>

#define MAXSTRINGS 5000
#define CUTOFF (float)(0.6)

using namespace std;

// all utils code 
vector<string> randomStrings(MAXSTRINGS);

void generateRandomStrings( int n )
{
    srand(time(0)); 
    int randomNumber = rand(); 
    int length;

    string letters = "abcdefghijklmnopqrstuvwxyz";

    for( int i = 0; i<n; i++)
    {
        length = (rand() % 6) + 5;
        string temp = "";
        for( int j = 0; j<length; j++)
        {
            temp += letters[rand() % 26];
        }
        randomStrings[i] = temp;
    }
}

bool isPrime( int n )
{
    if( n == 1 ) return false;
    if( n == 2 ) return true;
    if( n % 2 == 0 ) return false;

    for( int i = 3; i<=sqrt(n) + 1; i+=2)
    {
        if( n % i == 0 ) return false;
    }

    return true;
}

int nextPrime ( int n )
{
    while( !isPrime(++n) );
    return n;
}


// Hash Functions

int hashFunction1( string key, int tableSize )            // slide er first Hash Function
{
    int hash = 0;
    for( int i = 0; i<key.length(); i++)
    {
        hash += key[i];
    }
    return hash % tableSize;
}                                                          // in use 

// int hashFunction2(string key, int tableSize)                // slide er second Hash Function
// {
//     int hash = 0;
//     for(int i = 0; i < 3 && i < key.length(); i++)
//     {
//         int charValue = key[i] - 'a' + 1;
//         hash += charValue * pow(27, i);
//     }
//     return hash % tableSize;
// }

//// auxilary hashfunctions

int auxHash( string key, int tableSize )
{
    int hash = 0;
    for(int i = 0; i < 3 && i < key.length(); i++)
    {
        int charValue = key[i] - 'a' + 1;
        hash += charValue * pow(27, i);
    }
    return hash % tableSize;
}


///// node class /////

class node 
{
    public:

    string key;
    int value;

    node(string key, int value)
    {
        this->key = key;
        this->value = value;
    }
};

///// hash table class /////

class HashTable
{
    int tableSize;
    int currentSize;
    vector <node*> table;

    int multiplier;

    public:

    HashTable( int tableSize )
    {
        this->tableSize = nextPrime(tableSize);
        this->currentSize = 0;
        table.resize(this->tableSize, NULL);
        multiplier = 0;
    }

    int doubleHash( string key, int value )
    {
        int hash1 = hashFunction1( key, tableSize );
        int hash2 = auxHash( key, tableSize );

        int index = ( hash1 + ( multiplier * hash2) ) % tableSize;
        return index;
    }

    bool insertNode( string key , int value)
    {
        int index = doubleHash(key, tableSize);
        // << "Index : " << index+1 << endl;

        if( table[index] != NULL )
        {
            index = collisionHandler( key );
        }

        table[index] = new node( key, value );
        currentSize++;  

        if( (currentSize / (float)tableSize) > CUTOFF ) {
            cout << "vai kortesi\n\n" <<endl;
            rehash();
        }
        return true;
    }
    
    bool removeNode( string key )
    {
        int index = find( key, tableSize );

        if( index == -1 ) return false;

        table[index] = NULL;
        currentSize--;
    }

    int collisionHandler( string key )                         // kono ekta key insert korar jnno empty slot khuje 
    {                                                       // index return korbe
        int hash1 = hashFunction1( key, tableSize );
        int hash2 = auxHash( key, tableSize );

        int index = ( hash1 + ( multiplier * hash2) ) % tableSize;

        while( table[index] != NULL )
        {
            index = ( hash1 + ( multiplier * hash2) ) % tableSize;
            multiplier++;
            cout << "kala" << endl;
        }

        return index;
    }

    int findEmptySlot( string key )                         // kono ekta key insert korar jnno empty slot khuje 
    {                                                       // index return korbe
        int i = 0;
        int hash1 = hashFunction1( key, tableSize );
        int hash2 = auxHash( key, tableSize );

        int index = ( hash1 + ( i * hash2) ) % tableSize;

        while( table[index] != NULL && i<= tableSize)
        {
            index = ( hash1 + ( i * hash2) ) % tableSize;
            i++;
        }

        if( i > tableSize ) return -1;
        return index;
    }

    int find( string key, int value )                       // kono key, value pair ache kina check korbe
    {                                                       // thakle index, else -1 return korbe
        int index = doubleHash( key, value );

        if( table[index] == NULL ) return -1;
        else if( table[index] != NULL && table[index]->key == key ) return index;
        
        //else

        int hash1 = hashFunction1( key, tableSize );
        int hash2 = auxHash( key,tableSize );
        int i = 0;

        while( table[index] != NULL && table[index]->key != key && i <= tableSize )          // i check korar dorkar nai, karon null paboi
        {                                                                                   // jehetu load factor < 1
            index = ( hash1 + ( i * hash2) ) % tableSize;
            i++;
        }

        if( i > tableSize ) return -1;
        else return index;
    }

    void rehash()
    {   
        int newTableSize = nextPrime( tableSize * 2 );
        vector <node*> tempTable = table;

        table.clear();
        table.resize(newTableSize, NULL);

        tableSize = newTableSize;
        currentSize = 0;

        for( int i = 0; i<tempTable.size(); i++)
        {
            if( tempTable[i] != NULL )
            {
                insertNode( tempTable[i]->key, tempTable[i]->value );
            }
        }
    }

    void printHashTable()
    {
        cout << tableSize << endl;
        for( int i = 0; i<tableSize; i++)
        {
            if( table[i] != NULL ) cout << "Index : " << i+1 << " : " << table[i]->key << endl;
            else cout << "Index : " << i+1 << " : " << "NULL" << endl;
        }
    
    }

};


int main()
{

    generateRandomStrings(MAXSTRINGS);
    // for( int i = 0; i<MAXSTRINGS; i++)
    // {
    //     cout << randomStrings[i] << endl;
    //     cout << randomStrings[i].length() << endl;
    // }
    cout << "\n" << endl;

    HashTable ht(5000);
    cout << "hash table created" << endl;

    for( int i = 0; i<MAXSTRINGS; i++)
    {
        ht.insertNode( randomStrings[i], i );
        cout << i << " inserted" << endl;
    }

    cout << "inserted" << endl; 
    ht.printHashTable();
    


    return 0;
}