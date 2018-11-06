#include <cstdio>
#include <cstdlib>

#include "set.h"
template<typename T>
class BstSet : public Set<T>
{
 private:
  class Node
  {
   public:
    T key;
    //    V value;
    Node * left;
    Node * right;
    Node() : left(NULL), right(NULL) {}
    Node(T key, Node * left, Node * right) : key(key), left(left), right(right) {}
  };

 public:
  Node * root;
  BstSet() : root(NULL) {}
  void copyHelper(Node * current) {
    if (current != NULL) {
      add(current->key, current->value);
      copyHelper(current->left);
      copyHelper(current->right);
    }
  }
  BstSet(BstSet & rhs) : root(NULL) { copyHelper(rhs.root); }
  virtual void add(const T & key) {
    Node ** curr = &root;
    while (*curr != NULL) {
      if (key == (*curr)->key) {
        // (*curr)->value = value;
        return;
      }
      else if (key < (*curr)->key) {
        curr = &((*curr)->left);
      }
      else {
        curr = &((*curr)->right);
      }
    }
    (*curr) = new Node(key, NULL, NULL);
  }
  BstSet & operator=(BstSet & rhs) {
    if (this != &rhs) {
      BstSet temp(rhs);
      std::swap(root, temp.root);
    }
    return *this;
  }
  virtual bool contains(const T & key) const {
    Node * const * curr = &root;
    while (*curr != NULL) {
      if ((*curr)->key == key) {
        return true;
      }
      else if (key < (*curr)->key) {
        curr = &((*curr)->left);
      }
      else {
        curr = &((*curr)->right);
      }
    }
    return false;
  }
  virtual void remove(const T & key) {
    Node ** curr = &root;
    while (*curr != NULL) {
      if (((*curr)->key) == key) {
        if ((*curr)->left != NULL && (*curr)->right != NULL) {
          Node ** p = &((*curr)->left);
          while (((*p)->right) != NULL) {
            p = &((*p)->right);
          }
          (*curr)->key = (*p)->key;
          //(*curr)->value = (*p)->value;
          Node * toFree = *p;
          *p = (*p)->left;
          delete toFree;
        }
        else {
          if ((*curr)->left == NULL) {
            Node * temp = *curr;
            (*curr) = (*curr)->right;
            delete temp;
          }
          else if ((*curr)->right == NULL) {
            Node * temp = *curr;
            (*curr) = (*curr)->left;
            delete temp;
          }
          else {
            delete (*curr);
            *curr = NULL;
          }
        }
      }
      else if (key < (*curr)->key) {
        curr = &((*curr)->left);
      }
      else {
        curr = &((*curr)->right);
      }
    }
  }
  void destroy(Node * current) {
    if (current != NULL) {
      destroy(current->left);
      destroy(current->right);
      delete current;
    }
  }
  virtual ~BstSet() { destroy(root); }
  friend void check(void);
};
