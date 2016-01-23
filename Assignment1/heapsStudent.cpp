#include "heaps.h"


Heap *heapFromArray(string *input, int length) {

	Heap *heaps[length];

    for(int i = 0; i < length; i++){
    	
    	heaps[i]->name = input[i];
    	
    	// check is the heap have children
    	if(2*i+2 == length){
	    	heaps[i]->left = heaps[2*i+1];
	    	heaps[i]->right = nullptr;
    	}
    	else if(2*i+2 > length){
	    	heaps[i]->left = nullptr;
	    	heaps[i]->right = nullptr;
	    }
	    else{
	    	heaps[i]->left = heaps[2*i+1];
    		heaps[i]->right = heaps[2*i+2];
	    }

	    return heaps[0];
    }
}

int numElements(Heap h) {
    
int num = 0;

    if(h.right != nullptr){
    	num = num + numElements(*h.right);
    }
    else if(h.left != nullptr){
    	num = num + numElements(*h.left);
    }
    else{
    	return num;
    }

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
