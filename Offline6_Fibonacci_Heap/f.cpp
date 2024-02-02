// we are implementin fibpnacci heap data structure in c++

#include <iostream>
#include <vector>
#include <math.h>
#include <bits/stdc++.h>

using namespace std;


template <typename T> 
class node 
{
    
    public :

        int key;
        T value;
        int rank;
        bool marked;
        node<T> *parent;
        node<T> *child;
        node<T> *left;
        node<T> *right;
    
    node( int key, T value)
    {
        this->key = key;
        this->value = value;
        rank = 0;
        marked = false;
        parent = child = nullptr;
        left = right = this;
    }
};






/// fibonacci class begisn here

template <typename T> 
class fibonacci
{
    node<T> * max;
    vector<node<T> *> root_list;
    int totalnode;

    public :

    fibonacci(){
        max = nullptr;
        totalnode = 0;
    }


    // INSERT 

    void insert( int key, T value );
    int extractMax();
    void consolidate();
    void printHeap();

    void join ( node<T>* &newRoot , node<T>* &child );
    void swap ( node<T>* &a, node<T>* &b );
    void printRootList();

};

template<typename T>
void fibonacci<T> :: swap( node<T>* &a, node<T>* &b )
{
    node<T> * temp = a;
    a = b;
    b = temp;
}

template<typename T>
void fibonacci<T> :: insert( int key, T value )
{
    if( totalnode == 0 )
    {
        max = new node<T>(key, value);
        root_list.push_back(max);
        totalnode++;
        return;
    }
    
    node<T> *firstNode = root_list.front();
    node<T> *lastNode = root_list.back();
    node<T> *newNode = new node<T>(key, value);

    lastNode->right = newNode;
    newNode->left = lastNode;

    firstNode->left = newNode;
    newNode->right = firstNode;

    root_list.push_back(newNode);

    if( newNode->key > max->key )
    {
        max = newNode;
    }

    totalnode++;
}


template<typename T>   
int fibonacci<T> :: extractMax()
{
    if( totalnode == 0 )
    {
        cout << "Heap is empty" << endl;
        return -1;
    }
    
    cout << "extracting max" << endl;
    node<T> * tempMax = max;

    node<T> * maxLeft = max->left;
    node<T> * maxRight = max->right;

    node<T> * maxChild = max->child;

    if( maxChild == nullptr )
    {
        if( totalnode == 1 )
        {
            root_list.clear();
            max = nullptr;
            totalnode--;
            return tempMax->key;
        }


        for( int i = 0; i<root_list.size(); i++ )
        {
            if( root_list[i]->key == max->key )
            {
                root_list.erase(root_list.begin() + i);
                break;
            }
        }

        maxLeft->right = maxRight;
        maxRight->left = maxLeft;
        

        int temp = max->key;
        delete max;

        cout << "consolidating in max == nullptr" << endl;
        consolidate();

        return temp;
    }

    node<T> * firstChild = maxChild;
    node<T> * lastChild = maxChild->right;

    cout << "bugged here" << endl;
    do
    {
        firstChild->parent = nullptr;
        root_list.push_back(firstChild);

        if( firstChild->key > max->key )
        {
            max = firstChild;
        }

        firstChild = firstChild->left;
    }
    while( firstChild != lastChild );

    maxChild->right = maxRight;
    maxRight->left = maxChild;

    lastChild->left = maxLeft;
    maxLeft->right = lastChild;

    // removing from root list
    for( int i = 0; i<root_list.size(); i++ )
    {
        if( root_list[i]->key == tempMax->key )
        {
            root_list.erase(root_list.begin() + i);
            break;
        }
    }

    cout << "consolidating" << endl;
    consolidate();
    
    totalnode--;

    int temp = tempMax->key;
    delete tempMax;

    return temp;

}


// consolidate function

template<typename T>
void fibonacci<T> :: consolidate()
{
    int maxRank = 1000;         // log2(totalnode) + 1;

    vector<node<T> *> rankList(maxRank, nullptr);

    for( auto tempRoot : root_list)
    {
        node<T> * tempNode = tempRoot;
        int tempRank = tempNode->rank;

        while( rankList[tempRank] != nullptr )
        {
            node<T> * tempPoint = rankList[tempRank];

            // jetar key boro seta tempNode hobe, join e first parameter NEWROOT
            if( tempNode->key < tempPoint->key )
            {
                swap( tempNode, tempPoint );
            }

            cout << "joining " << tempNode->key << " and " << tempPoint->key << endl;
            join( tempNode, tempPoint );

            rankList[tempRank] = nullptr;
            tempRank++;

            rankList[tempRank] = tempNode;
        }
    }

    max = nullptr;
    root_list.clear();

    for( int i = 0; i<maxRank; i++ )
    {
        if( rankList[i] != nullptr)
        {
            if( max == nullptr)
            {
                root_list.push_back(rankList[i]);
                max = rankList[i];
            }
            else
            {
                root_list.push_back(rankList[i]);
                if( rankList[i]->key > max->key )
                {
                    max = rankList[i];
                }
            }
        }
    }

}

template<typename T>
void fibonacci<T> :: join( node<T>* &newRoot, node<T>* &childNode )
{
    for( int i = 0; i<root_list.size(); i++ )
    {
        if( root_list[i]->key == childNode->key )
        {
            root_list.erase(root_list.begin() + i);
            break;
        }
    }

    // making childNode a children of NewRoot
    // last child is the leftmost child here

    // 1 + 1
    if( newRoot->child == nullptr )
    {
        newRoot->child = childNode;

        childNode->parent = newRoot;
        childNode->left = childNode;
        childNode->right = childNode;

        newRoot->rank = newRoot->rank + 1;
        childNode->marked = false;
        return;
    }

    // more than 1 + 1
    node<T> * firstChild = newRoot->child;
    node<T> * lastChild = firstChild->right;

    childNode->parent = newRoot;

    lastChild->left = childNode;
    childNode->right = lastChild;

    childNode->left = firstChild;
    firstChild->right = childNode;

    newRoot->rank = newRoot->rank + 1;
    childNode->marked = false;
}


template<typename T>
void fibonacci<T> :: printRootList()
{
    if( totalnode == 0 )
    {
        cout << "Heap is empty" << endl;
        return;
    }

    cout << "printing heap from first root to last" << endl;
    for( auto i : root_list )
    {
        cout << i->key << " ";
    }
    cout << endl;
    cout << "max : " << max->key << endl;
    cout << "check loop : last element : " << root_list.front()->left->key << endl;
    cout << "check loop : first element : " << root_list.back()->right->key << endl;
}




int main()
{
    fibonacci<int> f;

    f.insert(1, 10);
    f.insert(2, 20);
    f.insert(3, 30);
    f.printRootList();


    f.extractMax();
    f.printRootList();


}