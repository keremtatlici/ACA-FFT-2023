import numpy as np
import cv2

class myPath:
    def __init__(self, prefix_path, postfix_path):
        self.prefix_path = prefix_path
        self.postfix_path = postfix_path

read_path = myPath("datasets/gray/", "_gray.txt") #this should be results/ , _fft.txt
save_path = myPath('results/fft_png/','_fft.png')

fft_image512_readpath = read_path.prefix_path + '512x512'+ read_path.postfix_path
fft_image1024_readpath = read_path.prefix_path +'1024x1024'+ read_path.postfix_path
fft_image2048_readpath = read_path.prefix_path +'2048x2048'+ read_path.postfix_path
fft_image4096_readpath= read_path.prefix_path +'4096x4096'+ read_path.postfix_path
fft_image8192_readpath = read_path.prefix_path +'8192x8192'+ read_path.postfix_path

fft_image512 = np.loadtxt(fft_image512_readpath, dtype=np.uint8)
# fft_image1024 = np.loadtxt(fft_image1024_readpath, dtype=np.uint8)
# fft_image2048 = np.loadtxt(fft_image2048_readpath, dtype=np.uint8)
# fft_image4096 = np.loadtxt(fft_image4096_readpath, dtype=np.uint8)
# fft_image8192 = np.loadtxt(fft_image8192_readpath, dtype=np.uint8)

fft_image512_savepath = save_path.prefix_path + '512x512'+ save_path.postfix_path
# fft_image1024_savepath = save_path.prefix_path +'1024x1024'+ save_path.postfix_path
# fft_image2048_savepath = save_path.prefix_path +'2048x2048'+ save_path.postfix_path
# fft_image4096_savepath= save_path.prefix_path +'4096x4096'+ save_path.postfix_path
# fft_image8192_savepath = save_path.prefix_path +'8192x8192'+ save_path.postfix_path

cv2.imwrite(fft_image512_savepath, fft_image512)
# cv2.imwrite(fft_image1024_savepath, fft_image1024)
# cv2.imwrite(fft_image2048_savepath, fft_image2048)
# cv2.imwrite(fft_image4096_savepath, fft_image4096)
# cv2.imwrite(fft_image8192_savepath, fft_image8192)


