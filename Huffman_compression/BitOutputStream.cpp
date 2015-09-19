/*  Author: Lijun Chen
*   Date: 02/23/2015
*   File Overview: define a class BitOutputStream that delegates to 
*   an object of an existing iostream class, and that adds a writeBit 
*   method (and a flush method which flushes the 8-bit buffer)
*   Assignment Number: 3
*/  


#include <iostream>
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
using namespace std;
typedef unsigned char byte;

/** A flush method which flushes the 8-bit buffer 
 */
void BitOutputStream::flush(){
	out.put(buf);
	out.flush();
	buf = nbits = 0;

}

/** Input the bit i(0 or 1).
 * 	A method can write this bit into outputstream
 */
void BitOutputStream::writeBit(int i){
	if(nbits == 8){
		flush();
	}
	if(i == 0){

		buf = buf& (~((1)<<(7-nbits)));
	}
	else{
		buf = buf|((1)<<(7-nbits));
	}
	
	nbits++;

}