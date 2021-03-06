#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void mergeSort(vector<int>& left, vector<int>& right, vector<int>& sorted_numbers)
{
    int L = left.size(); // to get the size of left vector
    int R = right.size(); // to get the size of right vector
    int i_s = 0, j_l = 0, k_r = 0; // i for series sorted number, j for left and k for right side.

    while (j_l < L && k_r < R) // if the condition fits, the push the number into the sorted vector. 
    {
        if (left[j_l] < right[k_r]) {
            sorted_numbers[i_s] = left[j_l]; // if the left side is less than right side, push the left side into sorted vector.
            j_l++;
        }
        else {
            sorted_numbers[i_s] = right[k_r]; // if the right side is less than left side, push the right side into sorted vector.
            k_r++;
        }
        i_s++; // enter the next index of sorted vector.
    }

    // do the rest situation swap then finish the whole process of sort.
    while (j_l < L) {
        sorted_numbers[i_s] = left[j_l]; 
        j_l++; i_s++;
    }
    while (k_r < R) {
        sorted_numbers[i_s] = right[k_r];
        k_r++; i_s++;
    }
}

void sort(vector<int>& unsorted_numbers) {
	// if the size is less than or equal to 1 then pass it becuase the comparison will not work.
    if (unsorted_numbers.size() <= 1) return;

    int mid = unsorted_numbers.size() / 2; // calculate the medium number to divide the series number to two parts.
    vector<int> left;
    vector<int> right;
    // divide the series number to two parts untile they cannot be separated any more.
    for (size_t j = 0; j < mid;j++)
        left.push_back(unsorted_numbers[j]);
    for (size_t j = 0; j < (unsorted_numbers.size()) - mid; j++)
        right.push_back(unsorted_numbers[mid + j]);

    //breakdown both side to remain only one number
    sort(left); 
    sort(right);
    // start to compare value and combine
    mergeSort(left, right, unsorted_numbers);
}

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
	int size;

	// read one line of number per time by using "getline"
    while( getline(data,per_row) )
    {    
    	// read unit of number per time by using "istringstream" and push it into the "store"
    	istringstream token(per_row);	
    	int key;
    	while(token >> key)
    	{
    		//push the number into the store vector
    		store.push_back(int(key));
    	}
    	// start to execute the merge sort
	    sort(store);
	    
	    // buile/open merge.txt to save the sorted series nubmers.
		ofstream storage("merge.txt", ios::app);
		for(int i = 0; i < store.size(); i++)
		{
			storage << store[i];
			storage << " ";
		}
		// add \r\n to the end of the whole series numbers to enter the next line.
		storage << "\r\n";
		//close the output file.
		storage.close();

		//clear the space where saves the current numbers to provide space to the next file reading
	    store.clear();
	}
	// close the data.txt
    data.close();
    return 0;
}