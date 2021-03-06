#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <algorithm>
using namespace std;

struct point_type
{
	int x;
	int y;
};

void cal_length(int point_num,vector< struct point_type >& input,vector< vector<int> >& output){
    int x,y;
    float get;
    int inte;
    for(int i=0;i<point_num-1;i++){
        for(int j=i+1;j<point_num;j++){
            x = input[i].x-input[j].x;
            y = input[i].y-input[j].y;
            get = sqrt(int(pow(x,2))+int(pow(y,2)));
            inte = round(get);
            output[i][j] = inte; //round the number then save it into output
            output[j][i] = inte;
            //cout << output[i][j] << " ";
        }
        //cout << endl;
    }

    //print the edge table
    /*for(int i=0;i<output.size();i++){
        for(int j=0;j<output[i].size();j++){
            cout << setw(3) << output[i][j];
        }
        cout << endl;
    }*/
}

void generate_point_list(int point_number,vector<int>& input){
    for(int i=0;i<point_number;i++){
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
    vector< struct point_type >& point,
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
    vector<int> point_count(point_num,0);//to count the frequency of every point
    choice.push_back(0);
    //cout << "Point" << setw(8) << "(x,y)" << setw(10) << "Distance" << endl;
    find_min(start, min, min_index, edge_weight, point_list);
    point_count[start]++;
    point_count[min_index]++;
    sum += min;
    choice.push_back(min_index);
    update_point_list(min_index,point_list);
    record_path[count_index].push_back(0);
    record_path[count_index++].push_back(min_index);
    //cout << "("<< point[0].x << "," << point[0].y << ")"<< " - ";
    //cout << "("<< point[min_index].x << "," << point[min_index].y << ")"<< setw(6);
    //cout << min << endl;
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
        point_count[start]++;
        point_count[min_index_cmp]++;
        //cout << "("<< point[start].x << "," << point[start].y << ")"<< " - ";
        //cout << "("<< point[min_index_cmp].x << "," << point[min_index_cmp].y << ")"<< setw(6);
        //cout << min << endl;
        sum += min_cmp;
        choice.push_back(min_index_cmp);
        update_point_list(min_index_cmp,point_list);
    }
    /*
    for(int x=0; x<point_count.size();x++)
    {
    	cout << point_count[x] << endl;
    }*/
    return sum;
}

int main(int argc, char** argv)
{
    string save_data;
    int singal_data;
    clock_t start,end;
    //vector<int> second_d;
    vector< struct point_type > point;
    start = clock();
    //int count = 0; //index of the points
    int get_point_num  = 0;
    struct point_type single_point;
    fstream input;
    input.open(argv[1]); //open the txt file
    
    while(getline(input, save_data)){
        if(save_data.size() <= 3) break;
        istringstream token(save_data);
        token >> singal_data;
        token >> singal_data;
        single_point.x = singal_data;
        token >> singal_data;
        single_point.y = singal_data;
        point.push_back(single_point);
        get_point_num++;
    }

    vector<int> second_dd(get_point_num,-1);
    vector< vector<int> > edge_weight(get_point_num,second_dd); //save the edge data into edge_weight
    
    vector<int> point_list;
    generate_point_list(get_point_num,point_list);

    vector<int> record_path_2;
    vector< vector<int> > record_path(get_point_num-1,record_path_2);
    //save the point data into the vector container (2_dimension)

    vector<int> choice;
    cal_length(get_point_num,point,edge_weight); //calculate the distance between each point

    int TSP_sum = 0;
    int min;
    int Start;
    int Start_init;
    int min_index;
    vector<int> TSP_cmp(get_point_num,0);
    //vector<int> temp;
    vector<int> track_2;
    vector< vector<int> > track(get_point_num,track_2);
    
    for(int b=0;b<get_point_num;b++)
    {
        generate_point_list(get_point_num,point_list);
        Start_init = b;
        Start = b;
        update_point_list(Start,point_list);
        track[b].push_back(Start);
        for(int x=0;x < get_point_num-1; x++)
        {
            find_min(Start, min, min_index, edge_weight, point_list);
            TSP_sum += min;
            track[b].push_back(min_index);
            
            Start = min_index;
            update_point_list(min_index,point_list);
        } 
        
        TSP_sum += edge_weight[min_index][Start_init];
        //cout << TSP_sum << endl;
        TSP_cmp[b] = TSP_sum;
        TSP_sum = 0;
    }

    int cmp = TSP_cmp[0];
    int index = 0;
    for(int a = 1;a < TSP_cmp.size();a++)
    {
        if(cmp > TSP_cmp[a]) 
        {
            index = a;
            cmp = TSP_cmp[a];
        }
    }
    end = clock();
    cout << "TSP:" << cmp << endl;
    cout << "Running time:" << double(end-start)/CLOCKS_PER_SEC << endl;

    string a = ".tour";
    string out_name = argv[1]+a;
    ofstream output;
    output.open(out_name);
    output << cmp  << "\n";
    for(int s=0;s<get_point_num;s++)
    {
        output << track[index][s] << "\n";
    }
    output.close();
    return 0;
}