// Challenge 09: sequence alignment
// Zebulon Mcknight 
// 11/08/2024
// This program reads in 2 sequences of characters and performs a global 
// sequence alignment to return the best possible similarity score. 
#include <iostream>
#include <vector> 
#include <algorithm> 
using namespace std; 

// Quick helper function to minimize number of lines
int score(char a, char b)
{
	if (a==b)
	{
		return 1; 
	} 
	return -1; 
} 

// Performs sequence alignment and returns correct value of m,n
int alignment(vector<vector<int>> matrix, string seq1, string seq2, int m, int n)
{
	// Initializing values of the matrix, taken from chatGPT 
	for (int i = 1; i <= m; i++)
	{
		matrix[i][0] = i * -1; 
	} 
	for (int j = 1; j <= n; j++)
	{
		matrix[0][j] = j * -1; 
	} 

	// Looping through matrix and calculating score. This loop calculates the 
	// score for adding a gap in either sequence, or taking the match/mismatch 
	// score, it then takes and scores the maximum score for that entry. 
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			// Score for match/mismatch
			int match = matrix[i - 1][j - 1] + score(seq1[i-1], seq2[j-1]); 
			// Scores for a gap in seq1/seq2 respectively 
			int gap1 = matrix[i - 1][j] - 1; 
			int gap2 = matrix[i][j - 1] - 1; 
			matrix[i][j] = max({match, gap1, gap2}); 
		} 
	} 

	// Value of best alignment for entire sequence 
	return matrix[m][n]; 
} 

int main(int argc, char *argv[]) {
	// Reading in each sequence and initializing empty matrix 
	string seq1, seq2; 
	cin>>seq1; 
	cin>>seq2; 
	int m = seq1.size(), n = seq2.size(); 
	vector <vector <int>> matrix(m + 1, vector<int>(n+1, 0)); 

	// Calling sequence alignment function 
	cout<<alignment(matrix, seq1, seq2, m, n)<<endl;  

    return 0;
}


