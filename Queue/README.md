# Queue

## What is it?

Queue is a project that implements a queue in two ways: on two stacks and on a singly linked list.

## Usage

Currently this library is can be compiled by g++ for Linux.

To use you need to download the folder with the code. Then go to the stack folder and enter the following commands:
    
    mkdir build
    cd build
    cmake ..
    make

To use cmake for queue project with all flags use this command:
cmake .. -DADD_SANITIZERS=ON -DADD_CLANG_TIDY=ON -DADD_BENCHMARK=ON -DADD_STACK_IMPL_TESTING=ON -DADD_LIST_IMPL_TESTING=ON
