#!/bin/bash

#test case 1
./ext2reader ./in/in0 > ./out/my_output0
diff ./out/my_output0 ./out/out0

