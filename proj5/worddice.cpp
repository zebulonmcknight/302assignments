// Lab 5 Worddice
// Zebulon Mcknight
// 11/13/2024
// This program uses Edmonds-Karp algorithm to determine if a set of lettered 
// dice can be used to spell a list of words.
//
// I reviewed this Geeks for Geeks article for help with edmonds-karp: https://www.w3schools.com/dsa/dsa_algo_graphs_edmondskarp.php#:~:text=The%20Edmonds%2DKarp%20algorithm%20works,as%20possible%20through%20that%20path. 
// I also designed my graph implementation off of ChatGPT's implementation. 

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include <climits> 
using namespace std;

// BFS function to find augmenting path and track dice used for each letter. 
bool bfs(vector<vector<int>>& capacity, vector<vector<int>>& adj, vector<int>& parent, vector<int>& dice_used, int source, int sink) {
    // Establish the parent of each node in the graph 
	for (size_t i = 0; i < parent.size(); i++)
    {
        parent[i] = -1; 
    }
	
	// Push the source node onto the queue 
    parent[source] = source;
    queue<pair<int, int>> q;
    q.push({source, INT_MAX});

	// While their are nodes to visit 
    while (!q.empty()) {
		// Pop off the current node 
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

		// For every connected node, if it is unvisited, visit it
        for (int next : adj[cur]) 
		{
            if (parent[next] == -1 && capacity[cur][next] > 0) 
			{
				// Update the path and flow, and if you can reach the sink, return true
				// indicating their is a path from source to sink through these nodes 
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == sink) 
				{
                    return true;
                }

				// Push node onto queue 
                q.push({next, new_flow});
            }
        }
    }
	// If you cannot find a path return false 
    return false;
}

// Edmonds-Karp implementation. This function will calculate the maximum flow and 
// track which dice are used to spell each word 
int edmonds_karp(vector<vector<int>>& capacity, vector<vector<int>>& adj, int source, int sink, vector<int>& dice_used, int numDice, int wordLen) {
    int flow = 0;

	// parent will store the node that each node is connected to in the path 
    vector<int> parent(adj.size());

	// While we can find new paths through the graph, calculate th flow 
    while (bfs(capacity, adj, parent, dice_used, source, sink)) 
	{
        int cur_flow = INT_MAX;
        int cur = sink;

        // Backtrack through the graph to find the flow and dice used 
        while (cur != source) {
            int prev = parent[cur];
            cur_flow = min(cur_flow, capacity[prev][cur]);

			// Creating residual edges and reversing flow 
			capacity[prev][cur] -= cur_flow; 
			capacity[cur][prev] += cur_flow; 

			if (prev > 0 && prev <= numDice && cur > numDice && cur <= numDice + wordLen) {
                // Record which die was used to spell the letter
                int letter_index = cur - numDice - 1;
                dice_used[letter_index] = prev - 1; 
            }
			
            cur = prev;
        }

		// Add flow of current path 
        flow += cur_flow;
        cur = sink;
    }

    return flow;
}

// Function to check if the word can be spelled with the dice, and track the dice used
bool worddice(const vector<string>& dice, const string& word, vector<int>& dice_used) {
    int numDice = dice.size();
    int wordLen = word.size();
    
    int source = 0;
    int sink = numDice + wordLen + 1; 

	// capacity will store edges and their capacity 
    vector<vector<int>> capacity(sink + 1, vector<int>(sink + 1, 0));
	// adj acts as an adjacency list for the graph 
    vector<vector<int>> adj(sink + 1);

    // Create source connections to dice
    for (int i = 0; i < numDice; i++) {
        capacity[source][i + 1] = 1; 
        adj[source].push_back(i + 1);
        adj[i + 1].push_back(source);
    }

    // Create dice to word connections
    for (int i = 0; i < numDice; i++) {
        for (int j = 0; j < wordLen; j++) {
            if (dice[i].find(word[j]) != string::npos) {
                capacity[i + 1][numDice + j + 1] = 1;
                adj[i + 1].push_back(numDice + j + 1);
                adj[numDice + j + 1].push_back(i + 1);
            }
        }
    }

    // Create word connections to sink
    for (int j = 0; j < wordLen; j++) {
        capacity[numDice + j + 1][sink] = 1;
        adj[numDice + j + 1].push_back(sink);
        adj[sink].push_back(numDice + j + 1);
    }

    // Initialize dice_used vector to track which dice spell each letter
    dice_used.resize(wordLen, -1);

    // If the maximum flow is equal to the length of the word we can spell it
    // using one letter from each die. 
    return edmonds_karp(capacity, adj, source, sink, dice_used, numDice, wordLen) == wordLen;
}

// Main function
int main(int argc, char* argv[]) {
    if (argc != 3) 
	{
        cerr << "Usage: " << argv[0] << " <dice_file> <words_file>" << endl;
        return 1;
    }

    ifstream diceFile(argv[1]);
    ifstream wordsFile(argv[2]);
	
    vector<string> dice;
    string line;

    // Read in dice; 
    while (getline(diceFile, line)) 
	{
        dice.push_back(line);
    }

    // Read in words and check if each can be spelled
    while (getline(wordsFile, line)) 
	{
        vector<int> dice_used; // Will hold the order of dice used
        
		// If the word can be spelled, print the order of dice used 
		if (worddice(dice, line, dice_used)) 
		{
			// Printing dice order 
            for (size_t i = 0; i < dice_used.size(); i++) 
			{
                if (i > 0) cout << ",";
                cout << dice_used[i];
            }
            cout << ": " << line << endl;
        } 
        else 
		{
            cout << "Cannot spell " << line << endl;
        }
    }

    return 0;
}

