#include <cstdio>
#include <cstdlib>

#include "map.h"
template<typename K, typename V>
class BstMap : public Map<K, V>
{
 private:
  class Node
  {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node() : left(NULL), right(NULL) {}
    Node(K key, V value, Node * left, Node * right) :
        key(key),
        value(value),
        left(left),
        right(right) {}
  };

 public:
  Node * root;
  BstMap() : root(NULL) {}
  void copyHelper(Node * current) {
    if (current != NULL) {
      add(current->key, current->value);
      copyHelper(current->left);
      copyHelper(current->right);
    }
  }
  BstMap(BstMap & rhs) : root(NULL) { copyHelper(rhs.root); }
  virtual void add(const K & key, const V & value) {
    Node ** curr = &root;
    while (*curr != NULL) {
      if (key == (*curr)->key) {
        (*curr)->value = value;
        return;
      }
      else if (key < (*curr)->key) {
        curr = &((*curr)->left);
      }
      else {
        curr = &((*curr)->right);
      }
    }
    (*curr) = new Node(key, value, NULL, NULL);
  }
  BstMap & operator=(BstMap & rhs) {
    if (this != &rhs) {
      BstMap temp(rhs);
      std::swap(root, temp.root);
    }
    return *this;
  }
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * const * curr = &root;
    while (*curr != NULL) {
      if ((*curr)->key == key) {
        return (*curr)->value;
      }
      else if (key < (*curr)->key) {
        curr = &((*curr)->left);
      }
      else {
        curr = &((*curr)->right);
      }
    }
    throw std::invalid_argument("Find Error!\n");
  }
  virtual void remove(const K & key) {
    Node ** curr = &root;
    while (*curr != NULL) {
      if (((*curr)->key) == key) {
        if ((*curr)->left != NULL && (*curr)->right != NULL) {
          /*
	  Node * p = (*curr)->left;
          while (p->right->right != NULL) {
            p = p->right;
          }
          (*curr)->key = p->key;
          (*curr)->value = p->value;
          // delete p;
	  */
          Node ** p = &((*curr)->left);
          while (((*p)->right) != NULL) {
            p = &((*p)->right);
          }
          (*curr)->key = (*p)->key;
          (*curr)->value = (*p)->value;
          delete *p;
          *p = NULL;
        }
        else {
          if ((*curr)->left == NULL) {
            Node * temp = *curr;
            (*curr) = (*curr)->right;
            delete temp;
          }
          else if ((*curr)->right == NULL) {
            Node * temp = *curr;
            (*curr) = (*curr)->right;
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
  virtual ~BstMap() { destroy(root); }
  friend void check(void);
};
