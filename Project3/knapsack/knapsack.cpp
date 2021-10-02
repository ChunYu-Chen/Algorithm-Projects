#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;

void knapsack(int element_num, int capacity, vector<int>& weight, vector<int>& value, vector< vector<int> >& result)
{   
    for (int i = 1; i <= element_num; ++i)
    {
        for (int j = 1; j <= capacity; ++j)
        {
            if (weight[i] > j) //if the current rest space cannot accept this item then just pass the previous value to current space.
            {
                result[i][j] = result[i - 1][j]; 
            }
            else
            {
                //to compare the value which add the current item and another one. if value_after is bigger than value_before, then update the best value.
                int value_after = result[i - 1][j - weight[i]] + value[i]; 
                int value_before = result[i - 1][j]; 
                if (value_after > value_before)
                {
                    result[i][j] = value_after;
                }
                else
                {
                    result[i][j] = value_before;
                }
            }
        }
    }
}

int resursion(int element_num,int index,int leftWeight,int curValue, vector<int>& v, vector<int>& w)
{
    int res=0;
    if(index>=element_num+1) return curValue; // the element is used up then return the value.
    if(w[index]>leftWeight) // if the weight of current item is bigger than left weight, pass it.
        res=resursion(element_num,index+1,leftWeight,curValue, v, w);
    else //if the left weight is bigger than current item, to recurse the two choices about take the current item and do not take the current item.
        res=max(resursion(element_num,index+1,leftWeight,curValue,v,w),resursion(element_num,index+1,leftWeight-w[index],curValue+v[index],v,w));
    return res;
     
}

int main()
{
    srand((unsigned)time(NULL)); //random seed
    int element_num = 40; //item number
    int capacity = 110; // max capacity
    int max_rec; // variable to store the max recursion running time
    clock_t start, end; //to get the cpu time 
    while( element_num < 60) // give a range
    {
        
        vector<int> weight(1, 0);
        vector<int> value(1, 0);

        for (int i = 1; i <= element_num; ++i) 
        {
            weight.push_back(i); // give weight to each item
            /*int save;
            save = rand()%30;
            while(save == 0) save = rand()%30;
            weight.push_back(save);*/
        }

        for (int i = 1; i <= element_num; ++i) //generate the random number to each item as value
        {
            int get;
            get = rand()%20;
            while(get == 0) get = rand()%20;
            value.push_back(get);
        }

        vector< vector<int> > result(element_num + 1, vector<int>(capacity + 1, 0)); 

        cout << "N=" << element_num << " ";
        cout <<  "W=" << capacity << " ";

        start = clock();
        max_rec = resursion(element_num,0,capacity,0,value,weight);
        end = clock();
        cout << "REC time:" << (double)(end-start) / CLOCKS_PER_SEC << "s" << " ";

        start = clock();
        knapsack(element_num, capacity, weight, value, result);
        end = clock();
        cout << "DP time:" << (double)(end-start) / CLOCKS_PER_SEC << "s" << " ";

        cout << "Max DP:" << result[element_num][capacity] << " ";
        cout << "Max Rec:" << max_rec << endl;
        element_num +=2;
    }
 
    return 0;
}
