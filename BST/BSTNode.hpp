#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>

/** Binary Search Tree node class header and class defintion file.
 *  Author: Christopher Jensen
 */

template<typename Data>
class BSTNode {

public:

  BSTNode<Data>* left;
  BSTNode<Data>* right;
  BSTNode<Data>* parent;
  Data const data;   // the const Data in this node.

  // Initializes a BSTNode with the given Data item,
  BSTNode(const Data &d);

  /** Returns the successor of this BSTnode or 0 if there is none.
   *  Successor means sequentially next.  
   */
  BSTNode<Data>* successor(); 

}; 

// ********** Function definitions ****************

// Had to switch 'data(d)' to the end of this inline declaration for compile-time 
// errors to go away. 
template <typename Data>
BSTNode<Data>::BSTNode(const Data &d) : left(0), right(0), parent(0), data(d) {}

/* Returns a pointer to the BSTNode that contains the item that is sequentially next 
 * in the tree 
 */
template <typename Data>
BSTNode<Data>* BSTNode<Data>::successor()
{
  // If there is a node to the right then the successor is to the right somewhere.
  // This code finds that successor.
  BSTNode<Data>* currNode = 0;

  if (right) {
    currNode = right;
    while (currNode->left) {
      currNode = currNode->left;
    }
    return currNode;
  }

  // This is testing to see if the node being visited is the last sequencially.
  if (!parent) {
    return 0;
  }

  currNode = parent;
  while(data > currNode->data) {
    currNode = currNode->parent;
    if (currNode->data > data) {
      return currNode;
    }
    if (currNode->parent == 0) 
      return 0;
  }

  if (data < parent->data) {
    return parent;
  }

  return 0;
}

/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
