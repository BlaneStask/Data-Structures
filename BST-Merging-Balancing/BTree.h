
using namespace std;

class Node {
  public:
  int data;
  Node *left;
  Node *right;
  Node *parent;

  Node(int x) {
    data = x;
    left = right = parent = NULL;
  }

  Node(int x, Node *p) {
    data = x;
    parent = p;
    left = right = NULL;
  }

  void print(int indent) {
    cout << data << endl;
    indent ++;

    if (right != NULL) {
      for (int i = 0; i < indent ; i++ ) cout << "\t";
      right->print(indent);
    }

    if (left != NULL) {
      for (int i = 0; i < indent ; i++ ) cout << "\t";
      left->print(indent);
    }
  }

};

class BTree {
  public:
  Node *root;
  
  BTree(){};
  BTree(Node *r){
    root = r;
  }

  void insert(int x) {
    Node *prev = NULL;
    Node *curr = root;

    //traverse down the tree to find the correct position
    while (curr != NULL) {
      prev = curr;
      if (x <= curr->data) 
        curr = curr->left;
      else 
        curr = curr->right;
    }

    //insert the Node
    // case 1: the tree is empty, this is the first Node
    if (root == NULL) {
      root = new Node (x);
    }
    // case 2: tree is not empty
    else if (x <= prev->data) 
      prev->left = new Node(x, prev) ;
    else // x > prev->data
      prev->right = new Node(x, prev);
  }

  void rotateRight(Node *Gr, Node *Par, Node *Ch) {
    if (Par != root ) {
      //Gr becomes Ch's parent
      Gr->right = Ch;
      Ch->parent = Gr;

      if (Ch->right != NULL) {
      // right child of Ch (Q) becomes left child of Par
        Par->left = Ch->right;
        Ch->right->parent = Par; //only works when Q is not null
      }
      else {
        Par->left = NULL;
      }

      //Ch acquires Par as its right child
      Ch->right = Par;
      Par->parent = Ch;
    }
    else {
      if (Ch->right != NULL) {
      // right child of Ch (Q) becomes left child of Pa
        Par->left = Ch->right;
        Ch->right->parent = Par; //only works when Q is not null
      }
      else {
        Par->left = NULL;
      }

      //Ch acquires Par as its right child
      Ch->right = Par;
      Par->parent = Ch;

      root = Ch;
    }
  }

  void createBackbone() {
    Node *tmp = root;
    while (tmp != NULL) {
      if (tmp->left != NULL) {
        rotateRight(tmp->parent, tmp, tmp->left);
        //print the tree after each rotation
        root->print(0);
        tmp = tmp->parent;
      }
      else {
        tmp = tmp->right;
      }
    }
  }

};




























