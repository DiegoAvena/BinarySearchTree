#include "BinarySearchTree.h"
#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {

  BinarySearchTree<int, int> tree(20);
  tree.insert(10, 10);
  tree.insert(25, 25);
  tree.insert(15, 15);
  tree.insert(30, 30);
  tree.insert(22, 22);
  tree.insert(21, 21);
  tree.inOrderPrint(tree.getRoot());
  cout<<"The height of the tree is: "<<tree.height(tree.getRoot()->getKey())<<endl;
  tree.erase(20);
  cout<<"After erasing 20..."<<endl;
  tree.inOrderPrint(tree.getRoot());

  cout<<endl;
  cout<<"The sum of all the keys in the tree is: "<<tree.sumUpKeys(tree.getRoot())<<endl;
  cout<<"The sum of all the values in the tree is: "<<tree.sumUpValues(tree.getRoot())<<endl;
  cout<<"The height of the tree is: "<<tree.height(tree.getRoot()->getKey())<<endl;
  cout<<"The depth of the node with key 30 is: "<<tree.depth(30)<<endl;

  try {

    tree.height(100);

  }
  catch (NodeNotFoundInTreeException exception) {

    cout<<exception.getErrorMessage()<<endl;

  }

  return 0;

}
