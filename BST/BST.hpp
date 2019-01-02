#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>

/* Template-based BST class header and class definition file. 
 * Author: Christopher Jensen
 */

template<typename Data>
class BST {

public:

  // define iterator as an aliased typename for BSTIterator<Data>
  typedef BSTIterator<Data> iterator;

  BST() : root(nullptr), isize(0) {}

  // Deletes every node in this BST
  ~BST();

  /** Inserts Data item reference into this BST.
   *  Returns a pair -- first element is an iterator pointing to the newly
   *  inserted node or the node that already contains the item, second 
   *  element is a bool which is true if the Data item was inserted of 
   *  false if it was already in the BST. Function only uses '<' operator
   *  when comparing Data items. 
   */

  std::pair<iterator, bool> insert(const Data &item);

  /** Finds a Data item in the BST.
   *  Returns an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   */
  iterator find(const Data &item) const;
  
  // Returns the number of items currently in the BST. 
  unsigned int size() const;
  
  /** Returns the height of the BST.
   *  The height of a tree starts with root at height 0
	 *  The height of an empty tree is -1
   */ 
  int height() const;

  // Returns true if the BST is empty, else false. 
  bool empty() const;

  // Returns an iterator pointing to the first (smallest) item in the BST.
  iterator begin() const;

  // Return an iterator pointing past the last item in the BST.
  iterator end() const;


private:

  // Helper function for finding deepest node
  void deepHelper(const BSTNode<Data> *node, int level, int &greatestLevel, Data &data) const;
  
  // Returns the deepest node's data member.
  Data deepestNode(const BSTNode<Data>* someNode) const;

  // Return the height of the deepest node as an int.
  int findHeightOfNode(const Data& item) const;

  // Pointer to the root of this BST, or 0 if the BST is empty 
  BSTNode<Data> *root;
  
  // Number of Data items stored in this BST. 
  unsigned int isize;

  // Returns node pointer to the first element of the BST. 
  static BSTNode<Data>* first(BSTNode<Data> *root);

  // Does a postorder traversal, and deletes all nodes
  static void deleteAll(BSTNode<Data> *n);
 };

// ********** Function definitions ****************

// Default destructor. Deletes every node in this BST.
template <typename Data>
BST<Data>::~BST() {
  if (isize) {
    deleteAll(root);
  }
}

template <typename Data>
std::pair<BSTIterator<Data>, bool> BST<Data>::insert(const Data &item) {
  BSTNode<Data>* curr = root;

  // if BST is empty, create root node with data
  if (!root) { 
    root = new BSTNode<Data>(item);
    isize++;
    return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(root), true);
  }
  
  while(true) {
    Data currData = curr->data;
    if (item < currData) {
      if (curr->left) 
        curr = curr->left;
      else {
        BSTNode<Data>* newNode = new BSTNode<Data>(item);
        curr->left = newNode;
        newNode->parent = curr;
        isize++;
        return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(curr->left), true);
      }
    }
    else if (currData < item) {
      if (curr->right) 
        curr = curr->right;
      else {
        BSTNode<Data>* newNode = new BSTNode<Data>(item);
        curr->right = newNode;
        newNode->parent = curr;
        isize++;
        return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(curr->right), true);
      }
    }
    else 
      return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(curr), false);  
  }
}

template <typename Data>
BSTIterator<Data> BST<Data>::find(const Data &item) const
{
  BSTNode<Data>* curr = root;

  if (!root) {
    return BSTIterator<Data>(nullptr);
  }

  while(true) {
    Data currData = curr->data;
    if (item < currData){
      if (curr->left)
        curr = curr->left;
      else
        return BSTIterator<Data>(nullptr);
    }
    else if (currData < item) {
      if (curr->right) 
        curr = curr->right;
      else
        return BSTIterator<Data>(nullptr);
    }
    else
      return BSTIterator<Data>(curr);
  }
}
  
// Returns the number of items currently in the BST. 
template <typename Data>
unsigned int BST<Data>::size() const
{
  return isize;
}

// Returns height of BST
template <typename Data> 
int BST<Data>::height() const
{
  if (!isize) {
    return -1;
  }
  else if (isize == 1) {
    return 0;
  }
  
  Data deepest = deepestNode(root);
  return findHeightOfNode(deepest); 
}

template <typename Data>
void BST<Data>::deepHelper(const BSTNode<Data> *node, int level, int &greatestLevel, Data &data) const
{
  if (node) {
    deepHelper(node->left, ++level, greatestLevel, data);

    if (greatestLevel < level) {
      greatestLevel = level; 
      data = node->data;
    }

    deepHelper(node->right, level, greatestLevel, data);
  }
}

/* Helper function for height().
 * Takes in a BSTNode pointer and returns a constant reference to 
 * the deepest node's data member variable
 */
template <typename Data>
Data BST<Data>::deepestNode(const BSTNode<Data> *someNode) const
{
  Data data = someNode->data;
  int greatestLevel = -1;

  deepHelper(someNode, 0, greatestLevel, data);
  return data;
}

/* Another helper function for height().
 * Takes in a constant reference to a node's data member variable 
 * and returns the height of that node in the tree 
 */
template <typename Data>
int BST<Data>::findHeightOfNode(const Data &item) const
{
  int heightOfDeepestNode = 0;
  BSTNode<Data>* curr = root;
  while (curr) {
    if (curr->data < item) {
      curr = curr->right;
      heightOfDeepestNode++;
    }
    else if (item < curr->data) {
      curr = curr->left;
      heightOfDeepestNode++;
    }
    else {
      return heightOfDeepestNode;
    }
  }
  return heightOfDeepestNode;
}


// Returns true if the BST is empty, else false. 
template <typename Data>
bool BST<Data>::empty() const
{
  if (isize == 0){ 
    return true;
  }
  else {
    return false;
  }
}

// Returns an iterator pointing to the first (smallest) item in the BST.
template <typename Data>
BSTIterator<Data> BST<Data>::begin() const
{
  return BSTIterator<Data>(first(root));
}

// Returns an iterator pointing past the last item in the BST.
template <typename Data>
BSTIterator<Data> BST<Data>::end() const
{
  return BSTIterator<Data>(nullptr);
}

/** Finds the first element of the BST.
 *  Helper function for the begin method above.
 */ 
template <typename Data>
BSTNode<Data>* BST<Data>::first(BSTNode<Data>* root)
{
  BSTNode<Data>* curr = root;
  while (curr->left) {
      curr = curr->left;
  }
  return curr;
}

// Does a postorder traversal, deletes all nodes in this BST
template <typename Data>
void BST<Data>::deleteAll(BSTNode<Data>* n)
{
   if (n->left) {
     deleteAll(n->left);
   }
   if (n->right) {
     deleteAll(n->right);
   }
   delete n;
}

#endif //BST_HPP