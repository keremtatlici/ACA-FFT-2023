#include <complex>
#include <iostream>
#include <vector>
#include <valarray>


const double PI = 3.141592653589793238460;

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

using namespace std;


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

  // Printing the values
  for (int i = 0; i < x.size(); i++)
  {
    for (int j = 0; j < x[i].size(); j++)
    {
      cout << x[i][j] << "  ";
    }
    cout << endl;
  }

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
  for (int i = 0; i < x.size(); i++)
  {
    for (int j = 0; j < x[i].size(); j++)
    {
      cout << x[i][j] << "  ";
    }
    cout << endl;
  }
  cout << endl;
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

  // Printing the values
  for (int i = 0; i < x.size(); i++)
  {
    for (int j = 0; j < x[i].size(); j++)
    {
      cout << x[i][j] << "  ";
    }
    cout << endl;
  }

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
  printf("Final Result \n");
  // Printing the values
  for (int i = 0; i < x.size(); i++)
  {
    for (int j = 0; j < x[i].size(); j++)
    {
      cout << x[i][j] << "  ";
    }
    cout << endl;
  }

}

//main method
//int main(int argc, char *argv[])
int main()
{
  vector<vector<complex<double>>> arr {
                                  {3, 10, 12, 6},
                                  {4, 3, 1, 2},
                                  {3, 3, 1, 3},
                                  {5, 3, 8, 6}
                                };
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
  cout <<"The coefficients are : ";

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

  cout <<"After ifft : ";

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
  return 0;
}
