#!/bin/bash

cd Src
make
cd ..
cp Src/mc mc
./mc
