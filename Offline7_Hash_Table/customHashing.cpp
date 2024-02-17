#include <iostream>
#include <vector>   
#include <list>     
#include <algorithm>
#include <string>

#include <bits/stdc++.h>

#define MAXSTRINGS 100
#define CUTOFF (float)(0.6)
#define c1 37
#define c2 59

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
// customHash(k, i) = (Hash(k) + C1 × i × auxHash(k) + C2 × i2) % N

int auxHash( string key, int tableSize )            // slide er first Hash Function
{
    int hash = 0;
    for( int i = 0; i<key.length(); i++)
    {
        hash += key[i];
    }
    return 7 - (hash % 7) ;
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

int hashFunction1( string key, int tableSize )
{
    int hash = 0;
    for(int i = 0; i < 3 && i < key.length(); i++)
    {
        int charValue = key[i] - 'a' + 1;
        hash += charValue * pow(27, i);
    }
    return hash ;
}


///// node class /////

class node 
{
    public:

    string key;
    int value;
    bool isDeleted;

    node(string key, int value)
    {
        this->key = key;
        this->value = value;
        isDeleted = false;
    }
};

///// hash table class /////

class HashTable
{
    int tableSize;
    int currentSize;
    vector <node*> table;


    public:

    HashTable( int tableSize )
    {
        if( isPrime( tableSize )) this->tableSize = tableSize;
        else this->tableSize = nextPrime( tableSize );

        currentSize = 0;
        table.resize( this->tableSize, nullptr );

        cout << "Table Size: " << this->tableSize << endl;
        cout << "Current Size: " << currentSize << endl;
    }

    // int doubleHash( string key )
    // {
    //     int index = hashFunction1( key, tableSize ) + multiplier*auxHash( key, tableSize );
    //     return index;
    // }

    int findKey ( string key )                                                // checks if a key exists
    {   
        int hash1 = hashFunction1( key, tableSize );
        int hash2 = auxHash( key, tableSize );   
        int i = 0;                                                             // returns -1 if key not found
        int index = (hash1 + c1*i*hash2 + c2*i*i ) % tableSize;

        if( table[index] == nullptr )
        {
            // cout << "fisrt index ei null" <<endl;
            return -1;
        }
        else if( table[ index ] != nullptr && table[index]->key == key && table[index]->isDeleted == false)
        {
            return index;
        }
        else 
        {            
            while( 1 )
            {
                if( table[index] == nullptr ) {
                    // cout << "while er vitor null" << " " << i <<endl;
                    return -1;
                }
                else if ( table[index]->key == key  && table[index]->isDeleted == false ){
                    return index;
                }
                i++;
                index = ( hash1+ c1*i*hash2 + c2*i*i ) % tableSize;
            }
        }
    }

    node* findNode( string key )                                                // returns the node if key found
    {
        int index = findKey( key );                                            
        if( index == -1 ) return nullptr;                                       // returns nullptr if key not found
        return table[index];
    }

    bool insertNode( string key , int value)
    {
        //cout << "in insert Node : " << value << endl;
        int index = findKey( key );
        if( index != -1 ) return false;

        int hash1 = hashFunction1( key, tableSize );
        int hash2 = auxHash( key, tableSize );
        int i = 0;
        index = (hash1 + c1*i*hash2 + c2*i*i ) % tableSize;

        while( 1 )
        {
            if( table[index] == nullptr )
            {
                table[index] = new node( key, value );
                currentSize++;
                if( (float)currentSize/tableSize > CUTOFF ) rehash();
                return true;
            }
            else if( table[index]->isDeleted == true )
            {
                table[index]->key = key;
                table[index]->value = value;
                table[index]->isDeleted = false;
                currentSize++;
                if( (float)currentSize/tableSize > CUTOFF ) rehash();
                return true;
            }
            i++;
            index = (hash1 + c1*i*hash2 + c2*i*i ) % tableSize;
        }
    
    }

    void rehash()
    {
        cout << "Rehashing\n\n" << "Table Size: " << tableSize << endl;
        // int oldTableSize = tableSize;
        // vector<node*> oldTable;

        // for( int i = 0; i<tableSize; i++ )
        // {
        //     if( table[i] != nullptr )
        //     {
        //         oldTable.push_back( new node( table[i]->key, table[i]->value ) );
        //     }
        //     else{
        //         oldTable.push_back( nullptr );
        //     }
        // }

        // tableSize = nextPrime( tableSize*2 );
        // table.resize(tableSize, nullptr);
        // currentSize = 0;

        // for( int i = 0; i<oldTableSize; i++ )
        // {
        //     if( oldTable[i] != nullptr && oldTable[i]->isDeleted == false )
        //     {
        //         insertNode( oldTable[i]->key, oldTable[i]->value );
        //     }
        // }

        int oldTableSize = tableSize;
        int newTableSize = nextPrime( tableSize*2 );

        vector<node*> newTable( newTableSize, nullptr );

        for( int i = 0; i<oldTableSize; i++ )
        {
            if( table[i] != nullptr && table[i]->isDeleted == false )
            {
                int hash1 = hashFunction1( table[i]->key, newTableSize );
                int hash2 = auxHash( table[i]->key, newTableSize );
                int j = 0 ;
                int index = (hash1 + c1*j*hash2 + c2*j*j ) % newTableSize;

                while( 1 )
                {
                    if( newTable[index] == nullptr )
                    {
                        newTable[index] = new node( table[i]->key, table[i]->value );
                        break;
                    }
                    j++;
                    index = ( hash1 + c1*j*hash2 + c2*j*j ) % newTableSize;
                }
            }
        }

        tableSize = newTableSize;
        table = newTable;
    }

    bool removeNode( string key )
    {
        int index = findKey( key );
        if( index == -1 ) return false;

        node* temp = table[index];  
        temp->isDeleted = true;
        currentSize--;

        return true;
    }

    void printHashTable()
    {
        cout << tableSize << endl;
        for( int i = 0; i<tableSize; i++)
        {
            cout << "Index : " << i << " : ";
            if( table[i] != nullptr )
            {
                cout << table[i]->key << " ";
            }
            else cout << "NULL ";
            cout << endl;
        }
    }

    int countNotNullValues()
    {
        int count = 0;
        for (int i = 0; i < tableSize; i++)
        {
            if (table[i] != nullptr)
            {
                count++;
            }
        }
        return count; 
    }
};


int main()
{

    generateRandomStrings(MAXSTRINGS);

    HashTable ht( 1000 );

    // cout << ht.insertNode( "aaaaaa", 0 ) << endl;
    // cout << ht.findKey( "aaaaaa" ) << endl;

    // cout << ht.insertNode( "aaaaaaaa", 0 ) << endl;
    // cout << ht.findKey( "aaaaaaaa" ) << endl;
    
    // // ht.removeNode( "aaaaaaaa" );
    // cout << ht.findKey( "aaaaaaaa" );

    for( int i  = 0; i<MAXSTRINGS; i++)
    {
        // cout <<"index " << i << " " << ht.insertNode( randomStrings[i], i ) << endl;
        string temp = randomStrings[i];
        cout << ht.insertNode( temp , i ) << endl;

    }

    // cout << ht.findKey( "arianadilarianadil" ) << endl;    
    // cout << ht.insertNode( "arianadilarianadil", 1 ) << endl;

    cout << "insertion over \n\n\n\n";

    //ht.printHashTable();
    //ht.printHashTable();
    cout << ht.countNotNullValues();


    for( int i = 0; i<MAXSTRINGS ; i++)
    {
        cout << ht.removeNode( randomStrings[i] ) << endl;
    }

    cout << "Removal over" << endl;

    for( int i = 0; i<MAXSTRINGS ; i++)
    {
        cout << ht.findKey( randomStrings[i] ) << endl;
    }

    // cout << ht.countNotNullValues( ) << endl;
    return 0;
}