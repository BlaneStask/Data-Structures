#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "MyList.h"
using namespace std;

bool isStopWord(string w, string *words, int n) {
  for (int i = 0; i < n ; i++) {
    if (words[i].compare(w) == 0) 
      return true;
  }
  return false;
}

int main() {
	ifstream stopwordsfile;
	stopwordsfile.open("stopwords.txt");
  int numOfSW = 176;

	string line;  // each line of the text file
  string stopwords[numOfSW];
  int i = 0;
	while (!stopwordsfile.eof())
	{
		getline(stopwordsfile, line);
    stopwords[i] = line;
    //cout << stopwords[i] << endl;
    i++;
	}
	stopwordsfile.close();

  ifstream textfile;
  textfile.open("sometext.txt");
  string word;

  MyLinkedList *list = new MyLinkedList();
  int count = 0;
  string first, second;

  while (!textfile.eof()) {
    getline(textfile, line);
    // removing punctuation
    line.erase(remove_if(line.begin(), line.end(), ::ispunct), line.end());

    // to lower case
    transform(line.begin(), line.end(), line.begin(), ::tolower); 

    //read word by word from a line
    istringstream iss(line);
    count = 0;
    while (iss >> word) {
      if (!isStopWord(word, stopwords, numOfSW)) {
        //cout << word << endl;
        if (count == 0) {
          first = word;
        }
        else {
          second = word;
          list->insert(new Node(first, second));
          first = word;
        }
        count ++;
      }


 	  }
    list->printList();
   // cout << line << endl;
  }


  


	return 0;
}

