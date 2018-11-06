#include <assert.h>

#include <cstdio>
#include <cstdlib>

#include "bstmap.h"
void check(void) {
  BstMap<int, int> b1;

  b1.add(1, 2);
  b1.add(2, 10);
  b1.add(3, 8);
  BstMap<int, int> b;
  b.add(18, 108);
  // BstMap<int, int> b(b1);
  b = b1;
  assert(b.root->right->right->key == 3 && b.root->right->right->value == 8);

  /*
  assert(b.root != NULL && b.root->key == 1 && b.root->value == 2 && b.root->left == NULL &&
         b.root->right == NULL);
  b.add(0, 0);
  assert(b.root != NULL && b.root->left->key == 0 && b.root->left->value == 0 &&
         b.root->left->left == NULL && b.root->left->right == NULL);
  b.add(2, 4);
  assert(b.root != NULL && b.root->right->key == 2 && b.root->right->value == 4 &&
         b.root->right->left == NULL && b.root->right->right == NULL);
  assert(b.lookup(0) == 0);
  assert(b.lookup(1) == 2);
  assert(b.lookup(2) == 4);
  b.add(2, 10);
  assert(b.lookup(2) == 10);
  //  b.lookup(3);
  b.add(3, 8);
  b.remove(1);
  assert(b.root->left == NULL && b.root->value == 0 && b.root->key == 0);
  */
}

int main() {
  check();
  return EXIT_SUCCESS;
}
