// Sollin's algorithm to find Minimum Spanning 

#include <stdio.h> 

 
struct Edge 
{ 
	int src, dest, weight; 
}; 

struct Graph 
{ 
	
	int V, E; 

	Edge* edge; 
}; 


struct subset 
{ 
	int parent; 
	int rank; 
}; 


int find(struct subset subsets[], int i); 
void Union(struct subset subsets[], int x, int y); 


void boruvkaMST(struct Graph* graph) 
{ 
	
	int V = graph->V, E = graph->E; 
	Edge *edge = graph->edge; 

	
	struct subset *subsets = new subset[V]; 

	
	int *cheapest = new int[V]; 

	
	for (int v = 0; v < V; ++v) 
	{ 
		subsets[v].parent = v; 
		subsets[v].rank = 0; 
		cheapest[v] = -1; 
	} 

	int numTrees = V; 
	int MSTweight = 0; 

	
	while (numTrees > 1) 
	{ 
		
		for (int v = 0; v < V; ++v) 
		{ 
			cheapest[v] = -1; 
		} 

		
		for (int i=0; i<E; i++) 
		{ 
		
			int set1 = find(subsets, edge[i].src); 
			int set2 = find(subsets, edge[i].dest); 

		
			if (set1 == set2) 
				continue; 

			else
			{ 
			if (cheapest[set1] == -1 || 
				edge[cheapest[set1]].weight > edge[i].weight) 
				cheapest[set1] = i; 

			if (cheapest[set2] == -1 || 
				edge[cheapest[set2]].weight > edge[i].weight) 
				cheapest[set2] = i; 
			} 
		} 


		for (int i=0; i<V; i++) 
		{ 
			if (cheapest[i] != -1) 
			{ 
				int set1 = find(subsets, edge[cheapest[i]].src); 
				int set2 = find(subsets, edge[cheapest[i]].dest); 

				if (set1 == set2) 
					continue; 
				MSTweight += edge[cheapest[i]].weight; 
				printf("Edge %d-%d included in MST\n", 
					edge[cheapest[i]].src, edge[cheapest[i]].dest); 

			
				Union(subsets, set1, set2); 
				numTrees--; 
			} 
		} 
	} 

	printf("Weight of MST is %d\n", MSTweight); 
	return; 
} 

struct Graph* createGraph(int V, int E) 
{ 
	Graph* graph = new Graph; 
	graph->V = V; 
	graph->E = E; 
	graph->edge = new Edge[E]; 
	return graph; 
} 
 
int find(struct subset subsets[], int i) 
{ 
	if (subsets[i].parent != i) 
	subsets[i].parent = 
			find(subsets, subsets[i].parent); 

	return subsets[i].parent; 
} 

void Union(struct subset subsets[], int x, int y) 
{ 
	int xroot = find(subsets, x); 
	int yroot = find(subsets, y); 

	if (subsets[xroot].rank < subsets[yroot].rank) 
		subsets[xroot].parent = yroot; 
	else if (subsets[xroot].rank > subsets[yroot].rank) 
		subsets[yroot].parent = xroot; 

	else
	{ 
		subsets[yroot].parent = xroot; 
		subsets[xroot].rank++; 
	} 
} 


int main() 
{ 
	
	int V = 6; // Number of vertices in graph 
	int E = 8; // Number of edges in graph 
	struct Graph* graph = createGraph(V, E); 


	// add edge 0-1 
	// edge 0-1
        graph->edge[0].src = 0;
        graph->edge[0].dest = 1;
        graph->edge[0].weight = 12;

        // edge 0-5
        graph->edge[1].src = 0;
        graph->edge[1].dest = 5;
        graph->edge[1].weight = 16;

        // edge 0-3
        graph->edge[2].src = 0;
        graph->edge[2].dest = 3;
        graph->edge[2].weight = 8;

        // edge 1-2
        graph->edge[3].src = 1;
        graph->edge[3].dest = 2;
        graph->edge[3].weight = 7;

        // edge 2-3
        graph->edge[4].src = 2;
        graph->edge[4].dest = 3;
        graph->edge[4].weight = 9;

        // edge 2-5
        graph->edge[5].src = 2;
        graph->edge[5].dest = 5;
        graph->edge[5].weight = 5;

        // edge 4-5
        graph->edge[6].src = 4;
        graph->edge[6].dest = 5;
        graph->edge[6].weight = 15;

        // edge 3-4
        graph->edge[7].src = 3;
        graph->edge[7].dest = 4;
        graph->edge[7].weight = 3;

	boruvkaMST(graph); 

	return 0; 
} 

