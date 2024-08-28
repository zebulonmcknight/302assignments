// Challenge 03: Palindrome Permutation
// Zebulon Mcknight
// This program reads in a string of words and determines if the string could be 
// a palindrome permutation. A palindrome permutation is defined as any string
// which can be rearranged to be a palindrome. To determine this the program checks
// for characters with an odd number of occurences, if more than one such character
// exists it is not a palindrome permutation. 

#include <iostream> 
#include <unordered_map> 
using namespace std; 

int main(int argc, char *argv[]) 
{
	string line; 

	while (getline(cin, line, '\n'))
	{
		// map will hold letters and the number of times each letter occurs in
		// the string line. 
		unordered_map <char, int> map; 
	
		// For every character in the line
		for (size_t i = 0; i < line.size(); i++)
		{
			// Filtering out all punctuation and spaces
			if ((line[i] >= 65 && line [i] <= 90) || (line[i] >= 97 && line[i] <= 122))
			{
				// If the letter isn't already in the map, add it with 1 occurence
				if (map.find(line[i]) == map.end())
				{
					map.insert({line[i], 1}); 
				} 

				// If the letter is already in the map, increment its occurence counter
				else
				{
					map[line[i]]++; 
				} 
			} 
		} 
		
		unordered_map <char, int>::iterator it; 
		int oddCount = 0; 
		
		// Counting the number of letters in the map with an odd number of occurences 
		for (it = map.begin(); it != map.end(); it++)
		{
			if (it->second % 2 != 0)
			{
				oddCount++; 
			}  
		} 

		// If there are multiple odd characters, its not a palindrome
		if (oddCount > 1)
		{
			cout<<"\""<<line<<"\" is not a palindrome permutation"<<endl; 
		} 

		else 
		{
			cout<<"\""<<line<<"\" is a palindrome permutation"<<endl; 
		}  
	} 

	return 0;
}

