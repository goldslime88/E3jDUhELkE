#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;

public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(0), isize(0) {  }


  /** Default destructor.
      Delete every node in this BST.
   */ // TODO
  virtual ~BST() {
    deleteAll(root);

  }

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return  true if the item was added to this BST
   *  as a result of this call to insert,
   *  false if an item equal to this one was already in this BST.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use >, <=, >=)
   */ // TODO->Done
  virtual bool insert(const Data& item) {
    isize++;
    if(root == 0){
      root = new BSTNode<Data>(item);
      return true;
    }

    BSTNode<Data>* temp = root;
    while(temp != 0){
      if(temp->data < item){
        if(temp->right == 0){
          temp->right = new BSTNode<Data>(item);
          temp->right->parent = temp;
          return true;
        }
        temp = temp->right;
      }
      else if(item < temp->data){
        if(temp->left == 0){
          temp->left = new BSTNode<Data>(item);
          temp->left->parent = temp;
          return true;
        }
        temp = temp->left;
      }
      else{
        isize--;
        return false;
      }

    }
    return false;

  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use >, <=, >=)
   */ // TODO->DONE
  iterator find(const Data& item) const {
    if(root == 0){
      return typename BST<Data>::iterator(0);
    }
    BSTNode<Data>* temp = root;
    while(temp != 0){
      if(temp->data == item){

        return typename BST<Data>::iterator(temp);
      }
      else if(temp->data < item){
        temp = temp->right;
      }
      else{
        temp = temp->left;
      }
     
    }

    return typename BST<Data>::iterator(0);

  }

  
  /** Return the number of items currently in the BST.
   */ // TODO->DONE;
  unsigned int size() const {
    return isize;

  }

  /** Return true if the BST is empty, else false.
   */ // TODO->DONE;
  bool empty() const {
    return (root == 0);

  }

  /** Return an iterator pointing to the first item in the BST (not the root).
   */ // TODO->DONE;
  iterator begin() const {
    BSTNode<Data>* temp = root;
    while(temp->left != 0){
      temp = temp->left;
    }
    return typename BST<Data>::iterator(temp);

  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(0);
  }

  /** Perform an inorder traversal of this BST.
   */
  void inorder() const {
    if(root == 0)

    std::cout<<"Tree is empty!"<<std::endl;

    inorder(root);
    std::cout<<std::endl;
  }


private:

  /** Recursive inorder traversal 'helper' function */

  /** Inorder traverse BST, print out the data of each node in ascending order.
      Implementing inorder and deleteAll base on the pseudo code is an easy way to get started.
   */ // TODO->DONE;
  void inorder(BSTNode<Data>* n) const {
    /* Pseudo Code:
      if current node is null: return;
      recursively traverse left sub-tree
      print current node data
      recursively traverse right sub-tree
    */
    if(n == 0){
      return;
    }
    else{
      inorder(n->left);
      std::cout<<n->data<<", ";
      inorder(n->right);
    }

    
  }

  /** Find the first element of the BST
   */ 
  static BSTNode<Data>* first(BSTNode<Data>* root) {
    if(root == 0) return 0;
    while(root->left != 0) root = root->left;
    return root;
  }

  /** do a postorder traversal, deleting nodes
   */ // TODO->DONE;
  static void deleteAll(BSTNode<Data>* n) {
    /* Pseudo Code:
      if current node is null: return;
      recursively delete left sub-tree
      recursively delete right sub-tree
      delete current node
    */

    if(n == 0){
      return;
    }
    else{
      deleteAll(n->left);
      deleteAll(n->right);
      std::cout<<"Node of data->"<<n->data<<" deleted."<<std::endl;
      delete n;
      n = 0;

    }
  }


 };


#endif //BST_HPP
