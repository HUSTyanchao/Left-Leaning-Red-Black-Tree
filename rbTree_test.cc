#include "rbtree.h"

#include <string>
#include <iostream>

int main() {

  BST<int, std::string> bst;
  for (int i = 0; i < 11; ++i) {
    bst.put(i, std::to_string(i));
  }

  std::string str{"not find"};
  bst.get(10, str);
  std::cout << str << std::endl;

  int key = -1;
  bst.max(key);
  std::cout << "max: " << key << "\n";
  key = -1;
  bst.min(key);
  std::cout << "min: " << key << "\n";

  return 0;
}
