#include <iostream>
#include <vector>   
#include <list>     
#include <algorithm>
#include <string>

#include <bits/stdc++.h>

#define MAXSTRINGS 10000


using namespace std;

// all utils code 
vector<string> randomStrings(MAXSTRINGS);


set<int> selectRandomIndices( int size ) 
{
    set<int> indices;
    srand(1);                                                // use current time as seed for random generator

    while (indices.size() < size / 10) {
        int random_index = rand() % size;
        indices.insert(random_index);
    }

    return indices;
}



void generateRandomStrings( int n )
{
    srand(1); 
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

// int hashFunction1( string key, int tableSize )            // slide er first Hash Function
// {
//     int hash = 0;
//     for( int i = 0; i<key.length(); i++)
//     {
//         hash += key[i];
//     }
//     return hash % tableSize;
// }                                                          // in use 

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

int hashFunction1( string key, int tableSize )            // slide er first Hash Function
{
    int hash = 0;
    for(int i = 0; i < 3 && i < key.length(); i++)
    {
        int charValue = key[i] - 'a' + 1;
        hash += charValue * pow(27, i);
    }
    return hash;
}     


// node class 
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

class HashTable
{

    vector <list<node>> table;
    int tableSize;
    int currentSize;
    int maxChainLength;
    int insertCount;
    int removeCount;

    int probeCount;
    int collision;

    public:

    HashTable(int tableSizet, int maxChainLength)
    {
        if( isPrime(tableSizet) ){
            this->tableSize = tableSizet;
        }
        else{
            this->tableSize = nextPrime(tableSizet);
        }

        this->maxChainLength = maxChainLength;
        table.resize(this->tableSize);
        currentSize = 0;
        insertCount = 0;
        removeCount = 0;

        probeCount = 0;
        collision = 0;
    }

    bool find( string key )         // startIndex er por theke shob list er prottek key check kore dekhbe ache
    {
        int index = hashFunction1(key, tableSize) % tableSize;
        
        list<node> & chain = table[index];
        for( auto node : chain)
        {
            probeCount++;
            if( node.key == key){
                return true;
            }
        }
        return false;
    }

    list<node> :: iterator find( list<node> :: iterator begin, list<node> :: iterator end, string key )       // ekta chain e key ache kina check kore
    {
        for( auto it = begin; it != end; it++ )
        {
            probeCount++;
            if( it->key == key){
                return it;
            }
        }
        return end;
    }

    bool insertNode( string key, int value)              // rehashing er jnnno criteria rakhi nai apatoto
    {
        if( currentSize == tableSize ) rehash( tableSize*2 );

        int index = hashFunction1(key, tableSize) % tableSize ;

        list<node> & chain = table[index];

        if( find( key ) ) return false;          // duplicate check
        
        if( chain.size() != 0 )  collision++;

        chain.push_front( node(key, value) );
        currentSize++;
        insertCount++;

        //checking after 100 insertions
        if( insertCount % 100 == 0)
        {
            // cout << "insertCount : " << insertCount << endl;
            // cout << "tableSize : " << tableSize << endl;
            for( int i = 0; i<tableSize; i++)
            {
                if( table[i].size() > maxChainLength )          // rehashing if > maxChainLength
                {
                    int newTableSize = tableSize*2;
                    // cout << "tableSize : " << tableSize << endl;
                    // cout << "newTableSize : " << newTableSize << endl;
                    // cout << "increase Rehashing\n\n" << endl; 
                    rehash( newTableSize );
                    cout << "before break : " << nextPrime( newTableSize ) << endl;
                    break;
                }
            }
        }
        return true;
    }

    bool removeNode ( string key )
    {
        int index = hashFunction1(key, tableSize) % tableSize ;
        list<node> & chain = table[index];

        auto it = find( chain.begin(), chain.end(), key);
        if( it == chain.end() ) return false;

        chain.erase(it);
        currentSize--;
        removeCount++;

        // checking after 100 removals
        if( removeCount % 100 == 0)
        {
            for( int i = 0; i<tableSize; i++)
            {
                if( table[i].size() < 0.8*maxChainLength )          // rehashing if < 0.8*maxChainLength
                {
                    int newTableSize = tableSize/2;
                    rehash( newTableSize );
                    break;
                }
            }
        }
        return true;
    }

    void rehash( int newTableSize )
    {
        // int oldTableSize = tableSize;
        // vector<list<node>> oldTable = table;
        
        // tableSize = nextPrime(newTableSize);

        // for( int i = 0; i<oldTableSize; i++)
        // {
        //     table[i].clear();
        // }

        // table.clear();
        // table.resize(tableSize);
        // currentSize = 0;

        // for( int i = 0; i<oldTableSize; i++)
        // {
        //     for( auto node : oldTable[i])
        //     {
        //         insertNode(node.key, node.value);
        //     }
        // }

        vector<list<node>> oldTable = table;

        int oldTableSize = tableSize;
        int newTableSizePrime = nextPrime( newTableSize );

        vector<list<node>> newTable( newTableSizePrime );
        table = newTable;

        tableSize = newTableSizePrime;
        currentSize = 0; 
        insertCount = 0;
        collision = 0;

        for( int i = 0; i<oldTableSize; i++)
        {
            for( auto node : oldTable[i] ){
                insertNode( node.key, node.value );
            }
        }

        //cout << "Rehashing Done " << newTableSize << endl ;
    }

    int probeCountSearch()
    {
        probeCount = 0;
        set<int> random_indices = selectRandomIndices( MAXSTRINGS );

        // Use random indices to select strings from randomStrings 
        for (int index : random_indices) {
            string key = randomStrings[index];
            bool check = find(key);
            //cout << "Key of '" << key << "' is at index: " << keyIndex << endl;
        }

        int temp = probeCount;
        probeCount = 0;
        return temp;
    }

    int getCollison()
    {
        return collision;
    }

    void printHashTable()
    {
        cout << tableSize << endl;
        for( int i = 0; i<tableSize; i++)
        {
            cout << "Index : " << i << " : ";
            for( auto node : table[i])
            {
                cout << node.key << " ";
            }
            cout << endl;
        }
    }

    bool checker()
    {
        for( int i = 0; i<tableSize; i++)
        {
            if( table[i].size() > maxChainLength && table[i].size() < 0.8*maxChainLength ) return false;
        }
        return true;
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

    HashTable ht( 5000, 15 );
    
    for( int i = 0; i<MAXSTRINGS; i++)
    {
        ht.insertNode(randomStrings[i], i);
        //cout << i << endl;
    }
    
    cout << ht.getCollison() << endl;
    cout << "inserting done\n" << endl;

    // for ( int i = 0; i<MAXSTRINGS/2; i++)
    // {
    //     ht.removeNode(randomStrings[i]);
    // }
    
    if( ht.checker() ) cout << "checker : true" << endl;
    else cout << "checker : false" << endl;

    cout << ht.probeCountSearch() << endl;
    // cout << ht.getCollison() << endl;

    return 0;
}