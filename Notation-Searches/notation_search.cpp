#include <iostream>
#include <stack>
#include <queue>
using namespace std;

int priority(char op){
    int tmp;
    if (op == '^')
        tmp = 1;
    else  if (op == '*' || op == '/')
        tmp = 2;
    else  if (op == '+' || op == '-')
        tmp = 3;
    return tmp;
}

string postfix(string infix){
    stack <char> ops;
    string postfix = "";
    for(int i = 0; i < infix.length(); i++){
        if(infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^'){
            while(!ops.empty() && priority(ops.top()) <= priority(infix[i])){
                postfix += ops.top();
                ops.pop();
            }
            ops.push(infix[i]);
        } 
        else if(infix[i] == '('){
            ops.push(infix[i]);
        } 
        else if(infix[i] == ')'){
            while(ops.top() != '('){
                postfix += ops.top();
                ops.pop();
            }
            ops.pop();
        } 
        else{
            postfix += infix[i];
        }
    }
    while(!ops.empty()){
        postfix += ops.top();
        ops.pop();
    }
    return postfix;
}

int eval(string postfix){
    int val = 0;
    int val2 = 0;
    int val3 = 0;
    char c;
    stack <int> tmp;
    for(int i = 0; i < postfix.size(); i++){
        if(isdigit(postfix[i])){
            tmp.push(postfix[i]);
        }
        else if(postfix[i] == '*'|| postfix[i] == '/' || postfix[i] == '+' || postfix[i] == '-'){
            switch(c){
                case '*':
                    val2 = tmp.top();
                    tmp.pop();
                    val3 = tmp.top();
                    val = val3 * val2;
                    break;

                case '/':
                    val2 = tmp.top();
                    tmp.pop();
                    val3 = tmp.top();
                    val = val3 / val2;
                    break;

                case '+':
                    val2 = tmp.top();
                    tmp.pop();
                    val3 = tmp.top();
                    val = val3 + val2;
                    break;

                case '-':
                    val2 = tmp.top();
                    tmp.pop();
                    val3 = tmp.top();
                    val = val3 - val2;
                    break;
            }
            tmp.push(val);
        }
    }
    val = tmp.top();
    return val;
}

template<class T> class Node{
    public:
        T key;
        Node *left;
        Node *right;
        T data;
        Node(T d){
            T data = d;
        }
        T *newNode(int data){ 
            Node<T> *tmp = new Node<T>; 
            tmp->data = data; 
            tmp->left = tmp->right = NULL; 
            return tmp; 
        }
};

template<class T> class Tree{
    private:
        Node<T> *root;
    public:
        void depth_first(){
            stack <T> vals;
            Node<T> *tmp = root;
            vals.push(tmp->data);
            while(vals.empty() == false){
                while(tmp->left != 0){
                    tmp = tmp->left;
                    vals.push(tmp->data);
                }
                while(vals.empty() == false){
                    tmp->data = vals.top();
                    vals.pop();
                    cout << tmp->data << " ";
                    if(tmp->right != 0){
                        tmp = tmp->right;
                        vals.push(tmp->data);
                        break;
                    }
                }
            }
        }
        void breadth_first(){
            queue <T> vals;
            vals.push(root->data);
            while(vals.empty() == false){
                Node <T> *tmp = vals.front();
                cout << tmp->data << " ";
                vals.pop();
                if(tmp->left != NULL){
                    vals.push(tmp->left);
                }
                if(tmp->right != NULL){
                    vals.push(tmp->right);
                }
            }
        }
};

template<class T> class myStack{
    private:
        stack <T> vals;
        T min_val;
    public:
        void min(){
            if(vals.empty()){
                cout << "Empty Stack, no min value" << endl;
            }
            else{
                cout << "Min value: " << min_val << endl;
            }
        }
        void pop(){
            if(vals.empty()){
                cout << "Empty Stack, no value to pop" << endl;
            }
            int top = vals.top();
            vals.pop();
            if(top < min_val){
                cout << min_val << endl;
                min_val = 2 * min_val - top;
            }
            else{
                cout << top << endl;
            }
        }
        void push(int val){
            if(vals.empty()){
                min_val = val;
                vals.push(val);
            }
            if(val < min_val){
                vals.push(2 * val - min_val);
                min_val = val;
            }
            else{
                vals.push(val);
            }
        }
};

int main(){ 
    string prob = "5*((9+3)*(4*2)+7)";
    cout << postfix(prob) << endl;
    cout << eval(postfix(prob)) << endl;
    Tree <int> t;
    t.depth_first();
    Tree <int> t2;
    t2.breadth_first();
    myStack <int> vals;
    vals.push(14);
    vals.push(10);
    vals.min();
    vals.push(7);
    vals.push(19);
    vals.min();
    vals.pop();
    return 0;
}
