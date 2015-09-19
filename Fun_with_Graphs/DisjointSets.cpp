/** 
 * Author: Bobby Huang, Lijun Chen 
 * Filename: DisjointSet.cpp 
 * Assignment: PA4
 *
 * This is the implementation of disjoint sets.
 **/

#include "DisjointSets.hpp" 
#include <iostream>

using namespace std;


disjointSets::disjointSets(int pVectorSize){
  parentVector.resize(pVectorSize); 
  numSets = 0; 
  numElements = 0; 
} 

disjointSets::~disjointSets(){
  parentVector.clear();
  numElements = 0; 
  numSets = 0; 

}

/*
 * This method finds and returns the sentinal of int a 
 */ 
int disjointSets::find(int a){
  int curr = a;
  int sentinal = a;  
  while(parentVector[sentinal] != -1){ 
    sentinal = parentVector[sentinal]; 
  }
  while(curr != sentinal){ 
    int temp = curr;
    curr = parentVector[curr];
    parentVector[temp] = sentinal;
  }
  return sentinal; 
}

/* 
 * This method takes two arguments (a and b), sets the sentinal of element b
 * to be the parent of element a's sentinal.   
 */
void disjointSets::setUnion(int a, int b){   
  int sentinalA = find(a); 
  int sentinalB = find(b); 
  if(sentinalA == sentinalB){ 
    return; 
  } 
  else{ 
    parentVector[sentinalB] = sentinalA; 
    numSets--;
  } 
}
/*
 * Adds newElement into this set and set it's value to -1 which indicates
 * that it is a sentinal
 */ 
void disjointSets::add(int newElement){ 
  parentVector[newElement] = -1;
  numElements++;
  numSets++;
}

/* 
 * Returns the number of sets in this disjoint set
 */
int disjointSets::numOfSets(){ 
  return numSets;
}

/*
 * Returns the number of elements in this disjoint set
 */
int disjointSets::numOfElements(){
  return numElements;
}


