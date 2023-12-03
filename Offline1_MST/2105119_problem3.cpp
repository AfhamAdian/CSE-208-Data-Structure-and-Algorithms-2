 #include<iostream>
#include<vector>
#include<algorithm>

// #include <bits/stdc++.h>

using namespace std;

template<typename T> class Graph
{
   vector<vector<int>> edgegraph;
   vector<vector<int>> edgegraphPr2;
   int nodecount;

   vector<vector<int>> mst;  
   vector<int> parent;  
   vector<int> rank; 
   int cost;      

   vector<vector<vector<int>>> allcomb;
   vector<vector<vector<int>>> allCostComb;
   vector<vector<vector<int>>> allMstAns;

   vector<int> critEdge;
   vector<int> psdoEdge;

   public:

   Graph(int n)
   {
      nodecount = n;
      cost = 0;
      
      for( int i = 0;i<n; i++)      //initializing 
      {
         parent.push_back(-1);
         rank.push_back(1);
      }
   }

   void addEdge(T w, T a, T b)
   {
      edgegraph.push_back({w,a,b});
      edgegraphPr2.push_back({w,a,b});
   }

   vector<vector<T>> getEdgeList(){
      return edgegraph;
   }
   
   void print(){
       for( auto edge : edgegraph){
         cout << "[ w:" << edge[0] << " a: " << edge[1] << " b: " << edge[2] << " ]" << endl;
      }
   }

   ////////////////////// Functions for all possible combination /////////////////
   
   void generateCombo(vector<vector<int>> arr) {

    int n = arr.size();

      for (int i = 0; i < (1 << n); ++i) {
         vector<vector<int>> currentCombination;
         for (int j = 0; j < n; ++j) {
               if (i & (1 << j)) {
                  currentCombination.push_back(arr[j]);
               }
         }
         allcomb.push_back(currentCombination);
      }


      // for( auto vv : allcomb){
      //    for( auto v: vv ){
      //       cout << "[ w:" << v[0] << " a: " << v[1] << " b: " << v[2] << " ]" << ", ";
      //    }
      //   cout << endl;
      // }

      //cout << "All possible combination generation complete" << endl;
   }



   /////////////////////// Functions For MST //////////////////////////

   int find( int i){
      if( parent[i] == -1) return i;

      return find(parent[i]);
   }

   void join(int a, int b)
   {
      parent[a] = b;
   }

   /////////////////// kruskal for MST /////////////////

   void kruskal()                              
   {     
      cost = 0;                     
      sort(edgegraph.begin(),edgegraph.end()); 

      for (auto edge : edgegraph)
      {
         int f1 = find(edge[1]);
         int f2 = find(edge[2]);

         if( f1 != f2 ){
            mst.push_back(edge);
            cost += edge[0];
            join(f1,f2);                     // As we should join the roots
         }
      }

    //   for( auto edge : mst){
    //      cout << "[ w:" << edge[0] << " a: " << edge[1] << " b: " << edge[2] << " ]" << endl;
    //   }
    //   cout << "Cost : " << cost << endl; 
   }


   ///////// Function for Cycle Detection ///////////

   bool cycleDet( vector<vector<int>> tempGraph)            //return false if cycle found
   {
      //sort(tempGraph.begin(),tempGraph.end());
      for(int i = 0; i<nodecount; i++){
          parent[i] = -1;
      }
      
      for (auto edge : tempGraph)
      {
         int f1 = find(edge[1]);
         int f2 = find(edge[2]);

         if( f1 != f2 ){
            mst.push_back(edge);
        //cout << " a : " << edge[1] << " b: " << edge[2] << " ,";
        // += edge[0];
            join(f1,f2);                                  // As we should join the roots
         }
         else {
            return false;
         }
      }
        // cout << endl;
        // for(int i = 0; i<nodecount; i++){
        //     cout << parent[i] << " ";
        // }
        // cout << endl;
      return true;
   }

   //////////// Function for Finding All MST /////////////

   void allMst()
   {
      kruskal();
      generateCombo(edgegraph);

    //   cout << "All combo size : " << allcomb.size() << endl;

      for( auto vv: allcomb)
      {
         int flag[nodecount] = {0},flag2 = 0;
         if( vv.size() != nodecount-1 ) continue;
         int tempcost = 0;
         for(auto v: vv)
         {
            tempcost += v[0];
            flag[v[1]]++;
            flag[v[2]]++;
         }
         for(int i = 0; i<nodecount; i++)
         {
            if(flag[i] == 0) flag2 = 1;
         }
         if(tempcost==cost && flag2 == 0) allCostComb.push_back(vv);
      }

    //   cout << "Cost MSt : " << allCostComb.size() << endl;

      for( auto vv : allCostComb){
         if( cycleDet(vv) == true ){
            allMstAns.push_back(vv);
         }
      }

    //   for( auto vv: allMstAns)
    //   {
    //      for(auto v: vv)
    //      {
    //         cout << "[ w:" << v[0] << " a: " << v[1] << " b: " << v[2] << " ]" << ", "; 
    //      }
    //      cout << endl;
    //   }
   }

   //////////////// Function for edge number //////////////

   bool edgeCompare(vector<int> a, vector<int> b)
   {
      if( a[0] == b[0] && a[1] == b[1] && a[2] == b[2]) return true;
      return false;
   }


   void critEdgeFinder()
   {
      allMst();
      
    //   for( auto edge : edgegraphPr2)
    //   {
    //     cout << edge[1]+1 << " " << edge[2]+1 << endl;
    //   }

      int count = 0;
      for( auto edge : edgegraphPr2)
      {
        
         //cout <<"[ " << edge[1]+1 << " " << edge[2]+1 << " " << edge[0] << " ]"<< endl;
         int flag = 0;
         for(auto vv : allMstAns)
         {
            for( auto v : vv)
            {
               if( edgeCompare(v,edge) ) {
                  flag++;
                  break;
               }
            }
         }
        // if( flag == allMstAns.size() ) critEdge.push_back(count);
        // else if( flag != 0 ) psdoEdge.push_back(count);

        if( flag == 0 ){}
        else if( flag == allMstAns.size() ) critEdge.push_back(count);
        else psdoEdge.push_back(count);

        count++;
      }


        if( critEdge.size() != 0 ){
            cout << "Critical edges: [";
            for( int i = 0; i<critEdge.size(); i++)
            {
                cout << critEdge[i];
                if( i!= critEdge.size()-1 ) cout << ",";
            }
            cout << "]" << endl;
        }

        if( psdoEdge.size() != 0 ){
                cout << "Pseudo critical edges: [";
                for( int i = 0; i<psdoEdge.size(); i++)
                {
                    cout << psdoEdge[i];
                    if( i!= psdoEdge.size()-1 ) cout << ",";
                }
                cout << "]";
        }
   }

};


int main()
{
   int node,edge;

   cin >> node >> edge;
   Graph<int> graph(node);

   while(edge--)
   {
      int w,a,b;
      cin >> a >> b >> w;

      graph.addEdge(w,a,b);
   }
   
    //graph.print();
    //graph.allMst();
   graph.critEdgeFinder();
  
   
   return 0;
}