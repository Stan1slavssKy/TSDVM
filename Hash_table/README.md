# Hash_table

## What is it?

Here I implemented a dictionary based on a hash table with a separate chaining to solve collisions

## Usage

Currently this project is can be compiled by g++ for Linux.

To use you need to download the folder with the code. Then go to the Hash_table folder and enter the following commands:
    
    mkdir build
    cd build
    cmake ..
    make

To use cmake for hash table with all flags use this command:
cmake .. -DADD_SANITIZERS=ON -DADD_CLANG_TIDY=ON -DADD_HASH_TABLE_TESTING=ON
