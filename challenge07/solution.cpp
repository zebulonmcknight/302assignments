// Challenge 08: Repeated DNA sequences
// Zebulon Mcknight 
// 10/22/24 
//
#include <iostream> 
#include <map> 
#include <string> 
using namespace std; 

int main(int argc, char *argv[]) {
	string line; 

	while (cin>>line)
	{
		map <string, int> m;

		for (size_t i = 0; i <= line.size() - 9; i++) 
		{
			if (line.size() - i < 9)
			{
				break; 
			} 

			string chunk = line.substr(i, 9);  

			if (m.find(chunk) == m.end())
			{
				m.insert({chunk, 1}); 
			} 

			else 
			{
				m[chunk]++; 
			} 
		}

		for (auto& it: m)
		{
			if (it.second > 1)
			{
				cout<<it.first<<endl; 
			} 
		}

		cout<<"-1"<<endl; 
	} 
		
	return 0;
}


