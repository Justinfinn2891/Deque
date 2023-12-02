#include <iostream>
#include <cstdlib> // for rand()
#include <ctime>   // for srand()

#include "deque.h"

using namespace std;

void automatedTests() {
  // Seed the random number generator
  srand(static_cast<unsigned>(time(nullptr)));
  
  // Create a deque of integers
  Deque<int> myDeque;
  
  // Perform a large number of pushes to both sides
  const int numOperations = 10;
  
  for (int i = 0; i < numOperations; i++) {
    int value = rand() % 100; // Random value between 0 and 99
    if (i % 2 == 0) {
      myDeque.push_front(value);
    } else {
      myDeque.push_back(value);
    }
  }
  
  // Display the deque size after pushes
  cout << "Deque size after pushes: " << myDeque.size() << endl;
    
    // Perform a large number of pops from both sides
    for (int i = 0; i < numOperations / 2; i++) {
      if (!myDeque.empty()) {
	if (i % 2 == 0) {
	  myDeque.pop_front();
	} else {
	  myDeque.pop_back();
	}
      }
    }
    
    // Display the deque size after pops
    cout << "Deque size after pops: " << myDeque.size() << endl;
    
    // Perform a large number of [] access operations
    for (int i = 0; i < numOperations; i++) {
      if (!myDeque.empty()) {
	// Generate a random index within the current size of the deque
	int index = rand() %myDeque.size();
	// Accessing elements using operator[]
	int element = myDeque[index];
	// Do something with the element to ensure it's working
	cout << "Accessed element at index " << index << ": " << element << endl;
      }
    }
}

int main() {
    automatedTests();
    return 0;
}

//the randomized function was pieced together using this website: https://www.cs.fsu.edu/~myers/c++/notes/rand.html
