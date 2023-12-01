#include "deque.h"
using namespace std;


Deque::Deque()
{
  size = 0;
  mapSize = 0;
  first_block = 0;
  first_element = 0;

  // row = first_block + ((first_element + i) / block_size)
  // column = (first__element + i) % block_size;
}
