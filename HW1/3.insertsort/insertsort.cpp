#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char** argv)
{
	// open the data.txt
	fstream data;
	data.open("data.txt");

	// give a vector "store" to store the data from reading the file
	vector<int> store;
	string per_row;
	int point;
	int cmp;

	// read one line of number per time by using "getline"
    while( getline(data,per_row) )
    {    
    	// read unit of number per time by using "istringstream" and push it into the "store"
    	istringstream token(per_row);	
    	int key;
    	//if it can be read then the while loop will be continued to read the data.
    	while(token >> key)
    	{
    		store.push_back(int(key)); // stores the data into the vector.
    	}
        
        // do the insertion sort
    	for(int i = 1; i<store.size(); i++)
    	{
    		point = store[i];
    		cmp = i - 1;
    		//to compare the value and swap their location in the vector.
    		while(cmp >= 0 && point < store[cmp])
    		{
    			store[cmp+1] = store[cmp];
    			cmp = cmp-1;
    		}
    		store[cmp+1] = point;
    	}
    	//build/open a txt file to save the sorted series numbers
		ofstream storage("insert.txt", ios::app);
		for(int i = 0; i < store.size(); i++)
		{
			storage << store[i];
			storage << " ";
		}
		// finish the current line then add the \r\n to enter the next line
		storage << "\r\n";
		storage.close();

		//clear the space where saves the current numbers to provide space to the next file reading
    	store.clear();
    }

    //close the data.txt
    data.close();
    return 0;
}