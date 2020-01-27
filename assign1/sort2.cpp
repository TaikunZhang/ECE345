//MERGE_SORT ALGORITHM 

#include <cstdlib>
#include <iostream>     
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm> 
#include <set>
#include <limits>
#include <queue>
#include <tgmath.h> 
#include <chrono>
using namespace std::chrono;
using namespace std;

void mergesort(vector<double>& arr, int l, int r);
void merge(vector<double>& arr, int l, int m, int r);

void mergesort(vector<double>& arr, int l, int r){
    if (l < r) 
    { 
        int m = floor((l+r)/2); 
        mergesort(arr, l, m); 
        mergesort(arr, m+1, r); 
        merge(arr, l, m, r); 
    } 
}
void merge(vector<double>& arr, int l, int m, int r){
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
    vector<double> left;
    vector<double> right;
   
    for(i = 0; i < n1; i++){
        left.push_back(arr[l+i]);
    }
    for(j = 0; j < n2; j++){
        right.push_back(arr[m+1+j]);
    }
    i=0;
    j=0;
    k=l;
    while(i < n1 && j < n2){
        if(left[i] <= right[j]){
            arr[k] = left[i];
            i++;
        }
        else{
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while(i < n1){
        arr[k] = left[i];
        i++;
        k++;
    }
    while(j < n2){
        arr[k] = right[j];
        j++;
        k++;
    }
}

int main(int argc, char* argv[]){
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
    mergesort(arr,0,arr.size()-1);
    //high_resolution_clock::time_point t_end = high_resolution_clock::now();
    for(int i = 0; i < arr.size(); ++i){
        cout << arr[i] << endl;
    }
    //auto duration = duration_cast<nanoseconds>(t_end-t_start).count();
    //cout << duration << endl;
    //cout << arr.size() << endl;
    return 0;
}
