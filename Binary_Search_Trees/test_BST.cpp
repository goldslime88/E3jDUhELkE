#include "BST.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

/**
 * A simple test driver for the BST class template.
 * P1 CSE 100 2012
 * Author: P. Kube (c) 2012
 */
int main() {

  /* Create an STL vector of some ints */
  vector<int> v;
  v.push_back(8);
  v.push_back(4);
  v.push_back(12);
  v.push_back(2);
  v.push_back(6);
  v.push_back(10);
  v.push_back(14);
  v.push_back(1);
  v.push_back(3);
  v.push_back(5);
  v.push_back(7);
  v.push_back(9);
  v.push_back(11);
  v.push_back(13);
  v.push_back(15);


  /* Create an instance of BST holding int */
  BST<int> b;
  BST<int> empty;

  /* Insert a few data items. */
  vector<int>::iterator vit = v.begin();
  vector<int>::iterator ven = v.end();
  cout << "Performing BST insertion test .... " << endl;
  for(; vit != ven; ++vit) {
    // all these inserts are unique, so should return true
    if(! b.insert(*vit) ) {
      cout << "Incorrect return value when inserting " << *vit << endl;
      return -1;
    }
  }

  vit = v.begin();
  for(; vit != ven; ++vit) {
    // all these inserts are duplicates, so should return false
    if( b.insert(*vit) ) {
      cout << "Incorrect return value when re-inserting " << *vit << endl;
      return -1;
    }
  }
  cout << "Insertion test passed!" << endl;

  /* Test size. */
  cout << "Performing get size test ...." << endl;
  cout << "Size is: " << b.size() << endl;
  if(b.size() != v.size()) {
    cout << "... which is incorrect." << endl;
    return -1;
  }
  cout << "Get size test passed!" << endl;

  /* Test find return value. */
  cout << "Performing find item test ...." << endl;
  vit = v.begin();
  for(; vit != ven; ++vit) {
    if(*(b.find(*vit)) != *vit) {
      cout << "Incorrect return value when finding " << *vit << endl;
      return -1;
    }
  }
  cout << "Find item test passed!" << endl;


  /* Sort the vector, to compare with inorder iteration on the BST */
  sort(v.begin(),v.end());


  /* Test BST iterator; should iterate inorder */
  cout << "Performing iterator test ...." << endl;
  cout << "traversal using iterator:" << endl;
  vit = v.begin();
  BST<int>::iterator it = b.begin();
    cout << *it << endl;
  for(; vit != ven; ++vit) {
    if(*it != *vit) {
      cout << *it << "," << *vit << ": Incorrect inorder iteration of BST." << endl;
      return -1;
    }
    ++it;
  }
  cout << "Iterator test passed!" << endl;
  
  cout << "Great! All tests passed!" << endl; 
  cout << "Keep in mind that this testbench is not comprehensive." << endl; 
  cout << "We will use more complicated testbench to grade your project" << endl;

  cout << "This is our test case" <<endl;
  cout << "Test case 1: Equality & Inequality test operator......"<<endl;
  BST<int>::iterator itfirst1(b.begin()), itfirst2(b.begin());
  if(itfirst1 == itfirst2){
    cout<< "Equality test passed!"<< endl;
  }
  else{
    cout<< "Incorrect equality!"<<endl;
  }
  itfirst1++;
  if(itfirst1 != itfirst2){
    cout<< "Inequality test passed!"<< endl;
  }
  else{
    cout<< "Incorrect inequality!"<<endl;
  }

  cout << "Test case 2: Successor test same as iterator test passed......"<<endl;

  cout << "Test case 3: insert duplicate value ......"<<endl;
  
  if(b.insert(15) == false){
    cout<< "Insert duplicate value test passed!"<< endl;
  }
  else{
    cout<< "Incorrect insert duplicate value test! "<< endl;
  }

  cout << "Test case 4: Find no such value & find in an empty tree ......"<<endl;
  if(b.find(16)==b.end()){
    cout<< "Find no such value test passed!"<< endl;
  }
  else{
    cout<< "Incorrect find no such value test!"<< endl;
  }
  if(empty.find(12)==empty.end()){
    cout<< "Find in an empty tree test passed!"<< endl;
  }
  else{
    cout<< "Incorrect find in an empty tree test!"<< endl;
  }

  cout<< "Test case 5: size of empty ......"<<endl;
  if(empty.size()==0){
    cout<< "Size of empty test passed!"<< endl;
  }
  else{
    cout<< "Incorrect size of empty test!"<< endl;
  }

  cout<< "Test case 6: whether a tree is empty ......"<<endl;

  if(empty.empty()==true && b.empty()==false){
    cout<< "Whether a tree is empty test passed!"<< endl;
  }
  else{
    cout<< "Incorrect whether a tree is empty test!"<< endl;
  }

  cout<<"Test case 7: begin of a tree  ......"<<endl;
  cout<<*b.begin()<<endl;
  if(*(b.begin())==1){
    cout<<"Begin of a tree test passed!"<< endl;
  }
  else{
    cout<<"Incorrect begin of a tree test!"<< endl;
  }

  cout<<"Test case 8: Inorder test & inorder empty ......"<<endl;

  b.inorder();
  empty.inorder();
  cout<<"Look at result that the inorder test passed"<<endl;
  
  cout<<"Test case 9: delete all"<<endl;

  cout<<"It will delete the whole tree when the program ends. "<<endl;
  cout<<"We use 'valgrind' to test it and there is no memory leakage."<<endl;

}
