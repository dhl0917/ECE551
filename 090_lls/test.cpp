#include <assert.h>
#include <stdio.h>

#include <iostream>

#include "ll.h"
void testList(void) {
  LinkedList<int> l1;
  assert(l1.head == NULL && l1.tail == NULL && l1.size == 0);
  l1.addFront(0);
  l1.addBack(1);
  assert(l1.head->data == 0 && l1.tail->data == 1 && l1.getSize() == 2);
  LinkedList<int> l2(l1);
  assert(l2.head->data == 0 && l2.tail->data == 1 && l2.getSize() == 2);
  assert(l2[0] == 0 && l2[1] == 1);
  l2.remove(0);
  assert(l2.head->data == 1 && l2.tail->data == 1 && l2.getSize() == 1);
  l2.remove(1);
  assert(l2.head == NULL && l2.tail == NULL && l2.getSize() == 0);
  l2.addBack(10);
  assert(l2.head->data == 10 && l2.tail->data == 10 && l2.getSize() == 1);

  l1.addBack(2);
  assert((*l1.head).next->data == 1);
  l2 = l1;
  assert(l2.head->data == 0 && l2.tail->data == 2 && l2.getSize() == 3);
  assert((*l2.head).next->data == 1);
  //  assert(l2.head->data == 0 && (*l2.head).next->data == 1 && l2.tail->data == 2 &&
  //         l2.getSize() == 3);
  LinkedList<int> l3;
  l3 = l1;
  assert(l3.head->data == 0 && l3.tail->data == 2 && l3.getSize() == 3);

  /*
  LinkedList<int> l1;
  l1.addBack(0);
  l1.addBack(1);
  l1.addBack(2);
  assert(l1[0] == 0);
  assert(l1[1] == 1);
  assert(l1[2] == 2);
  assert(l1.head->data == 0 && (*l1.head).next->data == 1 && l1.tail->data == 2 &&
         l1.getSize() == 3);
  LinkedList<int> l2(l1);
  assert(l2[1] == 1);
  assert(l2.head->data == 0 && (*l2.head).next->data == 1 && l2.tail->data == 2 &&
         l2.getSize() == 3);
  l2.addBack(10);
  l2 = l1;
  assert(l2[0] == 0);
  assert(l2[1] == 1);
  assert(l2[2] == 2);
  */
}

int main() {
  testList();
  return EXIT_SUCCESS;
}
