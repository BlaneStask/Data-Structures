#include <iostream> 
#include <fstream>
#include <list>
using namespace std;
 
#define PRIME 7 
int numOfSW = 175;
int val = 0;

class SeparateH{ 
    list<int> *table;
    public: 
        SeparateH(int b){
            table = new list<int>[numOfSW]; 
        }
        void Insert(int key){ 
            int index = hashFunction(key); 
            table[index].push_back(key); 
        } 
        void Delete(int key){ 
            int index = hashFunction(key); 
            list<int> :: iterator i; 
            for(i = table[index].begin(); i != table[index].end(); i++){ 
                if(i != table[index].end() && *i == key){
                    cout << "Word: " << key << " Deleted" << endl;
                    table[index].erase(i); 
                    return;
                } 
            } 
            cout << "Word: " << key << " does not appear in the table" << endl;
        }  
        void Search(int key){ 
            int index = hashFunction(key); 
            list<int> :: iterator i; 
            for(i = table[index].begin(); i != table[index].end(); i++){ 
                if(i != table[index].end() && *i == key){
                    cout << "Word: " << key << " Found" << endl;
                    return; 
                }
            } 
            cout << "Word: " << key << " does not appear in the table" << endl;
        }  
        int hashFunction(int x){ 
            return (x % numOfSW); 
        } 
        void displayHash(){ 
            for (int i = 0; i < numOfSW; i++){ 
                cout << i + 1; 
                for(auto x : table[i]) 
                cout << " --> " << x; 
                cout << endl; 
            } 
        } 
};

class CoalescedH{ 
    list<int> *table; 
    public: 
        CoalescedH(int b){ 
            table = new list<int>[numOfSW]; 
        }
        void Insert(int key){ 
            int index = hashFunction(key); 
            table[index].push_back(key);  
        } 
        void Delete(int key){ 
            int index = hashFunction(key); 
            list<int> :: iterator i; 
            for(i = table[index].begin(); i != table[index].end(); i++){ 
                if(*i == key){
                    cout << "Word: " << key << " Deleted" << endl;
                    table[index].erase(i); 
                    return; 
                }
            } 
            cout << "Word: " << key << " does not appear in the table" << endl;
        } 
        void Search(int key){ 
            int index = hashFunction(key); 
            list<int> :: iterator i; 
            for(i = table[index].begin(); i != table[index].end(); i++){ 
                if(i != table[index].end() && *i == key){
                    cout << "Word: " << key << " Found" << endl;
                    return; 
                }
            } 
            cout << "Word: " << key << " does not appear in the table" << endl;
        } 
        int hashFunction(int x){ 
            return (x % numOfSW); 
        } 
        void displayHash(){ 
            for (int i = 0; i < numOfSW; i++){ 
                cout << i + 1; 
                for(auto x : table[i]) 
                cout << " --> " << x; 
                cout << endl; 
            } 
        } 
};

template<typename K, typename V> 
  
class HashNode{ 
    public: 
        V value; 
        K key; 

        HashNode(K key, V value){ 
            this->value = value; 
            this->key = key; 
        } 
}; 

template<typename K, typename V> 

class LinearProb{ 
    HashNode<K,V> **arr; 
    int size; 
    HashNode<K,V> *dummy; 
    public: 
        LinearProb(){ 
            size = 0; 
            arr = new HashNode<K,V>*[numOfSW]; 
            for(int i = 0 ; i < numOfSW ; i++) 
                arr[i] = NULL; 
            dummy = new HashNode<K,V>(-1, -1); 
        } 
        int hashCode(K key){ 
            return key % numOfSW; 
        } 
        void Insert(K key, V value){ 
            HashNode<K,V> *temp = new HashNode<K,V>(key, value); 
            int hashIndex = hashCode(key); 
            while(arr[hashIndex] != NULL && arr[hashIndex]->key != key && arr[hashIndex]->key != -1){ 
                hashIndex++; 
                hashIndex %= numOfSW; 
            } 
            if(arr[hashIndex] == NULL || arr[hashIndex]->key == -1) 
                size++; 
            arr[hashIndex] = temp; 
        } 
        void Delete(int key){ 
            int hashIndex = hashCode(key); 
            while(arr[hashIndex] != NULL){ 
                if(arr[hashIndex]->key == key){ 
                    HashNode<K,V> *temp = arr[hashIndex]; 
                    arr[hashIndex] = dummy; 
                    size--; 
                    cout << "Word: " << key << " deleted" << endl; 
                    return; 
                } 
                hashIndex++; 
                hashIndex %= numOfSW; 
            } 
            cout << "Word: " << key << " does not appear in the table" << endl;
            return; 
        } 
        void Search(int key){ 
            int hashIndex = hashCode(key); 
            int counter = 0;  
            while(arr[hashIndex] != NULL){
                int counter = 0; 
                if(counter++ > numOfSW)
                    return;         
                if(arr[hashIndex]->key == key) 
                    cout << "Word: " << key << " found" << endl; 
                    return; 
                hashIndex++; 
                hashIndex %= numOfSW; 
            } 
            cout << "Word: " << key << " does not appear in the table" << endl;
            return; 
        } 
        void displayHash(){ 
            for(int i = 0 ; i < numOfSW ; i++){ 
                if(arr[i] != NULL && arr[i]->key != -1) 
                    cout << "Key: " << arr[i]->key << "  Value: "<< arr[i]->value << endl; 
            } 
        } 
}; 

class DoubleHash{  
    int* hashTable; 
    int curr_size; 
    public: 
        bool isFull(){ 
            return (curr_size == numOfSW); 
        } 
        int hash1(int key){ 
            return (key % numOfSW); 
        } 
        int hash2(int key) { 
            return (PRIME - (key % PRIME)); 
        } 
        DoubleHash(){ 
            hashTable = new int[numOfSW]; 
            curr_size = 0; 
            for (int i = 0; i < numOfSW; i++) 
                hashTable[i] = -1; 
        } 
        void Insert(int key){ 
            if (isFull()) 
                return; 
            int index = hash1(key); 

            if (hashTable[index] != -1) { 
                int index2 = hash2(key); 
                int i = 1; 
                while (1) { 
                    int newIndex = (index + i * index2) % numOfSW; 
                    if(hashTable[newIndex] == -1){ 
                        hashTable[newIndex] = key; 
                        break; 
                    } 
                    i++; 
                } 
            } 
            else
                hashTable[index] = key; 
            curr_size++; 
        }
        void Delete(int key){ 
            int index1 = hash1(key); 
            int index2 = hash2(key); 
            int i = 0; 
            while(hashTable[(index1 + i * index2) % numOfSW] != key){ 
                if(hashTable[(index1 + i * index2) % numOfSW] == -1){ 
                    cout << "Word: " << key << " does not appear in the table" << endl; 
                    return; 
                } 
                i++; 
            } 
            hashTable -= hashTable[(index1 + i * index2) % numOfSW];
            cout << "Word: " << key << " deleted" << endl; 
        } 
        void Search(int key){ 
            int index1 = hash1(key); 
            int index2 = hash2(key); 
            int i = 0; 
            while(hashTable[(index1 + i * index2) % numOfSW] != key){ 
                if(hashTable[(index1 + i * index2) % numOfSW] == -1){ 
                    cout << "Word: " << key << " does not appear in the table" << endl; 
                    return; 
                } 
                i++; 
            } 
            cout << "Word: " << key << " found" << endl; 
        } 
        void displayHash(){ 
            for(int i = 0; i < numOfSW; i++){ 
                if (hashTable[i] != -1) 
                    cout << i + 1 << " --> " << hashTable[i] << endl; 
                else
                    cout << i + 1 << endl; 
            } 
        } 
};

int returnHash(string s){
    int sum = 0, index = 0;
    for(string::size_type i = 0; i < s.length(); i++){
        sum += s[i] + i;
    }
    val += 1;
    index = sum % numOfSW;
    return index * 33 + val;
}
 
int main(){ 
    ifstream stopwordsfile;
    stopwordsfile.open("stopwords.txt");  
    string arr[numOfSW]; 
    string line; 
    string stopwords[numOfSW];  
    int i = 0;
    while (!stopwordsfile.eof()){
        getline(stopwordsfile, line);    
        stopwords[i] = line;
        arr[i] = stopwords[i];    
        i++;
    }
    stopwordsfile.close();  
    int hword;
/*
    // a) Separate Chaining
    SeparateH h(numOfSW);
    for(int i = 0; i < numOfSW; i++){
        hword = returnHash(arr[i]);
        h.Insert(hword);   
    }
    h.displayHash();
    string word;
    cout << "Give word to be deleted: ";
    cin >> word;
    hword = returnHash(word);
    h.Delete(hword); 
    cout << endl;
    cout << "Give word to be searched for: "; 
    cin >> word;
    hword = returnHash(word);
    h.Search(hword - 1); 
    cout << endl;
    cout << "Hash table: " << endl; 
    h.displayHash(); 
*/
/*
    // b) Coalesced Chaining
    CoalescedH h(numOfSW);
    for(int i = 0; i < numOfSW; i++){
        hword = returnHash(arr[i]);
        h.Insert(hword);   
    }
    h.displayHash();
    string word;
    cout << "Give word to be deleted: ";
    cin >> word;
    hword = returnHash(word);
    h.Delete(hword); 
    cout << endl;
    cout << "Give word to be searched for: "; 
    cin >> word;
    hword = returnHash(word);
    h.Search(hword); 
    cout << endl;
    cout << "Hash table: " << endl; 
    h.displayHash();
*/
/*
    // c) Open Addressing and Linear Probing
    LinearProb<int, int> *h = new LinearProb<int, int>;
    for(int i = 0; i < numOfSW; i++){
        hword = returnHash(arr[i]);
        h->Insert(i + 1, hword);   
    }
    h->displayHash();
    string word;
    cout << "Give word to be deleted: ";
    cin >> word;
    hword = returnHash(word);
    h->Delete(hword); 
    cout << endl;
    cout << "Give word to be searched for: "; 
    cin >> word;
    hword = returnHash(word);
    h->Search(hword - 1); 
    cout << endl;
    cout << "Hash table: " << endl; 
    h->displayHash();
*/
/*
    // d) Open Addressing and Double Hashing 
    DoubleHash h;
    for(int i = 0; i < numOfSW; i++){
        hword = returnHash(arr[i]);
        h.Insert(hword);   
    }
    h.displayHash();
    string word;
    cout << "Give word to be deleted: ";
    cin >> word;
    hword = returnHash(word);
    h.Delete(hword); 
    cout << endl;
    cout << "Give word to be searched for: "; 
    cin >> word;
    hword = returnHash(word);
    h.Search(hword); 
    cout << endl;
    cout << "Hash table: " << endl; 
    h.displayHash();
*/
    return 0;
} 
