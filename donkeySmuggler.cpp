#include<iostream>
#include<stdio.h>
using namespace std;
#define INFINITY 9999
#define max 5


void dijkstra(int G[max][max],int dis[max], int paths[max][max], int n,int startnode) {
   int cost[max][max],distance[max],pred[max];
   int visited[max],count,mindistance,nextnode,i,j;
   for(i=0;i<n;i++)
      for(j=0;j<n;j++)
   if(G[i][j]==0)
      cost[i][j]=INFINITY;
   else
      cost[i][j]=G[i][j];
   for(i=0;i<n;i++) {
      distance[i]=cost[startnode][i];
      pred[i]=startnode;
      visited[i]=0;
   }
   distance[startnode]=0;
   visited[startnode]=1;
   count=1;
   while(count<n-1) {
      mindistance=INFINITY;
      for(i=0;i<n;i++)
         if(distance[i]<mindistance&&!visited[i]) {
         mindistance=distance[i];
         nextnode=i;
      }
      visited[nextnode]=1;
      for(i=0;i<n;i++)
         if(!visited[i])
      if(mindistance+cost[nextnode][i]<distance[i]) {
         distance[i]=mindistance+cost[nextnode][i];
         pred[i]=nextnode;
      }
      count++;
   }
   int k=0;
   for(i=0;i<n;i++)
   if(i!=startnode) {
      cout<<"\nDistance of node"<<i<<"="<<distance[i];
      dis[i]=distance[i];
      cout<<"\nPath="<<i;
      paths[i][0]=i;
      j=i;
      k=1;
      do {

         j=pred[j];
         cout<<"<-"<<j;
         paths[i][k]=j;
        k++;
      }while(j!=startnode);
   }
}

int main() {
   int G[max][max]={{0,1,4,3,10},{1,0,5,7,8},{4,5,0,2,1},{3,7,2,0,6},{10,8,1,6,0}};
   int dis[max]={0};
   int paths[max][max]={0};
   int n=max;
   int u=4;
   dijkstra(G,dis,paths,n,u);
   for(int i=0;i<n;i++)
    cout<<dis[i];
   for(int i=0;i<n;i++)
   {
       cout<<endl;
       for(int j=0;j<n;j++)
       {
           cout<<paths[i][j]<<" ";
       }

   }
   return 0;
}
