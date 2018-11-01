#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>
#include <stdexcept>

//YOUR CODE GOES HERE
template<typename T>
class LinkedList
{
 private:
  class Node
  {
   public:
    Node * next;
    Node * prev;
    T data;
    Node() : next(NULL), prev(NULL), data(0) {}
    Node(Node * next, Node * prev, T data) : next(next), prev(prev), data(data) {}
  };

 public:
  Node * head;
  Node * tail;
  int size;
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    for (int i = 0; i < rhs.size; i++) {
      (*this).addBack(rhs[i]);
    }
  }
  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head;
      head = temp->next;
      delete (temp);
    }
    tail = NULL;
  }  //destructor
  void addFront(const T & item) {
    if (head == NULL) {
      head = new Node(NULL, NULL, item);
      tail = head;
      size += 1;
    }
    else {
      head = new Node(head, NULL, item);
      head->next->prev = head;
      size += 1;
    }
  }
  void addBack(const T & item) {
    if (head == NULL) {
      head = new Node(NULL, NULL, item);
      tail = head;
      size += 1;
    }
    else {
      tail = new Node(NULL, tail, item);
      tail->prev->next = tail;
      size += 1;
    }
  }
  int find(const T & item) {
    for (int i = 0; i < size; i++) {
      if ((*this)[i] == item) {
        return i;
      }
    }
    return -1;
  }
  bool remove(const T & item) {
    /*
    int index = find(item);
    if (index == -1) {
      return false;
    }
    else {
    */
    Node ** curr = &head;
    while (*curr != NULL && (*curr)->data != item) {
      curr = &((*curr)->next);
    }
    if (*curr == NULL) {
      return false;
    }
    else {
      Node * ans = *curr;
      *curr = ans->next;
      if (*curr != NULL) {
        (*curr)->prev = ans->prev;
      }
      else {
        tail = ans->prev;
      }
      delete ans;
      size -= 1;
      return true;
      // }
    }
  }
  LinkedList & operator=(LinkedList & rhs) {
    /*    if (this != &rhs) {
      LinkedList temp(rhs);
      LinkedList * usedToDelete = new LinkedList();
      usedToDelete->head = head;
      usedToDelete->tail = tail;
      delete usedToDelete;
      (*this).head = temp.head;
      (*this).tail = temp.tail;
      (*this).size = temp.size;
    }
    return (*this);
    */
    if (this != &rhs) {
      LinkedList temp(rhs);
      Node * myhead;
      Node * mytail;
      myhead = head;
      head = temp.head;
      temp.head = myhead;
      mytail = tail;
      tail = temp.tail;
      temp.tail = mytail;
      size = temp.size;
    }
    return (*this);
  }
  T & operator[](int index) {
    //exception out of bounds
    if (index < 0 || index >= size) {
      throw std::out_of_range("out of range");
    }
    Node * curr = head;
    for (int i = 0; i < index; i++) {
      curr = curr->next;
    }
    return curr->data;
  }
  const T & operator[](int index) const {
    //exception out of bounds
    if (index < 0 || index >= size) {
      throw std::out_of_range("out of range");
    }
    Node * curr = head;
    for (int i = 0; i < index; i++) {
      curr = curr->next;
    }
    return curr->data;
  }
  int getSize() const { return size; }
  friend void testList(void);
};

#endif
