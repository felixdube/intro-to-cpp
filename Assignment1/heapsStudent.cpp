#include "heaps.h"
#include <iostream>
#include <vector>
#include <math.h>


// place all the nodes of a heap in a vector using inorder traversal
void inorder(Heap *root, std::vector<Heap>& listToAdd)
{
    if(root != NULL)
    {
       inorder(root->left, listToAdd);
       listToAdd.push_back(*root);
       inorder(root->right, listToAdd);
    }
}

// create heap
Heap *heapFromArray(string *input, int length) {

	Heap *nodes = new Heap[length];

    for(int i = 0; i < length; i++){
    	
    	nodes[i].name = input[i];

    	if(2*i+2 == length){
	     	// this node have 1 child
	     	nodes[i].left = &nodes[2*i+1];
	     	nodes[i].right = nullptr;
    	}
    	else if(2*i+2 > length){
    		// this node does not have children
	    	nodes[i].left = nullptr;
	    	nodes[i].right = nullptr;
	    }
	    else{
	     	// this node have 2 children
	     	nodes[i].left = &nodes[2*i+1];
	     	nodes[i].right = &nodes[2*i+2];
	     }
	 }
	
	return &nodes[0];
    
}


int numElements(Heap h) {
	int num = 1;

	// add the number of children if any, by recursion
	if(h.right != nullptr){
		num =  1 + numElements(*h.left) + numElements(*h.right);
	 }
	else if(h.left != nullptr){
		num =  1 + numElements(*h.left);
	}

	 return num;
}


size_t lengthOfContent(Heap h) {
    int len = h.name.length();

	// add the length of children if any, by recursion
	if(h.right != nullptr){
		len = len + lengthOfContent(*h.left) + lengthOfContent(*h.right);
	 }
	else if(h.left != nullptr){
		len =  len + lengthOfContent(*h.left);
	}

	 return len;
}


Heap **returnAllHeaps(Heap h) {
	int length = numElements(h);
	static Heap *nodes = new Heap[length];
	nodes[0] = h;

 	for(int i = 0; i < length; i++){
    	if(2*i+2 == length){
	     	// this node have 1 child
	     	nodes[2*i+1] = *nodes[i].left;
    	}
    	else if(2*i+2 > length){
    		// this node does not have children
	    }
	    else{
	     	// this node have 2 children
	     	nodes[2*i+1] = *nodes[i].left;
	     	nodes[2*i+2] =  *nodes[i].right;
	     }
	 }

	 return &nodes;
}


string *printLinear(Heap h) {
    int length = numElements(h);
    string *heapsString = new string[length];
	Heap *nodes = *returnAllHeaps(h);

	for(int i = 0; i< length; i++){
		heapsString[i] = nodes[i].name;
	}

	return heapsString;
}


string printPretty(Heap h) {
    int numNodes = numElements(h);
    int numLines = 1;
    Heap *node = *returnAllHeaps(h);

    // find the height of the heap
    Heap *leftHeap = new Heap;
    leftHeap = h.left;

    while(leftHeap != nullptr){
    	numLines++;
    	leftHeap = leftHeap->left;
    }

    // get the node in order from left to right (in order)
    std::vector<Heap> heapInorder;
    inorder(&h, heapInorder);

    // initialize the char[] with blank spaces
    char pretty[lengthOfContent(h)*numLines+numLines];
	for (int i = 0; i< lengthOfContent(h)*numLines+numLines; i++){
    	pretty[i] = ' ';
	} 

    // add line changes
    for(int i = 1; i < numLines; i++){
    	pretty[i*lengthOfContent(h)+i-1] = '\n';
    }

    // add terminator
    pretty[lengthOfContent(h)*numLines+numLines -1] = '\0';

    // find where the node belongs and place it
    int nodeStart;
    for(int i = 0; i< numNodes; i++){

    	nodeStart = 0;
    	// find out where it belongs horizontally 
    	for(int j = 0; j< i; j++){
    		nodeStart = nodeStart + heapInorder.at(j).name.length();
    	}

    	// find out on which line the node belongs
    	bool lineFound = false;
    	int k = 0;
    	int line;
    	while(!lineFound){
			if(node[k].name == heapInorder.at(i).name){
				line = (int) log2((double)(k+1));
				lineFound = true;
			}
    		else{
    			k++;
    		}
    	}

    	// place the node where it belongs
    	for(int z = 0; z< heapInorder.at(i).name.length(); z++){

    		pretty[line*(lengthOfContent(h)+1)+nodeStart+z] = heapInorder.at(i).name.at(z);
    	}
    }    

    string str(pretty);
    return str;

}
