#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <vector>
#include "disjoint.h"
using namespace std;

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

class Superball {
  public:
    Superball(int argc, char **argv);
    int r, c, mss, empty;
    vector<int> board;
    vector<int> goals;
    vector<int> colors;
    void make_move();
};

void usage(const char *s) {
    fprintf(stderr, "usage: sb-player rows cols min-score-size colors\n");
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

void Superball::make_move() {
    // Create disjoint set object, with size equal to the number of cells
    DisjointSetByRankWPC dset(r * c);

    // Traverse the board and group contiguous cells of the same color
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int index = i * c + j;
            if (board[index] == '.' || board[index] == '*') continue;

            // Check for neighboring cells with the same color and union them
            if (j + 1 < c && board[index] == board[index + 1]) {
                dset.Union(dset.Find(index), dset.Find(index + 1));
            }
            if (i + 1 < r && board[index] == board[index + c]) {
                dset.Union(dset.Find(index), dset.Find(index + c));
            }
        }
    }

    // Store the sizes of each set and whether it contains a goal
    vector<int> set_sizes(r * c, 0);
    vector<bool> has_goal(r * c, false);

    for (int i = 0; i < r * c; i++) {
        if (board[i] != '.' && board[i] != '*') {
            int root = dset.Find(i);
            set_sizes[root]++;
            if (goals[i]) has_goal[root] = true;  // Mark if this set has a goal
        }
    }

    // Look for a scoring move
    for (int i = 0; i < r * c; i++) {
        int root = dset.Find(i);
        if (has_goal[root] && set_sizes[root] >= mss) {
            cout << "SCORE " << i / c << " " << i % c << endl;
            return;
        }
    }

    // No scoring move available, perform a swap
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c - 1; j++) {
            if (board[i * c + j] != board[i * c + j + 1]) {
                cout << "SWAP " << i << " " << j << " " << i << " " << j + 1 << endl;
                return;
            }
        }
    }
    // If no swap is found (should never happen), just output a default swap
    cout << "SWAP 0 0 0 1" << endl;
}

int main(int argc, char **argv) {
    Superball *s;
    s = new Superball(argc, argv);

    // Make a move (either score or swap)
    s->make_move();

    return 0;
}

