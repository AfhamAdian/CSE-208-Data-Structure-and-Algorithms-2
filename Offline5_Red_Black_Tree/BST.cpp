#include <iostream>
#include <cstring>
#include<bits/stdc++.h>
#include"BST.h"

template <typename T>
BST<T>::BST()
{
    mainroot = NULL;
    totalnode = 0;
    ll = rr = lr = rl = false;
}

template<typename T> BST<T> :: ~BST(){}

// template <typename T>
// void BST<T>::insert(T key)
// {
//     if (totalnode == 0)
//     {
//         mainroot = new node<T>(key);
//         totalnode++;
//         return;
//     }
//     inserthelp(mainroot, key);
// }

// template <typename T>
// void BST<T>::inserthelp(node<T> *&root, T key)
// {
//     if (root == NULL)
//     {
//         root = new node<T>(key);
//         totalnode++;
//         return;
//     }
//     if (key >= root->value)
//     {
//         inserthelp(root->right, key);
//     }
//     else if (key < root->value)
//     {
//         inserthelp(root->left, key);
//     }
// }

///*

// template <typename T>
// void BST<T>::insert(T key, string str)
// {
//     if (totalnode == 0)
//     {
//         mainroot = new node<T>(key);
//         totalnode++;
//         return;
//     }
//     inserthelp(mainroot, key);
// }

// template <typename T>
// node<T>* BST<T>::inserthelp(node<T> *&root, T key, string str)
// {
//     if (root == NULL)
//     {
//         root = new node<T>(key);
//         totalnode++;
//         return root;
//     }
//     if (key >= root->value)
//     {
//         root->right = inserthelp(root->right, key);
//     }
//     else if (key < root->value)
//     {
//         root->left = inserthelp(root->left, key);
//     }
//     return root;
// }

//*/
//
template <typename T>
void BST<T>::output()
{
    cout << "";
    outputhelp(mainroot);
    cout << "";
}

template <typename T>
void BST<T>::outputhelp(node<T> *&root)
{
    if (root == NULL)
        return;

    if( root->color == red )
        cout << dye :: light_red(root->output) ;
    else cout << ( root-> output );

    if (root->left == NULL && root->right == NULL)
        return;
    // if( root-> left != NULL)
    // {
    cout << "(";
    outputhelp(root->left);
    cout << ",";
    // }
    // if( root -> right != NULL )
    // {
    outputhelp(root->right);
    cout << ")";
    // }
    return;
}

template <typename T>
node<T> *BST<T>::find(T key)
{
    return findhelp(mainroot, key);
}

template <typename T>
node<T> *BST<T>::findhelp(node<T> *&root, T key)
{
    if (root == NULL)
    {
        cout << "not found" << endl;
        return NULL;
    }
    if (root->value == key)
    {
        cout << "found " << endl;
        return root;
    }
    if (key > root->value)
    {
        return findhelp(root->right, key);
    }
    if (key < root->value)
    {
        return findhelp(root->left, key);
    }
}

template <typename T>
void BST<T>::preorder()
{
    preorder(mainroot);
}

template <typename T>
void BST<T>::inorder()
{
    inorder(mainroot);
}

template <typename T>
void BST<T>::postorder()
{
    postorder(mainroot);
}

template <typename T>
void BST<T>::preorder(node<T> *&root)
{
    if (root == NULL)
        return;

    cout << root->value << " ";
    preorder(root->left);
    preorder(root->right);
}

template <typename T>
void BST<T>::inorder(node<T> *&root)
{
    if (root == NULL)
        return;

    inorder(root->left);
    cout << root->value << " ";
    inorder(root->right);
}

template <typename T>
void BST<T>::postorder(node<T> *&root)
{
    if (root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    cout << root->value << " ";
}

template<typename T> void BST<T> :: Delete(T key)
{
    deletehelp(mainroot,key);
}

template<typename T>node<T>* BST<T>::deletehelp(node<T>* &root, T key)
{
    if (root == NULL) return NULL;

    if (root->value > key)
    {
        root->left = deletehelp(root->left, key);
    }
    else if (root->value < key)
    {
        root->right = deletehelp(root->right, key);
    }
    else // root->value == key
    {
        if (root->right == NULL && root->left == NULL)
        {
            delete root;
            return NULL;
        }
        else if (root->right == NULL)
        {
            node<T>* temp = root;
            root = root->left;
            delete temp;
        }
        else if (root->left == NULL)
        {
            node<T>* temp = root;
            root = root->right;
            delete temp;
        }
        else // Both left and right subtrees are present
        {
            node<T>* temp = findmin(root->right);
            root->value = temp->value;
            root->right = deletehelp(root->right, temp->value);
        }
    }
    return root;
}

template <typename T> node<T>* BST<T> :: findmin( node<T>* root )
{
    if( root->left == NULL ) return root ;
    return findmin(root->left);
}

template<typename T> T BST<T> :: findmint(node<T>* root)
{
    node<T>* temp= findmin(root);
    return temp->value;
}



//// NEW FUNCTIONS of REDBLACK TREE



// rotate functions

// root er right child ke new root dhore notun tree banabe, then oi tree er root return korbe

template<typename T> node<T>* BST<T> :: rotateLeft( node<T>* &root )
{
    // cout << "rotate left e dhukse" << endl;

    node<T>* x = root->right;
    node<T>* y = x->left;

    // cout << "1" << endl;
    // if( x == NULL ) cout << "x null bhai" << endl;

    x->left = root;
    root->parent = x;
    // cout << " 2" << endl;

    root->right = y;
    if( y != NULL  )
        y->parent = root;

    // cout << "rotateLeft shesh hoise" << endl;
    return x;
}

// node er left child ke root dhore tree banay, tar root return korbe

template<typename T> node<T>* BST<T> :: rotateRight( node<T>* &root )
{
    node<T>* x = root->left;
    node<T>* y = x->right;

    x->right = root;
    root->parent = x;

    root->left = y;
    if( y!= NULL )
        y->parent = root;

    //cout << "rotateRight shesh hoise" << endl;
    return x;
}




/// insertion in red black tree

template <typename T>
void BST<T>::insert(T key, string str)
{
    //cout << "dhukse" << endl;
    if (totalnode == 0)
    {
       // cout << "in 1" << endl;
        mainroot = new node<T>(key,str);
        mainroot->color = black;
        totalnode++;
        return;
    }

    inserthelp(mainroot, key, str);
    
    //cout << "insertion done\n\n" << endl;
}

template <typename T>
node<T>* BST<T>::inserthelp(node<T>* &root, T key, string str)
{
    // cout << "help e dhukse" << endl;
    bool redConflict = false;
    if (root == NULL)
    {
        //cout << "NULL paisi, value disi " << key << endl;
        root = new node<T>( key, str );
        totalnode++;
        return root;
    }

    if (key >= root->key )
    {
        root->right = inserthelp(root->right, key, str);
        root->right->parent = root;

        // identifying if root has red red conflict with its newly added right child
        if( root != mainroot ){
            if( root->color == red && root->right->color == red ){
                redConflict = true;
                // cout << endl;
                // cout << ":right ::::: " << root->key << " -> " << root->right->key << endl;
            }
        }
    }
    else if (key < root->key )
    {
        root->left = inserthelp(root->left, key, str);
        root->left->parent = root;

        // identifying if root has red red conflict with its newly added left child
        if( root != mainroot ){
            if( root->color == red && root->left->color == red ){
                redConflict = true;
                //cout << endl;
                //cout << "left :::::: " << root->key << " -> " << root->left->key << endl;
            }
        }
    }
    // performing rotations when the recusioin is unfolding

    if( ll )
    {
        root = rotateLeft(root);
        root->color = black;            // 1.same level er shob node ke ekoi color dite chacchi
        root->left->color = red;        // 2.rotation er por root er right child mainroot hobe = black color dibo
        ll = false;                     // 3.rotation er por ager root, notun root er left child hoye jabe, so color = red
    }                                   // red disi karon, notun root er right side e insert disi, so right er color red
                                        // + left, right er parent er color black... so left child o red dbo

    else if( rr )
    {
        root = rotateRight( root );
        root->color = black;
        root->right->color = red;
        rr = false;
    }
    else if( rl )
    {
        root->right = rotateRight( root->right );          // ei step e color change er dorkar nai
        root->right->parent = root;                       // duitai red red thakbe then porer step e color change kore root = B, left = red , right = red kore dibo
        //cout << "rl ordhek hoise " << endl; 
        root = rotateLeft( root );
        root->color = black;
        root->left->color = red;
        
        //cout << "rl shesh hoise " << endl; 
        rl = false;
    }
    else if( lr )
    {
        root->left = rotateLeft( root->left );
        root->left->parent = root;

        root = rotateRight( root );
        root->color = black;
        root->right->color = red;

        lr = false;
    }


    // Handling redConflicts
    if( redConflict == true )
    {
        //cout << "conflict kothai check korchi" << endl;
        if( root->parent->right == root )
        {
            if( root->parent->left == NULL || root->parent->left->color == black )
            {
                //cout << "right uncle black " << endl;
                if( root->left != NULL && root->left->color == red  ){
                    rl = true;
                    //cout << "rl" << endl;
                }
                else if ( root->right != NULL && root->right->color == red ){
                    ll = true;          // duitai right e thakle root er left rotation korte hobe
                    //cout << "ll" << endl;

                }
            }  
            else 
            {
                //cout << "right root coloring" << endl;
                root->parent->left->color = black;
                root->color = black;
                
                if( root->parent != mainroot )
                    root->parent->color = red;
            }  
        }
        else 
        {
            if( root->parent->right == NULL || root->parent->right->color == black )
            {
                //cout << "right uncle black " << endl;
                if( root ->right != NULL &&  root->right->color == red )
                    lr = true;
                else if ( root->left != NULL && root->left->color == red)
                    rr = true;             // duitai left e thkle root er right rotation
            }
            else 
            {
                //cout << "left root coloring" << endl;
                root->parent->right->color = black;
                root->color = black;

                if( root->parent != mainroot )
                    root->parent->color = red;
            }
        }
        redConflict = false;
    }
    return root;
}