#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <math.h>
#include <algorithm>
using namespace std;

void cal_length(int point_num,vector< vector<int> >& input,vector< vector<int> >& output){
    int x,y;
    float get;
    int inte;
    for(int i=0;i<point_num-1;i++){
        for(int j=i+1;j<point_num;j++){
            x = input[i][0]-input[j][0];
            y = input[i][1]-input[j][1];
            get = sqrt(int(pow(x,2))+int(pow(y,2)));
            inte = round(get);
            output[i][j] = inte; //round the number then save it into output
            output[j][i] = inte;
        }
    }
}

void generate_point_list(int point_number,vector<int>& input){
    for(int i=1;i<point_number;i++){
        input.push_back(i);
    }
}

//update the point list
void update_point_list(int index, vector<int>& input){
    vector<int> temp;
    //cout << "index:" << index << " ";
    for(int i = 0;i < input.size();i++){
        if(index != input[i]){
            //cout << "input[i]:" << input[i] << " ";
            temp.push_back(input[i]);
       }
    }
    //cout << endl;
    input.clear();
    input = temp;
}

void find_min(
    int& start, 
    int& min, 
    int& min_index, 
    vector< vector<int> >& edge_weight, 
    vector<int>& point_list){

    min = edge_weight[start][point_list[0]];
    min_index = point_list[0];
    for(int i=1;i<point_list.size();i++){
        if(min > edge_weight[start][point_list[i]]){
            min = edge_weight[start][point_list[i]];
            min_index = point_list[i];
        }
    }
    //cout << "min:" << min << " "<< endl;
    //cout << "min_index:" << min_index << endl;
}
int cal_mst(
    int start, 
    int point_num,
    vector< vector<int> >& point,
    vector<int>& point_list,
    vector< vector<int> >& edge_weight,
    vector<int>& choice,
    vector< vector<int> >& record_path){

    int count_index = 0; //count record index
    int sum = 0;
    int min;
    int min_index;
    int min_cmp;
    int min_index_cmp;
    choice.push_back(0);
    cout << "Point" << setw(8) << "(x,y)" << setw(10) << "Distance" << endl;
    find_min(start, min, min_index, edge_weight, point_list);
    sum += min;
    choice.push_back(min_index);
    update_point_list(min_index,point_list);
    record_path[count_index].push_back(0);
    record_path[count_index++].push_back(min_index);
    cout << "("<< point[0][0] << "," << point[0][1] << ")"<< " - ";
    cout << "("<< point[min_index][0] << "," << point[min_index][1] << ")"<< setw(6);
    cout << min << endl;
    //cout << "one:"<<min_index << endl;

    while(!(choice.size() == point_num)){
        find_min(choice[0], min, min_index, edge_weight, point_list);
        min_cmp = min;
        min_index_cmp = min_index;
        start = choice[0];

        //cout << "0:" << 0 << "-" << min << endl;
        for(int i=1 ; i< choice.size();i++){
            find_min(choice[i], min, min_index, edge_weight, point_list);
            //cout << "i:" << i << "-" << min << endl;
            if(min_cmp > min){
                min_cmp = min;
                min_index_cmp = min_index;
                start = choice[i];
            }
        }
        record_path[count_index].push_back(start);
        record_path[count_index++].push_back(min_index_cmp);
        cout << "("<< point[start][0] << "," << point[start][1] << ")"<< " - ";
        cout << "("<< point[min_index_cmp][0] << "," << point[min_index_cmp][1] << ")"<< setw(6);
        cout << min << endl;
        sum += min_cmp;
        choice.push_back(min_index);
        update_point_list(min_index,point_list);
    }
    return sum;
}

int main(int argc, char** argv)
{
    string save_data;
    int singal_data;
    vector<int> second_d;
    vector< vector<int> > point(0,second_d);
    
    int count = 0; //index of the points
    int get_point_num;

    fstream input;
    input.open(argv[1]); //open the txt file
    getline(input, save_data); // read the first number which represent the number of point.
    istringstream(save_data) >> get_point_num; //get the point number
    point.resize(get_point_num); //set the vector capacity as number of point

    vector<int> second_dd(get_point_num,-1);
    vector< vector<int> > edge_weight(get_point_num,second_dd); //save the edge data into edge_weight
    
    vector<int> point_list;
    generate_point_list(get_point_num,point_list);

    vector<int> record_path_2;
    vector< vector<int> > record_path(get_point_num-1,record_path_2);
    //save the point data into the vector container (2_dimension)
    while(!input.eof()){
        getline(input, save_data);
        istringstream token(save_data);
        while(token >> singal_data){
            point[count].push_back(singal_data);
        }
        count++;
    }

    vector<int> choice;
    cal_length(get_point_num,point,edge_weight); //calculate the distance between each point

    //start to calculate the MST
    update_point_list(0, point_list);
    int start_init = 0;
    int sum_distance;
    sum_distance = cal_mst(start_init,get_point_num, point,point_list,edge_weight,choice, record_path);
    /*for(int i=0; i< record_path.size();i++){
        for(int j=0; j< record_path[i].size();j++){
            cout << record_path[i][j] << " ";
        }
        cout << endl;
    }*/
    cout << "Total distance:" << sum_distance << endl;
    return 0;
}