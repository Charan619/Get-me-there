#include<iostream>
#include<stdio.h>
using namespace std;
#define INFINITY 9999
#define max 5


void dijkstra(int G[max][max],int dis[max], int paths[max][max], int n,int endnode) {
   int cost[max][max],distance[max],pred[max];
   int visited[max],count,mindistance,nextnode,i,j;
   for(i=0;i<n;i++)
      for(j=0;j<n;j++)
   if(G[i][j]==0)
      cost[i][j]=INFINITY;
   else
      cost[i][j]=G[i][j];
   for(i=0;i<n;i++) {
      distance[i]=cost[endnode][i];
      pred[i]=endnode;
      visited[i]=0;
   }
   distance[endnode]=0;
   visited[endnode]=1;
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
   {
   paths[i][0]=i;
   if(i!=endnode) {
      cout<<"\nDistance of node"<<i<<"="<<distance[i];
      dis[i]=distance[i];
      cout<<"\nPath="<<i;

      j=i;
      k=1;
      do {

         j=pred[j];
         cout<<"<-"<<j;
         paths[i][k]=j;
        k++;
      }while(j!=endnode);
   }
   }
}


void trafficChange(int G[max][max])
{
   int s,f;
   cout<<"Enter the road to be changed";
   cin>>s;
   cin>>f;
   cout<<"Enter the new traffic value";
}


void donkeySmuggler(int G[max][max],int dis[max], int paths[max][max], int n,int src,int endnode,int pos[3])
{
   for(int i=0;i<n;i++)
   {
      pos[0]=src;
      pos[1]=dis[src]-dis[paths[src][1]];
      pos[2]=paths[src][1];

      while(pos[2]!=endnode || pos[1]!=0)
      {
         if(pos[1]!=0)
         {
            cout<<endl<<pos[1]<<"kms to go to reach town "<<pos[2];
            pos[1]--;
         }
         else
         {
            cout<<endl<<"reached town "<<pos[2];
            pos[0]=pos[2];
            pos[1]=dis[pos[0]] - dis[paths[pos[0]][1]];
            pos[2]=paths[pos[0]][1];
         }
         char c;
         cout<<" Change traffic?";
         cin>>c;
         if(c=='y')
         {
            trafficChange(G);
         }

      }
      cout<<endl<<"reached town "<<pos[2];
      cout<<endl<<pos[0]<<pos[1]<<pos[2];

      return;
   }
}

int main() {
   int G[max][max]={{0,1,4,3,10},{1,0,5,7,8},{4,5,0,2,1},{3,7,2,0,6},{10,8,1,6,0}};
   int dis[max]={0};
   int paths[max][max]={0};
   int n=max;
   int u,src;
   cout<<"Enter source node";
   cin>>src;
   cout<<"Enter destination node";
   cin>>u;
   dijkstra(G,dis,paths,n,u);
   cout<<endl;
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
   for(int i =0;i<n;i++)
   {
      cout<<paths[src][i];
   }
   int pos[3]={src,0,paths[src][1]};
   donkeySmuggler(G,dis,paths,n,src,u,pos);

   return 0;
}
