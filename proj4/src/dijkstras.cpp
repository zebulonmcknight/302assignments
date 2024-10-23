// dijsktras.cpp
//
// Zebulon Mcknight 
// 10/23/2024
// This program implements dijkstras algorithm to perform pathfinding on a 
// game board of various tiles. 
#include <iostream>
#include <list> 
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <algorithm>

using namespace std;

// Helper function for format output 
void print(list<pair<int, int>> path, int totalCost)
{
    cout << totalCost << endl;

    for (auto i:path)
    {
        cout << i.first << " " << i.second << endl;
    }
}

// Performs dijkstras algorithm and calls print
void dijkstras(vector<vector<int>> matrix, int rows, int columns, int startx, int starty, int endx, int endy)
{
	// List storing the coordinates of tiles in the order we visit them 
	list<pair<int, int>> path; 

    // Priority queue storing costs and coordinates of possible next tiles (cost, x, y)
	// Also one of the ugliest lines of code ever written
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

    // 2D vector to store the minimum cost to reach each cell
    vector<vector<int>> cost(rows, vector<int>(columns, INT_MAX));

    // Direction pair for moving up, down, left, right
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	 
    // Parent vector to reconstruct the path
	// Another contender for ugliest line of code 
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(columns, make_pair(-1, -1)));

	// Start by pushing the starting point into the queue with cost 0
    pq.push({0, startx, starty});
    cost[startx][starty] = 0;

    while (!pq.empty())
    {
        // Extracting current tiles cost and coordinates 
        tuple<int, int, int> current = pq.top(); //highest priority (lowest cost) tile 
        pq.pop();
		int currentCost = get<0>(current); 
        int x = get<1>(current); 
        int y = get<2>(current); 
        
		// If we reached the end, build the path and exit
        if (x == endx && y == endy)
        {
            pair<int, int> cur = make_pair(endx, endy);

            // Rebuild the path by backtracking through the parent array
            while (cur.first != -1 && cur.second != -1)
            {
                path.push_front(cur);
                cur = parent[cur.first][cur.second];
            }

            print(path, currentCost);
            return;
        } 

        // Explore neighbors of current tile
        for (size_t i = 0; i < directions.size(); i++)
        {
			// Coordinates of each neighbor
			int nx = x+directions[i].first; 
			int ny = y+directions[i].second; 

			// If the neighbor is in bounds 
			if (nx >= 0 && nx < rows && ny >= 0 && ny < columns)
			{	
				// Add the cost of the possible next tile
				int newCost = currentCost + matrix[x][y]; 

				// If this is the lowest cost route, take it 
				if (newCost < cost[nx][ny])
				{
					// Updating cost, queue, and parent
					pq.push({newCost, nx, ny}); 
					cost[nx][ny] = newCost; 
					parent[nx][ny] = make_pair(x, y); 
				} 
			}
		} 
    }
}

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
		costMap.insert({name, cost}); 
	} 
	
	// Boardsize 
	int rows, columns; 
	cin>>rows>>columns; 

	vector<vector <int>> matrix;

	// Initializing size of board 
    matrix.resize(rows);
    for (auto &row : matrix) {
        row.resize(columns);
    }

	// Reading tiles into board
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			char tile; 
			cin>>tile; 
			matrix[i][j] = (costMap.at(tile)); 
		} 
	} 
	
	// Initializing start and end coordinates 
	int startx, starty, endx, endy; 

	// If else statements allow use with generated input for benchmarking 
	if (cin>>startx>>starty); 
	else 
	{
		startx = 0, starty = 0; 
	} 
	
	if (cin>>endx>>endy); 
	else 
	{	
		endx = rows - 1, endy = columns - 1; 
	} 

	// Calling dijkstras!!! 
	dijkstras(matrix, rows, columns, startx, starty, endx, endy); 

    return 0;
}

