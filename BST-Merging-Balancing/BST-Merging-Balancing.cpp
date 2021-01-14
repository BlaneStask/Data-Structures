#include <iostream>
#include "BTree.h"

using namespace std;
int main() {
  int n = 9;
  int a[] = {5, 10, 20, 15, 30, 25, 40, 23, 28} ;

  BTree *tree = new BTree();

  for (int i = 0; i < 9 ; i ++) {
    tree->insert(a[i]);
  }

  tree->root->print(0);
  tree->createBackbone();
  tree->root->print(0);

}