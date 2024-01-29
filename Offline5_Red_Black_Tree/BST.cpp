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






/////////////////////////////////// NEW FUNCTIONS of REDBLACK TREE ///////////////////


template<typename T> bool BST<T> :: isEmpty()
{
    return totalnode == 0;
}

template<typename T> int BST<T> :: size()
{
    return totalnode;
}

template<typename T> bool BST<T> :: clear()
{
    if( totalnode == 0 ) return false;

    while( totalnode ){
        deleteNode(mainroot);
    }
    
    return true;
}


template <typename T> void BST<T>::inorderNew()
{
    inorderNew(mainroot);
}

template <typename T> void BST<T>::inorderNew(node<T> *&root)
{
    if (root == NULL)
        return;
    inorderNew(root->left);
    if( root->color == red ) {
        cout <<  dye :: light_red(root->key);
        cout << " -> " << dye :: light_red(root->value ) << endl;
    }
    else {
        cout <<  root->key;
        cout << " -> " << root->value << endl;
    }
    
    inorderNew(root->right);
}

// rotate functions

// root er right child ke new root dhore notun tree banabe, then oi tree er root return korbe

template<typename T> node<T>* BST<T> :: rotateLeft( node<T>* root )
{
    // cout << "rotate left e dhukse,key : " << root->key  << endl;

    node<T>* temp = root;
    node<T>* x = root->right;
    node<T>* y = x->left;

    x->left = root;
    root->right = y;

    root->parent = x;

    if( y != NULL  )
        y->parent = root;

    if( temp == mainroot ){ 
        mainroot = x;
        mainroot->parent = NULL;
    }

    // cout << "rotateLeft shesh hoise" << endl;
    return x;
}

// node er left child ke root dhore tree banay, tar root return korbe

template<typename T> node<T>* BST<T> :: rotateRight( node<T>* root )
{
    node<T>* temp = root;
    node<T>* x = root->left;
    node<T>* y = x->right;

    x->right = root;
    root->left = y;

    root->parent = x;

    if( y != NULL )
        y->parent = root;

    if( temp == mainroot ){
         mainroot = x;
         mainroot->parent = NULL;
    }
    
    // cout << "rotateRight shesh hoise " << root->key << endl;

    return x;
}




//// rotate new

template<typename T> void BST<T> :: rotateRight2(node<T>* &x) {

    node<T>* parent = x->parent;
    node<T>* newRoot = x->left;

    if( x == NULL ) {
        cout << "NO Right Child. Left rotation cannot be done" << endl;
        return;
    }

    node<T>* newLeft = x->left->right;

    if( parent != NULL )
    {
        if(x->isLeftChild())  
            parent->left = newRoot;
        else 
            parent->right = newRoot;

        newRoot->parent = parent;
    }
    else {
        newRoot->parent = NULL;
        mainroot = newRoot;
    }

    newRoot->right = x;
    x->parent = newRoot;

    x->left = newLeft;
    if( newLeft != NULL )   newLeft->parent = x;
  }



template<typename T> void BST<T> :: rotateLeft2(node<T>* &x) {

    node<T>* parent = x->parent;
    node<T>* newRoot = x->right;

    if( x == NULL ) {
        cout << "NO Left Child. Right rotation cannot be done" << endl;
        return;
    }

    node<T>* newLeft = x->right->left;

    if( parent != NULL )
    {
        if(x->isLeftChild())  
            parent->left = newRoot;
        else 
            parent->right = newRoot;

        newRoot->parent = parent;
    }
    else {
        newRoot->parent = NULL;
        mainroot = newRoot;
    }

    newRoot->left = x;
    x->parent = newRoot;

    x->right = newLeft;
    if( newLeft != NULL )   newLeft->parent = x;
  }

///////////////////////////////////////////



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

    if( key == root->key )
    {
        root->value = str;
        root->output = to_string(key) + "_" + str;
    }
    else if (key > root->key )
    {
        root->right = inserthelp(root->right, key, str);
        root->right->parent = root;

        // identifying if root has red red conflict with its newly added right child
        if( root != mainroot ){
            if( root->color == red && root->right->color == red ){
                redConflict = true;
                // cout << endl;
                // cout << "right ::::: " << root->key << " -> " << root->right->key << endl;
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

    //rotations perform korchi jokhon recusioin is unfolding

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
            redConflict = false;
            return root;
        }

        // root jodi parent er left e thake

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

        redConflict = false;
    }
    return root;
}




//// bismillah deletioin shuru friday 11.03 e /////


template <typename T> node<T>* BST<T> :: replacedNode( node<T>* &x )
{
    bool check = false;                                 // aj

    if( x->left == NULL && x->right == NULL ){          // x leaf hole
        return NULL;
    }

    check = true;
    // cout << check << endl;

    if( x->left != NULL && x->right != NULL ){          // node er 2 ta child e thakle
        return findmin( x->right );
    }

    if( x->left != NULL ) return x->left;
    else return x->right;
}


template <typename T> void BST<T> :: fixDB ( node<T>* &x )
{
    if( x == mainroot ){ 
        return;
    }

    node<T>* sibling = x->getSiblingNode();
    node<T>* parentX = x->parent;

    // cout << parentX << endl;
    // cout << parentX->right << " rl " << parentX->left << endl;
    // cout << "s   " << sibling <<endl;
    // return;

    if( sibling == NULL ) {              // kono sibling nai,s o db parent e push kore fix kora lgbe
        fixDB( parentX );
        return;
    }
    
    // sibling thakle :

    if( sibling->color == red )          // sibling red hole, CASE 4
    {
        parentX->color = red;            // parent, sibling er color swap
        sibling->color = black;

        if( sibling->isLeftChild() ){    // DB er dike rotation
            rotateRight2( parentX );     
        } else{
            rotateLeft2( parentX );
        } 

        fixDB( x );                      // DB thakle, reapply other cases
        return;
    }

    // Now sibling color is surely black, so

    if( sibling->redChildfinder() )
    {
        // cout << " sibling black and has one red child " <<endl;
        if( sibling->left != NULL && sibling->left->color == red )
        {
            if( sibling->isLeftChild() ){                   // CASE 6 : sibling black, far child red 
                
                // cout << "Left Left CASE 6 " << x->key << endl;
                sibling->left->color = sibling-> color;     // sibling must be black as child is red, so ekhane red child ke black banacchi
                sibling->color = parentX->color;            // parent & sibling er color swap
                //parentX->color = black;

                rotateRight2( parentX );                     // DB er dike rotation
            }   
            else                                            // right-left config
            {                                               // case 5 -> case 6
                // cout << "right-left1 CASE 5 " << x->key << endl;
                sibling->left->color = parentX->color;       

                //sibling->parent->right = rotateRight( sibling );
                rotateRight2( sibling );
                rotateLeft2( parentX );
            } 
            parentX->color = black;
            return;          
        }
     
        // sibling er right child red hole

        if( sibling->isLeftChild() ){                   // right-left config
                                                            // case 5 -> case 6
            
            // cout << "right-left2 CASE 5 " << x->key << endl;
            sibling->right->color = parentX->color;
            rotateLeft2( sibling );
            rotateRight2( parentX );
        }
        else{                                           // right-right config
                                                        // case 6
            // cout << "right-right CASE 6 " << x->key << endl;
            sibling->right->color = sibling->color;     
            sibling->color = parentX->color;
            rotateLeft2( parentX );
        }
        parentX->color = black;
        return;

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


template <typename T> void BST<T> :: deleteNode( node<T>* v )
{
    node<T>* u = replacedNode( v );

    // cout << "Node to be deleted V : " ;
    // if( v != NULL ) cout << v->key << " ";
    // else cout << " null ";

    // if( u!= NULL ) cout << "u : " << u->key << " " << endl;
    // else cout << " u : null " << endl;

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
            totalnode--;
            return;
        }

        if ( DB == true ) {                   // v te null add korle v te DB hobe
            // cout << "catch 12 : fixDB running  " << v->key << endl;
            fixDB( v );
        }
        else {
            if( v->getSiblingNode() != NULL )
                v->getSiblingNode()->color = red;
        }

        if ( v->isLeftChild() ) parent->left = NULL;
        else parent->right = NULL;

        totalnode--;
        delete v;
        return;
    }

    // cout << "v in deletenode 2 " << v->key << endl;

    if( (v->left == NULL) || (v->right == NULL) ){              // jenoko 1 ta child null 
        
        //output();
        //cout << endl;
        //cout << mainroot->key << " " << mainroot->left << " " << mainroot->right << endl;
        //cout << v->key <<" " << v->left << "  " << v->right << endl;
        // cout << "one child in deletenode " << endl;
        
        if( v == mainroot ){                                // red_black tree er Condition er jnno mainroot er ek side e child thakle,1 tar beshi child tahkte parbe na
           
            mainroot = u;
            u->key = v->key;
            u->value = v->value;
            u->output = v->output;

            u->right = u->left = NULL;
            
            totalnode--;
            delete v;
            return;
        }

        // cout << "deleting v in 21: " << v->key << endl;
        // cout << "parent p: " << parent->key<< endl;
        // cout << "u : " << u->key << endl;
        // cout << "parent right : " << parent->right->key << endl;
        // cout << endl;

        if( v->isLeftChild() == true ){
            parent->left = u;
            // cout << "left " <<endl;
        }
        else{
            parent->right = u;
            // cout << "right " <<endl;
        }

        // cout << "deleting v in 21: " << v->key << endl;
        // cout << "parent p: " << parent->key<< endl;
        // cout << "u : " << u->key << endl;
        // cout << "parent right : " << parent->right->key << endl;

        totalnode--;
        delete v;
        u->parent = parent;
         
        if( DB == true ){
            fixDB( u );                                  // normally u+v er color u te push kori, ekhane u,v duitai e black hawai u te DB push hobe
        } else {
            u->color = black;                            // u red thakle, v er black diye replace korar por u black hoye jabe
        }
        return;
    }

    /// now V has 2 children, we can not delete it, swap value with successor and find a node that we can delete
    // swapping u and v values

    string tempStr = u->value;
    string tempOutput = u->output;
    int tempKey = u->key;
    
    u->key = v->key;
    u->value = v->value;
    u->output = v->output;

    v->key = tempKey;
    v->value = tempStr;
    v->output = tempOutput;

    deleteNode(u);
}



template <typename T> void BST<T> :: deleteKey( int n )
{
    // cout << n << " key is to be delted\n " << endl;
    node<T>* v = find(n);
        if( v == NULL ){
        cout << n << " not found " << endl;
        return;
    }

    if( mainroot == NULL )
        return;
    
    //<T>* v = find(n);
    node<T>* u;

    if( v == NULL ){
        cout << n << " not found " << endl;
        return;
    }
    deleteNode(v); 
}
