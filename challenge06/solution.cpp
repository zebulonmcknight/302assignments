#include <iostream>
#include <vector>
#include <climits>  // For INT_MAX
#include <algorithm>  // For std::sort
using namespace std;

// Function to find the vertex with the minimum key value, from the set of vertices not yet included in MST
int minKey(vector<int> &key, vector<bool> &inMST, int nvertices) {
    int min = INT_MAX;
    int minIndex;

    for (int v = 0; v < nvertices; v++)
        if (!inMST[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }

    return minIndex;
}

void print(vector<int> &parent, vector<vector<int>> &graph, int nvertices) {
    int totalWeight = 0;
    vector<pair<char, char>> edges;

    // Loop through vertices and construct the MST edges
    for (int i = 1; i < nvertices; i++) {
        if (parent[i] != -1) {
            // Calculate total weight
            totalWeight += graph[i][parent[i]];

            // Add the edge to the vector (sorted as per alphabetical order)
            char from = char(parent[i] + 'A');
            char to = char(i + 'A');
            if (from > to) {
                swap(from, to);  // Ensure edges are sorted alphabetically
            }
            edges.push_back({from, to});
        }
    }

    // Sort the edges alphabetically
    sort(edges.begin(), edges.end());

    // Print total weight of the MST
    cout << totalWeight << endl;

    // Print each edge
    for (size_t i = 0; i < edges.size(); i++)
    {
        cout << edges[i].first << edges[i].second << endl;
    }
}

// Function to construct and print MST for a graph represented using adjacency matrix representation
void prim(vector<vector<int>> &graph, int nvertices) {
    vector<int> parent(nvertices);  // Array to store the MST
    vector<int> key(nvertices);     // Key values used to pick minimum weight edge
    vector<bool> inMST(nvertices);  // To represent the set of vertices included in MST

    // Initialize all keys as INFINITE and inMST[] as false
    for (int i = 0; i < nvertices; i++) {
        key[i] = INT_MAX;
        inMST[i] = false;
    }

    // Always include the first vertex in the MST.
    key[0] = 0;      // Make key 0 so that this vertex is picked first
    parent[0] = -1;  // First node is always the root of the MST

    for (int count = 0; count < nvertices - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(key, inMST, nvertices);

        // Add the picked vertex to the MST set
        inMST[u] = true;

        // Update key value and parent index of the adjacent vertices
        for (int v = 0; v < nvertices; v++) {
            // graph[u][v] is the weight of the edge u-v, key[v] is the minimum weight found so far
            // Update key only if graph[u][v] is smaller and vertex v is not in MST yet
            if (graph[u][v] != -1 && !inMST[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the constructed MST
    print(parent, graph, nvertices);
}

int main() {
    int nvertices;
	bool first = true; 
    // Read number of vertices
    while (cin >> nvertices) {
        vector<vector<int>> graph(nvertices, vector<int>(nvertices));  // Create an nvertices * nvertices graph

        // Input the distance matrix
        for (int i = 0; i < nvertices; i++) {
            for (int j = 0; j < nvertices; j++) {
                cin >> graph[i][j];
            }
        }

        // Call Prim's algorithm to find the MST and print it
		
		if (!first)
		{
			cout<<endl; 
		}
        prim(graph, nvertices);

		first = false; 
    }

    return 0;
}

