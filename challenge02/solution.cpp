// Challenge 02: Closest Numbers
// Name:  Zebulon Mcknight

// Brief description:

// This code solves yyyy based on the following idea/implementation...

#include <algorithm>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

// Main Execution

vector <int> smallestDifference(vector <int> &arr)
{
	vector <int> answer; 
	int minDiff = INT_MAX;

	for (size_t i = 0; i < arr.size() - 1; i++)
	{ 
		int diff = arr[i+1] - arr[i]; 
		
		if (diff < minDiff)
		{
			answer.clear(); 
			minDiff = diff; 
			answer.push_back(arr[i]); 
			answer.push_back(arr[i+1]); 
		} 

		else if (diff == minDiff)
		{
			answer.push_back(arr[i]); 
			answer.push_back(arr[i+1]); 
		} 
	}

	return answer; 
} 

int main(int argc, char *argv[]) {
	
	int size;
	vector <int> arr; 

	while (cin>>size)
	{
		for (int i = 0; i < size; i++)
		{
			int val; 
			cin>>val; 
			arr.push_back(val);  
		} 

		sort(arr.begin(), arr.end()); 

		vector <int> answer = smallestDifference(arr); 

		for (size_t i = 0; i < answer.size(); i++)
		{
			if (i != 0)
			{
				cout<<" "<<answer[i]; 
			} 
			else 
			{
				cout<<answer[i]; 
			} 
		} 
		cout<<endl; 

		arr.clear(); 
	} 

    return EXIT_SUCCESS;
}
