#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>

#include "il.h"
void testList(void) {
  IntList l1;
  assert(l1.head == NULL && l1.tail == NULL && l1.size == 0);
  IntList l2 = IntList(l1);
  assert(l2.head == NULL && l2.tail == NULL && l2.size == 0);
  l1.addFront(0);
  l1.addBack(1);
  l1.addBack(2);
  assert(l1.head != NULL && l1.tail != NULL && l1.size == 3 && (*l1.head).data == 0 &&
         (*l1.tail).data == 2 && (*l1.head).next->data == 1);

  IntList l3 = IntList(l1);
  assert(l3.head != NULL && l3.tail != NULL && l3.size == 3 && (*l3.head).data == 0 &&
         (*l3.tail).data == 2 && (*l3.head).next->data == 1);

  l1.remove(5);
  assert(l1.head != NULL && l1.tail != NULL && l1.size == 3 && (*l1.head).data == 0 &&
         (*l1.tail).data == 2 && (*l1.head).next->data == 1);
  l1.remove(2);
  assert(l1.head != NULL && l1.tail != NULL && l1.size == 2 && (*l1.head).data == 0 &&
         (*l1.tail).data == 1 && (*l1.head).next->data == 1);
  l1.addBack(2);
  l1.remove(0);
  assert(l1.head != NULL && l1.tail != NULL && l1.size == 2 && (*l1.head).data == 1 &&
         (*l1.tail).data == 2 && (*l1.head).next->data == 2);
  l1.addFront(0);
  l1.remove(1);
  assert(l1.head != NULL && l1.tail != NULL && l1.size == 2 && (*l1.head).data == 0 &&
         (*l1.tail).data == 2 && (*l1.head).next->data == 2);
  l1.remove(2);
  l1.addBack(1);
  l1.addBack(2);

  assert(l1.getSize() == 3);
  assert(l1.find(0) == 0);
  assert(l1.find(1) == 1);
  assert(l1.find(2) == 2);
  assert(l1.find(5) == -1);

  IntList * pointToList = new IntList(l1);
  assert(pointToList->getSize() == 3);
  delete pointToList;
  // try {
  assert(l1[0] == 0);
  assert(l1[1] == 1);
  assert(l1[2] == 2);
  // l1[6];
  // }
  /*
  catch (std::out_of_range & e) {
    abort();
  }
  */
  l2 = l1;
  assert(l2.head != NULL && l2.tail != NULL && l2.size == 3 && (*l2.head).data == 0 &&
         (*l2.tail).data == 2 && (*l2.head).next->data == 1);
}

int main(void) {
  testList();
  return EXIT_SUCCESS;
}
