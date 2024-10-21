// dijsktras.cpp
#include <iostream> 
#include <unordered_map> 
using namespace std; 


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

	char matrix [rows][columns]; 

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cin>>matrix[i][j]; 
		} 
	} 

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

