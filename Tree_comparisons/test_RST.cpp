#include "RST.hpp"
#include "countint.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

// random generator function:
int myrandom (int i) { return rand()%i;}

int test_RST_rotate(int N) {
  
  cout << endl << "### Testing RST rotateLeft and rotateRight functionality ..." << endl << endl;
  
  /* Create an STL vector of some countints, in sorted order */
  vector<countint> v;
  vector<countint> v_sorted;
  for(int i=0; i<N; i++) {
    //    v.push_back(i);
    v.push_back(i);
    v_sorted.push_back(i);
  }
  
  // Create a reproducible psuedo-random insertion order
  std::random_shuffle ( v.begin(), v.end(), myrandom);

  /* Create an empty instance of RST holding countint */
  RST<countint> r = RST<countint>();

  /* Insert the data items, in order */
  cout << "Inserting " << N << " random keys in initially empty RST...";
  vector<countint>::iterator vit = v.begin();
  vector<countint>::iterator ven = v.end();
  for(; vit != ven; ++vit) {
    // all these inserts are unique, so should return true
    if(! r.BSTinsert(*vit) ) {
      cout << endl << "Incorrect return value when inserting " << *vit << endl;
      return -1;
    }
  }
  cout << " done." << endl;

  // r.inorder();
  
  // cout << "Rotating an arbitrary node with rotateLeft... ";
  cout << "Rotating an arbitrary node with rotateLeft... "<< endl;
  vit = v.begin();
  ven = v.end();
  for(; vit != ven; ++vit) {
    int ret = r.findAndRotate(*vit, true);
    if (ret == 0)
    {
      break;
    } else if (ret < 0)
    {
      cout << endl << "Failed to rotate node " << *vit << endl;
      return -1;
    }
  }
  
   // r.inorder();
  
  /* Test iterator; should iterate the entire tree inorder */
  cout << "Checking traversal using iterator...";
  vit = v_sorted.begin();
  BST<countint>::iterator en = r.end();
  BST<countint>::iterator it = r.begin();
  int i = 0;
  for(; it != en; ++it) {
    //    cout << *it << endl;
    if(*it != *vit) {
      cout << endl << "Incorrect inorder iteration of RST." << endl;
      return -1;
    }
    ++i;
    ++vit;
  }
  if(i!=N) {
    cout << endl << "Early termination during inorder iteration of RST." << endl;
    return -1;
  }
  cout << " OK." << endl;
  
  // cout << "Rotating an arbitrary node with rotateRight... ";
  cout << "Rotating an arbitrary node with rotateRight... "<< endl;
  vit = v.begin();
  ven = v.end();
  for(; vit != ven; ++vit) {
    int ret = r.findAndRotate(*vit, false);
    if (ret == 0)
    {
      break;
    } else if (ret < 0)
    {
      cout << endl << "Failed to rotate node " << *vit << endl;
      return -1;
    }
  }
  
  
  // r.inorder();
  
  /* Test iterator; should iterate the entire tree inorder */
  cout << "Checking traversal using iterator...";
  vit = v_sorted.begin();
  en = r.end();
  it = r.begin();
  i = 0;
  for(; it != en; ++it) {
    //    cout << *it << endl;
    if(*it != *vit) {
      cout << endl << "Incorrect inorder iteration of RST." << endl;
      return -1;
    }
    ++i;
    ++vit;
  }
  if(i!=N) {
    cout << endl << "Early termination during inorder iteration of RST." << endl;
    return -1;
  }
  cout << " OK." << endl;

  cout << endl << "### ROTATION TESTS PASSED ####" << endl << endl;
  
  return 0;
}

int test_RST_insert(int N) {

  cout << "### Testing RST insert functionality ..." << endl << endl;
  
  double  maxcompsperkey =  (log(N) * 2.5); 

  /* Create an STL vector of some countints, in sorted order */
  vector<countint> v;
  for(int i=0; i<N; i++) {
    //    v.push_back(i);
    v.push_back(i);
  }

  /* Create an empty instance of RST holding countint */
  RST<countint> r = RST<countint>();

  /* Clear the comparison counter */
  countint::clearcount();

  /* Insert the data items, in order */
  cout << "Inserting " << N << " sorted keys in initially empty RST...";
  vector<countint>::iterator vit = v.begin();
  vector<countint>::iterator ven = v.end();
  for(; vit != ven; ++vit) {
    // all these inserts are unique, so should return true
    if(! r.insert(*vit) ) {
      cout << endl << "Incorrect return value when inserting " << *vit << endl;
      return -1;
    }
  }
  cout << " done." << endl;
  // r.inorder();
  
  //  r.inorder();
  
  /* Test iterator; should iterate the entire tree inorder */
  cout << "Checking traversal using iterator...";
  vit = v.begin();
  BST<countint>::iterator en = r.end();
  BST<countint>::iterator it = r.begin();
  int i = 0;
  for(; it != en; ++it) {
    //    cout << *it << endl;
    if(*it != *vit) {
      cout << endl << "Incorrect inorder iteration of RST." << endl;
      return -1;
    }
    ++i;
    ++vit;
  }
  if(i!=N) {
    cout << endl << "Early termination during inorder iteration of RST." << endl;
    return -1;
  }
  cout << " OK." << endl;

  /* How many comparisons did it take to do the inserts, avg per key? */
  double compsperkey =  countint::getcount() / (double) N;
  cout << "That took " << compsperkey << " average comparisons per key, ";
  if(compsperkey <= maxcompsperkey) cout << "OK. " << endl;
  else if (compsperkey <= maxcompsperkey * 2) cout << "could be better... max is " << maxcompsperkey << endl;
  else {
    cout << "way too many!" << endl;
    return -1;
  }

  /* Test iterator; should iterate the entire tree inorder */
  cout << "Checking traversal using iterator...";
  vit = v.begin();
  en = r.end();
  it = r.begin();
  i = 0;
  for(; it != en; ++it) {
    //    cout << *it << endl;
    if(*it != *vit) {
      cout << endl << "Incorrect inorder iteration of RST." << endl;
      return -1;
    }
    ++i;
    ++vit;
  }
  if(i!=N) {
    cout << endl << "Early termination during inorder iteration of RST." << endl;
    return -1;
  }
  cout << " OK." << endl;
  
  cout << endl << "### INSERTION TESTS PASSED ####" << endl << endl;
  
  return 0;
}

int test_RST_rotate_case1(int N) {
  RST<countint> r = RST<countint>();
  r.BSTinsert(2);
  r.BSTinsert(1);
  cout<<"Before rotate"<<endl;
  r.inorder();
  int ret = r.findAndRotate(2, false);
  if (ret == 0)
  {
  } else if (ret < 0)
  {
    cout << endl << "Failed to rotate node " << 2 << endl;
    return -1;
  }
  cout<<"After rotate"<<endl;
  r.inorder();
  return 0;



}

int test_RST_rotate_case2(int N) {
  RST<countint> r = RST<countint>();
  r.BSTinsert(2);
  r.BSTinsert(3);
  cout<<"Before rotate"<<endl;
  r.inorder();
  int ret = r.findAndRotate(2, true);
  if (ret == 0)
  {
  } else if (ret < 0)
  {
    cout << endl << "Failed to rotate node " << 2 << endl;
    return -1;
  }
  cout<<"After rotate"<<endl;
  r.inorder();
  return 0;



}

int test_RST_rotate_case3(int N) {
  RST<countint> r = RST<countint>();
  r.BSTinsert(2);
  r.BSTinsert(1);
  cout<<"Before rotate"<<endl;
  r.inorder();
  int ret = r.findAndRotate(2, true);
  if (ret == 0)
  {
  } else if (ret < 0)
  {
    cout << endl << "Failed to rotate node " << 2 << endl;
    return -1;
  }
  cout<<"After rotate"<<endl;
  r.inorder();
  return 0;



}

int test_RST_rotate_case4(int N) {
  RST<countint> r = RST<countint>();
  r.BSTinsert(2);
  r.BSTinsert(3);
  cout<<"Before rotate"<<endl;
  r.inorder();
  int ret = r.findAndRotate(2, false);
  if (ret == 0)
  {
  } else if (ret < 0)
  {
    cout << endl << "Failed to rotate node " << 2 << endl;
    return -1;
  }
  cout<<"After rotate"<<endl;
  r.inorder();
  return 0;



}

int test_RST_rotate_case5(int N) {
  RST<countint> r = RST<countint>();
  r.BSTinsert(3);
  r.BSTinsert(2);
  r.BSTinsert(1);
  cout<<"Before rotate"<<endl;

  r.inorder();
  int ret = r.findAndRotate(3, false);
  if (ret == 0)
  {
  } else if (ret < 0)
  {
    cout << endl << "Failed to rotate node " << 2 << endl;
    return -1;
  }
  cout<<"After rotate"<<endl;
  r.inorder();
  return 0;



}

int test_RST_rotate_case6(int N) {
  RST<countint> r = RST<countint>();
  r.BSTinsert(3);
  r.BSTinsert(1);
  r.BSTinsert(2);
  cout<<"Before rotate"<<endl;
  r.inorder();
  int ret = r.findAndRotate(3, false);
  if (ret == 0)
  {
  } else if (ret < 0)
  {
    cout << endl << "Failed to rotate node " << 2 << endl;
    return -1;
  }
  cout<<"After rotate"<<endl;
  r.inorder();
  return 0;



}

int test_RST_rotate_case7(int N) {
  RST<countint> r = RST<countint>();
  r.BSTinsert(3);
  r.BSTinsert(1);
  r.BSTinsert(2);
  cout<<"Before rotate"<<endl;

  r.inorder();
  int ret = r.findAndRotate(1, true);
  if (ret == 0)
  {
  } else if (ret < 0)
  {
    cout << endl << "Failed to rotate node " << 2 << endl;
    return -1;
  }
  cout<<"After rotate"<<endl;
  r.inorder();
  return 0;



}

int test_RST_rotate_case8(int N) {
  RST<countint> r = RST<countint>();
  r.BSTinsert(1);
  r.BSTinsert(2);
  r.BSTinsert(3);
  cout<<"Before rotate"<<endl;
  r.inorder();
  int ret = r.findAndRotate(1, true);
  if (ret == 0)
  {
  } else if (ret < 0)
  {
    cout << endl << "Failed to rotate node " << 2 << endl;
    return -1;
  }
  cout<<"After rotate"<<endl;
  r.inorder();
  return 0;



}

int test_RST_rotate_case9(int N) {
  RST<countint> r = RST<countint>();
  r.BSTinsert(1);
  r.BSTinsert(3);
  r.BSTinsert(2);
  cout<<"Before rotate"<<endl;

  r.inorder();
  int ret = r.findAndRotate(1, true);
  if (ret == 0)
  {
  } else if (ret < 0)
  {
    cout << endl << "Failed to rotate node " << 2 << endl;
    return -1;
  }
  cout<<"After rotate"<<endl;
  r.inorder();
  return 0;



}

int test_RST_rotate_case10(int N) {
  RST<countint> r = RST<countint>();
  r.BSTinsert(1);
  r.BSTinsert(3);
  r.BSTinsert(2);
  cout<<"Before rotate"<<endl;

  r.inorder();
  int ret = r.findAndRotate(3, false);
  if (ret == 0)
  {
  } else if (ret < 0)
  {
    cout << endl << "Failed to rotate node " << 2 << endl;
    return -1;
  }
  cout<<"After rotate"<<endl;
  r.inorder();
  return 0;



}


bool test_RST_insert_by_testOurRstPriority(int N){
  cout << "### Our Testing RST insert functionality ..." << endl << endl;
  
  
  /* Create an STL vector of some countints, in sorted order */
  vector<countint> v;
  for(int i=0; i<N; i++) {
    //    v.push_back(i);
    v.push_back(i);
  }

  /* Create an empty instance of RST holding countint */
  RST<countint> r = RST<countint>();

  /* Clear the comparison counter */
  countint::clearcount();

  /* Insert the data items, in order */
  cout << "Inserting " << N << " sorted keys in initially empty RST..."<<endl;
  vector<countint>::iterator vit = v.begin();
  vector<countint>::iterator ven = v.end();
  for(; vit != ven; ++vit) {
    // all these inserts are unique, so should return true
    if(! r.insert(*vit) ) {
      cout << endl << "Incorrect return value when inserting " << *vit << endl;
      return -1;
    }
  }

  if(r.testOurRstPriorityMethod()){
    cout << "### OUR RST INSERT TESTS PASSED #### " << endl;
  }
  
  return 1;


}


/**
 * A simple partial test driver for the RST class template.
 * P2 CSE 100
 * Author: P. Kube (c) 2010, 2011, 2012
 */
int main(int argc, char** argv) {
  srand (unsigned(149));

  

  int N = 1000;
  if(argc > 1) N = atoi(argv[1]);
  // a good RST implementation should need no more than this number
  // of key comparisons when inserting N keys
  
  int return_value = test_RST_rotate(N);
  
  if (return_value != 0) {
    return return_value;
  }
  cout<<endl<<"### TESTING OUR RST ROTATE TEST CASES "<<endl<<endl;

  cout<<"#Test case 1 right rotate with 2 nodes, 2->1, rotate 2"<<endl;
  test_RST_rotate_case1(N);

  cout<<"#Test case 2 left rotate with 2 nodes, 2->3, rotate 2"<<endl;
  test_RST_rotate_case2(N);

  cout<<"#Test case 3 right rotate with 2 nodes to an invalid node, 2->1, rotate 1"<<endl;
  test_RST_rotate_case3(N);

  cout<<"#Test case 4 left rotate with 2 nodes to an invalid node, 2->3, rotate 3"<<endl;
  test_RST_rotate_case4(N);

  cout<<"#Test case 5 right rotate with 3 nodes, 3->2->1, rotate 3"<<endl;
  test_RST_rotate_case5(N);

  cout<<"#Test case 6 right rotate with 3 nodes, 3->1->2, rotate 3"<<endl;
  test_RST_rotate_case6(N);

  cout<<"#Test case 7 left rotate with 3 nodes, 3->1->2, rotate 1"<<endl;
  test_RST_rotate_case7(N);

  cout<<"#Test case 8 left rotate with 3 nodes, 1->2->3, rotate 1"<<endl;
  test_RST_rotate_case8(N);

  cout<<"#Test case 9 left rotate with 3 nodes, 1->3->2, rotate 1"<<endl;
  test_RST_rotate_case9(N);

  cout<<"#Test case 10 right rotate with 3 nodes, 1->3->2, rotate 3"<<endl;
  test_RST_rotate_case10(N);

  cout << endl << "### OUR RST ROTATE TESTS PASSED ####" << endl << endl;


  test_RST_insert(N);
  test_RST_insert_by_testOurRstPriority(N);
  
}
