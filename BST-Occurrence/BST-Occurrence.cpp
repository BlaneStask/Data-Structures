#include<iostream>      
#include<fstream>
using namespace std;

struct LinkedList{
   int line_no;
   struct LinkedList *next;
   LinkedList(int data){
       this->line_no = data;
       this->next = NULL;
   }
};

struct BST{
   string word;
   struct LinkedList *head,*tail;
   struct BST *left;
   struct BST *right;

   BST(string word, int data){
       this->word=word;
       this->head=new LinkedList(data);
       this->tail=this->head;
       this->left=this->right=NULL;
   }
};

class implement{
   public:
       struct BST *root;
       implement(){
           root = NULL;
       }
       void insertInto(BST *bst, string word, int data);
       void insert(string word, int line_no);
      
};

void implement::insertInto(BST *bst, string word, int data){
   if(bst == NULL){
       return;
   }
   if(bst->word == word){
       struct LinkedList *node = new LinkedList(data);
       (bst->tail)->next = node;
       bst->tail = node;
       return;
   }
   if(bst->word > word){
       if(bst->left != NULL){
           insertInto(bst->left, word, data);
       }
       else{
           bst->left = new BST(word, data);
       }
       return;
   }
   else{
       if(bst->right != NULL)
           insertInto(bst->right, word, data);
       else{
           bst->right = new BST(word, data);
       }
   }
}

void implement::insert(string word, int line_no){
   if(root == NULL){
       root = new BST(word, line_no);
       return;
   }
   insertInto(root, word, line_no);
}

void inorder(BST *node){
   if(node == NULL) return;
   inorder(node->left);
   cout << (node->word) << " => ";
   LinkedList *temp = node->head;
   while(temp != NULL){
       cout << temp->line_no << " ";
       temp = temp->next;
   }
   cout << endl;
   inorder(node->right);
}
string trim(string word){
   transform(word.begin(), word.end(), word.begin(), ::tolower);
   int n = word.length();
   int i = 0, j = n - 1;
   for(; i < n; ++i){
       if(word[i] >= 97 && word[i] <= 122) break;
   }
   for(; j >- 1; --j){
       if(word[j] >= 97 && word[j] <= 122) break;
   }
   return word.substr(i, j-i+1);
}
int main(){
   string s;
   cout<<"filename: ";
   cin>>s;
   ifstream in(s.c_str());
   implement bst;
   string line;
   int line_no = 1;
   string delim = " ";
   while(!in.eof()){
       getline(in, line);
       int start = 0;
       int end = line.find(delim);
       string word;
       while(end != std::string::npos){
           word = line.substr(start, end-start);
           word = trim(word);
           bst.insert(word, line_no);
           start = end + 1;
           end = line.find(delim, start);
       }
        word = line.substr(start,end-start);
        word = trim(word);
        bst.insert(word, line_no);
        ++line_no;
   }
   inorder(bst.root);
   return 0;
}