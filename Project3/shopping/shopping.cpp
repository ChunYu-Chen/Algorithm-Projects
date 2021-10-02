#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

void knapsack(int element_num, int capacity, vector<int>& weight, vector<int>& value, vector< vector<int> >& result, vector<int>& item)
{   
    for (int i = 1; i <= element_num; ++i)
    {
        for (int j = 1; j <= capacity; ++j)
        {
            if (weight[i] > j) //if the current rest space cannot accept this item
            {
                result[i][j] = result[i - 1][j]; 
            }
            else
            {
                int value_after = result[i - 1][j - weight[i]] + value[i]; 
                int value_before = result[i - 1][j]; 
                //to discriminate if the current item is valueable or not.
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

    int w = capacity, total_value = result[element_num][capacity];
    for (int i = element_num; i > 0 && total_value > 0; i--) { 
        if (total_value == result[i - 1][w])  
            continue;         
        else { 
            // This item is included. 
            item.push_back(i); 
            // Since this weight is included its  
            // value is deducted 
            total_value = total_value - value[i]; 
            w = w - weight[i]; 
        } 
    } 
    /*int x = element_num, y = capacity;         //failed finding item code
    while(x>0 && y>0){
    	if(result[x][y] == result[x - 1][y - weight[x]] + value[x])
    	{
    		item.push_back(x);
    		y = y - weight[x];
    	}
    	x = x-1;
    }*/
}

int main()
{
	fstream buy;
	buy.open("shopping.txt"); 
	string save;

	int member_number, member_number_save;
	int element_num,element_num_save;
	vector<int> value(1,0);
	vector<int> weight(1,0);
	
	int item_count = 0;
	int capacity;
	vector<int> count;
	int number_family;
	int Case_num = 1;

	getline(buy,save); //read the data 
	istringstream token(save);
	token >> number_family; //read data individually
	ofstream output("result.txt"); //open the result.txt to store the result

	while(number_family--)
	{
		output << "Test Case " << Case_num << "\r\n";
		//cout << "Test Case " << Case_num << endl;
		Case_num++;

		getline(buy,save);
		istringstream token(save);	
    	int key;
    	token >> key; //read data individually
    	element_num = int(key); // save the element number 
    	element_num_save = int(key);

    	while(element_num_save--){ 
    		getline(buy,save); //read the every item's information
			istringstream token(save);	
			token >> key;
    		value.push_back(int(key));
    		token >> key;
    		weight.push_back(int(key));
    	}
    
    	getline(buy,save);
		istringstream token2(save);
		token2 >> key;
		member_number = int(key); //get the family memeber number 
		member_number_save = int(key);

		vector< vector<int> > item(member_number, vector<int>(0)); //to save the item's index which every family member toke

		while(member_number_save--){
			getline(buy,save); //read the every loading weight of family members
			istringstream token(save);	
			token >> key;
			capacity = key;
 			
 			//create a result table to store the calculating process and result
			vector< vector<int> > result(element_num + 1, vector<int>(capacity + 1, 0));
			//calculator the every one's best value
			knapsack(element_num, capacity, weight, value, result, item[item_count]); 
			item_count++;
			//store each best value number
			int gett = result[element_num][capacity];
			count.push_back(gett);

			//initiate the result table
			for(int a=0;a <element_num+1;a++){
				for(int b=0;b <capacity+1;b++){
					result[a][b] = 0;
				}
			}
		}
		//initiate value and weight 
		value.clear();
		value.push_back(0);
		weight.clear();
		weight.push_back(0);

		for(int x = 1; x < count.size();x++){
			count[0] += count[x];
		}
		//cout << "Total:" << count[0] << endl;
		output << "Total Price:" << count[0] << "\r\n";
		
		//output the each item which every family memeber toke
		for(int people=0;people<member_number;people++){
			//cout << people+1 << ":";
			output << people+1 << ":";
			for(int q=item[people].size()-1; q>=0;q--){
				//cout << item[people][q] << " ";
				output << item[people][q] << " ";
			}
			output << "\r\n";
			//cout << endl;
		}
		item_count = 0;
		count.clear();
		output << "\r\n";
	}
	buy.close();
	output.close();
	return 0;
}