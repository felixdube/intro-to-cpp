//QUESTION 1

#include "priorities.h"
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <math.h>

//QUESTION 1

Heap::Heap(const vector<string> & dataToAdd) {
    for(int i = 0; i < dataToAdd.size(); i++){
    	Node *nodeToAdd = new Node;
    	nodeToAdd->data = dataToAdd.at(i);
    	nodeToAdd->priority = i;
    	content.push_back(*nodeToAdd);
    }
}

Heap::Heap(const Heap& h) {
    content = h.content;
}


//Question 2

size_t Heap::lengthOfContent(unsigned long index) const {
    int len = content.at(index).data.length();

    // if both child exits
    if(index*2+2 < content.size()){
    	len = len + lengthOfContent(index*2+1) + lengthOfContent(index*2+2);
    }

    // if there is only one child
    else if (index*2+1 < content.size()){
    	len = len + lengthOfContent(index*2+1);
    }

    return len;
}


ostream &operator<<(ostream & out, const Heap& h) {
	
	// number of nodes in the heap
	int numNode = h.content.size();
	
	// string where the nodes are added
	string toPrint = "";

	// number of node that needs to be printed on the current row
	int numNodeThisRow = 1;
	
	// number of node that have been placed on the current row
	int numNodeDoneThisRow = 0;

	// place all the node in string
	for (int i = 0; i < numNode; i++) {

		// add white space for the left subtree
		if (2*i+1 < numNode) {
			int whiteSpaces = h.lengthOfContent(2*i+1);
			for (int j = 0; j < whiteSpaces; j++) {
				toPrint += " ";
			}
		}

		// print the current node
		toPrint += h.content.at(i).data;

		// add white space for the right subtree
		if (2*i+2 < numNode) {
			int whiteSpaces = h.lengthOfContent(2*i+2);
			for (int j = 0; j < whiteSpaces; j++) {
				toPrint += " ";
			}
		}

		numNodeDoneThisRow++;

		// check if row is done
		// if not we need to find the node above for which we need to leave space
		if (numNodeDoneThisRow == numNodeThisRow) {
			numNodeThisRow *= 2;
			numNodeDoneThisRow = 0;
			toPrint += "\n";
		}
		else {
			// find the parent of a left child

			// go up until you find a left child
			int kid = i;
			while (kid % 2 == 0) {
				kid = (kid - 1) / 2;
			}

			// find its parent
			int parent = (kid - 1) / 2;

			// add the white spaces for the parent
			int whiteSpaces = h.content.at(parent).data.length();
			for (int j = 0; j < whiteSpaces; j++) {
				toPrint += " ";
			}
		}

	}

    out << toPrint;   

    return out;
}



//QUESTION 3

vector<string> Heap::printLinear() const{
    vector<string> strings;

    // place all the node in the string vector one by one
    for(int i = 0 ; i < content.size(); i++){
    	strings.push_back("(" + content.at(i).data+", "+ to_string(content.at(i).priority) + ")");
    }
    return strings;
}


//QUESTION 4

unsigned int Heap::operator[](string s) const{
    
	// check if the node exist
    if(has(s)) {
    	bool found = false;
    	int index = 0;

    	// find where the node is in the heap
    	while(!found) {
    		if(content.at(index).data == s) {
    			found = true;
    			break;
    		}
    		index++;
    	}

    	// return the priority of the node with data s
    	return content.at(index).priority;
    }
    else{
    	return 0;
    }
}

//QUESTION 5

void Heap::heapifyUp(unsigned long index) {
	
	// check if then index is the root
	if(index == 0) {
		return;
	}
	
	// check if the parent has higher priority
	else if (content.at(index).priority < content.at((index-1)/2).priority) {

	    	// if the node have higher priority than its parent, swap
	    	swap(content.at(index), content.at((index-1)/2));
	    	
	    	// update index
	    	heapifyUp((index-1)/2);
	}
	else {
		return;
	}
}


void Heap::push(string data, unsigned int priority) {
    
    if(!has(data)){
		// create the new node to be pushed
	    Node *toAdd = new Node;
	    
	    // add the data and the priority to the node
	    toAdd->data = data;
	    toAdd->priority = priority;
	    
	    // place the node in the heap
	    content.push_back(*toAdd);

	    // swap the node to the rigth position
	    heapifyUp(content.size() - 1);
	}
}


Heap& Heap::operator+=(const Heap& h) {

	// push all the nodes of h in the heap
    for(int i = 0; i < h.content.size(); i++) {
    	push(h.content.at(i).data, h.content.at(i).priority);
    }
    return *this;
}


// QUESTION 6

void Heap::heapifyDown(unsigned long index) {
   	// no child
	if(2*index+1 >= content.size()){
		return;
	} 

	// one child
	else if (2*index+2 == content.size()){

		// if child is higher priority
		if(content.at(index).priority > content.at(2*index+1).priority){
			swap(content.at(index), content.at(2*index+1));
			heapifyDown(2*index+1);
		}
	}

	// if two child
	// if index has higher priority
   	else if(content.at(index).priority < content.at(2*index+1).priority &&
   		content.at(index).priority < content.at(2*index+2).priority){
   		return;
   	}

   	// if left child has higher priority
	else if(content.at(2*index+1).priority < content.at(index).priority &&
   		content.at(2*index+1).priority < content.at(2*index+2).priority){
   		swap(content.at(index), content.at(2*index+1));
		heapifyDown(2*index+1);
   	}

   	// if right child has higher priority
   	else if(content.at(2*index+2).priority < content.at(index).priority &&
   		content.at(2*index+2).priority < content.at(2*index+1).priority){
   		swap(content.at(index), content.at(2*index+2));
		heapifyDown(2*index+2);
   	}

}


string Heap::pop() {

	string data = content.at(0).data;

	// place a the end the node we want to remove
	swap(content.at(0), content.at(content.size() - 1));

	// remove the last node
	content.pop_back();

	// heapifydown the node we placed at the top
	heapifyDown(0);

	return data;
}


// QUESTION 7

Heap::Heap(istream &in) {

	// map that count the number of times a words appears
	map<string, int> countMap;

	// countain all the words of the stream
	vector<string> words;

	// next word in the stream
	string nextWord;

	// max count value
	int max = 0;

	// for all the word in the stream
	while (!in.eof()){
		in >> nextWord;

		// if the word is not in the map add it to the map and the vector
		if(countMap.find(nextWord) == countMap.end()){
			countMap[nextWord] = 1;
			words.push_back(nextWord);
		}

		// if the word is already in the map, increament its count
		else{
			countMap[nextWord] += 1;
			if(countMap[nextWord] > max){
				max = countMap[nextWord];
			}
		}
	}

	// add to the heap all the word in the vector
	// priority = max - count
	for (int i = 0; i < countMap.size(); i++){
    	push(words.at(i), max - countMap[words.at(i)]);
	}
}