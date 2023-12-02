#ifndef DEQUE_H
#define DEQUE_H
#include <iostream>

template <typename T>
class Deque {
private:
  T** blockmap;
  std::size_t frontBlock;
  std::size_t backBlock;
  std::size_t frontIndex;
  std::size_t backIndex;
  std::size_t blockSize;
  std::size_t dequeSize;
  
  // Helper methods
  void resizeFront() {
    if (frontIndex == 0) {
      if (frontBlock == 0) {
	// Need to resize the blockmap by adding a new block at the front and adjusting frontBlock accordingly
	// Allocate a new blockmap with increased size
	T** newBlockmap = new T*[blockSize + 1];
	// Copy the existing blockmap to the new one
	std::copy(blockmap, blockmap + blockSize, newBlockmap + 1);
	// Allocate a new block at the front
	newBlockmap[0] = new T[blockSize];
	// Update frontBlock and blockmap
            ++frontBlock;
            blockmap = newBlockmap;
      } else {
	// Shift all blocks to the right to make space for a new block at the front
	for (std::size_t i = blockSize; i > 0; --i) {
	  blockmap[i] = blockmap[i - 1];
	}
	// Allocate a new block at the front
	blockmap[0] = new T[blockSize];
      }
      // Adjust frontIndex and backBlock
      frontIndex = blockSize - 1;
      ++backBlock;
    } else {
      // No need to resize the blockmap, just adjust frontIndex
      --frontIndex;
    }
  }
  
  void resizeBack() {
    if (backIndex == blockSize - 1) {
      if (backBlock == blockSize - 1) {
	// Need to resize the blockmap by adding a new block at the back and adjusting backBlock accordingly
	// Allocate a new blockmap with increased size
	T** newBlockmap = new T*[blockSize + 1];
	// Copy the existing blockmap to the new one
	std::copy(blockmap, blockmap + blockSize, newBlockmap);
	// Allocate a new block at the back
	newBlockmap[blockSize] = new T[blockSize];
	// Update backBlock and blockmap
	++backBlock;
	blockmap = newBlockmap;
      } else {
	// Shift all blocks to the left to make space for a new block at the back
	for (std::size_t i = 0; i < blockSize - 1; ++i) {
	  blockmap[i] = blockmap[i + 1];
	}
	// Allocate a new block at the back
	blockmap[blockSize - 1] = new T[blockSize];
      }
      // Adjust backIndex and frontBlock
      backIndex = 0;
      ++frontBlock;
    } else {
      // No need to resize the blockmap, just adjust backIndex
      ++backIndex;
    }
  }



  
public:
  // Constructors and Destructor
  Deque():blockmap(nullptr),frontBlock(0),backBlock(0),frontIndex(0),backIndex(0),blockSize(1),dequeSize(0)
  {
    // Initialize blockmap with a single block
    blockmap = new T*[1];
    blockmap[0] = new T[blockSize];
  }
  
  ~Deque() {
    // Deallocate memory for each block
    for (std::size_t i = 0; i <= backBlock; ++i) {
      delete[] blockmap[i];
    }
    // Deallocate memory for the blockmap array
    delete[] blockmap;
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
    return blockmap[frontBlock][frontIndex];
  }

  const T& front() const {
    if (empty()) {
      // Handle the case where the deque is empty
      throw std::out_of_range("Deque is empty. Cannot access front element.");
    }
    return blockmap[frontBlock][frontIndex];
  }
  
  T& back() {
    if (empty()) {
      // Handle the case where the deque is empty
      throw std::out_of_range("Deque is empty. Cannot access back element.");
    }
    return blockmap[backBlock][backIndex];
  }

  const T& back() const {
    if (empty()) {
      // Handle the case where the deque is empty
      throw std::out_of_range("Deque is empty. Cannot access back element.");
    }
    return blockmap[backBlock][backIndex];
  }
  
  // Modifiers
  void push_front(const T& value) {
    // Check if the front block is full
    if (frontIndex == 0) {
      // If the front block is full, resize the deque to make space at the front
      resizeFront();
    }
    // Move the front index to the left
    --frontIndex;
    // Insert the new value
    blockmap[frontBlock][frontIndex] = value;
    // Increment the deque size
    ++dequeSize;
  }
  
  void pop_front() {
    if (empty()) {
      // Handle the case where the deque is empty
      throw std::out_of_range("Deque is empty. Cannot perform pop_front.");
    }
    // Move the front index to the right
    ++frontIndex;
    // Decrement the deque size
    --dequeSize;
    // Check if the front block is empty after the pop operation
    if (frontIndex == blockSize) {
      // If the front block is empty, resize the deque to remove the empty block
      resizeFront();
    }
  }
  
  void push_back(const T& value) {
    // Check if the back block is full
    if (backIndex == blockSize - 1) {
      // If the back block is full, resize the deque to make space at the back
      resizeBack();
    }
    // Move the back index to the right
    ++backIndex;
    // Insert the new value
    blockmap[backBlock][backIndex] = value;
    // Increment the deque size
    ++dequeSize;
  }
  
  void pop_back() {
    if (empty()) {
      // Handle the case where the deque is empty
      throw std::out_of_range("Deque is empty. Cannot perform pop_back.");
    }
    // Move the back index to the left
    --backIndex;
    // Decrement the deque size
    --dequeSize;
    // Check if the back block is empty after the pop operation
    if (backIndex == static_cast<std::size_t>(-1)) {
      // If the back block is empty, resize the deque to remove the empty block
      resizeBack();
    }
  }
  
  // Operator overloading
  T& operator[](std::size_t index) {
    if (index >= dequeSize) {
      // Handle the case where the index is out of bounds
      throw std::out_of_range("Index out of bounds in operator[].");
    }

    std::size_t blockIndex = frontIndex + index;
    std::size_t blockNumber = frontBlock;
    
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

    std::size_t blockIndex = frontIndex + index;
    std::size_t blockNumber = frontBlock;
    
    // Adjust blockNumber and blockIndex if the index spans multiple blocks
    while (blockIndex >= blockSize) {
      blockIndex -= blockSize;
      ++blockNumber;
    }
    return blockmap[blockNumber][blockIndex];
  }
};

#endif //DEQUE_H
