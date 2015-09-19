/**
 * Author: Bobby Huang, Lijun Chen
 * Filename: DisjointSets.hpp
 * Assigment: PA4
 *
 * This file is the header file for disjoint sets. 
 **/


#ifndef DISJOINTSETS_HPP
#define DISJOINTSETS_HPP

#include <vector> 

class disjointSets{ 
public: 
  // constructor 
  disjointSets(int pVectorSize);
  //destructor  
  ~disjointSets();

  /*
   * This method finds and returns the sentinal of int a 
   */ 
  int find(int a); 
  /* 
   * This method takes two arguments (a and b), sets the sentinal of element b
   * to be the parent of element a's sentinal.   
   */
  void setUnion(int a, int b);
  /* 
   * Returns the number of sets in this disjoint set
   */
  int numOfSets(); 
  /*
   * Returns the number of elements in this disjoint set
   */
  int numOfElements();
   /*
    * Adds newElement into this set and set it's value to -1 which indicates
    * that it is a sentinal
    */ 
  void add(int newElement);
private: 
  int numSets;  //number of sets in the disjoint set
  int numElements; //number of elements in the disjoint set
  std::vector<int> parentVector; //parentVector[i] is i's parent. 

};

#endif //DISJOINTSETS_HPP
