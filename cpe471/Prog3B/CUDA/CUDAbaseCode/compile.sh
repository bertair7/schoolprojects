#/bin/bash
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/rablair/opencv_build/lib
/usr/local/cuda-8.0/bin/nvcc -I /home/rablair/opencv_build/include -I /home/rablair/opencv_build/include/opencv -L /home/rablair/opencv_build/lib -g -o output BlurColor.cu -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs
