// Challenge 05: Graph Paths
// Zebulon Mcknight
// This program reads in a directed graph from standard input, along with a set
// of paths to search for within the graph. It prints wether or not a valid path 
// between two vertices exists. 
#include <iostream>
#include <list> 
#include <vector>  
#include <stack>
using namespace std; 

// Iterative Depth First Search Algorithm. I'm pretty sure youre not supposed 
// to do that and this should be recursive but whos gonna stop me. Also I looked
// at like 19 different resources trying to figure out how to do this so I might
// be cheating idrk. 
bool dfs(list<char> * adj_list, int nedges, char &src, char &dest)
{
	// Visited vector 
	vector <bool> visited(nedges, false);  

	// Stack is used to keep vertices in depth first order 
	stack <char> s; 
	s.push(src); 

	// While there are remaining vertices 
	while (!s.empty())
	{
		// Check if the current is the destination 
		char current = s.top(); 
		s.pop(); 
		if (current == dest)
		{
			return true; 
		} 

		// if it isn't, loop through the adj_list to add all of the current 
		// vertices neighbors to the stack. 
		for (int i = 0; i < nedges; i++)
		{
			if (!visited[i] && adj_list[i].front() == current)
			{
				visited[i] = true; 
				
				list<char>::iterator it; 
				for (it = adj_list[i].begin(); it != adj_list[i].end(); it++)
				{
					s.push(*it); 
				} 
			} 
		} 
	} 

	// If every vertice is visited and the dest is not found, there is no path. 
	return false; 
}  

// Main Execution 
int main(int argc, char *argv[]) {
	int nedges; 

	// Tracker for which graph we are viewing 
	int graphNum = 1; 

	// Read in loop 
	while (cin>>nedges)
	{
		// Adjacency list 
		list<char> adj_list[nedges];   

		char src, dest; 
		
		// Reading in graph 
		for (int i = 0; i < nedges; i++)
		{
			cin>>src>>dest; 

			adj_list[i].push_back(src); 
			adj_list[i].push_back(dest); 
		} 

		int npaths; 
		cin>>npaths; 
		
		// Reading in paths to search for 
		for (int i = 0; i < npaths; i++)
		{
			cin>>src>>dest;
			
			// Searching for paths 
			if (dfs(adj_list, nedges, src, dest))
			{
				cout<<"In Graph "<<graphNum<<" there is a path from "<<src<<" to "<<dest;  
			} 

			else 
			{
				cout<<"In Graph "<<graphNum<<" there is no path from "<<src<<" to "<<dest;  
			} 
			
			cout<<endl; 
		}   
		// Incrementing graph number and looping 
		graphNum++;

		if (graphNum <= 5)
		{
			cout<<endl; 
		} 
	}  
	return (0);
}



