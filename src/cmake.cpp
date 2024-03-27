#include <iostream>
#include "add.h"
#include "subtraction.h"
int main() {
  double first_value = 100, second_value = 200;
  add(first_value, second_value);
  subtraction(first_value, second_value);

#ifdef PRINTING
  std::cout << "Debug information..." << std::endl;
#endif
  // Your code here
  std::cout << "Debug information!!!" << std::endl;

  return 0;
}
