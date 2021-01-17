#include <iostream>
#include "BTree.h"
using namespace std;

int main(){
  int n = 11;
  int a[] = {'P', 'Q', 'F', 'R', 'E', 'S', 'D', 'T', 'C', 'A', 'B'};
  BTree *tree = new BTree();
  tree->insertZigZig(a, n);
  tree->print();
  tree->semisplay('T');
  tree->print();
  tree->semisplay('T');
  tree->print();
  n = 15;
  int b[] = {'g','f','H','e','G','d','F','c','E','b','D','a','C','A','B'};
  tree = new BTree();
  tree->insertZigZig(b, n);
  tree->print();
  tree->splay('a');
  tree->print();
  int c[] = {'g','f','H','A','e','d','G','B','c','b','F','C','a','D','E'};
  tree = new BTree();
  tree->insertZigZag(c, n);
  tree->print();
  tree->splay('a');
  tree->print();
}
