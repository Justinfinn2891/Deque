#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Deque {
 private:
  T** blockmap;
  std::size_t frontBlock;
  std::size_t index; // Single index variable to represent both front and back indexes
  std::size_t blockSize;
  std::size_t dequeSize;
  
  // Helper methods
 void resizeFront() {
    if (index == 0) {
        // Need to resize the blockmap by adding a new block at the front
        // Allocate a new blockmap with increased size
        T** newBlockmap = new T*[blockSize + 1];
        // Copy the existing blockmap to the new one
        std::copy(blockmap, blockmap + blockSize, newBlockmap + 1);
        // Allocate a new block at the front
        newBlockmap[0] = new T[blockSize];
        // Update frontBlock and blockmap
        ++frontBlock;
        blockmap = newBlockmap;
        // Update blockSize to the new size
        ++blockSize;
        // Adjust index to the last position of the new front block
        index = blockSize - 1;
    } else {
        // No need to resize the blockmap, just adjust index
        --index;
    }
    std::cout << "front resize complete" << std::endl;
}

void resizeBack() {
    std::cout << "resizing back" << std::endl;
    // Need to resize the blockmap by adding a new block at the back
    // Allocate a new blockmap with increased size
    T** newBlockmap = new T*[blockSize + 1];
    // Copy the existing blockmap to the new one
    std::copy(blockmap, blockmap + blockSize, newBlockmap);
    // Allocate a new block at the back
    newBlockmap[blockSize - 1] = new T[blockSize];

    // Update blockmap to point to the new blockmap
    blockmap = newBlockmap;

    // Increment frontBlock to point to the new back block
    ++frontBlock;

    // Update blockSize to the new size
    ++blockSize;

    // Reset index to the first position of the new back block
    index = 0;
    std::cout << "back resize complete" << std::endl;
}
  
  
public:
  // Constructors and Destructor
  Deque() : blockmap(nullptr), frontBlock(0), index(0), blockSize(1), dequeSize(0) {
    // Initialize blockmap with a single block
    blockmap = new T*[1];
    blockmap[0] = new T[blockSize];
  }
  
  ~Deque() {
    // Deallocate memory for each block
    for (std::size_t i = 0; i <blockSize; ++i) {
      delete[] blockmap[i];
    }
    
    // Deallocate memory for the blockmap
    delete[] blockmap;
    std::cout<<"Destroyed Deque"<<std::endl;
  }
  
  
  
  
  // Capacity
  bool empty() const {
    // checks to see if the deque is empty and returns true or false
    return dequeSize == 0;
  }
  
  std::size_t size() const {
    // Checks the size of the deque
    return dequeSize;
  }
  
  // Element access
  T& front() {
    if (empty()) {
      // Handle the case where the deque is empty
      throw std::out_of_range("Deque is empty. Cannot access front element.");
    }
    return blockmap[frontBlock][index];
  }
  
  const T& front() const {
    if (empty()) {
      // Handle the case where the deque is empty
      throw std::out_of_range("Deque is empty. Cannot access front element.");
    }
    return blockmap[frontBlock][index];
  }
  
  T& back() {
    if (empty()) {
      // Handle the case where the deque is empty
      throw std::out_of_range("Deque is empty. Cannot access back element.");
    }
    // Adjust index to the last position of the current back block
    std::size_t adjustedIndex = (index == 0) ? blockSize - 1 : index - 1;
    return blockmap[frontBlock][adjustedIndex];
  }

  const T& back() const {
    if (empty()) {
      // Handle the case where the deque is empty
      throw std::out_of_range("Deque is empty. Cannot access back element.");
    }
    // Adjust index to the last position of the current back block
    std::size_t adjustedIndex = (index == 0) ? blockSize - 1 : index - 1;
    return blockmap[frontBlock][adjustedIndex];
  }

  // Modifiers
  void push_front(const T& value) {
    // Check if the front block is full
    if (index == 0) {
      // If the front block is full, resize the deque to make space at the front
      resizeFront();
    }
    // Move the index to the left
    --index;
    // Insert the new value
    blockmap[frontBlock][index] = value;
    // Increment the deque size
    ++dequeSize;
  }
  
  void pop_front() {
    if (empty()) {
      // Handle the case where the deque is empty
      throw std::out_of_range("Deque is empty. Cannot perform pop_front.");
    }
    // Move the index to the right
    ++index;
    // Decrement the deque size
    --dequeSize;
    // Check if the front block is empty after the pop operation
    if (index == blockSize) {
      // If the front block is empty, resize the deque to remove the empty block
      resizeFront();
    }
  }
  
  void push_back(const T& value) {
    // Check if the back block is full
    if (index == blockSize - 1) {
      // If the back block is full, resize the deque to make space at the back
      resizeBack();
    }
    else {
      // Move the index to the right
      ++index;
      // Insert the new value
      blockmap[frontBlock][index] = value;
      // Increment the deque size
      ++dequeSize;
    }
  }

  void pop_back() {
    if (empty()) {
      // Handle the case where the deque is empty
      throw std::out_of_range("Deque is empty. Cannot perform pop_back.");
    }
    
    // Move the index to the left
    --index;
    
    // Decrement the deque size
    --dequeSize;
    
    // Check if the back block is empty after the pop operation
    if (index == static_cast<std::size_t>(-1)) {
      // If the back block is empty, resize the deque to remove the empty block
      resizeBack();
      // Reset index to the last position of the new back block
      index = blockSize - 1;
    }

        // Adjust frontBlock if it goes below 0 after resizeBack
    if (frontBlock > 0 && index == 0) {
        --frontBlock;
        index = blockSize - 1;
    }

  }
  
  // Operator overloading
  T& operator[](std::size_t index) {
    if (index >= dequeSize) {
      // Handle the case where the index is out of bounds
      throw std::out_of_range("Index out of bounds in operator[].");
    }

    std::size_t blockNumber = frontBlock;
    std::size_t blockIndex = (index + this->index) % blockSize;

 // Adjust blockNumber and blockIndex if the index spans multiple blocks
    while (blockIndex >= blockSize) {
        blockIndex -= blockSize;
        ++blockNumber;
    }
    
    return blockmap[blockNumber][blockIndex];
  }
  
  const T& operator[](std::size_t index) const {
    if (index >= dequeSize) {
      // Handle the case where the index is out of bounds
      throw std::out_of_range("Index out of bounds in operator[].");
    }
    
    std::size_t blockNumber = frontBlock;
    std::size_t blockIndex = (index + this->index) % blockSize;

 // Adjust blockNumber and blockIndex if the index spans multiple blocks
    while (blockIndex >= blockSize) {
        blockIndex -= blockSize;
        ++blockNumber;
    }
    
    return blockmap[blockNumber][blockIndex];
  }
};

#endif // DEQUE_H
