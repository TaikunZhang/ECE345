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

void insertion_sort(vector<double>& arr){
    int i,j;
    double key;
    for(i = 1; i < arr.size(); ++i){
        key = arr[i];
        j = i-1;
        while(j >= 0 && key < arr[j]){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

int main(int argc, char* argv[])
{
    ifstream myfile (argv[1]);
    string line,word;
    vector<double> arr;
    //int size = 0;
    //int limit = 25000;
    if (myfile.is_open()){

        while (!myfile.eof()){
            getline (myfile,line);
            stringstream s(line); 
            int count = 0;
            while (getline(s, word, ',') && count < 1 /*&& size <= limit*/) { 
                int k = stoi(word);
                arr.push_back(k);
                count++; 
                //size++;
            }
        }
            myfile.close();
    } 
    //high_resolution_clock::time_point t_start = high_resolution_clock::now();
    insertion_sort(arr);
    //high_resolution_clock::time_point t_end = high_resolution_clock::now();

    for(int i = 0; i < arr.size(); ++i){
        cout << arr[i] << endl;
    }
    //auto duration = duration_cast<nanoseconds>(t_end-t_start).count();
    //cout << duration << endl;
    //cout << arr.size() << endl;
    return 0;
}
