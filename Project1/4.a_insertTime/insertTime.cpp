#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(int argc, char** argv)
{
	// give a vector "store" to store the data from reading the file
	vector<int> store;
	int point;
	int cmp;
	int count_n = 5000;

	// give the seed to let the number will be randonm.
	srand((unsigned)time(NULL));
    
    // set the double loop let it generate given times of number by random.
   	for(int i=0; i< 10; i++)
    {
    	for(int j=0; j< count_n; j++)
    	{
    		store.push_back(rand()%10000);//generates a random number from 0 to 10000.
    	}
    	
    	// do the insertion sort
    	for(int k = 1; k < store.size(); k++)
    	{
    		point = store[k]; //give the point number to the variable "point".
    		cmp = k - 1; 

    		while(cmp >= 0 && point < store[cmp]) // place the smaller number to the prior location.
    		{
    			store[cmp+1] = store[cmp]; //swap the two numbers index place if the condition fits.
    			cmp = cmp-1;
    		}
    		store[cmp+1] = point; //enter the next run to compare.
    	}
    
    	cout << "n:" << count_n << endl; // print the number "n"
    	//print the running time in unit "s".
    	cout << "Running time:" << (double)clock() / CLOCKS_PER_SEC << "s" << endl;
    	store.clear(); //clear the space where saves the current numbers to provide space to the next file reading
    	// modify the n value
    	count_n += 5000;
    }
    return 0;
}