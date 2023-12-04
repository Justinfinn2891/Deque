/**
 * @file deque.h
 * @author Justin Finn and Gabriel Speer
 * @date 2023-12-04
 * @brief .h file containing the template and Deque class 
 * 
 * file containing template and deque class 
 */

#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>

template <typename T>



/**
 * deque class that holds the methods for deque
 *
 * @class Deque deque.h "Deque/deque.h"
 * @brief class holding the variables in methods for deque 
 *
 */
class Deque {
private:
  // VARIABLES
    T** blockmap;
    int size;          // Total number of elements in the deque
    int mapsize;       // Number of blocks in the double array
    const static int blocksize = 4096;  // Size of each block
    int firstblock;    // Index of the first block in the blockmap
    int firstElement;  // Index of the first element in the deque

public:
    

/**
 * constructor
 *
 * @pre 
 * @post 
 * 
 */
  Deque() : blockmap(nullptr), size(0), mapsize(0), firstblock(0), firstElement(0) {}

  

/**
 * destructor
 *
 * @pre 
 * @post 
 * 
 */
  ~Deque() {
        if (blockmap != nullptr) {
            for (int i = 0; i < mapsize; ++i) {
                delete[] blockmap[i];
            }
            delete[] blockmap;
        }
    }

    // Add element to the front

/**
 * adds element to the front
 *
 * @param const T& value 
 * @pre 
 * @return void 
 * @post 
 * 
 */
    void push_front(const T& value) {
        if (blocksize == 0) {
            // Initial allocation
            blockmap = new T*[1];
            blockmap[0] = new T[1];
            mapsize = 1;
        } else if (size % blocksize == 0) {
            // Allocate a new block if the current one is full
            T** newBlockmap = new T*[mapsize + 1];
            for (int i = 0; i < mapsize; ++i) {
                newBlockmap[i + 1] = blockmap[i];
            }
            newBlockmap[0] = new T[blocksize];
            delete[] blockmap;
            blockmap = newBlockmap;
            ++mapsize;
        }

        // Shift elements to make space for the new element
        for (int i = size; i > 0; --i) {
            blockmap[i / blocksize][i % blocksize] = blockmap[(i - 1) / blocksize][(i - 1) % blocksize];
        }

        // Add the new element to the front
        blockmap[0][0] = value;
        ++size;
    }

    // Remove element from the front

/**
 * removes element from the front
 *
 * @pre 
 * @return void 
 * @post 
 * 
 */
    void pop_front() {
        if (empty()) {
            std::cerr << "Deque is empty. Cannot pop from the front." << std::endl;
            return;
        }

        // Shift elements to fill the gap left by the front element
        for (int i = 0; i < size - 1; ++i) {
            blockmap[i / blocksize][i % blocksize] = blockmap[(i + 1) / blocksize][(i + 1) % blocksize];
        }

        // If the last block is now empty, deallocate it
        if ((size - 1) % blocksize == 0 && mapsize > 1) {
            delete[] blockmap[mapsize - 1];
            --mapsize;
        }

        --size;
    }

    // Add element to the back

/**
 * pushes element to the back
 *
 * @param const T& value 
 * @pre 
 * @return void 
 * @post 
 * 
 */
    void push_back(const T& value) {
        if (blocksize == 0) {
            // Initial allocation
            blockmap = new T*[1];
            blockmap[0] = new T[1];
            mapsize = 1;
        } else if (size % blocksize == 0) {
            // Allocate a new block if the current one is full
            T** newBlockmap = new T*[mapsize + 1];
            for (int i = 0; i < mapsize; ++i) {
                newBlockmap[i] = blockmap[i];
            }
            newBlockmap[mapsize] = new T[blocksize];
            delete[] blockmap;
            blockmap = newBlockmap;
            ++mapsize;
        }

        // Add the new element to the back
        blockmap[size / blocksize][size % blocksize] = value;
        ++size;
    }

    // Remove element from the back

/**
 * removes element from the back
 *
 * @pre 
 * @return void 
 * @post 
 * 
 */

  void pop_back() {
        if (empty()) {
            std::cerr << "Deque is empty. Cannot pop from the back." << std::endl;
            return;
        }

        // If the last block is now empty, deallocate it
        if (size % blocksize == 1 && mapsize > 1) {
            delete[] blockmap[mapsize - 1];
            --mapsize;
        }

        --size;
    }

    // Return a copy of the front element
    T front() const {
        if (empty()) {
            std::cerr << "Deque is empty. No front element." << std::endl;
            return T(); // Return default value for the type
        }

        return blockmap[0][0];
    }

    // Return a copy of the back element
    T back() const {
        if (empty()) {
            std::cerr << "Deque is empty. No back element." << std::endl;
            return T(); // Return default value for the type
        }

        return blockmap[(size - 1) / blocksize][(size - 1) % blocksize];
    }

    // Check if the deque is empty
    bool empty() const {
        return size == 0;
    }

    // Return the size of the deque
    int getSize() const {
        return size;
    }

    // Operator to access elements by index
    T operator[](int index) const {
        if (index >= size) {
            std::cerr << "Index out of bounds." << std::endl;
            return T(); // Return default value for the type
        }

        return blockmap[(index + firstElement) / blocksize][(index + firstElement) % blocksize];
    }
};

#endif //DEQUE_H
