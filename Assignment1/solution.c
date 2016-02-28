#include "heaps.h"

Heap *heapFromArray(string *input, int length) {
    // ----
    // create an array of Heap pointers that will hold addresses
    // to all the nodes of the Heap
    Heap *allHeaps[length];
    // ----
    // create the top of the heap - this will be returned
    allHeaps[0] = new Heap;
    // ----
    // set the content for each of these nodes
    for(int ada = 0; ada < length; ada++) {
        // ----
        //set name from input
        allHeaps[ada]->name = input[ada];
        // ----
        //set left child to the element at index (ada * 2 + 1)
        if (ada*2+1 < length) {
            // have to create the left child
            allHeaps[ada]->left = new Heap;
            // save its address in the array allHeaps
            allHeaps[ada * 2 + 1] = allHeaps[ada]->left;
            // ----
            //set right child to the element at index (ada * 2 + 2)
            if (ada*2+2 < length) {
                // have to create the left child
                allHeaps[ada]->right = new Heap;
                // save its address in the array allHeaps
                allHeaps[ada * 2 + 2] = allHeaps[ada]->right;
            }
        }
    } // end for loop
    // only return the address of the top node
    return allHeaps[0];
} // end heapFromArray


int numElements(Heap h) {
    int num = 1; // count 1 for this node
    // ----
    if(h.left != nullptr) {
        // count the left heap recursively
        num += numElements(*(h.left));
        // ----
        if (h.right != nullptr) {
            // count the left heap recursively
            num += numElements(*(h.right));
        }
    }
    // return the calculated value
    return num;
} // end numElements

size_t lengthOfContent(Heap h) {
    // count the lenth of the name of current node
    size_t num = h.name.length();
    // ----
    if(h.left != nullptr) {
        // count the length of the content the left heap recursively
        num += lengthOfContent(*(h.left));
        // ----
        if (h.right != nullptr) {
            // count the length of the content the left heap recursively
            num += lengthOfContent(*(h.right));
        }
    }
    // return the calculated value
    return num;
} // end lengthOfContent


Heap **returnAllHeaps(Heap h) {
    // we will need the number of elements
    int length = numElements(h);
    // ----
    // create the array that we will return
    // it is an array of pointers
    Heap **allHeaps = new Heap*[length];
    // ----
    // create the top Heap using the content from parameter h
    allHeaps[0] = new Heap(h);
    // ----
    // save the addresses of all other nodes
    for (int ada = 0; ada < length; ada++) {
        if (ada * 2 + 1 < length) { // left
            allHeaps[ada * 2 + 1] = allHeaps[ada]->left;
            // ----
            if (ada*2+2 < length) { // right
                allHeaps[ada * 2 + 2] = allHeaps[ada]->right;
            }
        }
        
    } // end for loop
    // ----
    return allHeaps;
} // end returnAllHeaps

string *printLinear(Heap h) {
    // get an array with all addresses
    Heap **allHeaps = returnAllHeaps(h);
    // ----
    // we will need the number of elements
    int length = numElements(h);
    // ----
    // create array of strings to return
    string *toRet = new string[length];
    // ----
    // retreive the names of all nodes
    for (int ada = 0; ada < length ; ada++) {
        toRet[ada] = allHeaps[ada]->name;
    }
    return toRet;
} // end printLinear


string printPretty(Heap h) {
    // get an array with all addresses
    Heap **allHeaps = returnAllHeaps(h);
    // ----
    // we will need the number of elements
    int length = numElements(h);
    // ----
    // toRet will hold the content that we will return
    string toRet = "";
    // ----
    // elementsPerRowToDo counts the number of elements that have to
    // be printed per row. It starts at 1, and then it doubles
    // on every other row... 1,2,4,8,16,etc.
    int elementsPerRowToDo = 1;
    // elementsPerRowDone counts the number of elements that have
    // already been printed on each row. When this value reaches
    // elementsPerRowToDo, then we go to the next row
    int elementsPerRowDone = 0;
    // ----
    // print all elements in the order returned by returnAllHeaps
    for (int ada = 0; ada < length; ada++) {
        // ----
        // print white spaces for the left sub-tree
        if (allHeaps[ada]->left != nullptr) {
            // get the left node
            Heap *leftNode = allHeaps[ada]->left;
            // use lengthOfContent to know how many white spaces to print
            size_t whiteSpaces = lengthOfContent(*leftNode);
            // append enough white spaces to toRet
            for (int bee = 0; bee < whiteSpaces; bee++) {
                toRet += " ";
            }
        }
        // ----
        // print name of current node
        toRet += allHeaps[ada]->name;
        // ----
        // print white spaces for the right sub-tree
        if (allHeaps[ada]->right != nullptr) {
            // get the right node
            Heap *rightNode = allHeaps[ada]->right;
            // use lengthOfContent to know how many white spaces to print
            size_t whiteSpaces = lengthOfContent(*rightNode);
            // append enough white spaces to toRet
            for (int bee = 0; bee < whiteSpaces; bee++) {
                toRet += " ";
            }
        }
        // ----
        //element was printed.
        elementsPerRowDone++;
        // What next? New row, or skip space for a node above
        if (elementsPerRowDone == elementsPerRowToDo) {
            // next tow has to print double the amount of nodes
            elementsPerRowToDo *= 2;
            // reset the counter elementsPerRowDone
            elementsPerRowDone = 0;
            // go to next line in toRet
            toRet += "\n";
        } else {
            // find the node above for which we need to leave space
            // go up on the tree to the grand-grand-parents until one
            // is the parent of a left child
            // ----
            // start at current node
            int kid = ada;
            // go up while kid is a right child
            // note that all right childen have even index
            while(kid % 2 == 0 /* kid is a right child */ ) {
                kid = (kid - 1) / 2; // go up to the parent
            }
            // ----
            // found the ascendant for which we have to print white space
            int parent  = (kid - 1) / 2;
            // get length of parent's name
            size_t whiteSpaces = allHeaps[parent]->name.length();
            // append enough white spaces to toRet
            for (int bee = 0; bee < whiteSpaces; bee++) {
                toRet += " ";
            }
        } // end if...else on elementsPerRowDone
    } // end of for loop
    return toRet;
} // end printPretty