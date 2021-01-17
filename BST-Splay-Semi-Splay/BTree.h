
using namespace std;

class Node {
  public:
  char data;
  Node *left;
  Node *right;
  Node *parent;

  Node(char x) {
    data = x;
    left = right = parent = NULL;
  }

  Node(char x, Node *p) {
    data = x;
    parent = p;
    left = right = NULL;
  }

  void printPreOrder(int indent) {
    cout << data << endl;
    indent ++;

    if (right != NULL) {
      for (int i = 0; i < indent ; i++ ) cout << "\t";
      right->printPreOrder(indent);
    }

    if (left != NULL) {
      for (int i = 0; i < indent ; i++ ) cout << "\t";
      left->printPreOrder(indent);
    }
  }
  
void print(int indent) {

    if (right != NULL) right->print(indent + 1);

    for (int i = 0; i < indent; i++ ) cout << "\t";
    cout << data << endl;
  
    if (left != NULL) left->print(indent + 1);
   
  }

};

class BTree {
  public:
  Node *root;
  
  BTree(){};
  BTree(Node *r){
    root = r;
  }

  void insert(char x) {
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

  void insertZigZig(int* a, int n) {
    insert(a[0]);
    int k = 1;
    Node *prev = root;
    while (k < n-1 ) {
      prev->left = new Node(a[k], prev);
      prev->right = new Node(a[k+1], prev);
      prev = prev->left;
      k = k + 2;
    }
  }

  void insertZigZag(int* a, int n) {
    insert(a[0]);
    int k = 1;
    Node *prev = root;
    while (k < n-1 ) {
      prev->left = new Node(a[k], prev);
      prev->right = new Node(a[k+1], prev);
      if ((k+1) % 4 == 0) prev = prev->right;
      else prev = prev->left;
      k = k + 2;
    }
  }

  void rotateRight(Node *Gr, Node *Par, Node *Ch) {
 
    // right child of Ch (Q) becomes left child of Par
    Par->left = Ch->right;
    if (Ch->right != NULL) Ch->right->parent = Par;

    //Ch acquires Par as its right child
    Ch->right = Par;
    Par->parent = Ch;
      
    Ch->parent = Gr;

    if (Par != root ) {
      //Gr becomes Ch's parent
      if (Gr->left == Par) Gr->left = Ch;
      else Gr->right = Ch;
    }
    else {
       root = Ch;
    }
  }

  void rotateLeft(Node *Gr, Node *Par, Node *Ch) {
  
    Par->right = Ch->left;
    if (Ch->left != NULL) Ch->left->parent = Par;

    Ch->left = Par;
    Par->parent = Ch;

    Ch->parent = Gr;
    
    if (Par != root) {
      if (Gr->left == Par) Gr->left = Ch;
      else Gr->right = Ch;
    } 
    else {
      root = Ch;
    }
  }

  Node* search(Node *node, char x) {
    if (node == NULL) return node;
    if (node->data == x) return node;
    Node *tmp = search(node->left, x);
    if (tmp != NULL) return tmp;
    return search(node->right, x);
  }

  void splay(char x) {

    Node *Ch = search(root, x);
    
    while (Ch->parent != NULL) {
      Node *Par = Ch->parent;
      Node *Gr = Par->parent;
      
      if (Gr == NULL) {
        if (Par->left == Ch) rotateRight(Gr, Par, Ch);
        else rotateLeft(Gr, Par, Ch);
      }
      else {
        // Zig-Zig left case
        if (Gr->left == Par && Par->left == Ch) {
          rotateRight(Gr->parent, Gr, Par);
          rotateRight(Par->parent, Par, Ch);
        } 
        // Zig-Zig right case
        else if (Gr->right == Par && Par->right == Ch) {
          rotateLeft(Gr->parent, Gr, Par);
          rotateLeft(Par->parent, Par, Ch); 
        }
        // Zig-Zag left-right case
        else if (Gr->left == Par && Par->right == Ch) {
          rotateLeft(Gr, Par, Ch);
          rotateRight(Gr->parent, Gr, Ch);
        }
        // Zig-Zag right-left case
        else {
          rotateRight(Gr, Par, Ch);
          rotateLeft(Gr->parent, Gr, Ch);          
        }
      }
    }
    
  }

void semisplay(char x) {

    Node *Ch = search(root, x);
    
    while (Ch->parent != NULL) {
      Node *Par = Ch->parent;
      Node *Gr = Par->parent;
      
      if (Gr == NULL) {
        if (Par->left == Ch) rotateRight(Gr, Par, Ch);
        else rotateLeft(Gr, Par, Ch);
      }
      else {
        // Zig-Zig left case
        if (Gr->left == Par && Par->left == Ch) {
          rotateRight(Gr->parent, Gr, Par);
          Ch = Par;
        } 
        // Zig-Zig right case
        else if (Gr->right == Par && Par->right == Ch) {
          rotateLeft(Gr->parent, Gr, Par);
          Ch = Par;
        }
        // Zig-Zag left-right case
        else if (Gr->left == Par && Par->right == Ch) {
          rotateLeft(Gr, Par, Ch);
          rotateRight(Gr->parent, Gr, Ch);
        }
        // Zig-Zag right-left case
        else {
          rotateRight(Gr, Par, Ch);
          rotateLeft(Gr->parent, Gr, Ch);          
        }
      }
    }
    
  }

  void print() {
    cout << "-----------------" << endl;
    root->print(0);
  }
};




























