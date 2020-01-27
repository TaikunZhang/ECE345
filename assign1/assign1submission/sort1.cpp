//INSERTION_SORT ALGORITHM 

#include <cstdlib>
#include <iostream>     
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm> 
#include <set>
#include <limits>
#include <chrono>
using namespace std::chrono;
using namespace std;

typedef struct node{
    double key;
    vector<string> values;
    node(int k, vector<string>& v){
        key = k;
        values = v;
    }
    node& operator =(node &n){
        this->key = n.key;
        this->values = n.values;
        return *this;
    }
}node;

void insertion_sort(vector<node>& arr){
    int i,j;
    double key;
    for(i = 1; i < arr.size(); ++i){
        node temp = arr[i];
        j = i-1;
        while(j >= 0 && temp.key < arr[j].key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = temp;
    }
}

int main(int argc, char* argv[])
{
    ifstream myfile (argv[1]);
    string line,word;
    vector<node> arr;
    //int size = 0;
    //int limit = 25000;
    if (myfile.is_open()){

        while (!myfile.eof()){
            getline (myfile,line);
            stringstream s(line); 
            int count = 0;
            int key;
            vector<string> values;
            while (getline(s, word, ',') /*&& size <= limit*/) { 
                if(count < 1){
                    key = stoi(word);
                    count++;
                }
                values.push_back(word);
                //size++;
            }
            arr.push_back(node(key,values));
        }
            myfile.close();
    } 
    //high_resolution_clock::time_point t_start = high_resolution_clock::now();
    insertion_sort(arr);
    //high_resolution_clock::time_point t_end = high_resolution_clock::now();

    for(int i = 0; i < arr.size(); i++){
        if(i == arr.size()-1)
            cout << arr[i].key << endl;
        else
            cout << arr[i].key << ',';
        for(int j = 0; j < arr[i].values.size(); j++){
            if(j == arr[i].values.size()-1)
                cout << arr[i].values[j] << endl;
            else
                cout << arr[i].values[j] << ',';
        }
    }
    //auto duration = duration_cast<nanoseconds>(t_end-t_start).count();
    //cout << duration << endl;
    //cout << arr.size() << endl;
    return 0;
}
