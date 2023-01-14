#include <complex>
#include <iostream>
#include <vector>
#include <valarray>
#include <fstream>

//g++ -std=c++11 playground.cpp -o playground.out

using namespace std;

string path_image512 = "datasets/gray/512x512_gray.txt";
string path_image1024 = "datasets/gray/1024x1024_gray.txt";
string path_image2048 = "datasets/gray/2048x2048_gray.txt";
string path_image4096 = "datasets/gray/4096x4096_gray.txt";
string path_image8192= "datasets/gray/8192x8192_gray.txt";
ofstream myfile;

int main()
{   
    ifstream f(path_image512);
    //store f in to a matrix
    vector<vector<int>> matrix;
    string line;
    while (getline(f, line)) {
        vector<int> row;
        int val;
        stringstream ss(line);
        while (ss >> val) {
            row.push_back(val);
        }
        matrix.push_back(row);
    }
    int image[matrix.size()][matrix[0].size()];

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            image[i][j] = matrix[i][j];
        }
    }
    //print image
    for (int i = 0; i < matrix.size(); i++) {
        //print new line
        cout << "\n\n\n" << endl;
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
    

    
}