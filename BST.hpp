#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>
using namespace std;

/** NAME: Robin Heinonen
  * DATE: 10/11/17
  * PID: A53091242
  * DESCRIPTION: binary search tree class definition
  * PA1 CSE 100 2017
  * Based on code by Christine Alvarado
  */
template<typename Data>
class BST {

public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
      This is inlined because it is trivial.
   */
  BST() : root(nullptr), isize(0) {}


  /** Default destructor.
      Delete every node in this BST.
  */
  ~BST();

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return a pair where the first element is an iterator
   *  pointing to either the newly inserted element or the element
   *  that was already in the BST, and the second element is true if the
   *  element was newly inserted or false if it was already in the BST.
   *
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=)
   */
  std::pair<iterator, bool> insert(const Data& item);


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=).  For the reasoning
   *  behind this, see the assignment writeup.
   */
  iterator find(const Data& item) const;


  /** Return the number of items currently in the BST.
   */
  unsigned int size() const;

  /** Return the height of the BST.
      height of a tree starts with root at height 0
   */
  unsigned int height() const;


  /** Return true if the BST is empty, else false.
   */ // TODO
  bool empty() const;

  /** Return an iterator pointing to the first (smallest) item in the BST.
   */
  iterator begin() const;

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const;

  /** do a pre-order traversal and print data of each node */

  void print() const;

private:

  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;

  /** recursive helper function for height */
  static int heightHelper(BSTNode<Data>* node);

  /** Find the first element of the BST
   * Helper function for the begin method above.
   */
  static BSTNode<Data>* first(BSTNode<Data>* root);

  /** do a postorder traversal, deleting nodes
   */
  static void deleteAll(BSTNode<Data>* n);

  /** preorder traversal. recursive helper for print() */
  static void preorder(BSTNode<Data>* n);
 };


// ********** Function definitions ****************


/** Default destructor.
    Delete every node in this BST.
*/
template <typename Data>
BST<Data>::~BST() {
  deleteAll(root);
}


/** Given a reference to a Data item, insert a copy of it in this BST.
 *  Return a pair where the first element is an iterator pointing to either the newly inserted
 *  element or the element that was already in the BST, and the second element is true if the
 *  element was newly inserted or false if it was already in the BST.
 *
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=)
 */
template <typename Data>
std::pair<BSTIterator<Data>, bool> BST<Data>::insert(const Data& item) {
  if(root==nullptr)
  {
    BSTNode<Data>* newNode=new BSTNode<Data>(item);
    root=newNode;
    isize++;
    return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(root), true);
  }
  BSTNode<Data>* currNode=root;

  while(currNode->data!=item)
  {
    if(item < currNode->data)
    {
      if(currNode->left==nullptr)
      {
        BSTNode<Data>* newNode=new BSTNode<Data>(item);
        currNode->left=newNode;
        newNode->parent=currNode;
        isize++;
        return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(currNode->left), true);
      }
      currNode=currNode->left;
    }

    else if(item > currNode->data)
    {
      if(currNode->right==nullptr)
      {
        BSTNode<Data>* newNode=new BSTNode<Data>(item);
        currNode->right=newNode;
        newNode->parent=currNode;
        isize++;
        return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(currNode->right), true);
      }
      currNode=currNode->right;
    }
  }
  return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(currNode), false);
}


/** Find a Data item in the BST.
 *  Return an iterator pointing to the item, or pointing past
 *  the last node in the BST if not found.
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=).  For the reasoning
 *  behind this, see the assignment writeup.
 */
template <typename Data>
BSTIterator<Data> BST<Data>::find(const Data& item) const
{
  if(root==nullptr)
  {
    return BSTIterator<Data>(nullptr);
  }

  BSTNode<Data>* currNode=root;

  while(currNode->data!=item)
  {
    if(item < currNode->data)
    {
      if(currNode->left==nullptr)
      {
        return BSTIterator<Data>(nullptr);
      }
      currNode=currNode->left;
    }

    else if(item > currNode->data)
    {
      if(currNode->right==nullptr)
      {
        return BSTIterator<Data>(nullptr);
      }
      currNode=currNode->right;
    }
  }
  return BSTIterator<Data>(currNode);

}


/** Return the number of items currently in the BST.
 */
template <typename Data>
unsigned int BST<Data>::size() const
{
  return isize;
}

/**
 * recursive helper method for height()
 */
template <typename Data>
int BST<Data>::heightHelper(BSTNode<Data>* node)
{
  if(node==nullptr)
    return 0;
  int leftHeight=heightHelper(node->left);
  int rightHeight=heightHelper(node->right);
  return std::max(leftHeight, rightHeight)+1;
}

/** Return the height of the BST.
 */
template <typename Data>
unsigned int BST<Data>::height() const
{
  if(root==nullptr)
    return 0;
  return heightHelper(root)-1;
}


/** Return true if the BST is empty, else false.
 */
template <typename Data>
bool BST<Data>::empty() const
{
  if(root==nullptr)
    return true;
  return false;
}

/** Return an iterator pointing to the first (smallest) item in the BST.
 */
template <typename Data>
BSTIterator<Data> BST<Data>::begin() const
{
  return BSTIterator<Data>(first(root));
}

/** Return an iterator pointing past the last item in the BST.
 */
template <typename Data>
BSTIterator<Data> BST<Data>::end() const
{
  return BSTIterator<Data>(nullptr);
}

/** Find the first element of the BST
 * Helper function for the begin method above.
 */
template <typename Data>
BSTNode<Data>* BST<Data>::first(BSTNode<Data>* root)
{
  BSTNode<Data>* currNode=root;
  while(currNode->left!=nullptr)
  {
    currNode=currNode->left;
  }
  return currNode;
}

/** do a postorder traversal, deleting nodes
 */
template <typename Data>
void BST<Data>::deleteAll(BSTNode<Data>* n)
{
  if(n==nullptr)
    return;
  deleteAll(n->left);
  deleteAll(n->right);
  delete n;
}

/** do a pre-order traversal and cout each node */
template <typename Data>
void BST<Data>::print() const
{
  return preorder(root);
}

/** preorder traversal. recursive helper for print() */
template <typename Data>
void BST<Data>::preorder(BSTNode<Data>* n)
{
  if(n==nullptr)
    return;
  cout << n->data << endl;
  preorder(n->left);
  preorder(n->right);
}

#endif //BST_HPP
