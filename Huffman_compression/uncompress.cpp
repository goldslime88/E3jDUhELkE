/*  Author: Lijun Chen
*   Date: 02/23/2015
*   File Overview: Uncompress the input file to the output file by Huffman
*	coding. This time we translate the file of binary Huffman code not the
*	char into origin file.
*   Assignment Number: 3
*/  

#include <queue>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
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

	//Read the header from input file 
	ifstream compFile;
	compFile.open(infile,ios::binary);
	if(!compFile){
		cout<<"File open error!\n";
		return 0;
	}
	if(compFile.is_open()){
		string temp;
		getline(compFile,temp);
		if(temp != "h"){
			cout<<"Not a correct compressed file!"<<endl;
			return 0;
		}
		else{
			getline(compFile,temp);
		}
		while(temp != "f"){
			int strSize = temp.size();
			int symbol = 0, count = 0;
			bool flag = false;
			for (int i = 0; i < strSize; ++i)
			{
				if(temp[i] != ' '){
					if(flag == false){
						symbol = symbol*10 + temp[i] -'0';
					}
					else{
						count = count*10 + temp[i] - '0';
					}
				}
				else{
					flag = true;
				}

			}	
			freqs[symbol] = count;
			sum = sum + count;
			getline(compFile,temp);

		}
		
	}

	//Build the Huffman code
    HCTree hctree;
	hctree.build(freqs);
	ofstream uncompFile;
	uncompFile.open(outfile,ios::binary);
	if(!uncompFile){
		cout<<"File open error!\n";
		return 0;
	}

	//Read the file and translate into symbol
	BitInputStream bitIStream(compFile);
	for(int i = 0; i < sum; ++i){
		uncompFile<<(byte)hctree.decode(bitIStream);
		uncompFile.flush();
	}
	uncompFile.close();
    compFile.close();
	



	return 0;
}