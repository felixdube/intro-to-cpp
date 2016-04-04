#include "huffman.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string.h>
#include "heap.h"


//QUESTION 1 - 0 credit

// check if a word exist in a vector of word
bool existInVector(string word, vector<string> vector) {
	for(int i = 0; i < vector.size(); i++){
		if(word == vector.at(i)){
			return true;
		}
	}
	return false;
}

//count the number of appearance of a word in a vector of words
int countInVector(string word, vector<string> vector) {
	int count = 0;

	for(int i = 0; i < vector.size(); i++) {
		if(word == vector.at(i)){
			count++;
		}
	}
	return count;
}

HuffmanTree::HuffmanHeap::HuffmanHeap(istream &instr) {

    // containt all the word of the stream
    vector<string> allWords;
    //contain all the word of the stream witouth repeat
    vector<string> allWordsSingle;

    char *nextWord = new char[256];

    // insert the words in the vectors
    while(!instr.eof()){
	    instr.getline(nextWord, 256, ' ');
	    allWords.push_back(nextWord);
	    if(!existInVector(nextWord, allWordsSingle)) {
	    	allWordsSingle.push_back(nextWord);
	    }
	}

	// insert all the word in the heap
    for(int i = 0; i < allWordsSingle.size(); i++) {
    	int priority = countInVector(allWordsSingle.at(i), allWords);
    	TreeNode* newTreeNode = new TreeNode(allWordsSingle.at(i));
    	push(newTreeNode, priority);
    }

}


void HuffmanTree::HuffmanHeap::pop() {

	// extract the two node with highest priority
	TreeNode* node1 = top();
	int priority1 = (*this)[node1];
	Heap::pop();
	
	TreeNode* node2 = top();
	int priority2 = (*this)[node2];
	Heap::pop();

	// push a new node on the heap with the two extracted nodes as children
	// and with a priority equal to the sum of their priority
	int priority = priority1 + priority2;
	TreeNode* newTreeNode = new TreeNode(node1, node2);

	push(newTreeNode, priority);
}



// QUESTION 2
void HuffmanTree::dfs(HuffmanCode& hc, TreeNode *tn, string &s) {
    
	// if this is a leaf add it to the map
    if(tn->word != nullptr){
    	hc.insert( pair<string, string>(*(tn->word), s));
    }

    //if the 0 child is not null, call dfs on it
    if(tn->children[0] != nullptr) {
    	s = s + "0";
    	dfs(hc, tn->children[0], s);
    	s = s.substr(0, s.length() - 1);
    }

 	//if the 0 child is not null, call dfs on it
    if(tn->children[1] != nullptr) {
    	s = s + "1";
    	dfs(hc, tn->children[1], s);
    	s = s.substr(0, s.length() - 1);
    }


}

//QUESTION 3

// check if a string contains only zeros and ones
bool isZeroOne(string s) {
	
	// if the string is empty return false
	if(s.size() == 0){
		return false;
	}

	for(int i = 0; i < s.size(); i++){
		if(s.at(i) != '0' && s.at(i) != '1'){
			return false;
		}
	}
	return true;
}


// check how many words there is in a string
int howManyWord(string s){
	
	// if the string is empty
	if(s.size() == 0){
		return 0;
	}

	// count the number of spaces
	int wordCount = 1;
	for(int i = 0; i < s.size(); i++){
		if(s.at(i) == ' '){
			wordCount++;
		}
	}

	return wordCount;
}

HuffmanCode::HuffmanCode(istream &input) {

    while(!input.eof()) {

    	// get the next line from the stream
    	char *nextLine = new char[256];
    	input.getline(nextLine, 256);

    	if(howManyWord(nextLine) == 0) {
    		break;
    	}


    	// check if there is two words on this line
    	if(howManyWord(nextLine) != 2) {
    		throw 0;
    	}

    	int j = 0;
    	string word1 = "";
    	string word2 = "";

    	// get the first word from the line
    	while(nextLine[j] != ' ') {
    		word1 += nextLine[j];
    		j++;
    	}

    	j++;

    	//get the second word from the line
    	while(j < strlen(nextLine)) {
    		word2 += nextLine[j];
    		j++;
    	}

    	if(!isZeroOne(word2)){
    		throw 0;
    	}

    	this->insert( pair<string, string>(word1, word2));


    }
}



//QUESTION 5
bool isPrefixOfAnother(string code, string allCode[]){
    bool toRet = false;
    for(int i = 0; i < sizeof(allCode) / sizeof(string); i++){
        if(allCode[i].length() > code.length()){
            if(code.compare(allCode[i].substr(0, code.length() - 1)) == 0){
                toRet = true;
            }
        }
    }
    return toRet;
}

HuffmanTree::HuffmanTree(const HuffmanCode &hc) {
    
    // get all the code
    string allCode[hc.size()];
    string allWord[hc.size()];
    int k = 0;
    for (map<string, string>::const_iterator it = hc.begin(); it != hc.end(); it++){

        // check if the code is made of 0 and 1
        if(!isZeroOne(it->second)){
            throw 2;
        } else {
            allCode[k] = it->second;
            allWord[k] = it->first;
            k++;
        }
    }

    // check if any of the code is the prefix of another
    for(int i = 0; i < sizeof(allCode) / sizeof(string); i++){
        if(isPrefixOfAnother(allCode[i], allCode)){
            throw 1;
        }
    }

    // create root
    root = new TreeNode();
    iter = root;


    for (int j = 0; j < sizeof(allCode) / sizeof(string); j++) {
        // create path to the leaf
        int i;
        for(i = 0; i < allCode[j].length() - 1; i++){
            if(allCode[j].at(i) == '0'){
                if(iter->children[0] == nullptr){
                    iter->children[0] = new TreeNode();
                    iter = iter->children[0];
                } else {
                    iter = iter->children[0];
                }

            } else {
                 if(iter->children[1] == nullptr){
                    iter->children[1] = new TreeNode();
                    iter = iter->children[1];
                } else {
                    iter = iter->children[1];
                }
            }
        }

        if(allCode[j].at(i) == '0'){
            if(iter->children[0] == nullptr){
                iter->children[0] = new TreeNode(allWord[j]);
                iter = iter->children[0];
            } else {
                iter = iter->children[0];
            }

        } else {
             if(iter->children[1] == nullptr){
                iter->children[1] = new TreeNode(allWord[j]);
                iter = iter->children[1];
            } else {
                iter = iter->children[1];
            }
        }

        resetIterator();
    }
}

// QUESTION 4

void HuffmanEncoder::encode(istream &fin, ostream &fout) const {
    while(!fin.eof()) {
        
        // get the next word
        char *nextWord = new char[256];
        fin.getline(nextWord, 256, ' ');


        // get the code of the word and insertit in the stream
        try {
            fout << code.at(nextWord);
        } catch(const out_of_range& e) {
            throw 1;
        }

    }
}


//QUESTION 6

void HuffmanDecoder::push(istream &f) {
    
    char *line = new char[1024];
    f.getline(line, 1024);

    const string* word;

    for(int i = 0; i < strlen(line); i++) {
        
        // check if the input is valid
        if(line[i] != '0' && line[i] != '1') {
            throw 0;
        }

        try {
            word = getWordFromIter();
            savedWords.push(word);
            resetIterator();
            i--;
        } catch(const double e) {

            // go down to the apropriate children
            if(line[i] == '0'){
                moveDownOnZero();
            }
            else if(line[i] == '1'){
                moveDownOnOne();
            }
        }
    }

    try {
        word = getWordFromIter();
        savedWords.push(word);
    } catch(const double e) {
       throw 1;
   }

}

