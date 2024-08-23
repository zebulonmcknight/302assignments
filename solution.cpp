// Challenge 01: Rotating Arrays
// Zebulon Mcknight
// 08/22/2024
// This program reads in a series of arrays from standard input, and then
// rotates them left or right by a given offset. 

#include <iostream> 
#include <vector> 
using namespace std; 

// rightRotation accepts an array from main by reference, as well as the arrays
// size and the offset to rotate it by. It then manipulates the array to 
// rotate it right by offset number of rotations. 
vector <int> rightRotation(vector <int> &array, int offset, int size)
{
	// These two lines triple the array, turning [1,2,3,4,5] -> [1,2,3,4,5,1,2,3,4,5,...] 
	array.insert(array.end(), array.begin(), array.end()); 
	array.insert(array.end(), array.begin(), array.begin() + size);

	// These lines erase all array elements apart from the desired final array. 
	// The correct iterators can be calculated using the offset of the desired
	// rotation. 
	array.erase(array.begin(), array.end() - size - offset); //delete beginning to start of array 
	array.erase(array.end() - offset, array.end()); //delete end of array to end 

	return array; 
} 

// leftRotation accepts an array from main by reference, as well as the arrays
// size and the offset to rotate it by. It then manipulates the array to 
// rotate it left by offset number of rotations.
vector <int> leftRotation(vector <int> &array, int offset, int size)
{	
	// These two lines triple the array, turning [1,2,3,4,5] -> [1,2,3,4,5,1,2,3,4,5,...] 
	array.insert(array.end(), array.begin(), array.end()); 
	array.insert(array.end(), array.begin(), array.begin() + size);

	// These lines erase all array elements apart from the desired final array. 
	// The correct iterators can be calculated using the offset of the desired
	// rotation. 
	array.erase(array.begin(), array.begin() + offset); //delete beginning to start of array
	array.erase(array.begin() + size + offset, array.end()); //delete end of array to end

	return array; 
} 

int main(int argc, char *argv[]) {
	vector <int> array; 
	int size, offset; //Size of array and number of spaces to rotate
	char direction; //Specified rotation direction 
	int current; //Current value the while loop is reading

	while (cin>>size>>offset>>direction)
	{
		// Extracting values from file into array
		for (int i = 0; i < size; i++)
		{
			cin>>current; 
			array.push_back(current); 
		}

		//Left rotation branch
		if (direction == 'L')
		{
			leftRotation(array, offset, size); 
			
			//Printing
			for (int i = 0; i < size - 1; i++)
			{
				cout<<array[i]<<" "; 
			} 
			cout<<array[size - 1]; 
			cout<<endl; 
		}

		//Right rotation branch
		else if (direction == 'R')
		{
			rightRotation(array, offset, size); 
			
			//Printing 
			for (int i = 0; i < size - 1; i++)
			{
				cout<<array[i]<<" "; 
			} 
			cout<<array[size - 1]; 
			cout<<endl; 
		} 
		
		//Resetting array for next loop
		array.clear(); 
	} 

    return 0;
}

