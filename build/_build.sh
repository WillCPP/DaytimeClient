#!/bin/bash

conan install ../src

cmake ../src -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release

cmake --build . 
