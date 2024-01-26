#include"BST.cpp"

int main()
{
     BST<int> a;

 


  //  a.insert(10,"Thors");
  //  a.insert(34,"Canute");
  //  a.insert(43,"Olaf");
  //  a.insert(15,"Einer");
  // //  a.insert(40,"Olmar");
  // //  a.insert(53,"Floki");
  // //  a.insert(90,"Thorfinn");
  // //  a.insert(12,"Snake");
  // //  a.insert(78,"Askeladd");


   a.insert(10,"Thors");
   a.insert(34,"Canute");
   a.insert(43,"Olaf");
   a.insert(45,"Einer");
  //  a.insert(40,"Olmar");
  //  a.insert(53,"Floki");
  //  a.insert(90,"Thorfinn");
  //  a.insert(12,"Snake");
  //  a.insert(78,"Askeladd");

   a.deleteKey(43);
   //a.deleteKey(78);

  //  a.insert(15,"Ymir");  




// I 90 Thorfinn
// I 12 Snake
// I 78 Askeladd
// I 53 Floki
// I 15 Ymir




//  a.insert(10,"a");
// a.insert(8,"1");
//    a.insert(12,"2");
//    a.insert(9,"3");
//    a.insert(11,"4");
//    a.output();
// //    a.find(12);
// //    a.inorder();
// //    a.Delete(8);
   a.output();


//     //  FILE* fp1 = freopen("input.txt", "r", stdin);
//     //  if (fp1 == NULL)
//     //  {
//     //      cout << "input file couldn't be opened" << endl;
//     //      return 1; // Exit the program with an error code
//     //  }

//     //  FILE* fp2 = freopen("output.txt", "w", stdout);
//     //  if (fp2 == NULL)
//     //  {
//     //      cout << "output file couldn't be opened" << endl;
//     //      return 1; // Exit the program with an error code
//     //  }

//      while (1)
//      {
//          char check;
//          int num;
//          string str;
//          scanf(" %c", &check); // Skip any leading whitespace (including newline)

//          switch (check)
//          {
//          case 'I':
//              scanf("%d", &num);
//              cin >> str;
//              a.insert( num, str );
//              //a.output();
//              cout <<"insertion done"<< endl;
//              break;

//          case 'D':
//              scanf("%d", &num);
//              a.Delete(num);
//              a.output();
//              cout << endl;
//              break;

//          case 'T':
//              cin >> str;
//              if (str == "In")
//              {
//                  a.inorder();
//                  cout << endl;
//              }
//              else if (str == "Pre")
//              {
//                  a.preorder();
//                  cout << endl;
//              }
//              else if (str == "Post")
//              {
//                  a.postorder();
//                  cout << endl;
//              }
//              break;

//          case 'F':
//              scanf("%d", &num);
//              a.find(num);
//              break;

//          default:
//              break;
//          }
//      }
//     return 0;
}
