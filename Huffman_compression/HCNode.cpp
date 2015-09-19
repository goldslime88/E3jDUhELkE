/*  Author: Lijun Chen
*   Date: 02/18/2015
*   File Overview: Define operator "<" when comparing two HCNodes.
*   Assignment Number: 3
*/  

#include <iostream>
#include "HCNode.hpp"

typedef unsigned char byte;

using namespace std;

/* Define operator "<" when comparing two HCNodes.
* Input
*    other - the HCNode after operator "<".
* Output - true if this.count > other.count. When this.count == other.count, 
*		   return this.symbol<other.symbol
*/ 

bool HCNode::operator<(const HCNode& other){
	if(count != other.count){
		return count > other.count;
	}
	return symbol < other.symbol;

}