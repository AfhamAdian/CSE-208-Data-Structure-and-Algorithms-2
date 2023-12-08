#include<iostream>
#include<vector>

using namespace std;

template<typename T> class Edge 
{
    public :
    
    int v;
    T wght;

    Edge(int v, T wght)
    {
        this->v = v;
        this->wght = wght;
    }
};


template<typename T> class Graph        // graph T = Wieght datatype
{
    int nodes;
    vector<vector<Edge<T>>> edgelist;

    vector<int> dist;

    public :

    Graph(int nodes)
    {
        this->nodes = nodes;
        edgelist.resize(nodes);
        dist.resize(nodes);

        reset_arr(dist);
    }

    void addEdge( int a, int b , T wght)            //Pushes Directed Edge 
    {
        edgelist[a].push_back(Edge<T>(b,wght));
    }

    // void removeEdge( int a, int b )
    // {
    //     for( )
    // }

    void reset_arr( vector<int> & arr)
    {
        for ( int i = 0; i<arr.size(); i++) arr[i] = INT_FAST32_MAX;
    }

    void print_graph()
    {
        for( int i = 0; i<edgelist.size(); i++ )
        {
            for( auto e : edgelist[i])
            {
                cout << i << " -> " << e.v << " w: " << e.wght << endl;
            }
        }
    }


    void print_distAll()
    {
        for( auto a : dist)
            cout << a << " ";
        cout << endl;
    }


    ////////////// BellMan_Ford ////////////////

    bool calcDistAll ( int src )            /// returns false if negetive cycle found
    {
        reset_arr(dist);
        dist[src] = 0;

        for( int count = 0; count <nodes-1; count++)
        {
            for( int  i = 0; i<nodes; i++)
            {
                for( auto e : edgelist[i])
                {
                    int u = i;
                    int v = e.v;

                    if( dist[u] != INT32_MAX && dist[v] > dist[u] + e.wght){
                            dist[v] = dist[u]+e.wght;
                            //cout << "ok  " << v << endl;
                    }
                }
            }
        }


        // checking if graph has negetive_cycle
        for( int  i = 0; i<nodes; i++)
        {
            for( auto e : edgelist[i])
            {
                int u = i;
                int v = e.v;

                if( dist[u] != INT32_MAX && dist[v] > dist[u] + e.wght)
                    return false;
            }
        }
        return true;
    }

    void minDist ( int src, int des, int lower, int upper, int extrA, int extrB)
    {
        vector<vector<Edge<T>>> temp = edgelist ;

        calcDistAll( src );

        int dist1 = dist[des];
        int dist2 = INT32_MAX, dist3=INT32_MAX;

        cout << " 1" << endl;

        addEdge( extrA, extrB, (T)lower );
    
        bool flag = calcDistAll( src );


        int t = lower;
        while( t <= upper && calcDistAll(src) == false){
            t++;
            edgelist = temp;
            addEdge( extrA, extrB, t);
        }

        int rrValue = t;
        dist2 = dist[des];

        if( dist2 == dist1){
            cout << "impossible" << endl;
        }
        else {
            cout << rrValue << " " << dist2 << endl;
        }

        edgelist = temp;                /// returning to the ORIGINAL Graph

        // dist2 = dist[des];
        // cout << flag << endl;

        // if( dist1 ==  INT32_MAX ){
        //     cout << " 1qqqq" << endl;
        //     cout << "impossible" << endl;
        //     edgelist = temp;
        //     return;
        // }

        // if( flag == false)
        // {
        //     if( upper < 0) {
        //         cout << "impossible" << endl;
        //         edgelist = temp;
        //         return;
        //     }
        //     edgelist = temp;
        //     addEdge( extrA, extrB, 0);

        //     calcDistAll( src );
        //     dist2 = dist[des];

        //     if( dist2 == dist1 ){
        //         cout<< " 4 " << endl;
        //         cout << "impossible" << endl;
        //         edgelist = temp;
        //         return;
        //     }
        //     else {
        //         cout << "0 " << dist2 << endl;
        //         edgelist = temp;
        //         return;
        //     }
        // }
        // else
        // {
        //     cout << " 2" << endl;
        //     cout <<  lower <<  " " << dist2 << endl;
        //     edgelist = temp;
        //     return;
        // }
        // cout << " 3" << endl;

    }



};





int main()
{
    int nodes,edges,a,b,lower,upper,src,des;
    
    cin >> nodes >> edges;

    Graph<int> graph(nodes+1);

    for( int i = 0; i<edges; i++)
    {
        int a,b,w;
        cin >> a >> b >> w;

        graph.addEdge( a,b,w );
    }
    cin >> a >> b;
    cin >> lower >> upper;
    cin >> src >> des;

    graph.minDist(src,des,lower,upper,a,b);

    //  cout <<  graph.calcDistAll(1) << endl;;
    //  graph.print_distAll();

    //graph.print_graph();

    return 0;
}