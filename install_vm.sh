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


git config --global user.name "keremtatlici"
git config --global user.email "krmttlc@gmail.com"


# write me script that removes below lines from .bashrc
#MPI_HOME=/usr/local/openmpi-4.1.1
#PATH=$MPI_HOME/bin:$PATH


#to run the code
#mpic++ -o fft_mpi fft_mpi.cpp -lm 
#mpirun -np 4 ./fft_mpi
# ulimit -s unlimited
#mpic++ -o fft_mpi fft_mpi.cpp -lm;mpirun -np 6 ./fft_mpi
#ssh -l valerien -i Desktop/key 35.192.101.4

#scp -i Desktop/key /Users/valerien/Downloads/id_rsa.pub valerien@34.28.191.186:/home/valerien/