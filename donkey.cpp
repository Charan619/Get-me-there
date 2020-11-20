// C++ program to print the paths between two vertices
#include <bits/stdc++.h>
using namespace std;

void split(list<int>& a, list<int> b, int val)
{
    a.clear();
    bool found = false;
    for( auto i : b)
    {
        if(i == val)
            found = true;
        if(found)
            a.push_back(i);
    }

}

void updatePathCost(vector<list<int>>& paths, map<pair<int, int>, float>& costs, vector<int>& pathCost)
{
    pathCost.clear();
    list<int>::iterator i;
    int n = paths.size(), j, k, m, sum;
    vector<int> path;
    for(j=0;j<n;j++)
    {
        path.clear();
        sum = 0;
        for(i = paths[j].begin(); i != paths[j].end(); ++i)
            path.push_back(*i);
        m = path.size();
        for(k = 0; k < m; k++)
        {
            sum += costs[pair<int,int>(path[k], path[k+1])];
        }
        pathCost.push_back(sum);
    }
}

int findMinPath(vector<int>& pathCost)
{
    int i, idx = 0;
    int n = pathCost.size();

    for(i = 1; i < n; i++)
        if(pathCost[i] < pathCost[idx])
            idx = i;
    return idx;
}

class Graph
{
    public:
        int V;
        int source, dest;
        bool pathExist;
        list<int> *adj;
        vector<int> pathCost;
        vector<list<int>> paths;
        map<pair<int, int>, float> costs;

        Graph(int V, int source, int dest);

        void addEdge(int v, int w, float cost);
        void updateCost(int v, int w, float cost);

        void loadCost();
        void loadPathUtil(int v1, int v2, bool visited[], list<int>& path);
        void loadPath();

        void showPaths(vector<list<int>>& paths, vector<int>& pathCost);
        void showCost();
};

Graph::Graph(int V, int source, int dest)
{
    this->V = V;
    this->source = source;
    this->dest = dest;
    adj = new list<int>[V];
}

void Graph::showPaths(vector<list<int>>& paths, vector<int>& pathCost)
{
    cout<<"-----------------\n";
    list<int>::iterator i;
    for(int j=0;j<paths.size();++j) {
        for(i=paths[j].begin(); i != --paths[j].end(); ++i)
            cout<<*i<<"->";
        cout<<*i<<"\ncost : "<<pathCost[j]<<endl;
    }
}

void Graph::showCost()
{
    pair<int,int> x;
    map<pair<int,int>, float>::iterator i;
    for(i = costs.begin(); i != costs.end(); ++i)
        cout<<"["<<i->first.first<<", "<<i->first.second<<"] : "<<i->second<<endl;
}

void Graph::addEdge(int v, int w, float cost)
{
    adj[v].push_back(w);
    costs.insert(pair<pair<int,int>, float>(pair<int,int>(v,w), cost));
}

void Graph::loadPathUtil(int v1, int v2, bool visited[], list<int>& path)
{
    list<int>::iterator i;

    visited[v1] = true;
    path.push_back(v1);

    if(v1==v2)
    {
        pathExist=true;

        paths.push_back(path);
        for(i = path.begin();i != --path.end() ; ++i)
            cout<<*i<<"->";

        cout<<*i<<endl;
    }
    else
    {
        list<int>::iterator i;
        for (i = adj[v1].begin(); i != adj[v1].end(); ++i)
            if (!visited[*i])
                loadPathUtil(*i, v2, visited, path);
    }

    path.pop_back();
    visited[v1]=false;
}

void Graph::loadPath()
{
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    list<int> path;
    vector<int> cost;
    pathExist=false;

    loadPathUtil(source,dest,visited,path);
    updatePathCost(this->paths, this->costs, this->pathCost);
    if(this->paths.size() > 0)
        pathExist = true;
}

void Graph::updateCost(int v, int w, float cost)
{
    costs[pair<int,int>(v, w)] = cost;
    updatePathCost(this->paths, this->costs, this->pathCost);
}

void copylist(list<int>& b, list<int>& a)
{
    b.clear();
    for(auto x : a)
        b.push_back(x);
}

void traverse(Graph g)
{
    int idx = findMinPath(g.pathCost), index = 0;
    list<int> trav;
    copylist(trav, g.paths[idx]);

    int node1, node2, dist, i, j, v1, v2, cst, n = g.paths.size();
    char ch;
    int nodeorigin = g.source;

    while(true)
    {
        if(trav.begin() != trav.end())
            node1 = trav.front();
        else
            break;
        trav.pop_front();
        if(trav.begin() != trav.end())
            node2 = trav.front();
        else
            break;

        dist = g.costs[pair<int, int>(node1, node2)];

        for(i = 0; i <= dist; i++)
        {
            cout<<"\nPackage travelled "<<i<<"/"<<dist<<"units from town "<<node1<< " to town "<< node2<<" \nUpdate Traffic(y/n) : ";
            cin>>ch;
            if(ch == 'y')
            {
                cout<<"Enter vertex 1 : ";
                cin>>v1;
                cout<<"Enter vertex 2 : ";
                cin>>v2;
                cout<<"Enter cost to be updated : ";
                cin>>cst;
                g.updateCost(v1, v2, cst);
                   dist = g.costs[pair<int, int>(node1, node2)];
                if(idx != findMinPath(g.pathCost))
                {
                   idx = findMinPath(g.pathCost);

                    vector<list<int>> paths1;
                    vector<list<int>> paths2;

                    vector<int> pathCosts1;
                    vector<int> pathCosts2;
                    vector<int> pathCosts3;

                    int idx1, idx2, idx3;
                    for(j = 0; j < n; j++)
                    {
                        if(find(g.paths[j].begin(), g.paths[j].end(), node1) != g.paths[j].end())
                        {
                            list<int> l1;
                            split(l1, g.paths[j], node1);
                            paths1.push_back(l1);
                        }

                        if(find(g.paths[j].begin(), g.paths[j].end(), node2) != g.paths[j].end())
                        {
                            list<int> l2 = {};
                            split(l2, g.paths[j], node2);
                            paths2.push_back(l2);
                        }
                    }
                    updatePathCost(paths1, g.costs, pathCosts1);
                    updatePathCost(paths2, g.costs, pathCosts2);

                    idx1 = findMinPath(pathCosts1);
                    idx2 = findMinPath(pathCosts2);
                    // actual paths 
                    idx3 = findMinPath(g.pathCost);

                    cout<<"Paths from "<<node1<<endl;
                    g.showPaths(paths1, pathCosts1);
                    cout<<"Paths from "<<node2<<endl;
                    g.showPaths(paths2, pathCosts2);
                    cout<<"Paths from Origin "<<endl;
                    g.showPaths(g.paths, g.pathCost);

                    if(pathCosts1[idx1] < pathCosts2[idx2] && pathCosts1[idx1] <= pathCosts3[idx3] )
                    {
                        cout<<"\nFace and Support 1 \n";
                        copylist(trav, paths1[idx1]);
                        break;
                    }
                    else if(pathCosts1[idx1] <= pathCosts2[idx2] && pathCosts2[idx1] <= pathCosts3[idx3])
                    {
                        cout<<"\nFace and Support 2 \n";
                        copylist(trav, paths2[idx2]);
                        break;
                    }
                    else
                    {
                        cout<<"\nFace and Suicide \n";
                        copylist(trav, g.paths[idx3]);
                    }
                }
            }
        }
    }
}


int main()
{
    cout<<"DONKEY AND SMUGGLER ALGORITHM\n";
    int n, opt = 0, v1=0, v2=6;
    cout<<"Enter the number of vertices : ";
    cin>>n;
	cout<<"Enter starting node : ";
    cin>>v1;
    cout<<"Enter destination node : ";
	cin>>v2;
    
    Graph g(n, v1, v2);

    char ch;
    cout<<"1)Existing Graph or 2)Custom graph ? ";
    cin>>opt;
    if(opt == 1)
    {


      g.addEdge(0, 1, 5);
      g.addEdge(1, 3, 5);
      g.addEdge(2, 1, 5);
      g.addEdge(3, 2, 5);
      g.addEdge(3, 4, 5);
      g.addEdge(4, 5, 5);
      g.addEdge(6, 4, 5);
      g.addEdge(5, 7, 5);
      g.addEdge(7, 6, 5);
      g.addEdge(0, 2, 5);
      g.addEdge(2, 6, 5);
    }
    else if(opt == 2)
    {
       int n1,n2,w1;
       while(1)
       {
          cout<<"Enter the nodes to add the edge between";
          cin>>n1>>n2;
          cout<<"Enter the weight : ";
          cin>>w1;
          g.addEdge(n1,n2,w1);
          cout<<"Continue adding(y/n) ? ";
          cin>>ch;
          if(ch=='n')
          {
             break;
          }
       }
    }
	
	g.loadPath();

	if(!g.pathExist){
	    cout<<"There is no path exist between "<<v1<<" and "<<v2;
	    exit;
	}

    traverse(g);

    return 0;
}
