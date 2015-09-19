/*  Author: Lijun Chen
*   Date: 02/23/2015
*   File Overview: define a class BitOutputStream that delegates to 
*   an object of an existing iostream class, and that adds a writeBit 
*   method (and a flush method which flushes the 8-bit buffer)
*   Assignment Number: 3
*/  



#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>
using namespace std;


class BitOutputStream{
private:
	char buf;
	int nbits;
	ostream & out;
public:

	BitOutputStream(ostream & os) : out(os), buf(0), nbits(0){}

	/** A flush method which flushes the 8-bit buffer 
 	*/
	void flush();
	
	/** Input the bit i(0 or 1).
 	* 	A method can write this bit into outputstream
 	*/
	void writeBit(int i);

};

#endif // BITOUTPUTSTREAM_HPP