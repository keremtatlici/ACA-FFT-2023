#include <complex>
#include <iostream>
#include <vector>
#include <valarray>

#include <stdio.h>
#include <fstream>

#include <stdlib.h>


#include <map>
using namespace std;

map<int, int> imageIndex{ { 512, 0 }, { 1024, 1 }, { 2048, 2 }, { 4096, 3 }, { 8192, 4 } };

string path_image512 = "datasets/gray/512x512_gray.txt";
string path_image1024 = "datasets/gray/1024x1024_gray.txt";
string path_image2048 = "datasets/gray/2048x2048_gray.txt";
string path_image4096 = "datasets/gray/4096x4096_gray.txt";
string path_image8192= "datasets/gray/8192x8192_gray.txt";

string datasetImages[5] = {path_image512, path_image1024, path_image2048, path_image4096, path_image8192};

string path_txt512 = "results/fft_txt/512x512_fft.txt";
string path_txt1024 = "results/fft_txt/1024x1024_fft.txt";
string path_txt2048 = "results/fft_txt/2048x2048_fft.txt";
string path_txt4096 = "results/fft_txt/4096x4096_fft.txt";
string path_txt8192 = "results/fft_txt/8192x8192_fft.txt";

string resultantImages[5] = {path_txt512, path_txt1024, path_txt2048, path_txt4096, path_txt8192};


const double PI = 3.141592653589793238460;

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;




// This function computes the 1D FFT of a given complex vector.
// The input vector is overwritten with the result.
void fft1d(vector<complex<double>> &x) 
{
  const size_t N = x.size();

  // Base case
  if (N <= 1) return;

  // Split the input vector into even and odd indices
  vector<complex<double>> even(N / 2), odd(N / 2);
  for (size_t i = 0; i < N / 2; i++) 
  {
    even[i] = x[i * 2];
    odd[i] = x[i * 2 + 1];
  }

  // Recursively compute the FFT of the even and odd indices
  fft1d(even);
  fft1d(odd);

  // Combine the results
  for (size_t k = 0; k < N / 2; k++) 
  {
    complex<double> t = polar(1.0, -2 * M_PI * k / N) * odd[k];
    x[k] = even[k] + t;
    x[k + N / 2] = even[k] - t;
  }
}

// Function to do the 2d fft.
void fft2d(vector<vector<complex<double>>> &x)
{
  const size_t rows = x.size();
  const size_t cols = x[0].size();
  
  //printf("rows: %d, cols: %d", rows, cols);  

  // 1 D fft row wise.
  for (int row = 0; row < rows; row++)
  {
    fft1d(x[row]);
  }
  
  // Transpose the matrix
  vector<vector<complex<double>>> xtrans(x[0].size(), vector<complex<double>>(x.size()));

  for (size_t i = 0; i < x.size(); ++i)
  {
    for (size_t j = 0; j < x[0].size(); ++j)
      xtrans[j][i] = x[i][j];
  }

  x = xtrans;

  // // Printing the values
  // for (int i = 0; i < x.size(); i++)
  // {
  //   for (int j = 0; j < x[i].size(); j++)
  //   {
  //     cout << x[i][j] << "  ";
  //   }
  //   cout << endl;
  // }

  // 1 D fft col wise.
  for (int col = 0; col < cols; col++)
  {
    fft1d(x[col]);
  }

  /*
  // Transpose it again.
  for (size_t i = 0; i < x.size(); ++i)
  {
    for (size_t j = 0; j < x[0].size(); ++j)
      xtrans[j][i] = x[i][j];
  }

  x = xtrans;
  */
  // Printing the values
  // for (int i = 0; i < x.size(); i++)
  // {
  //   for (int j = 0; j < x[i].size(); j++)
  //   {
  //     cout << x[i][j] << "  ";
  //   }
  //   cout << endl;
  // }
  // cout << endl;
}


void remove_coefficient()
{

}


void ifft1d(vector<complex<double>> &x)
{
  // Taking the conjugate 
  for (int i = 0; i < x.size(); i++)
  {
    x[i] = conj(x[i]);
  }
  fft1d(x);
  
  // Taking the conjugate 
  for (int i = 0; i < x.size(); i++)
  {
    x[i] = conj(x[i]);
  }
  
  // Normalizing the values. 
  for (int i = 0; i < x.size(); i++)
  {
    x[i] /= x.size();
  }
}

void ifft2d(vector<vector<complex<double>>> &x)
{
  const size_t rows = x.size();
  const size_t cols = x[0].size();
  
  //printf("rows: %d, cols: %d", rows, cols);  

  // 1 D fft row wise.
  for (int row = 0; row < rows; row++)
  {
    ifft1d(x[row]);
  }
  
  // Transpose the matrix
  vector<vector<complex<double>>> xtrans(x[0].size(), vector<complex<double>>(x.size()));

  for (size_t i = 0; i < x.size(); ++i)
  {
    for (size_t j = 0; j < x[0].size(); ++j)
      xtrans[j][i] = x[i][j];
  }

  x = xtrans;

  // // Printing the values
  // for (int i = 0; i < x.size(); i++)
  // {
  //   for (int j = 0; j < x[i].size(); j++)
  //   {
  //     cout << x[i][j] << "  ";
  //   }
  //   cout << endl;
  // }

  // 1 D fft col wise.
  for (int col = 0; col < cols; col++)
  {
    ifft1d(x[col]);
  }
  /* 
  // Transpose it again.
  for (size_t i = 0; i < x.size(); ++i)
  {
    for (size_t j = 0; j < x[0].size(); ++j)
      xtrans[j][i] = x[i][j];
  }

  x = xtrans;
  */
  //printf("Final Result \n");
  // // Printing the values
  // for (int i = 0; i < x.size(); i++)
  // {
  //   for (int j = 0; j < x[i].size(); j++)
  //   {
  //     cout << x[i][j] << "  ";
  //   }
  //   cout << endl;
  // }

}

//main method
//int main(int argc, char *argv[])
int main(int argc, char *argv[])
{
  int MAX;
  clock_t start, end;
  if ((argc == 2) && 
      (atoi(argv[1]) == 512 || atoi(argv[1]) == 1024 || 
       atoi(argv[1]) == 2048 || atoi(argv[1]) == 4096 ||
       atoi(argv[1]) == 8192 ))
  {
    MAX = atoi(argv[1]);
  }
  else
  {
    cout <<"Error: Wrong size of the image. Please provide a valid size \n"
    "Valid Size: 512, 1024, 2048, 4096 and 8192 \n";
  }
  start = clock();
  vector<vector<complex<double>>> arr(MAX, vector<complex<double>>(MAX));

  ifstream f(datasetImages[imageIndex[MAX]]);
  string line;
  int firstIdx = 0;
  
  // Reading the txt file to store in a 2d matrix.
  while (getline(f, line)) 
  {
      int val;
      stringstream ss(line);
      int secondIdx = 0;
      while (ss >> val) 
      {
          arr[firstIdx][secondIdx] = val;
          secondIdx++;
      }
      firstIdx++;
  }
//vector<complex<double>> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0, 0, 0}; 
  
  /*
  // Initializing the values.
  for (int i = 0; i < arr.size(); i++)
  {
    for (int j = 0; j < arr[i].size(); j++)
    {
      arr[i][j] = i; 
    }
  }
  */

  fft2d(arr);
  //cout <<"The coefficients are : ";

  /*
  // Printing the values
  for (int i = 0; i < arr.size(); i++)
  {
    for (int j = 0; j < arr[i].size(); j++)
    {
      cout << arr[i][j] << "  ";
    }
    cout << endl;
  }
  */

  ifft2d(arr);

  //cout <<"After ifft : ";

  /*
  // Printing the values
  for (int i = 0; i < arr.size(); i++)
  {
    for (int j = 0; j < arr[i].size(); j++)
    {
      cout << arr[i][j] << "  ";
    }
    cout << endl;
  }
  */


  ofstream myfile (resultantImages[imageIndex[MAX]]);

  // Storing the results in the txt file.
  if (myfile.is_open())
  {
    for (int i = 0; i < MAX; ++i) 
    {
      for (int j = 0; j < MAX; ++j) 
      {
        myfile << arr[i][j] << " ";
      }
      myfile << endl;
    }
    myfile.close();
  }
  end = clock();
   cout << (end-start)/1000000.0;
  return 0;
}
