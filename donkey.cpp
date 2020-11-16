# // C++ program to print the paths between two vertices
#include <bits/stdc++.h>
using namespace std;  
  
class Graph 
{ 
    public:
        int V;  
        bool pathExist;
        list<int> *adj; 
        vector<int> pathCost;
        vector<list<int>> paths;
        map<pair<int, int>, float> costs;

        Graph(int V);

        void addEdge(int v, int w, float cost); 
        void updateCost(int v, int w, float cost);

        void loadCost();
        void loadPathUtil(int v1, int v2, bool visited[], list<int>& path);  
        void loadPath(int v1, int v2);  

        void showPaths(); 
        void showCost();
}; 
  
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new list<int>[V]; 
} 
  
void Graph::showPaths()
{
    list<int>::iterator i;
    cout<<paths.size()<<endl;
    for(int j=0;j<paths.size();++j) {
        for(i=paths[j].begin(); i != paths[j].end(); ++i)
            cout<<*i<<"\t\t";
        cout<<pathCost[j]<<endl;
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
        for(i = path.begin();i != path.end() ; ++i) 
            cout<<*i<<"->";
       
        cout<<endl;
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
  
void Graph::loadPath(int v1, int v2) 
{ 
    bool *visited = new bool[V]; 
    for (int i = 0; i < V; i++) 
        visited[i] = false;

    list<int> path;
    vector<int> cost;
    pathExist=false;
    
    loadPathUtil(v1,v2,visited,path);
    updatePathCost(this.paths, this.costs, this.pathCost);
} 

void Graph::updateCost(int v, int w, float cost)
{
    costs[pair<int,int>(v, w)] = cost;
    updatePathCost(this.paths, this.costs, this.pathCost);
}

void updatePathCost(vector<list<int>>& paths, map<pair<int, int>, float>& costs, vector<int>& pathCost)
{
    pathCost.clear();
    list<int>::iterator i;
    int n = paths.size(), j, k, m, sum;
    vector<int> path;
    for(j=0;j<n;j++)
    {
        sum = 0;
        for(i = paths[j].begin(); i != paths[j].end(); ++i)
            path.push_back(*i);
        m = path.size();
        path.clear();
        for(k = 0; k < m; k++) 
        {
            sum += costs[pair<int,int>(path[k], path[k+1])];
        }
        pathCost.push_back(sum);
    }
}


  
void findMinPath(vector<int>& pathCost)
{
    int i, idx = 0;
    int n = pathCost.size();
    for(i = 1; i < n; i++)
        if(pathCost[i] < pathCost[idx])
            idx = i;
    return i;
}

void traverse(Graph g) 
{
    int idx = findMinPath(g.pathCost);
    list<int> trav = paths[idx];
    

    int node1, node2, dist, i, j, v1, v2, cst, n = g.paths.size();
    char ch;

    while(node1 == v2)
    {
        node1 = trav.pop_front();
        node2 = trav.front();
        dist = g.costs[pair<int, int>(node1, node2)];
        for(i = 1; i < dist; i++)
        {
            cout<<"Travelled "<<i<<"out of "<<dist<<" units\nUpdate Traffic(y/n) : ";
            cin>>ch;
            if(ch == "y") 
            {
                cout<<"Enter vertex 1 : ";
                cin>>v1;
                cout<<"Enter vertex 2 : ";
                cin>>v2;
                cout<<"Enter cost to be updated : ";
                cin>>cst;
                g.updateCost(v1, v2, cst);
                if(idx != findMinPath())
                {
                    vector<list<int>> paths1;
                    vector<list<int>> paths2;
                    vector<int> pathCosts1;
                    vector<int> pathCosts2;

                    vector<int> list1, list2;
                    for(j = 0; j < n; j++)
                    {
                        list<int>::iterator itr1 = find(paths[j].begin(), paths[j].end(), node1),
                                            itr2 = find(paths[j].begin(), paths[j].end(), node2);
                        int idx1, idx2;
                        if(itr1 != paths[j].end())
                        {
                            list<int> l1 = {};
                            l1.splice(l1.begin(), paths[j], itr1, paths[j].end());
                            paths1.push_back(l1);
                            list1.push_back(j);
                        }
                        if(itr2 != paths[j].end())
                        {
                            list<int> l2 = {};
                            l1.splice(l1.begin(), paths[j], itr1, paths[j].end());
                            paths2.push_back(l2);
                            list1.push_back(j);
                        }
                    }
                    updatePathCost(paths1, g.costs, pathCosts1);
                    updatePathCost(paths2, g.costs, pathCosts2);
                    idx1 = findMinPath(pathCosts1);
                    idx2 = findMinPath(pathCosts2);
                    if(pathCosts1[idx1] < pathCosts2[idx2])
                    {
                        trav = pathCosts1;
                        node2 = pathCosts1.front();
                        continue;
                    }
                    else    
                    {
                        trav = pathCosts2;
                        node1 = node2;
                        node2 = pathCosts2.front();
                        dist = costs[pair<int, int>(node1, node2)] - dist;
                        //iterating again from reverse
                        i = 0;
                    }
                }
            }
        }
    }
}


int main() 
{
    // Create a graph given in the above diagram
    Graph g(8);
    g.addEdge(0,1,1);
    g.addEdge(1, 3, 1); 
	g.addEdge(2, 1, 1); 
	g.addEdge(3, 2, 1); 
	g.addEdge(3, 4, 1); 
	g.addEdge(4, 5, 1); 
	g.addEdge(6, 4, 1);
	g.addEdge(5,7, 1);
	g.addEdge(7,6, 1);
	g.addEdge(0,2, 1);
	g.addEdge(2,6, 1);
	int v1=0, v2=6;
	g.loadPath(v1,v2);
    g.updatePathCost();
	if(!g.pathExist){
	    cout<<"There is no path exist between "<<v1<<" and "<<v2;
	}
    return 0; 
} 
