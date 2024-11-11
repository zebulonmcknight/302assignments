#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include <climits> 

using namespace std;

// BFS function to find augmenting path and track dice used for each letter
bool bfs(vector<vector<int>>& capacity, vector<vector<int>>& adj, vector<int>& parent, vector<int>& dice_used, int source, int sink) {
    for (size_t i = 0; i < parent.size(); i++)
    {
        parent[i] = -1; 
    }

    parent[source] = source;
    queue<pair<int, int>> q;
    q.push({source, INT_MAX});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next] > 0) { // Unvisited and has capacity
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == sink) {
                    return true;
                }
                q.push({next, new_flow});
            }
        }
    }

    return false;
}

// Edmonds-Karp (Ford-Fulkerson with BFS), tracks which dice are used to spell the word
int edmonds_karp(vector<vector<int>>& capacity, vector<vector<int>>& adj, int source, int sink, vector<int>& dice_used, int num_dice, int word_length) {
    int flow = 0;
    vector<int> parent(adj.size());

    while (bfs(capacity, adj, parent, dice_used, source, sink)) {
        int cur_flow = INT_MAX;
        int cur = sink;

        // Backtrack to find the flow value and mark dice used
        while (cur != source) {
            int prev = parent[cur];
            cur_flow = min(cur_flow, capacity[prev][cur]);
            cur = prev;
        }

        flow += cur_flow;
        cur = sink;

        // Update capacities and track dice used for each letter
        while (cur != source) {
            int prev = parent[cur];
            capacity[prev][cur] -= cur_flow;
            capacity[cur][prev] += cur_flow;

            if (prev > 0 && prev <= num_dice && cur > num_dice && cur <= num_dice + word_length) {
                // Record which die was used to spell the letter
                int letter_index = cur - num_dice - 1;
                dice_used[letter_index] = prev - 1; // Record the dice index
            }

            cur = prev;
        }
    }

    return flow;
}

// Function to check if the word can be spelled with the dice, and track the dice used
bool canSpellWord(const vector<string>& dice, const string& word, vector<int>& dice_used) {
    int n = dice.size();
    int m = word.size();
    
    int source = 0;
    int sink = n + m + 1;
    vector<vector<int>> capacity(sink + 1, vector<int>(sink + 1, 0));
    vector<vector<int>> adj(sink + 1);

    // Create source connections to dice
    for (int i = 0; i < n; i++) {
        capacity[source][i + 1] = 1; 
        adj[source].push_back(i + 1);
        adj[i + 1].push_back(source);
    }

    // Create dice to word connections
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (dice[i].find(word[j]) != string::npos) {
                capacity[i + 1][n + j + 1] = 1;
                adj[i + 1].push_back(n + j + 1);
                adj[n + j + 1].push_back(i + 1);
            }
        }
    }

    // Create word connections to sink
    for (int j = 0; j < m; j++) {
        capacity[n + j + 1][sink] = 1;
        adj[n + j + 1].push_back(sink);
        adj[sink].push_back(n + j + 1);
    }

    // Initialize dice_used vector to track which dice spell each letter
    dice_used.resize(m, -1);

    // If the maximum flow is equal to the length of the word we can spell it
    // using one letter from each die. 
    return edmonds_karp(capacity, adj, source, sink, dice_used, n, m) == m;
}

// Main function
int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <dice_file> <words_file>" << endl;
        return 1;
    }

    ifstream diceFile(argv[1]);
    ifstream wordsFile(argv[2]);

    vector<string> dice;
    string line;

    // Read dice input
    while (getline(diceFile, line)) {
        dice.push_back(line);
    }

    // Read words and check if they can be spelled
    while (getline(wordsFile, line)) {
        vector<int> dice_used; // Will hold the order of dice used
        if (canSpellWord(dice, line, dice_used)) {
            // Output dice indices used in order to spell the word
            for (size_t i = 0; i < dice_used.size(); i++) {
                if (i > 0) cout << ",";
                cout << dice_used[i];
            }
            cout << ": " << line << endl;
        } 
        else {
            cout << "Cannot spell " << line << endl;
        }
    }

    return 0;
}

