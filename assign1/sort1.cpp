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
    if (myfile.is_open()){

        while (!myfile.eof()){
            getline (myfile,line);
            stringstream s(line); 
            int count = 0;
            while (getline(s, word, ',') && count < 1) { 
                int k = stoi(word);
                arr.push_back(k);
                count++; 
            }
        }
            myfile.close();
    } 

    insertion_sort(arr);

    for(int i = 0; i < arr.size(); ++i){
        cout << arr[i] << endl;
    }
    return 0;
}
