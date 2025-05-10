// #include"BST.cpp"
#include"test.cpp"

int main()
{
    BST<int> a;
    int i = 1;
     FILE* fp1 = freopen("input.txt", "r", stdin);
     if (fp1 == NULL)
     {
         cout << "input file couldn't be opened" << endl;
         return 1; // Exit the program with an error code
     }

     FILE* fp2 = freopen("output.txt", "w", stdout);
     if (fp2 == NULL)
     {
         cout << "output file couldn't be opened" << endl;
         return 1; // Exit the program with an error code
     }

     while ( !feof(fp1) )
     {
         char check[5];
         int num;
         
         scanf(" %s", &check); // Skip any leading whitespace (including newline)

        if( strcmp(check,"I") == 0 ){
            char str[100];
            scanf("%d", &num);
            scanf("%s", str);
            cout << "\nCmd " << i << ": " << check[0] << " " << num << " " << str << endl;
            i++;
            a.insert( num, str );
            a.output();
            cout << endl;
        }
           
        else if(strcmp(check,"E") == 0 )
        {
            scanf("%d", &num);
            cout << "\nCmd " << i << ": " << check[0] << " " << num << endl;
            i++;
            node<int>* test = a.find( num );
            a.deleteKey( num );
            if( test != NULL) a.output();
            cout << endl;
        }
           
        else if(strcmp(check,"Clr") == 0 )
        {
            cout << "\nCmd " << i << ": " << check[0] << check[1] << check[2] << endl;
            i++;
            if( a.clear() ) cout << "successful" << endl;
            else  cout << "unsuccessful" << endl;
        }
           
        else if(strcmp(check,"F") == 0 )
        {
            scanf("%d", &num);
            cout << "\nCmd " << i << ": " << check[0] << " " << num << endl;
            i++;
            node<int>* test = a.find( num );

            if( test == NULL ) cout << num << " " << "not found" << endl;
            else cout << num << " " << "found" << endl;

        }
           
        else if(strcmp(check,"Em") == 0 )
        {
            cout << "\nCmd " << i << ": " << check[0] << check[1] << endl;
            i++;
            if( a.isEmpty() ) cout << "yes" << endl;
            else  cout << "no" << endl;
        }
           
        else if(strcmp(check,"S") == 0 )
        {
            cout << "\nCmd " << i << ": " << check[0] << endl;
            i++;
           cout << a.size() << endl;
        }
           
        else if ( strcmp( check,"Itr") == 0)
        {
            cout << "\nCmd " << i << ": " << check[0] << check[1] << check[2] << endl;
            i++;
            a.inorderNew();
        }
           
        else{
            cout << "input error" << endl;
        }
    }
    return 0;
}
