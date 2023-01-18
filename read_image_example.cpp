#include <complex>
#include <iostream>
#include <vector>
#include <valarray>
#include <fstream>

#define size 512
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
    string line;
    int image[size][size];
    
    int i = 0;
    while (getline(f, line)) 
    {
        vector<int> row;
        int val;
        stringstream ss(line);
        int j = 0;
        while (ss >> val) 
        {
            image[i][j] = val;
            j++;
            //row.push_back(val);
        }
        //matrix.push_back(row);
        i++;
    }

    //print image
    for (int i = 0; i < size; i++) 
    {
      //print new line
      cout << "\n\n\n" << endl;
      for (int j = 0; j < size; j++) 
      {
        cout << image[i][j] << " ";
      }
      cout << endl;
    }

    return 0;
    
}
