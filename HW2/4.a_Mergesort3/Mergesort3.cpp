#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void mergeSort(vector<int>& left, vector<int>& mid, vector<int>& right, vector<int>& sorted_numbers)
{
    int L = left.size(); // to get the size of left vector
    int M = mid.size(); // to get the size of mid vector
    int R = right.size(); // to get the size of right vector
    int i_s = 0, j_l = 0, u_m = 0, k_r = 0; // i_s for series sorted number, j_l for left, u_m for mid and k_r for right side.

    while (j_l < L && u_m < M &&k_r < R) // first matching, filter the minimun number within the three ranges.
    {
        if (left[j_l] < mid[u_m]) {
        	if(left[j_l] < right[k_r])
        	{
	            sorted_numbers[i_s++] = left[j_l++]; 
	        }
	        else{
	        	sorted_numbers[i_s++] = right[k_r++]; 
	        }
        }
        else{
        	if(mid[u_m] < right[k_r])
        	{
        		sorted_numbers[i_s++] = mid[u_m++]; 
        	}
        	else{
        		sorted_numbers[i_s++] = right[k_r++]; 
        	}
            
        }
    }

    // filter the second minimun number 
    while(j_l < L && u_m < M){
    	if(left[j_l] < mid[u_m])
    	{
    		sorted_numbers[i_s++] = left[j_l++];
    	}
    	else{
    		sorted_numbers[i_s++] = mid[u_m++];
    	}
    } 

    while(u_m < M && k_r < R){
    	if(mid[u_m] < right[k_r])
    	{
    		sorted_numbers[i_s++] = mid[u_m++];
    	}
    	else{
    		sorted_numbers[i_s++] = right[k_r++];
    	}
    } 

    while(j_l < L && k_r < R){
    	if(left[j_l] < right[k_r])
    	{
    		sorted_numbers[i_s++] = left[j_l++];
    	}
    	else{
    		sorted_numbers[i_s++] = right[k_r++];
    	}
    } 
    // do the rest situation swap then finish the whole process of sort.
    while (j_l < L) {
        sorted_numbers[i_s++] = left[j_l++]; 
    }
    while (u_m < M) {
    	sorted_numbers[i_s++] = mid[u_m++]; 
    }
    while (k_r < R) {
        sorted_numbers[i_s++] = right[k_r++];
    }
}

void sort(vector<int>& unsorted_numbers) {
	// if the size is equal to 2 then to compare the 2 numbers.If the size is less than 2, just pass it.
    if (unsorted_numbers.size() <= 2) {
    	if(unsorted_numbers.size() == 2){
	    	if(unsorted_numbers[0] > unsorted_numbers[1]){
	    		swap(unsorted_numbers[0],unsorted_numbers[1]);
	    		return;
	    	}
	    	else return;
	    }
	    else return;
    }

    int one_third = unsorted_numbers.size() / 3; // calculate the medium number to divide the series number to two parts.
    vector<int> left;
    vector<int> mid;
    vector<int> right;
    
    // divide the series number to three parts untile they cannot be separated any more.
    for (size_t j = 0; j < one_third; j++)
        left.push_back(unsorted_numbers[j]);
    for (size_t j = 0; j < one_third; j++)
        mid.push_back(unsorted_numbers[one_third + j]);
    for (size_t j = 0; j < (unsorted_numbers.size()) - 2*one_third; j++)
        right.push_back(unsorted_numbers[2*one_third + j]);
    
    //breakdown three sidse to remain only one or two number
    sort(left); 
   	sort(mid);
    sort(right);
    // start to compare value and combine
    mergeSort(left, mid, right, unsorted_numbers);
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
    	token >> key;
    	while(token >> key)
    	{
    		//push the number into the store vector
    		store.push_back(int(key));
    	}
    	// start to execute the merge sort
	    sort(store);
	    
	    // build/open merge3.txt to save the sorted series nubmers.
		ofstream storage("merge3.txt", ios::app);
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