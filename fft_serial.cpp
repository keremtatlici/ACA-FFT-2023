#include <stdio.h>
#include <fstream>
#include <valarray>
#include <stdlib.h>
#include <complex>
#include <iostream>
#include <map>

using namespace std;

map<int, int> imageIndex{{ 512, 0 }, { 1024, 1 }, { 2048, 2 }, { 4096, 3 }, { 8192, 4 }};

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

// This function computes the 1D FFT of a given complex vector.
// The input vector is overwritten with the result.
void fft1d(complex<double> *x, int N) 
{
  // Base case
  if (N <= 1) return;

  // Split the input vector into even and odd indices
  complex<double> even[N / 2], odd[N / 2];
  for (size_t i = 0; i < N / 2; i++) 
  {
    even[i] = x[i * 2];
    odd[i] = x[i * 2 + 1];
  }

  // Recursively compute the FFT of the even and odd indices
  fft1d(even, N/2);
  fft1d(odd, N/2);

  // Combine the results
  for (size_t k = 0; k < N / 2; k++) 
  {
    complex<double> t = polar(1.0, -2 * M_PI * k / N) * odd[k];
    x[k] = even[k] + t;
    x[k + N / 2] = even[k] - t;
  }
}

void ifft1d(complex<double> *x, int N)
{
  // Taking the conjugate 
  for (int i = 0; i < N; i++)
  {
    x[i] = conj(x[i]);
  }
  fft1d(x, N);
  
  // Taking the conjugate 
  for (int i = 0; i < N; i++)
  {
    x[i] = conj(x[i]);
  }
  
  // Normalizing the values. 
  for (int i = 0; i < N; i++)
  {
    x[i] /= N;
  }
}


int main (int argc, char *argv[]) 
{
  int MAX;
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

  const size_t rows = MAX;
  const size_t cols = MAX;

  clock_t t1, t2;

  t1 = clock();
  complex<double> buf[rows][cols]; 

  // Reading the file path.
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
      buf[firstIdx][secondIdx] = val;
      secondIdx++;
    }
    firstIdx++;
  }


  // FFT Part starts here.
  // 1 D fft row wise.
  for (int row = 0; row < rows; row++)
  {
    fft1d(buf[row], MAX);
  }

  complex<double> xtrans[rows][cols];

  // Transpose the matrix first time.
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
      xtrans[j][i] = buf[i][j];
  }

  //Copying the values from xtrans back to x for first time.
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
      buf[i][j] = xtrans[i][j];
  }


  // 1 D fft col wise.
  for (int row = 0; row < rows; row++)
  {
    fft1d(buf[row], MAX);
  }


  // FFT Part ends here.
  /****************************************************************************************************
  ****************************************************************************************************
  ****************************************************************************************************
   */
  // IFFT Part starts here.


  // 1 D ifft row wise.
  for (int row = 0; row < rows; row++)
  {
    ifft1d(buf[row], MAX);
  }

  // Transpose the matrix second time.
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
      xtrans[j][i] = buf[i][j];
  }

  //Copying the values from xtrans back to x for second time.
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
      buf[i][j] = xtrans[i][j];
  }


  // 1 D ifft col wise.
  for (int row = 0; row < rows; row++)
  {
    ifft1d(buf[row], MAX);
  }

  // Opening the file to store results in a txt file.
  ofstream myfile (resultantImages[imageIndex[MAX]]);

  // Storing the results in the txt file.
  if (myfile.is_open())
  {
    for (int i = 0; i < MAX; ++i) 
    {
      for (int j = 0; j < MAX; ++j) 
      {
        myfile << buf[i][j] << " ";
      }
      myfile << endl;
    }
    myfile.close();
  }

  t2 = clock();

  cout << (t2-t1)/1000000.0;
  return 0;
}





