/*  Author: Lijun Chen, Yiqiu Liu
*   Date: 01/28/2015
*   File Overview: Implemented RST rotate right, rotate left and item insert.
*   Assignment Number: 2
*/  
/*
Files from PA1 statement:
The BST code we are using for PA2 is from Yiqiu Liu and Lijun Chen. There is 
one small difference in the size() function. We implemented size() function 
using the protected variable isize and whenever a node is inserted in the tree,
we add one to isize.
However a BST tree may not be formed using insert() function. It can also be 
formed by linking node directly, which will cause some problem. Personally, 
we think the variable isize is quite misleading.
Also, we make some mistake by not checking whether a node has parent or not
in our successor() function, which will cause segment fault when traversing a
binary search tree that only has a root and left subtree.
*/
#ifndef RST_HPP
#define RST_HPP
#include "BST.hpp"
#include <iostream>

using namespace std;

template <typename Data>
class RST : public BST<Data> {

public:

  /* Insert new data into the RST if it is not already present.
   * Input
   *    item - the data to insert.
   *    return - true if the item was inserted. If the item was already contained in
   *       the tree then return false.
   */ 
  virtual bool insert(const Data& item) {
    
    if(this->root == 0){                //if tree is empty
      this->root = new BSTNode<Data>(item);
      this->root->priority = rand();
      return true;
    }
    BSTNode<Data>* temp = this->root;
    //use BST insert and give the new node a random priority
    while(temp != 0){                   
      if(temp->data < item){
        if(temp->right == 0){
          temp->right = new BSTNode<Data>(item);
          temp->right->priority=rand();
          temp->right->parent = temp;
          temp = temp->right;
          break;
        }
        temp = temp->right;
      }
      else if(item < temp->data){
        if(temp->left == 0){
          temp->left = new BSTNode<Data>(item);
          temp->left->priority=rand();
          temp->left->parent = temp;
          temp = temp->left;
          break;
        }
        temp = temp->left;
      }
      else{
        return false;
      }
    }

    
    //rotate the new node until it satisfies RST
    while(temp->parent != 0 && temp->priority >= temp->parent->priority){
      if(temp->parent->left == temp){
        rotateRight(temp->parent,temp);
      }else{
        rotateLeft(temp->parent,temp);
      }
    }
 


    return true;
  }


  /* Check the RST whether every node's priority is smaller than its parent
   * Input
   *    None
   * Output
   *    If every node in RST has smaller priority than its parent, return true.
   * Else, return false.
   */ 
  bool testOurRstPriorityMethod(){
    return testOurRstPriority(this->root);
  }

private:

  /* Perform a 'right rotation' that changes the structure of the tree without
   * interfering with the size, data content, and left->right order of nodes in the RST.
   * This rotation is done by changing the 'left', 'right', and/or 'parent' pointers
   * of a subset of nodes without changing their 'priority' values.
   *
   * Input
   *    par - a parent node in the RST with a left child
   *    child - the left child of 'par'
   *
   * Output
   *   The resulting tree will have 'par' and 'child' in the same order but switched
   *   in level, meaning 'par' will effectively become the right-child of 'child'.
   *
   */
  void rotateRight( BSTNode<Data>* par, BSTNode<Data>* child ) {
    
    BSTNode<Data> *grandPar = par->parent;
    if(grandPar == 0){                  //if par is the root of RST
      child->parent = 0;
      this->root = child;  
    }else if(grandPar->right == par){   //if par is on the right subtree of its parent
      grandPar->right = child;
      child->parent = grandPar;
    }else{                              //if par is on the left subtree of its parent
      grandPar->left = child;
      child->parent = grandPar;
    }
    par->left = child->right;
    if(child->right != 0){
      child->right->parent = par;
    }
    child->right = par;
    par->parent = child; 
    
  }

  
  /* Perform a 'left rotation' that changes the structure of the tree without
   * interfering with the size, data content, and left->right order of nodes in the RST.
   * This rotation is done by changing the 'left', 'right', and/or 'parent' pointers
   * of a subset of nodes without changing their 'priority' values.
   *
   * Input
   *    par - a parent node in the RST with a right child
   *    child - the right child of 'par'
   *
   * Output
   *   The resulting tree will have 'par' and 'child' in the same order but switched
   *   in level, meaning 'par' will effectively become the left-child of 'child'.
   *
   */
  void rotateLeft( BSTNode<Data>* par, BSTNode<Data>* child )
  {
    
    BSTNode<Data> *grandPar = par->parent;
    if(grandPar == 0){                  //if par is the root of the RST    
      child->parent = 0;  
      this->root = child;  
    }else if(grandPar->right == par){   //if par is on the right of its parent
      grandPar->right = child;
      child->parent = grandPar;
    }else{                              //if par is on the left of its parent
      grandPar->left = child;
      child->parent = grandPar;
    }
    par->right = child->left;
    if(child->left != 0){ 
      child->left->parent = par;         
    }  
    child->left = par;
    par->parent = child;    
  }
  /* Check the RST whether every node's priority is smaller than its parent
   *
   * Input 
   *   The root of this RST.
   *    
   *
   * Output
   *   If every node in RST has smaller priority than its parent, return true.
   * Else, return false.
   */

  bool testOurRstPriority(BSTNode<Data>* rstRoot){
    if(rstRoot == 0){
      return true;
    }
    else{
      bool temp;
      if(rstRoot->parent == 0){
        std::cout<<"I'm root and my priority is "<<rstRoot->priority<<std::endl;
        return testOurRstPriority(rstRoot->left)&&testOurRstPriority(rstRoot->right);
      }
      else{
        temp = (rstRoot->parent->priority > rstRoot->priority);
        if(temp == 1){
          std::cout<<"My priority is " <<rstRoot->priority<< " smaller than my parent's priority "
        <<rstRoot->parent->priority<<std::endl;
        }
        else{
          std::cout<<"WRONG!!!!!"<<std::endl;
        }
        
        return temp&&testOurRstPriority(rstRoot->left)&&testOurRstPriority(rstRoot->right);
      }
      
    }
  }


public:

  /* THIS FUNCTION IS USED FOR TESTING, DO NOT MODIFY
   * 
   * Calls BST::insert so we can add data to test rotateRight and rotateLeft before
   * implementing the fully correct version of RST::insert.
   * 
   */
  bool BSTinsert(const Data& item) {
    
    return BST<Data>::insert(item);
    
  }
  
  /* THIS FUNCTION IS USED FOR TESTING, DO NOT MODIFY
   * 
   * Locates the node for an item and rotates it left or right without changing the
   * left->right order of nodes in the RST
   * Input
   *    item - the Data item to rotate.
   *    leftOrRight - if true then rotateLeft, otherwise rotateRight
   *    output - 0 if item could be found and had a child to rotate with, 1 if not. -1 if
   *         rotation failed for other reasons
   */
  int findAndRotate(const Data& item, bool leftOrRight) {
    
     BSTNode<Data>* current = RST<Data>::root;
     while ( current != 0 ) {
       if ( item < current->data ) {
         current = current->left;
       }
       else if ( current->data < item ) {
         current = current->right;
       }
       else {  // already in the tree
         break;
       }
     }
     
     if (current == 0 or current->data != item) {
       return 1;
     }
     
     if (leftOrRight) {
       if (current->right == 0) {
         return 1;
       }
       BSTNode<Data>* right = current->right;
       rotateLeft(current, current->right);
       
       // make sure we actually do a rotation
       if (current->right == right) {
         return -1;
       }
       
     } else {
       if (current->left == 0) {
         return 1;
       }
       BSTNode<Data>* left = current->left;
       rotateRight(current, current->left);
       
       // make sure we actually do a rotation
       if (current->left == left) {
         return -1;
       }
     }
     return 0;
  }
};
#endif // RST_HPP
