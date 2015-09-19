/*  Author: Lijun Chen, Yiqiu Liu
*   Date: 02/04/2015
*   File Overview: benchmark the performance of a RST implementation, an ordinary BST 
*   implementation, and the C++ STL std::set structure (red-black tree). We can choose
*   whether the keys inserted in the structure are inserted in sorted order, or shuffled 
*   order. The size of the tree and the number of runs can be adjusted.
*   Assignment Number: 2
*/  

#include <iostream>
#include <math.h>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include "countint.hpp"
#include "BST.hpp"
#include "RST.hpp"

using namespace std;

// random generator function:
int myrandom (int i) { return rand()%i;}

/* Get average compares over number of nodes.
   * Input
   *    numOfNodes - number of the nodes in a data structure.
   *   	typeOfContainer - type of data structure: bst, rst, set.
   *    orderOfInsertion - insert sorted numbers or shuffled numbers.
   *Outout
   *	Average compares of find operation over number of nodes.
   */ 
double avgcomps(int numOfNodes,string typeOfContainer,string orderOfInsertion){
	double avgcomps;
	vector<countint> v;
	v.clear();
	for(int i=0;i < numOfNodes;++ i) {
  		v.push_back(i);
	}

	//Is it sorted or shuffled?
	if(orderOfInsertion == "shuffled"){
		std::random_shuffle ( v.begin(), v.end(), myrandom);
	}

	std::vector<countint>::iterator vit = v.begin();
 	std::vector<countint>::iterator ven = v.end();

	//The type of the containner is rst
	if(typeOfContainer == "rst"){
		RST<countint> s;
		for(vit = v.begin(); vit != ven; ++vit) {
    		s.insert(*vit);
 		}
 		countint::clearcount();
		for(vit = v.begin(); vit != ven; ++vit) {
  			s.find(*vit);
		}
		avgcomps = countint::getcount()/(double)numOfNodes;
	}

	//The type of the containner is bst
	if(typeOfContainer == "bst"){
		BST<countint> s;
		for(vit = v.begin(); vit != ven; ++vit) {
    		s.insert(*vit);
 		}
 		countint::clearcount();
		for(vit = v.begin(); vit != ven; ++vit) {
  			s.find(*vit);
		}
		avgcomps = countint::getcount()/(double)numOfNodes;
	}

	//The type of the containner is set
	if(typeOfContainer == "set"){
		std::set<countint> s;	
		for(vit = v.begin(); vit != ven; ++vit) {
    		s.insert(*vit);
 		}
 		countint::clearcount();
		for(vit = v.begin(); vit != ven; ++vit) {
  			s.find(*vit);
		}
		avgcomps = countint::getcount()/(double)numOfNodes;
	}
	return avgcomps;
}


int main(int argc, char const *argv[])
{
	std::string typeOfContainer;
	std::string orderOfInsertion;
	int maxSize;
	int numberOfRuns;	

	//seed random numbers
	srand ( unsigned(149) );

	// check the number of arguments
	if (argc != 5)
	{
		std::cout<<"THe number of arguments is not four, please check!"<<std::endl;
		return 0;
	}else{
		typeOfContainer = argv[1];
		orderOfInsertion = argv[2];
		maxSize = atoi(argv[3]);
		numberOfRuns = atoi(argv[4]);
		int nodes = 1;
		int runs = 0;
		double sum;
		double sqsum;
		double avg;
		double stdev;
		double tempComps;

		// check the validity of arguments
		if(typeOfContainer != "bst" && typeOfContainer != "rst" && typeOfContainer!= "set"){
			std::cout<<"Invalid argument, please check"<<std::endl;
			return 0;
		}
		if(orderOfInsertion != "sorted" && orderOfInsertion != "shuffled"){
			std::cout<<"Invalid argument, please check"<<std::endl;
			return 0;
		}
		if(maxSize < 1){
			std::cout<<"Invalid argument, please check"<<std::endl;
			return 0;
		}
		if(numberOfRuns < 1){
			std::cout<<"Invalid argument, please check"<<std::endl;
			return 0;
		}

		std::cout<<"#Benchmarking average number of comparisons for successful find"<<std::endl;
		std::cout<<"#Data structure: "<<typeOfContainer<<std::endl;
		std::cout<<"#Data: "<<orderOfInsertion<<std::endl;
		std::cout<<"#N is powers of 2, minus 1, from 1 to "<<maxSize<<std::endl;
		std::cout<<"#Averaging over "<<numberOfRuns<<" runs for each N"<<std::endl;
		std::cout<<"#"<<std::endl;
		std::cout<<"#N 	 avgcomps 	 stdev"<<std::endl;

		while(nodes < maxSize){
			runs = 0;
			sum = 0;
			sqsum = 0;

			// run numberOfRuns times
			for(;runs < numberOfRuns; ++ runs){

				tempComps = avgcomps(nodes,typeOfContainer,orderOfInsertion);
				sum	+= tempComps;
				sqsum += tempComps * tempComps;	

			}
			avg = sum / (double)numberOfRuns;
			stdev = sqrt(fabs((sqsum * (double)numberOfRuns - sum * sum)/(double)numberOfRuns/(double)numberOfRuns));
			std::cout<<setiosflags(ios::fixed)<<setiosflags(ios::right)<<setprecision(10);
			std::cout<<nodes<<" 	 "<<avg<<" 	 "<<stdev<<std::endl;

			//update number of nodes
			nodes = 2 * nodes + 1;
		}

	}
	return 0;
}

