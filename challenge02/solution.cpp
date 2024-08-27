// Challenge 02: Closest Numbers
// Name:  Zebulon Mcknight

// Brief description: This program accepts an array of integers and returns 
// the pair of items within the array with the smallest difference. 

#include <algorithm>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

// smallestDifference accepts a sorted array by reference and returns a vector
// containing the pair or pairs of items with the smallest difference. 
vector <int> smallestDifference(vector <int> &arr)
{
	vector <int> answer; 
	int minDiff = INT_MAX;

	//For every item in the array
	for (size_t i = 0; i < arr.size() - 1; i++)
	{ 
		//Calculate difference between each pair. 
		int diff = arr[i+1] - arr[i]; 
		
		if (diff < minDiff)
		{
			answer.clear(); 
			minDiff = diff; 
			answer.push_back(arr[i]); 
			answer.push_back(arr[i+1]); 
		} 
		
		//If a pair ties the minimum difference, return both pairs. 
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
	
	//While their are more arrays
	while (cin>>size)
	{
		//Read each array into a vector 
		for (int i = 0; i < size; i++)
		{
			int val; 
			cin>>val; 
			arr.push_back(val);  
		} 

		sort(arr.begin(), arr.end()); 
		
		//Getting array of pairs with smallest differences
		vector <int> answer = smallestDifference(arr); 

		//Printing
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

		//Clearing array for next loop
		arr.clear(); 
	} 

    return EXIT_SUCCESS;
}
