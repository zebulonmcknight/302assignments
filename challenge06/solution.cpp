// Zebulon Mcknight
// CS302 Challenge 6 - MST using Prims Algorithm 
// 10/18/2024
// This program uses prims algorithm to construct the minimum spanning tree of 
// a weighted, undirected graph. 
//
// I referenced both chatGPT and a Geeks for Geeks article to help develop this 
// program. https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>  
using namespace std;

// minKey loops through all vertices not yet in the MST and finds the vertex
// with the minimum edgeweight to be connected to the MST. 
int minKey(vector<int> &key, vector<bool> &inMST, int nvertices) {
    int min = INT_MAX;
    int minIndex;

    for (int i = 0; i < nvertices; i++)
        if (!inMST[i] && key[i] < min) {
            min = key[i];
            minIndex = i;
        }

	// Location of the vertex with the minimum weight to connect 
    return minIndex;
}

// Print function. I used chatGPT to help with this because I forgot pairs existed
// and was completely lost on how to print in the desired format lol. 
void print(vector<int> &parent, vector<vector<int>> &graph, int nvertices) {
    int totalWeight = 0;
    vector<pair<char, char>> edges;

    // Loop through vertices
    for (int i = 1; i < nvertices; i++) {
        if (parent[i] != -1) {
            // Calculate total weight
            totalWeight += graph[i][parent[i]];

            // Adding edges 
            char from = char(parent[i] + 'A');
            char to = char(i + 'A');

			//making sure vertices are ordered alphabetically 
            if (from > to) {
                swap(from, to);  
            }
            edges.push_back({from, to});
        }
    }

    // Sorting all edges alphabetically 
    sort(edges.begin(), edges.end());

	// Actually printing 
    cout << totalWeight << endl;
    for (size_t i = 0; i < edges.size(); i++)
    {
        cout << edges[i].first << edges[i].second << endl;
    }
}

// prim is the function which actually implements prims algorithm and creates 
// the MST. 
void prim(vector<vector<int>> &graph, int nvertices) {
    vector<int> parent(nvertices);  // Parent stores what vertex each other vertex is connected to 
    vector<int> key(nvertices);     // Key values represent the minimum edge weight 
    vector<bool> inMST(nvertices);  // Stores true or false if vertex in MST

    // Initialize all keys as INFINITE and inMST[] as false
    for (int i = 0; i < nvertices; i++) {
        key[i] = INT_MAX;
        inMST[i] = false;
    }

	// Picking A as the arbitrary first vertex. Initializing its parent to null 
    key[0] = 0;     
    parent[0] = -1; 

	
    for (int count = 0; count < nvertices - 1; count++) {
        // Finding which vertex we can connect to with minimum weight 
		int u = minKey(key, inMST, nvertices);

		// Adding next vertex to the MST 
        inMST[u] = true;
		
		// Checking all other vertices to see if they can connect to u 
        for (int v = 0; v < nvertices; v++) {
            if (graph[u][v] != -1 && !inMST[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the MST
    print(parent, graph, nvertices);
}

int main() {
    int nvertices;
	bool first = true; 
    
    while (cin >> nvertices) {
		// distance/adjacency matrix to represent the graph 
        vector<vector<int>> graph(nvertices, vector<int>(nvertices));

        // Reading in graph 
        for (int i = 0; i < nvertices; i++) {
            for (int j = 0; j < nvertices; j++) {
                cin >> graph[i][j];
            }
        } 
		
		// If this is the first loop, do not print a leading newline, otherwise do. 
		if (!first)
		{
			cout<<endl; 
		}

		// Calling prims algorithm 
        prim(graph, nvertices);

		first = false; 
    }

    return 0;
}

