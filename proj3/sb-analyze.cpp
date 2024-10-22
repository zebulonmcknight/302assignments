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
    int r;
    int c;
    int mss;
    int empty;
    vector<int> board;
    vector<int> goals;
    vector<int> colors;
};

void usage(const char *s) {
    fprintf(stderr, "usage: sb-analyze rows cols min-score-size colors\n");
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

int main(int argc, char **argv) {
    Superball *s;
    s = new Superball(argc, argv);

    DisjointSetByRankWPC dset(s->r * s->c);

    for (int i = 0; i < s->r; i++) {
        for (int j = 0; j < s->c; j++) {
            int index = i * s->c + j;
            if (s->board[index] == '.' || s->board[index] == '*') continue; 

            if (j + 1 < s->c && s->board[index] == s->board[index + 1]) {
                dset.Union(index, index + 1);
            }
            if (i + 1 < s->r && s->board[index] == s->board[index + s->c]) {
                dset.Union(index, index + s->c);
            }
        }
    }

    vector<int> set_sizes(s->r * s->c, 0);
    for (int i = 0; i < s->r * s->c; i++) {
        if (s->board[i] != '.' && s->board[i] != '*') {
            int root = dset.Find(i);
            set_sizes[root]++;
        }
    }

    cout << "Scoring sets:" << endl;
    for (int i = 0; i < s->r * s->c; i++) {
        if (s->goals[i] && set_sizes[dset.Find(i)] >= s->mss) {
            int root = dset.Find(i);
            cout << "  Size: " << set_sizes[root] << "  Char: " << s->board[i]
                 << "  Scoring Cell: " << i / s->c << "," << i % s->c << endl;
        }
    }

    return 0;
}

