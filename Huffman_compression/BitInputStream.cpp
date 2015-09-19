/*  Author: Lijun Chen
*   Date: 02/23/2015
*   File Overview: define a class BitInputStream that delegates to 
*   an object of an existing iostream class, and that adds a readBit 
*   method (and a fill method which can get the 8-bit buffer)
*   Assignment Number: 3
*/  


#include <iostream>
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
using namespace std;
typedef unsigned char byte;

/** A fill method which can get the 8-bit buffer 
 */
void BitInputStream::fill(){
	buf = in.get();
	nbits = 0;
}

/** A method can read bit from bitinputstream
 *  return the bit store in int(0 or 1)
 */
int BitInputStream::readBit(){
	if(nbits == 8){
		fill();
	} 
	int ans;
	ans = 1&(buf>>(7-nbits));
	nbits++;
	return ans;


}