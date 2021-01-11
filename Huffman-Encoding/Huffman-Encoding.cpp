#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "BTree.h"
using namespace std;


int main(){
  ifstream textfile ;
  textfile.open("sometext.txt");
  string line;

  int freq[26];
  for(int i = 0; i < 26; i++) freq[i] = 0;

  char ch;
  while(!textfile.eof()){
    getline(textfile, line);
    for(int i = 0; i < line.size(); i++){
      ch = line[i];
      if(ch >= 'a' & ch <= 'z'){
        freq[ch-'a']++;
      }
      if(ch >= 'A' & ch <= 'Z'){
        freq[ch-'A']++;
      }
    }
  }
  textfile.close();

  //for (int i = 0 ; i < 26; i++)
  //cout << char('a' + i) << " : " << freq[i] << endl;

  //initially, 26 trees
  BTree trees[26];
  for(int i = 0; i < 26; i++){
    trees[i].root = new Node('a' + i, freq[i]); 
    trees[i].root->print(0);
  }

  int min1, min2, idx1, idx2;
  // loop of 25 iterations, each iteration reduces the number of trees by 1
  for(int k = 0; k < 25 ; k++){
    min1 = 2147483647;
    idx1 = 0;
    min2 = 2147483647;
    idx2 = 0;

    //finding the first min tree
    for(int i = 0; i < 26; i++){
      if(min1 > freq[i] & freq[i] > 0){
        min1 = freq[i];
        idx1 = i;
      }
    }
    // finding the second min tree
    for(int i = 0; i < 26; i++){
      if(min2 > freq[i] & i != idx1 & freq[i] > 0){
        min2 = freq[i];
        idx2 = i;
      }
    }
    //merging two min trees
    BTree *newTree = new BTree(new Node('-', min1 + min2));
    newTree->root->left = trees[idx1].root;
    newTree->root->right = trees[idx2].root;
    //save the merged tree to the position of the first min
    trees[idx1] = *newTree;
    freq[idx1] = freq[idx1] + freq[idx2];
    //the position of the second min is set to negative to avoid scanning in the next iteration
    freq[idx2] = -1;
 }
 trees[idx1].root->print(0);
 trees[idx1].root->traverse("");
}
