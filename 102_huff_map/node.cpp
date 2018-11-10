#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!
  //Base case:
  if (sym != NO_SYM) {
    assert(left == NULL);
    assert(right == NULL);
    theMap.insert(std::pair<unsigned, BitString>(sym, b));
    return;
  }
  //recursion
  //to the left
  (*this).left->buildMap(b.plusZero(), theMap);
  //to the right
  (*this).right->buildMap(b.plusOne(), theMap);
}
