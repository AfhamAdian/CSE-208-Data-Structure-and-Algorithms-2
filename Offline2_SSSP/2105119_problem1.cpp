#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

template<typename T>
class Edge 
{
public:
    int v;
    T wght;

    Edge(int v, T wght)
    {
        this->v = v;
        this->wght = wght;
    }
};

template<typename T>
class Graph
{
    int **nodeArr;
    int capacity, city, road;

    vector<int> cost;
    vector<vector<Edge<T>>> adjCity;
    vector<vector<Edge<T>>> finalGraph;


public:

    Graph(int city, int road, int cap, vector<int>& cost)
    {
        this->city = city ;
        this->road = road ;
        this->capacity = cap;
        this->cost = cost;
        adjCity.resize(this->city+1);

        nodeArr = new int*[this->city+1];
        for (int i = 0; i < this->city+1; i++)
        {
            nodeArr[i] = new int[capacity+1];
        }

        int count = 0;
        for (int i = 1; i < this->city+1; i++)
        {
            for (int j = 0; j < capacity+1; j++)
            {
                //cout << count << " ";
                nodeArr[i][j] = count;
                count++;
            }
            //cout << endl;
        }
    }

    void printArr()
    {
        for (int i = 1; i < city+1; i++)
        {
            for (int j = 0; j < capacity+1; j++)
            {
                cout << nodeArr[i][j] << " ";
            }
            cout << endl;
        }
    }

    void addCityEdge(int a, int b, T w)
    {
        adjCity[a].push_back(Edge<T>(b, w));            ///////// undirected edge
        adjCity[b].push_back(Edge<T>(a, w)); 
    }

    void addFinalEdge( int a, int b, T w)               ///////// adds directed graph
    {                                                   
        finalGraph[a].push_back(Edge<T>(b, w));         
    }                                                   
            
    void makeFinalGraph()                                  //////// Final Grid Graph Maker
    {
        finalGraph.clear();
        finalGraph.resize((city)*(capacity+1));                    

        //cout << "resized" << endl;

        for (int i = 1; i < city+1; i++)
        {
            for (int j = 0; j < capacity+1; j++)
            {
                if( j < capacity ) {
                    addFinalEdge( nodeArr[i][j], nodeArr[i][j+1], cost[i] );
                }

                for( auto e : adjCity[i] ){
                    if(e.wght > j) continue;
                    else{
                        addFinalEdge( nodeArr[i][j], nodeArr[e.v][j-e.wght] , 0 );
                    }
                } 
            }
        }
        //cout << "Final Graph Completed" << endl;
    }

    void finalGraphPrint()
    {
        cout << finalGraph.size() << endl;
        for( int i = 0; i<finalGraph.size(); i++)
        {
            cout << i << " : ";  
            for( int j = 0; j<finalGraph[i].size(); j++ )
            {
                cout << finalGraph[i][j].v << "(" << finalGraph[i][j].wght << ")" << ", ";
            }
            cout << endl;
        }
    }

    //////////////////// Djkstra algo //////////////////

    void minDistHelper( int src, int des)                                   ///
    {
        //cout << " final kaj kore na " << endl;
        makeFinalGraph();
        //cout <<"finalgraph sze    " <<  finalGraph.size() << endl;
        minDist( src, des, finalGraph );
    }

    void minDist(int src, int des, vector<vector<Edge<T>>> adjList)          /// basically djaktra on any adjlist graph
    {
        //cout << adjList.size() << endl;
        int mincost = 0;

        vector<int> visit( adjList.size(), -1 );
        vector<int> dist ( adjList.size(), INT32_MAX );

        priority_queue< pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > pq;

        dist[src-1] = 0;
        pq.push(make_pair(0,src-1));


        while( !pq.empty() )
        {
            int u = pq.top().second;
            pq.pop();

            //cout << "popped " << u << ", ";

            for( auto e : adjList[u] )
            {
                int v = e.v;
                int roadDist = e.wght;
                if( visit[v] == 1) continue;


                if( dist[v] > dist[u] + roadDist ) {
                    dist[v] = dist[u]+roadDist;
                    pq.push( make_pair(dist[v],v) );
                }
            }
            visit[u] = 1;
        }

        //cout << (capacity+1)*(des-1) << endl;

        if( dist[ (capacity+1)*(des-1) ] == INT32_MAX){
            cout << "impossible" << endl;
            return;
        }
        cout << dist[ (capacity+1)*(des-1) ] << endl;
    }

};

int main()
{
    int city, road, capacity;

    cin >> city >> road >> capacity;

    vector<int> cityCost;
    cityCost.push_back(INT32_MAX);      /// cost size should be one more than 

    for (int i = 0; i < city; i++)
    {
        int temp;
        cin >> temp;
        cityCost.push_back(temp);
    }

     Graph<int> graph(city, road, capacity, cityCost);           // graph created

    for( int  i = 0; i<road; i++)
    {
        int a,b,dist;
        cin >> a >> b >> dist;
        graph.addCityEdge(a, b, dist);
    }

    int src,des;
    cin >> src >> des;

    //graph.minDistHelper(src,des);

    // graph.printArr() ;
    // cout << endl;

    // graph.makeFinalGraph();
    // graph.finalGraphPrint();

    // cout << endl;

    graph.minDistHelper(src,des);

    //vector<vector<Edge<int>>> adjList = {{Edge<int>(2,2),Edge<int>(1,4)}, {}, {Edge<int>(1,1)} };
    //graph.minDist(0,1,adjList);


    return 0;
}
