// #include <iostream>
#include <stdio.h>
#include <stdlib.h>
// #include <list>
// #include <vector.h>
#include <limits.h>
// #include <algorithm>
#include <queue>
#include <string.h>

int vertices;
// int graph[300][300];

bool breadth_first_search(int graph[vertices][vertices],int source,int sink, int *parent)
{
	bool visited[vertices];
	memset(visited,0,sizeof(visited));
	queue <int> q;
	q.push(source);
	visited[source]=true;
	parent[source]=-1;
	while(q.empty()==false)
	{
		int some_vertex=q.front();
		q.pop();
		for (int i = 0; i < vertices; ++i)
		{
			if(visited[i]==false && graph[some_vertex][i]>0)
			{
				q.push(i);
				parent[i]=some_vertex;
				visited[i]=true;
			}
		}
	}
	return (visited[sink]==true);
}

int ford_fulkerson(int graph[vertices][vertices],int source,int sink)
{
	int u,v;
	int residual_graph[vertices][vertices];
	for (int i = 0; i < vertices; ++i)
	{
		for (int j = 0; j < vertices; ++j)
		{
			residual_graph[i][j]=graph[i][j];
		}
	}
	int parent[vertices];
	int max_flow=0;
	while(breadth_first_search(residual_graph,source,sink,parent))
	{
		int path_flow = INT_MAX;
		for ( v = sink; v!=source; v=parent[v])
		{
			u=parent[v];
			path_flow = min(path_flow,residual_graph[u][v]);
		}
		for ( v = sink; v!=source; v=parent[v])
		{
			u=parent[v];
			residual_graph[u][v] -= path_flow;
			residual_graph[v][u] += path_flow;
		}
		max_flow +=path_flow;
	}
	return max_flow;
}

int main()
{
	// int vertices;
	scanf("%d",&vertices);
	int graph[vertices][vertices];
	int x,y,cost;
	
	// fill(&graph[0][0],&graph[0][0]+(vertices*vertices),0);
	for (int i = 0; i < vertices; ++i)
	{
		for (int j = 0; j < vertices; ++j)
			{
				graph[i][j]=0;
			}	
	}
	while(scanf("%d%d%d",&x,&y,&cost)!=EOF)
	{
		graph[x][y]=cost;
	}
	printf("%d\n",ford_fulkerson(graph,0,(vertices-1)) );
	return 0;
}