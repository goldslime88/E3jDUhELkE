/*  Author: Lijun Chen
*   Date: 02/23/2015
*   File Overview: Some HCTree methods. 
*	Build -> build the Huffman code tree by freqs vector.
*	encode -> encode the symbol by Huffman code and write char to the file.
*	encode -> encode the symbol by Huffman code and write bit to the file.
*	decode -> read the Huffman code in char and translate it into symbol.
*	decode -> read the Huffman code in bit and translate it into symbol.
*	deleteAll -> delete the Huffman tree.
*   Assignment Number: 3
*/  

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <fstream>
#include "HCTree.hpp"
#include "HCNode.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

using namespace std;
typedef unsigned char byte;


HCTree::~HCTree(){
	deleteAll(root);
}
/** Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs){
	std::priority_queue<HCNode*,std::vector<HCNode*>,HCNodePtrComp> pq;
	int sizeOfVector = freqs.size();
	int numOfSymbol = 0;
	int recordOnlyOne = 0;
	//Use freqs vector to create the HCNode
	for(int i = 0; i < sizeOfVector; ++i){
		if(freqs[i] != 0){
			HCNode* newNode = new HCNode(freqs[i],i);
			leaves[i] = newNode;
			pq.push(newNode);
			numOfSymbol++;
			recordOnlyOne = i;

		}	
	}
	//Check if there is only one HCNode
	if(numOfSymbol == 1){
		HCNode* newNode = new HCNode(0,0);
		root = newNode;
		newNode->c0 = leaves[recordOnlyOne];
		leaves[recordOnlyOne]->p = newNode;
		return;
	}

	//Find two HCNodes and combine it to one HCNode
	while(!pq.empty()){
		HCNode* smallest1 = pq.top();
		pq.pop();
		HCNode* smallest2 = pq.top();
		pq.pop();
		//smaller one in the right child ("1" child)
		int newCount = smallest1->count+smallest2->count;
		byte newChar = smallest1->symbol;
		HCNode* newNode = new HCNode(newCount, newChar);
		newNode->c1 = smallest1;
		newNode->c0 = smallest2;
		smallest1->p = newNode;
		smallest2->p = newNode;
		if(pq.empty()){
			root = newNode;
		}
		else{
			pq.push(newNode);
		}
	}

}

/** Write to the given ofstream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT 
 *  BE USED IN THE FINAL SUBMISSION.
 */

void HCTree::encode(byte symbol, ofstream& out) const{
	HCNode* temp = leaves[(int)symbol];
	string ans;
	while(temp->p != 0){
		if(temp->p->c0 == temp){
			ans = '0' + ans;
		}
		else if(temp->p->c1 == temp){
			ans = '1' + ans;
		}
		temp = temp->p;
	}
	
	out<<ans;
	
}
/** Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the ifstream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
 *  IN THE FINAL SUBMISSION.
 */
int HCTree::decode(ifstream& in) const{
	HCNode* temp = root;
	
	char c;
	while(in.get(c)){
		if(c == '1'){
			temp = temp->c1;

		}
		else{
			temp = temp->c0;
		}

		if(temp->c1 == 0 && temp->c0 == 0){
			return temp->symbol;
		}

	}
	return 0;
}

/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const{

	HCNode* temp = leaves[(int)symbol];
	string ans;
	//read the encoded symbol in string
	while(temp->p != 0){

		if(temp->p->c0 == temp){
			ans = '0' + ans;
		}
		else if(temp->p->c1 == temp){
			ans = '1' + ans;
		}
		temp = temp->p;
	}



	for(int i = 0; i < ans.size(); ++i){
		if(ans[i] == '0'){
			out.writeBit(0);
		}
		else{
			out.writeBit(1);
		}
	}
	


}

/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
int HCTree::decode(BitInputStream& in) const{
	HCNode* temp = root;
	while(temp->c1 != 0 || temp->c0 != 0){
		int tempbit = in.readBit();
		if(tempbit == 1){
			temp = temp->c1;

		}
		else{
			temp = temp->c0;
		}


	}
	return temp->symbol;




}

/** Call this function when delete the HCTree.
 */

void HCTree::deleteAll(HCNode* n){
    if(n == 0){
      return;
    }
    else{
      deleteAll(n->c0);
      deleteAll(n->c1);
      delete n;
      n = 0;
    }
}


