/*  Author: Lijun Chen
*   Date: 02/23/2015
*   File Overview: define a class BitInputStream that delegates to 
*   an object of an existing iostream class, and that adds a readBit 
*   method (and a fill method which can get the 8-bit buffer)
*   Assignment Number: 3
*/  


#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>
using namespace std;

class BitInputStream{
private:
	char buf;
	int nbits;
	istream & in;

public:
	BitInputStream(istream & is):in(is){
		buf = 0;
		nbits = 8;	
	}

	/** A fill method which can get the 8-bit buffer 
 	*/
	void fill();

	/** A method can read bit from bitinputstream
 	*  return the bit store in int(0 or 1)
 	*/
	int readBit();
	
};

#endif // BITINPUTSTREAM_HPP