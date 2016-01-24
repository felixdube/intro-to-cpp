#include "heaps.h"
#include <iostream>

Heap *heapFromArray(string *input, int length) {

	Heap *heaps[length];

   	static Heap h;
    heaps[0] = &h;

    for(int i = 0; i < length; i++){
    	
    	heaps[i]->name = input[i];

    	if(2*i+2 == length){
	     	// create one child
	     	auto hl = new Heap;

	     	// save the address of the child in the array
	     	heaps[2*i+1] = hl;

	     	//link child to parent
	     	heaps[i]->left = hl;
	     	heaps[i]->right = nullptr;
    	}
    	else if(2*i+2 > length){
    		// this node does not have children
	    	heaps[i]->left = nullptr;
	    	heaps[i]->right = nullptr;
	    }
	    else{
	     	// create two children
	     	auto hl = new Heap;
	     	auto hr = new Heap;

	     	// save the address of the child in the array
	     	heaps[2*i+1] = hl;
	     	heaps[2*i+2] = hr;

	     	//link child to parent
	     	heaps[i]->left = hl;
	     	heaps[i]->right = hr;
	     }
	 }
	
	return heaps[0];
    
}


int numElements(Heap h) {
	int num = 1;

	// divide and conquer
	if(h.right != nullptr){
		num =  1 + numElements(*h.left) + numElements(*h.right);
	 }
	else if(h.left != nullptr){
		num =  1 + numElements(*h.left);
	}

	 return num;
}


size_t lengthOfContent(Heap h) {
    //your code here
}


/* might want to do this for Q5
Heap **returnAllHeaps(Heap h) {
    //your code here
}*/

string *printLinear(Heap h) {
    //your code here
}


string printPretty(Heap h) {
    //your code here
}
