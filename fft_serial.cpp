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
  std::vector<std::complex<double>> even(N / 2), odd(N / 2);
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
    std::complex<double> t = std::polar(1.0, -2 * M_PI * k / N) * odd[k];
    x[k] = even[k] + t;
    x[k + N / 2] = even[k] - t;
  }
}


void fft2d()
{

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

void ifft2d()
{

}


//main method
//int main(int argc, char *argv[])
int main()
{
  //vector<complex<double>> arr[4][4]; 
  vector<complex<double>> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0, 0, 0}; 

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

  fft1d(arr);
  cout <<"The coefficients are : ";

  // Printing the values
  for (int i = 0; i < arr.size(); i++)
  {
    cout << arr[i] << endl;
  }

  ifft1d(arr);

  cout <<"After ifft : ";

  // Printing the values
  for (int i = 0; i < arr.size(); i++)
  {
    cout << arr[i] << endl;
  }
  return 0;
}
