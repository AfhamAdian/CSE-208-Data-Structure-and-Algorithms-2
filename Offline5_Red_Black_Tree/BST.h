#include <iostream>
#include <cstring>
#include "color.hpp"
#include<bits/stdc++.h>

#define red 1
#define black 0

using namespace std;

template <typename T>
class node
{

public:
    T key;
    string value;
    string output;
    bool color;

    node<T> *left;
    node<T> *right;
    node<T> *parent;
    int nodechild;


    node()
    {
        key = 0;
        left = right = parent =NULL;
        output = value = NULL;
        color = red;
    }

    node(T key)                       // new node by default color RED
    {                                 // parent ecternally set na korle null hobe
        
        this->key = key;
        left = right = parent = NULL;     
        value = "dummyData";
        color = red;
    }

    node(T key, string str)            // new node by default color RED
    {                                  // parent ecternally set na korle null hobe
        
        this->key = key;
        left = right = parent = NULL;
        value = str;
        output = to_string(key) + '_' + str;
        color = red;
    }
    ~node();
    int get_nodechild();
};

 template<typename T> node<T> :: ~node()
 {

 }

template <typename T>
int node<T>::get_nodechild()
{
    return nodechild;
}

template <typename T>
class BST
{
    node<T> *mainroot;
    int totalnode;

    bool ll,rr,lr,rl;

public:
    BST();
    ~BST();

    node<T>* rotateLeft ( node<T>* &node );
    node<T>* rotateRight ( node<T>* &node );

    void insert(T key, string str);
    node<T>* inserthelp(node<T> *&root, T key, string str);
    void output();
    void outputhelp(node<T> *&root);
    node<T>* find(T key);
    node<T>* findhelp(node<T> *&root, T key);
    void preorder();
    void inorder();
    void postorder();
    void preorder(node<T> *&mainroot);
    void inorder(node<T> *&mainroot);
    void postorder(node<T> *&mainroot);
    void Delete(T key);
    node<T>* deletehelp( node<T>* &mainroot, T key);
    node<T>* findmin( node<T>* root );
    T findmint(node<T>* root);

};