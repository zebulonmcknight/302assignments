/* Zebulon Mcknight 
 * 12/5/24
 * sb-play.cpp
 * This program interacts with the superball player to make a legal move for the 
 * game. 
 * I referenced ChatGPT specifically for help understanding the disjoint set class 
 * and its usage. 
 */ 

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <vector>
#include <set>
#include "disjoint.h"  // Include the header for Disjoint Set Union
using namespace std;

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

// Function to generate a move (Very similar to sb-analyze) 
void generate_move(Superball *s) {
  DisjointSetByRankWPC ds(s->r * s->c);  // Initialize Disjoint Set
	
  // Calling union on each starting cell 
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

  // Identify scoring sets 
  set<int> processed_roots;
  vector<vector<int>> components(s->r * s->c);

  // Collect all connected components
  for (int i = 0; i < s->r * s->c; i++) {
    if (s->board[i] != '.' && s->board[i] != '*') {
      int root = ds.Find(i);  // Find root for each element
      components[root].push_back(i);
    }
  }

  // If there is a scoring cell, score it immediately. 
  for (int i = 0; i < s->r; i++) {
    for (int j = 0; j < s->c; j++) {
      int idx = i * s->c + j;
      if (s->goals[idx] && s->board[idx] != '*') {
        int root = ds.Find(idx);
        if (components[root].size() >= s->mss && processed_roots.find(root) == processed_roots.end()) {
          // Print the scoring move
          cout << "SCORE " << i << " " << j << endl;
          return;
        }
        processed_roots.insert(root);
      }
    }
  }

  // If no scoring move is possible, perform a swap
  // Look for scoring cells to swap with potential future scoring sets
  for (int i = 0; i < s->r; i++) {
    for (int j = 0; j < s->c; j++) {
      int idx1 = i * s->c + j;
      if (s->board[idx1] == '.' || s->board[idx1] == '*') continue;

      // If this cell is part of a scoring set, try to swap with neighboring cells
      for (int k = i; k < s->r; k++) {
        for (int l = (k == i ? j + 1 : 0); l < s->c; l++) {
          int idx2 = k * s->c + l;
          if (s->board[idx2] == '.' || s->board[idx2] == '*') continue;
          // Print the swap move
          cout << "SWAP " << i << " " << j << " " << k << " " << l << endl;
          return;
        }
      }
    }
  }

  // If there are fewer than five pieces left, end the game by swapping an empty cell
  for (int i = 0; i < s->r; i++) {
    for (int j = 0; j < s->c; j++) {
      if (s->board[i * s->c + j] == '.') {
        cout << "SWAP " << i << " " << j << " " << i << " " << j << endl;
        return;
      }
    }
  }
}

int main(int argc, char **argv) {
  Superball *s = new Superball(argc, argv);
  generate_move(s);
  delete s;
  return 0;
}

