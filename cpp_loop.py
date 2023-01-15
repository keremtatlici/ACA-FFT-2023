import numpy as np
import subprocess

time_results = []

cmd = "mpirun -np 8 ./fft_mpi"

def run_cpp():
    result = subprocess.run(cmd, capture_output=True, shell=True)
    result = float(result.stdout.decode('utf-8'))
    return result

for i in range(20):
    result = run_cpp()
    time_results.append(result)

time_results = np.array(time_results)
print(time_results.mean())

