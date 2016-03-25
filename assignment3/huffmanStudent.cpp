#include "huffman.h"
#include <iostream>
#include <sstream>
#include <vector>


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
    cout << "heapcreation" << endl;

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
	int priority1 = content.front()->priority;
	TreeNode* node1 = *(content.front()->data);
	Heap::pop();
	
	int priority2 = content.front()->priority;
	TreeNode* node2 = *(content.front()->data);
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


HuffmanCode::HuffmanCode(istream &input) {
    //TODO
}



//QUESTION 4

HuffmanTree::HuffmanTree(const HuffmanCode &hc) {
    //TODO
}

// QUESTION 5

void HuffmanEncoder::encode(istream &fin, ostream &fout) const {
    //TODO
}


//QUESTION 5

void HuffmanDecoder::push(istream &f) {
    //TODO
}

