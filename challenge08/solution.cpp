// Challenge 09: sequence alignment
// Zebulon Mcknight 
// 11/08/2024
#include <iostream>
#include <vector> 
#include <algorithm> 
using namespace std; 

int score(char a, char b)
{
	if (a==b)
	{
		return 1; 
	} 
	return -1; 
} 

int alignment(vector<vector<int>> matrix, string seq1, string seq2, int m, int n)
{
	for (int i = 1; i <= m; i++)
	{
		matrix[i][0] = i * -1; 
	} 
	for (int j = 1; j <= n; j++)
	{
		matrix[0][j] = j * -1; 
	} 

	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			int match = matrix[i - 1][j - 1] + score(seq1[i-1], seq2[j-1]); 
			int gap1 = matrix[i - 1][j] - 1; 
			int gap2 = matrix[i][j - 1] - 1; 
			matrix[i][j] = max({match, gap1, gap2}); 
		} 
	} 

	return matrix[m][n]; 
} 

int main(int argc, char *argv[]) {
	string seq1, seq2; 
	cin>>seq1; 
	cin>>seq2; 

	int m = seq1.size(), n = seq2.size(); 
	vector <vector <int>> matrix(m + 1, vector<int>(n+1, 0)); 

	cout<<alignment(matrix, seq1, seq2, m, n)<<endl;  

    return 0;
}


