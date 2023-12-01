#include <iostream>

#ifndef DEQUE_H
#define DEQUE_H

class Deque{
 private:
  //T** blockSize; 
 int size;
 int mapSize;
 const static int blockSize = 5;
 int first_block;
 int first_element;

 
 
 public:

 Deque();
 
};

#endif DEQUE_H
