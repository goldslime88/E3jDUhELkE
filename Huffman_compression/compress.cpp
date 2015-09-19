/*  Author: Lijun Chen
*   Date: 02/23/2015
*   File Overview: compress the input file to the output file by Huffman
*	coding. This time we translate the file into binary Huffman code not the
*	char, which implements the real compress.
*   Assignment Number: 3
*/  

#include <queue>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include "HCTree.hpp"
#include "HCNode.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

using namespace std;
typedef unsigned char byte;
int main(int argc, char const *argv[])
{
	vector<int> freqs(256, 0);
	string infile, outfile;
	infile = argv[1];
	outfile = argv[2];
	int sum=0;
	
	//record the frequencies of each character
	ifstream uncompFile;
	uncompFile.open(infile,ios::in|ios::binary);
	if(!uncompFile){
		cout<<"File open error!\n";
		return 0; 
	}
	while(uncompFile.is_open()){
		byte c;
		c = uncompFile.get();
		if(!uncompFile.good()){
			break;
		}

		freqs[(int)c] = freqs[(int)c] + 1;
		sum	++;

	
	
	}
	uncompFile.close();

	//build the Huffman Coding Tree
	HCTree hctree;
	hctree.build(freqs);

	ofstream compFile;
	uncompFile.open(infile,ios::in|ios::binary);

	string record((istreambuf_iterator<char>(uncompFile)),(istreambuf_iterator<char>()));
	if(uncompFile.is_open()){
		//write the header
		byte c;
		compFile.open(outfile, ios::out|ios::binary);
		if(!compFile){
			cout<<"File open error!\n";
			return 0;
		}
		compFile<<"h"<<'\n';
		compFile.close();
		compFile.open(outfile, ios::out | ios::app|ios::binary);
		for(int i = 0; i < 256; ++i){
			if(freqs[i] != 0){
				compFile<<i<<" "<<freqs[i]<<'\n';
			}
			
		}

		//write the file
		compFile<<"f"<<'\n';


		BitOutputStream bitOStream(compFile);
		for (int i = 0; i < record.size(); ++i) {

			hctree.encode(record[i], bitOStream);
		
		}
		bitOStream.flush();

		compFile.close();
		uncompFile.close();
	}


	return 0;
}

