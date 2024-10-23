#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

void generate_map(int N) {
    // Tile definitions
    vector<pair<string, int>> tiles = {
        {"f", 3},  // Forest
        {"r", 5},  // River
        {"g", 1},  // Grassland
		{"G", 2},
		{"h", 4},
        {"m", 7}   // Mountain
    };
    
    // File name
    string file_name = "input" + to_string(N) + ".txt";
    
    // Open file
    ofstream file(file_name);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }
    
    // Seed for random number generation
    srand(time(0));
    
    // Write TILES_N (number of different tiles)
    file << tiles.size() << endl;
    
    // Write each tile name and its cost
    for (const auto& tile : tiles) {
        file << tile.first << " " << tile.second << endl;
    }
    
    // Write MAP_ROWS and MAP_COLUMNS
    file << N << " " << N << endl;
    
    // Generate and write the NxN map of random tiles
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int random_tile_index = rand() % tiles.size();  // Pick a random tile
            file << tiles[random_tile_index].first;  // Write tile symbol
            if (j < N - 1) file << " ";  // Add space between tiles
        }
        file << endl;  // Newline after each row
    }
    
    // Close the file
    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " N" << endl;
        return 1;
    }

    int N = atoi(argv[1]);  // Convert the command line argument to an integer
    if (N <= 0) {
        cerr << "N must be a positive integer!" << endl;
        return 1;
    }

    generate_map(N);  // Generate the map
    cout << "Map generated and saved to input" << N << ".txt" << endl;

    return 0;
}

