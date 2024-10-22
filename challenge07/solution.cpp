// Challenge 08: Repeated DNA sequences
// Zebulon Mcknight 
// 10/22/24 
// This program finds all of the repeated 9 character sequences in a long 
// string of DNA sequences. 

#include <iostream> 
#include <map> 
#include <string> 
using namespace std; 

int main(int argc, char *argv[]) {
	string line; 

	while (cin>>line)
	{	
		// m will store each 9 character chunk of the inputted string and the
		// number of times it appears
		map <string, int> m;

		// loop through each 9 character chunk 
		for (size_t i = 0; i <= line.size() - 9; i++) 
		{
			// break before leaving bounds of string 
			if (line.size() - i < 9)
			{
				break; 
			} 

			// chunk = string[i] -> string[i+9] 
			string chunk = line.substr(i, 9);  

			// if chunk not in map, add it to the map 
			if (m.find(chunk) == m.end())
			{
				m.insert({chunk, 1}); 
			} 
			
			// if chunk is already in the map, increase the number of appearances 
			else 
			{
				m[chunk]++; 
			} 
		}

		// if a chunk appears more than once, print it as a repeat
		for (auto& it: m)
		{
			if (it.second > 1)
			{
				cout<<it.first<<endl; 
			} 
		}
	
		// seperate sequences with -1 as a flag 
		cout<<"-1"<<endl; 
	} 
	return 0;
}


