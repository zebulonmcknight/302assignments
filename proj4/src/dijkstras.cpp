// dijsktras.cpp
/*void dijkstras(vector <vector<int>> matrix, int rows, int columns, int startx, int starty, int endx, int endy)
{
	pair <int, int> current;
	pair <int, int> end  = make_pair(endx, endy); 
	vector <pair <int, int>> path; 
	int totalCost = 0; 
	
	current = make_pair(startx, starty); 
	path.push_back(current);
	totalCost += matrix[startx][starty]; 
	
	priority_queue<int, vector <int>, greater<int>> pq;

	while (current != end)
	{
				 						
	} 

	print(path, totalCost);   
}  */ 

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <algorithm>  // For reverse()

using namespace std;

void print(vector<pair<int, int>> path, int totalCost)
{
    cout << totalCost << endl;

    for (size_t i = 0; i < path.size(); i++)
    {
        cout << path[i].first << " " << path[i].second << endl;
    }
}

void dijkstras(vector<vector<int>> matrix, int rows, int columns, int startx, int starty, int endx, int endy)
{
    vector<pair<int, int>> path;
    int totalCost = 0;

    // Priority queue storing pairs (currentCost, (x, y))
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

    // 2D vector to store the minimum distance to reach each cell
    vector<vector<int>> dist(rows, vector<int>(columns, INT_MAX));

    // Direction vectors for moving up, down, left, right
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // Start by pushing the starting point into the queue with cost 0
    pq.push(make_pair(0, make_pair(startx, starty)));
    dist[startx][starty] = 0;

    // Parent vector to reconstruct the path
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(columns, make_pair(-1, -1)));

    while (!pq.empty())
    {
        // Extract current node and cost
        pair<int, pair<int, int>> currentPair = pq.top();
        pq.pop();
        int currentCost = currentPair.first;
        int x = currentPair.second.first;
        int y = currentPair.second.second;

        // If we reached the end, build the path and exit
        if (x == endx && y == endy)
        {
            totalCost = currentCost;
            pair<int, int> cur = make_pair(endx, endy);

            // Rebuild the path by backtracking through the parent array
            while (cur.first != -1 && cur.second != -1)
            {
                path.push_back(cur);
                cur = parent[cur.first][cur.second];
            }

            reverse(path.begin(), path.end());
            print(path, totalCost);
            return;
        }

        // Explore neighbors
        for (size_t i = 0; i < directions.size(); i++)
        {
            int nx = x + directions[i].first;
            int ny = y + directions[i].second;

            // Check if the new position is within bounds
            if (nx >= 0 && nx < rows && ny >= 0 && ny < columns)
            {
                int newCost = currentCost + matrix[x][y]; // Cost of moving from (x, y) to (nx, ny)

                // If a shorter path to (nx, ny) is found
                if (newCost < dist[nx][ny])
                {
                    dist[nx][ny] = newCost;
                    pq.push(make_pair(newCost, make_pair(nx, ny)));
                    parent[nx][ny] = make_pair(x, y); // Set the parent to trace the path later
                }
            }
        }
    }
}
/*
void dijkstras(vector<vector<int>> matrix, int rows, int columns, int startx, int starty, int endx, int endy)
{
    vector<pair<int, int>> path;
    int totalCost = 0;

    // Priority queue storing pairs (currentCost, (x, y))
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

    // 2D vector to store the minimum distance to reach each cell
    vector<vector<int>> dist(rows, vector<int>(columns, INT_MAX));

    // Direction vectors for moving up, down, left, right
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // Start by pushing the starting point into the queue with cost 0
    pq.push(make_pair(0, make_pair(startx, starty)));
    dist[startx][starty] = 0;

    // Parent vector to reconstruct the path
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(columns, make_pair(-1, -1)));

    while (!pq.empty())
    {
        // Extract current node and cost
        pair<int, pair<int, int>> currentPair = pq.top();
        pq.pop();
        int currentCost = currentPair.first;
        int x = currentPair.second.first;
        int y = currentPair.second.second;

        // If we reached the end, build the path and exit
        if (x == endx && y == endy)
        {
            totalCost = currentCost;
            pair<int, int> cur = make_pair(endx, endy);

            // Rebuild the path by backtracking through the parent array
            while (cur.first != -1 && cur.second != -1)
            {
                path.push_back(cur);
                cur = parent[cur.first][cur.second];
            }

            reverse(path.begin(), path.end());
            print(path, totalCost);
            return;
        }

        // Explore neighbors
        for (size_t i = 0; i < directions.size(); i++)
        {
            int nx = x + directions[i].first;
            int ny = y + directions[i].second;

            // Check if the new position is within bounds
            if (nx >= 0 && nx < rows && ny >= 0 && ny < columns)
            {
                int newCost = currentCost + matrix[x][y]; // Cost of moving from (x, y) to (nx, ny)

                // If a shorter path to (nx, ny) is found
                if (newCost < dist[nx][ny])
                {
                    dist[nx][ny] = newCost;
                    pq.push(make_pair(newCost, make_pair(nx, ny)));
                    parent[nx][ny] = make_pair(x, y); // Set the parent to trace the path later
                }
            }
        }
    }

    // If we exit the loop without finding the end, print no path
    cout << "No path found." << endl;
}
*/ 


// Main Execution
int main(int argc, char *argv[]) {
	// Number of types of tiles 
	int numTiles; 
	cin>>numTiles;

	// Stores tile name, cost in pair 
	unordered_map <char, int> costMap; 

	for (int i = 0; i < numTiles; i++)
	{
		char name; 
		int cost; 

		cin>>name>>cost; 
		pair <char, int> costPair = make_pair(name, cost); 

		costMap.insert(costPair); 
	} 
	
	// Boardsize 
	int rows, columns; 
	cin>>rows>>columns; 

	vector<vector <int>> matrix;

    matrix.resize(rows);
    for (auto &row : matrix) {
        row.resize(columns);
    }

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			char tile; 
			cin>>tile; 
			matrix[i][j] = (costMap.at(tile)); 
		} 
	} 
	
	int startx, starty, endx, endy; 

	cin>>startx>>starty; 
	cin>>endx>>endy; 
	dijkstras(matrix, rows, columns, startx, starty, endx, endy); 

	// CHECKING CORRECT READ IN
	
	/*
	cout<<"tile map: "<<endl; 
	for (auto it : costMap)
	{
		cout<<it.first<<it.second<<endl; 
	} 

	cout<<"board: "<<endl; 
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cout<<matrix[i][j]; 
		} 
		cout<<endl; 
	} 
	 */ 
    return 0;
}

