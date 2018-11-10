#include <stdio.h>
#include <string.h>

#include "node.h"
Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t pq;
  int n = 257;
  for (int i = 0; i < n; i++) {
    if (counts[i] == 0) {
      continue;
    }
    pq.push(new Node(i, counts[i]));
  }
  while (pq.size() > 1) {
    Node * a = pq.top();
    pq.pop();
    Node * b = pq.top();
    pq.pop();
    pq.push(new Node(a, b));
  }
  Node * ans = pq.top();
  pq.pop();
  return ans;
}
