using namespace std;

class Node{
  public:
    string first;
    string second;
    Node *next;

    Node (string fst, string snd){
      first = fst;
      second = snd;
      next = NULL;
    }
};

class MyLinkedList{
  public:
    Node *head;
    Node *tail;

    MyLinkedList(){
      head = NULL;
      tail = NULL;
    }
    void insert(Node *newNode){
      if(tail == NULL){
        head = newNode;
      }
      else{
        tail->next = newNode;
      }
      tail = newNode;
    }
    void printList(){
      Node *temp = head;
      while(temp != tail){
        cout << temp->first << " " << temp->second << endl;
        temp = temp->next;
      }
    }
};
