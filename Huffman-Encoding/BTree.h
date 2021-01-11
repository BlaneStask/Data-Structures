using namespace std;

class Node{
    public:
	  int frequency;
	  char letter;
	  Node *left;
	  Node *right;

	  Node(char l, int f){
	    letter = l;
	    frequency = f;
	    left = right = NULL;
	  }

	  void print(int indent){
	    cout << letter << " : " << frequency << endl;
	    if(right != NULL){
	      for (int i = 0; i < indent ; i++ ) cout << "\t";
	      right->print(indent + 1);
	    }
	    if(left != NULL){
	      for (int i = 0; i < indent ; i++ ) cout << "\t";
	      left->print(indent + 1);
	    }
	  }

	  void traverse(string s){
	    // if the node is a leaf node, print out the letter and the code
	    if(left == NULL & right == NULL)
	      cout << letter << " : " << s << endl;

	    // otherwise, as an internal node
	    else if (left != NULL){
	      left->traverse(s + '0');
	      if(right != NULL) 
		right->traverse(s + '1');
	    }  
	  }
};

class BTree{
    public:
	  Node *root;
	  BTree(){};
	  BTree(Node *r){
	    root = r;
	  }
};
