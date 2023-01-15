#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <complex>
#include <iostream>

#define MAX 256
using namespace std;

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


int main (int argc, char *argv[]) 
{
  MPI_Status status;
  int myrank, size;
  
  const size_t rows = MAX;
  const size_t cols = MAX;
  complex<double> buf[rows][cols]; 

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int chunk = MAX/size;
  double t1, t2;
  if (myrank == 0)
  {
    t1 = MPI_Wtime();

    int count = 0;
    // I'm the master
    for (int i = 0; i < MAX; ++i) 
    {
      for (int j = 0; j < MAX; ++j) 
      {
        buf[i][j] = count;
        count++;
      }
    }
    
    // Send the values for the 1st time.
    for (int i = 1; i < size; ++i) 
    {
      int retVal = MPI_Send(buf[i*chunk], MAX * chunk, MPI_C_DOUBLE_COMPLEX, i, 555, MPI_COMM_WORLD);
    }
    
    /****************************************************************************************************
     ****************************************************************************************************
     ****************************************************************************************************
    */
    // FFT Part starts here.
    // 1 D fft row wise.
    for (int row = 0; row < chunk; row++)
    {
      fft1d(buf[row], MAX);
    }

    
    // Receiving the data from all the slaves for first time.
    for (int i = 1; i < size; ++i) 
    {
        int retVal = MPI_Recv(buf[i*chunk], MAX * chunk, MPI_C_DOUBLE_COMPLEX, i, 555, MPI_COMM_WORLD, &status);
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

    // Send the values for the 2nd time.
    for (int i = 1; i < size; ++i) 
    {
      int retVal = MPI_Send(buf[i*chunk], MAX * chunk, MPI_C_DOUBLE_COMPLEX, i, 555, MPI_COMM_WORLD);
    }
    
    // 1 D fft col wise.
    for (int row = 0; row < chunk; row++)
    {
      fft1d(buf[row], MAX);
    }

    // Receiving the data from all the slaves for second time.
    for (int i = 1; i < size; ++i) 
    {
        int retVal = MPI_Recv(buf[i*chunk], MAX * chunk, MPI_C_DOUBLE_COMPLEX, i, 555, MPI_COMM_WORLD, &status);
    }
    
    /*
    // These operations are not needed.
    // Transpose the matrix second time
    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
        xtrans[j][i] = buf[i][j];
    }

    //Copying the values from xtrans back to x second time
    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
        buf[i][j] = xtrans[i][j];
    }
    //printf("I'm the master; I received the following values:\n");

    for (int i = 0; i < MAX; ++i) 
    {
      for (int j = 0; j < MAX; ++j) 
      {
        //printf("Rank : %d, Value %d\n", myrank, buf[i][j]);
        cout <<"Rank : " << myrank << " value : " << buf[i][j] << endl;
      }
    }
    */
    
    /****************************************************************************************************
     ****************************************************************************************************
     ****************************************************************************************************
    */
  }
  else
  {
    complex<double> buf1[chunk][MAX];
    //I'm the slave
    // Receiving the value for the 1st time.
    int retVal = MPI_Recv(buf1, MAX * chunk, MPI_C_DOUBLE_COMPLEX, 0, 555, MPI_COMM_WORLD, &status);
   
   /*
    printf("I'm the slave; I received the following values:\n");
    
    for (int i = 0; i < chunk; ++i) 
    {
      for (int j = 0; j < MAX; ++j) 
      {
        //printf("Rank : %d, Value %d\n", myrank, buf[i][j]);
        cout <<"Rank : " << myrank << " value : " << buf1[i][j] << endl;
      }
    }
    */

    /****************************************************************************************************
     ****************************************************************************************************
     ****************************************************************************************************
    */
    
    // 1 D fft row wise.
    for (int row = 0; row < chunk; row++)
    {
      fft1d(buf1[row], MAX);
    }
    
    /*
    printf("I'm the slave; I received the following values:\n");
    
    for (int i = 0; i < chunk; ++i) 
    {
      for (int j = 0; j < MAX; ++j) 
      {
        //printf("Rank : %d, Value %d\n", myrank, buf[i][j]);
        //if (myrank == 1)
          cout <<"Rank : " << myrank << " value : " << buf1[i][j] << endl;
      }
    }
     */

    // Sending the data to the master first time.
    retVal = MPI_Send(buf1, MAX * chunk, MPI_C_DOUBLE_COMPLEX, 0, 555, MPI_COMM_WORLD);

    // Receiving the value for the 2nd time.
    retVal = MPI_Recv(buf1, MAX * chunk, MPI_C_DOUBLE_COMPLEX, 0, 555, MPI_COMM_WORLD, &status);
    
    // 1 D fft col wise.
    for (int row = 0; row < chunk; row++)
    {
      fft1d(buf1[row], MAX);
    }

    // Sending the data to the master second time.
    retVal = MPI_Send(buf1, MAX * chunk, MPI_C_DOUBLE_COMPLEX, 0, 555, MPI_COMM_WORLD);
    /****************************************************************************************************
     ****************************************************************************************************
     ****************************************************************************************************
    */



  }

  t2 = MPI_Wtime();
  MPI_Finalize();

  if (myrank == 0)
  //cout << "Total time elapsed = " << t2-t1 << " seconds" << endl;
  cout << t2-t1;
  return 0;
}





