#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
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
	// give a vector "store" to store the data from reading the file
	vector<int> store;
	int point;
	int cmp;
	int count_n = 5000;

	srand((unsigned)time(NULL));
    
    //let it generate
   	for(int i=0; i< 10; i++)
    {
    	for(int j=0; j< count_n; j++)
    	{
    		store.push_back(rand()%10000);//generates a random number from 0 to 10000.
    	}
    	
    	sort(store);
    	
    	cout << "n:" << count_n << " " << endl; //print the number "n"
    	cout << "Running time:" << (double)clock() / CLOCKS_PER_SEC << "s" << endl; //print the running time in unit "s"
    	store.clear(); //clear the space where saves the current numbers to provide space to the next file reading
    	count_n += 5000;
    }
    return 0;
}