# Typo corrector

## What is it?

Typo corrector can correct typos in the file you give him.

## Usage

Currently this project is can be compiled by g++ for Linux.

To use you need to download the folder with the code. Then go to the Hash_table folder and enter the following commands:
    
    mkdir build
    cd build
    cmake ..
    make

To use cmake for queue project with all flags use this command:
cmake .. -DADD_SANITIZERS=ON -DADD_CLANG_TIDY=ON -DADD_TYPO_CORRECTOR_TESTING=ON

You can also use the prescribed targets:

to run all: make
to run tests: make run_corrector_test
to formating code: make clang_format