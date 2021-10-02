#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
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
	// give a vector "store" to store the data from reading the file
	vector<int> store;
	int count_n = 5000;

	srand((unsigned)time(NULL));
    
    //let it generate 1o sets number
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