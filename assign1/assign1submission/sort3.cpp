/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: mahroos2
 *
 * Created on January 19, 2020, 2:38 PM
 */



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
#include <bits/stdc++.h> 

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

void bubbleSort(vector<node>& arr, int n)  
{  
    int i, j;
    for (i = 0; i < n-1; i++){
        for (j = 0; j < n-i-1; j++){
            
            if (arr[j].key > arr[j+1].key){
                node temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}  



void cocktailSort(vector<node>& arr, int n)
{ 
    bool swapped = true;
    int start = 0;
    int end = n - 1;
 
    while (swapped) {
        swapped = false;
  
        for (int i = start; i < end; ++i) {
            if (arr[i].key > arr[i + 1].key) {
                node temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                swapped = true;
            }
        }
        if (!swapped)
            break;
  
        swapped = false;
        --end;
        
        for (int i = end - 1; i >= start; --i) {
            if (arr[i].key > arr[i + 1].key) {
                node temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                swapped = true;
            }
        }
        ++start;
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
            if(myfile.eof())break;
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
    int n = arr.size();
    bubbleSort(arr, n);
    //cocktailSort(arr, n);
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

