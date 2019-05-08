#include "BST.hpp"
#include "BSTIterator.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;
/** NAME: Robin Heinonen
  * DATE: 10/11/17
  * PID: A53091242
  * DESCRIPTION: A test driver for the BST int class and class template.
  * PA1 CSE 100 2017
  * Based on code by Christine Alvarado
  * TODO: Add more tests
  */
int main() {

    /* Create an STL vector of some ints */
    /*test*/
    vector<int> v;
    v.push_back(3);
    v.push_back(4);
    v.push_back(1);
    v.push_back(2);
    v.push_back(100);
    v.push_back(-33);
    v.push_back(10);

    /* UNCOMMENT THE LINES BELOW TO TEST THE TEMPLATE-BASED ITERATOR */


    // Test the template version of the BST  with ints
    BST<int> btemp;
    for (int item : v) {
        // The auto type here is the pair of BSTIterator<int>, bool
        cout << "Inserting " << item << " into the int template-based BST...";
        auto p = btemp.insert(item);
        if (*(p.first) != item) {
            cout << "Wrong iterator returned.  "
                 << "Expected " << item << " but got " << *(p.first) << endl;
            return -1;
        }
        if (!p.second) {
            cout << "Wrong boolean returned.  Expected true but got "
                 << p.second << endl;
            return -1;
        }
        cout << "success!" << endl;

    }

    // Now test finding the elements we just put in
    for (int item: v) {
        cout << "Finding " << item << "...." << endl;
        BSTIterator<int> foundIt = btemp.find(item);
        if (*(foundIt) != item) {
            cout << "incorrect value returned.  Expected iterator pointing to "
                 << item << " but found iterator pointing to " << *(foundIt)
                 << endl;
            return -1;
        }
        cout << "success!" << endl;
    }



    // Test the iterator: The iterator should give an in-order traversal

    // Sort the vector, to compare with inorder iteration on the BST
    sort(v.begin(),v.end());

    cout << "traversal using iterator..." << endl;
    auto vit = v.begin();
    auto ven = v.end();

    // This is equivalent to BSTIterator<int> en = btemp.end();
    auto en = btemp.end();

    //This is equivalent to BST<int>::iterator it = btemp.begin();
    auto it = btemp.begin();
    for(; vit != ven; ++vit) {
        if(! (it != en) ) {
            cout << *it << "," << *vit
                 << ": Early termination of BST iteration." << endl;
            return -1;

        }
        cout << *it << endl;
        if(*it != *vit) {
            cout << *it << "," << *vit
                 << ": Incorrect inorder iteration of BST." << endl;
            return -1;
        }
        ++it;
        cout << "success!" << endl;
    }



    //attempt to insert already existing elements
    for(int item: v){
      cout<<"attempting to insert " <<item << " again...." << endl;
      auto p = btemp.insert(item);
      if (*(p.first)!=item){
        cout << "Wrong iterator returned. Expected iterator pointing to "
          << item<< ", returned iterator pointing to " << *(p.first) <<endl;
        return -1;
      }
      if(p.second){
        cout << "Wrong boolean returned. Expected false but got" << p.second
          << endl;
        return -1;
      }
      cout << "success!" << endl;
    }

    //test height function, size function, empty function
    BST<string> empty;
    BST<string> one;
    one.insert("root");
    if(empty.height()!=0)
    {
      cout << "incorrect height of empty. expected 0 but got "<< empty.height()
        << endl;
      return -1;
    }

    if(one.height()!=0)
    {
      cout << "incorrect height of singleton. expected 0 but got "<< one.height()
        << endl;
      return -1;
    }

    if(btemp.height()!=3)
    {
      cout << "incorrect height of large bst. expected 3 but got "<< btemp.height()
        << endl;
      cout << "displaying BST..." << endl;
      btemp.print();
      return -1;
    }

    if(empty.size()!=0)
    {
      cout << "incorrect size of empty. expected 0 but got "<< empty.size()
        << endl;
      return -1;
    }

    if(one.size()!=1)
    {
      cout << "incorrect size of singleton. expected 1 but got "<< one.size()
        << endl;
      return -1;
    }

    if(btemp.size()!=7)
    {
      cout << "incorrect size of large bst. expected 7 but got "<< btemp.size()
        << endl;
      return -1;
    }

    if(!empty.empty())
    {
      cout << "Empty bst found to be non-empty." << endl;
      return -1;
    }

    if(one.empty())
    {
      cout << "singleton found to be empty." << endl;
      return -1;
    }

    if(btemp.empty())
    {
      cout << "large bst found to be empty."<< endl;
      return -1;
    }

    cout << "Size(), height(), and empty() passed." << endl;

    //search for nonexistent element
    BSTIterator<int> findBig=btemp.find(-1);
    BSTIterator<string> findEmpty=empty.find("nope");
    BSTIterator<string> findOne=one.find("nope");
    if(findBig!=nullptr)
    {
      cout << "error: found -1 in large BST, returned " << *findBig << endl;
      return -1;
    }

    if(findEmpty!=nullptr)
    {
      cout << "error: found nope in empty BST, returned " << *findEmpty << endl;
      return -1;
    }

    if(findOne!=nullptr)
    {
      cout << "error: found nope in singleton BST, returned " << *findOne << endl;
      return -1;
    }

    cout << "All tests passed!" << endl;
    return 0;
}
