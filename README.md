#Fast Fourier Transform with MPI

Our aim for this project was to implement FFT in 2D to show strong scalability and weak scalability on GCP using MPI for different sized images.

#Fast Fourier Transform in 1D
The one-dimensional Fast Fourier Transform (1D-FFT) is a computational algorithm used to decompose a signal in the time or spatial domain into its corresponding frequency components in the frequency domain. The 1D-FFT is based on the mathematical concept of the discrete Fourier transform (DFT), which is a way of representing a finite sequence of data points in the complex plane.

#Fast Fourier Transform in 2D
The 2D-FFT algorithm works by first decomposing the image or signal into rows, and then for each row, it applies the 1D-FFT algorithm. The resulting frequency coefficients are then arranged in a two-dimensional matrix. Next, the algorithm transposes this matrix and decomposes each column using the 1D-FFT. The final result is a two-dimensional matrix of frequency coefficients that represents the original image or signal in the frequency domain.

#Environment Setup on GCP.
To setup the environment on GCP, create a vm and clone the repository on the GCP machine.
These are some of the requirements for deploying it on GCP.

sudo apt update -y
sudo apt install g++ gcc build-essential htop wget -y
wget https://download.open-mpi.org/release/open-mpi/v4.1/openmpi-4.1.1.tar.gz
tar -xzvf openmpi-4.1.1.tar.gz
cd openmpi-4.1.1/
./configure --prefix=/usr/local/openmpi-4.1.1
sudo make -j$(nproc)
sudo make install
sudo apt install python3 -y
sudo apt install python3-pip -y
pip3 install numpy
apt-get install ffmpeg libsm6 libxext6  -y
pip3 install opencv-python

To increase the size of the stack one can use,
ulimit -s unlimited 

#Compilation and Execution.

To convert the images in "datasets/rgb/" folder to "datasets/gray/" 
in txt format,  run the following command.
python3 convert\_image.py

In order to compile the fft\_serial.cpp, the command used will be:
g++ -g -O2 -o fft\_serial fft\_serial.cpp -std=c++11

To run this file run the command:
./fft\_serial 8192

In order to compile the fft\_mpi.cpp, the command used will be:
mpic++ -o -O2 fft\_mpi fft\_mpi.cpp -lm -std=c++11 

To run this file on a single machine, run the command:
mpirun -np 2  fft\_mpi 8192

To run this file on a cluster machine, run the command:
mpirun --prefix /usr/local/openMPI/ -np 8 --hostfile hostfile fft\_mpi 8192

This execution stores the file inside results/fft\_txt/ folder.

To convert txt files in results/fft\_txt/ folder, run the command,
pythond3 run\_txt\_images.py
