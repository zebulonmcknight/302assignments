/* Zebulon Mcknight
 * 12/5/24
 * sb-analyze.cpp
 * This program takes in a superball board, analyzes it, and prints all scoring sets. 
 * I referenced ChatGPT specifically for help understanding the disjoint set class
 * and its usage.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <vector>
#include <map>
#include <set> 
#include "disjoint.h"
using namespace std;

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

class Superball {
  public:
    Superball(int argc, char **argv);
    int r;
    int c;
    int mss;
    int empty;
    vector<int> board;
    vector<int> goals;
    vector<int> colors;
};

void usage(const char *s) {
  fprintf(stderr, "usage: sb-play rows cols min-score-size colors\n");
  if (s != NULL) fprintf(stderr, "%s\n", s);
  exit(1);
}

Superball::Superball(int argc, char **argv) {
  int i, j;
  string s;

  if (argc != 5) usage(NULL);

  if (sscanf(argv[1], "%d", &r) == 0 || r <= 0) usage("Bad rows");
  if (sscanf(argv[2], "%d", &c) == 0 || c <= 0) usage("Bad cols");
  if (sscanf(argv[3], "%d", &mss) == 0 || mss <= 0) usage("Bad min-score-size");

  colors.resize(256, 0);

  for (i = 0; i < strlen(argv[4]); i++) {
    if (!isalpha(argv[4][i])) usage("Colors must be distinct letters");
    if (!islower(argv[4][i])) usage("Colors must be lowercase letters");
    if (colors[argv[4][i]] != 0) usage("Duplicate color");
    colors[argv[4][i]] = 2 + i;
    colors[toupper(argv[4][i])] = 2 + i;
  }

  board.resize(r * c);
  goals.resize(r * c, 0);

  empty = 0;

  for (i = 0; i < r; i++) {
    if (!(cin >> s)) {
      fprintf(stderr, "Bad board: not enough rows on standard input\n");
      exit(1);
    }
    if (s.size() != c) {
      fprintf(stderr, "Bad board on row %d - wrong number of characters.\n", i);
      exit(1);
    }
    for (j = 0; j < c; j++) {
      if (s[j] != '*' && s[j] != '.' && colors[s[j]] == 0) {
        fprintf(stderr, "Bad board row %d - bad character %c.\n", i, s[j]);
        exit(1);
      }
      board[i * c + j] = s[j];
      if (board[i * c + j] == '.') empty++;
      if (board[i * c + j] == '*') empty++;
      if (isupper(board[i * c + j]) || board[i * c + j] == '*') {
        goals[i * c + j] = 1;
        board[i * c + j] = tolower(board[i * c + j]);
      }
    }
  }
}

// Function to print all scoring sets 
void analyze_superball(Superball *s) {
    DisjointSetByRankWPC ds(s->r * s->c);  // Initialize disjoint set

    // Perform union on adjacent cells of the same color
    for (int i = 0; i < s->r; i++) {
        for (int j = 0; j < s->c; j++) {
            int idx = i * s->c + j;

            // Skip empty cells and goal cells
            if (s->board[idx] == '.' || s->board[idx] == '*') continue;

            // Check right neighbor
            if (j < s->c - 1 && s->board[idx] == s->board[idx + 1]) {
                int root1 = ds.Find(idx);
                int root2 = ds.Find(idx + 1);
                if (root1 != root2 || root1 == -1 || root2 == -1) {
                    ds.Union(root1, root2);
                }
            }

            // Check down neighbor
            if (i < s->r - 1 && s->board[idx] == s->board[idx + s->c]) {
                int root1 = ds.Find(idx);
                int root2 = ds.Find(idx + s->c);
                if (root1 != root2 || root1 == -1 || root2 == -1) {
                    ds.Union(root1, root2);
                }
            }
        }
    }

    // Calculate the size of each connected component
    map<int, int> component_sizes;  // Map to store component sizes
    vector<vector<int>> components(s->r * s->c);  // Store components by root

    // Group cells by their root
    for (int i = 0; i < s->r * s->c; i++) {
        if (s->board[i] != '.' && s->board[i] != '*') {
            int root = ds.Find(i);
            components[root].push_back(i);  // Group cells by root
        }
    }

    // Find valid scoring sets
    vector<pair<int, pair<int, int>>> scoring_sets;  // Store valid scoring sets
    set<int> processed_roots;  // Set to track roots that have already been printed

    // Check for valid scoring sets, considering goal cells
    for (int i = 0; i < s->r; i++) {
        for (int j = 0; j < s->c; j++) {  
            int idx = i * s->c + j;
            if (s->goals[idx] && s->board[idx] != '*') {  // If it's a goal cell
                int root = ds.Find(idx);
				// If the set is large enough and hasn't been scored yet 
                if (components[root].size() >= s->mss && processed_roots.find(root) == processed_roots.end()) {
                    // Add this connected component to the scoring sets list
                    scoring_sets.push_back(make_pair(components[root].size(), make_pair(root, s->board[idx])));
                    processed_roots.insert(root);  // Mark this root as processed
                }
            }
        }
    }

    // Output the valid scoring sets
    cout << "Scoring sets:" << endl;
    for (const auto &entry : scoring_sets) {
        int size = entry.first;
        int root = entry.second.first;
        char color = entry.second.second;  
        cout << "  Size: " << size << "  Char: " << color << "  Scoring Cell: ";

        // Print the coordinates of the goal cell in the component
        for (int i : components[root]) {
            if (s->goals[i]) {
                cout << i / s->c << "," << i % s->c << endl;  // Print row and column of the goal cell
                break;  // Only print the first goal cell in the component
            }
        }
    }
}



int main(int argc, char **argv) {
  Superball *s = new Superball(argc, argv);
  analyze_superball(s);
  delete s;
  return 0;
}

