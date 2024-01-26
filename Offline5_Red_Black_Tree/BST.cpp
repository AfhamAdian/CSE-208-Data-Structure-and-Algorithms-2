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
        //cout << "not found" << endl;
        return NULL;
    }
    if (root->key == key)
    {
        //cout << "found " << endl;
        return root;
    }
    if (key > root->key)
    {
        return findhelp(root->right, key);
    }
    if (key < root->key)
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

// template<typename T> void BST<T> :: Delete(T key)
// {
//     deletehelp(mainroot,key);
// }

// template<typename T>node<T>* BST<T>::deletehelp(node<T>* &root, T key)
// {
//     if (root == NULL) return NULL;

//     if (root->value > key)
//     {
//         root->left = deletehelp(root->left, key);
//     }
//     else if (root->value < key)
//     {
//         root->right = deletehelp(root->right, key);
//     }
//     else // root->value == key
//     {
//         if (root->right == NULL && root->left == NULL)
//         {
//             delete root;
//             return NULL;
//         }
//         else if (root->right == NULL)
//         {
//             node<T>* temp = root;
//             root = root->left;
//             delete temp;
//         }
//         else if (root->left == NULL)
//         {
//             node<T>* temp = root;
//             root = root->right;
//             delete temp;
//         }
//         else // Both left and right subtrees are present
//         {
//             node<T>* temp = findmin(root->right);
//             root->value = temp->value;
//             root->right = deletehelp(root->right, temp->value);
//         }
//     }
//     return root;
// }

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

    //
    cout << "rotateRight shesh hoise" << endl;
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




//// bismillah deletioinshuru friday 11.03 e /////


template <typename T> node<T>* BST<T> :: replacedNode( node<T>* &x )
{
    if( x->left != NULL && x->right != NULL ){          // node er 2 ta child e thakle
        return findmin( x->right );
    }

    if( x->left == NULL && x->right == NULL ){          // x leaf hole
        return NULL;
    }

    if( x->left != NULL ) return x->left;
    else return x->right;
}


template <typename T> void BST<T> :: fixDB ( node<T>* &x )
{
    if( x == mainroot ) return;

    node<T>* sibling = x->getSiblingNode();
    node<T>* parentX = x->parent;

    if( sibling == NULL ) {              // kono sibling nai,s o db parent e push kore fix kora lgbe
        fixDB( parentX );
        return;
    }
    
    // sibling thakle:

    if( sibling->color == red )          // sibling red hole, CASE 4
    {
        parentX->color = red;            // parent, sibling er color swap
        sibling->color = black;

        if( sibling->isLeftChild() ){    // DB er dike rotation
            rotateRight( parentX );     
        } else{
            rotateLeft( parentX );
        } 

        fixDB( x );                      // DB thakle, reapply other cases
        return;
    }

    // Now sibling color is surely black, so

    if( sibling->redChildfinder() )
    {
        if( sibling->left != NULL && sibling->left->color == red )
        {
            if( sibling->isLeftChild() ){                   // CASE 6 : sibling black, far child red 

                sibling->left->color = sibling-> color;     // sibling must be black as child is red, so ekhane red child ke black banacchi
                sibling->color = parentX->color;            // parent & sibling er color swap
                //parentX->color = black;

                rotateRight( parentX );                     // DB er dike rotation
            }   
            else                                            // right-left config
            {                                               // case 5 -> case 6
                sibling->left->color = parentX->color;       

                rotateRight( sibling );
                rotateLeft( parentX );
            }                                    
        }
        else
        {
            if( sibling->isLeftChild() ){                   // right-left config
                                                            // case 5 -> case 6
                sibling->right->color = parentX->color;
                rotateLeft( sibling );
                rotateRight( parentX );
            }
            else{                                           // right-right config
                                                            // case 6
                sibling->right->color = sibling->color;     
                sibling->color = parentX->color;
                rotateRight( parentX );
            }
        }
        parentX->color = black;
    }
    else
    {
        // sibling black + sibling er 2 ta childreno BLack
        // CASE 3

        sibling->color = red;                       // DB parent ke 1ta black diye dibe, then sibling red hobe
        if( parentX->color == black )
             fixDB ( parentX );
        else 
            parentX->color = black;
    }

}


template <typename T> void BST<T> :: deleteNode( node<T>* &v)
{
    node<T>* u = replacedNode( v );

    node<T>* parent = v->parent;
    bool DB;

    if( (u == NULL || u->color == black) && ( v->color == black ) ) DB = true;
    else DB = false;

    // 1.basically amra leaf pele or kono node er just 1 ta child tahkeli,node delete korbo
    // 2.node u,v pawar por balancing er jnno coloring + DB check kore, balance korbo
    // 3. 1 er case na pawa prjnto recursively khujte tahkbo

    // v node leaf hole
    if( u == NULL )
    {
        if( v == mainroot ){
            mainroot = NULL;
            delete v;
            return;
        }

        if ( DB == true ) {                   // v te null add korle v te DB hobe
            fixDB( v );
        }
        else {
            if( v->getSiblingNode() != NULL )
                v->getSiblingNode()->color = red;
        }

        if ( v->isLeftChild() ) parent->left = NULL;
        else parent->right = NULL;

        delete v;
        return;
    }

    if( v->left == NULL || v->right == NULL ){              // jenoko 1 ta child null 
        
        if( v == mainroot ){                                // red_black tree er Condition er jnno mainroot er ek side e child thakle,1 tar beshi child tahkte parbe na
            v->key = u->key;
            v->value = u->value;
            v->output = u->output;

            v->left = v->right = NULL;
            delete u;
            return;
        }

        if( v->isLeftChild() )
            parent->left = u;
        else 
            parent->right = u;

        cout << "deleting v in 21: " << v->key << endl;
        cout << "parent p: " << parent->key<< endl;
        cout << "u : " << u->key << endl;
        delete v;
        u->parent = u;
        
        if( DB == true ){
            fixDB( u );                                  // normally u+v er color u te push kori, ekhane u,v duitai e black hawai u te DB push hobe
        } else {
            u->color = black;                            // u red thakle, v er black diye replace korar por u black hoye jabe
        }
        return;
    }

    /// now V has 2 children, we can not delete it, swap value with successor and find a node that we can delete

    // swapping u and v values
    bool temp = v->color;
    string tempStr = v->value;
    string tempOutput = v->output;
    int tempKey = v->key;
    
    u->color = v->color;
    u->key = v->key;
    u->value = v->value;
    u->output = v->output;

    v->color = temp;
    v->key = tempKey;
    v->value = tempStr;
    v->output = tempOutput;

    deleteNode(u);
}



template <typename T> void BST<T> :: deleteKey( int n )
{
    if( mainroot == NULL )
        return;
    
    node<T>* v = find(n);
    node<T>* u;

    if( v == NULL ){
        cout << "no such key found " << endl;
        return;
    }

    deleteNode(v); 

}
