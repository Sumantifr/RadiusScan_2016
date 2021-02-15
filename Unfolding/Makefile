#!/bin/bash
FILE=$1

echo ${FILE}
g++ -g -fno-stack-protector  `root-config --cflags` -I/usr/local/include -I/home/suman/RooUnfold/src ${FILE}.C -o ${FILE}.exe `root-config --glibs` -lMinuit -L/usr/local/lib -lCLHEP -L/home/suman/RooUnfold  -Wl,-rpath,/home/suman/RooUnfold -lRooUnfold
