#include <iostream>
#include <cstdlib>  // For rand() function

#include "deque.h"

template <typename T>
void stressTest(Deque<T>& myDeque, int numOperations) {
    for (int i = 0; i < numOperations; ++i) {
        int operationType = rand() % 4; // 0: push, 1: pop, 2: access front, 3: access random index
        if (operationType == 0) {
            int pushType = rand() % 2;  // 0: push_front, 1: push_back
            int value = rand() % 1000;  // Random value for push

            if (pushType == 0) {
                myDeque.push_front(value);
            } else {
                myDeque.push_back(value);
            }
        } else if (operationType == 1) {
            int popType = rand() % 2;  // 0: pop_front, 1: pop_back

            if (popType == 0) {
                myDeque.pop_front();
            } else {
                myDeque.pop_back();
            }
        } else if (operationType == 2) {
            if (!myDeque.empty()) {
                T frontValue = myDeque.front();
		 std::cout << "Accessed front element: " << frontValue << std::endl;
            }
        } else {
            if (!myDeque.empty()) {
                int randomIndex = rand() % myDeque.getSize();
                T value = myDeque[randomIndex];
		std::cout << "Accessed element at random index " << randomIndex << ": " << value << std::endl;
            }
        }
    }
}

int main() {
    const int numOperations = 1000;  // Number of Operatons
    Deque<int> myDeque;

    stressTest(myDeque, numOperations);

    std::cout << "Size after stress test: " << myDeque.getSize() << std::endl;

    return 0;
}
