#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "TreeNode.h"
#include <iostream>
#include "TreeEmptyException.h"
#include "NodeNotFoundInTreeException.h"
#include "NodeAlreadyExistsInTreeException.h"

template <typename K, typename V>

/*

-A data structure that stores nodes with both a key and value. Each node has a left and right child, which can be null (called leaves).
These nodes are sorted by their keys: nodes with keys greater than the keys of other nodes in the tree are stored on the left
and nodes with keys greater than other nodes are stored on the right. This tree does not balance itself.

*/
class BinarySearchTree {

protected:
  TreeNode<K, V>* root; //the root node of this tree
  unsigned int size; //the amount of nodes in this tree

  //traverses the tree and deletes every node, used by the destructor
  TreeNode<K, V>* deleteAll(TreeNode<K, V>* nodeToRemove) {

    if (nodeToRemove->left != NULL) {

      nodeToRemove->left = deleteAll(nodeToRemove->left);

    }

    if (nodeToRemove->right != NULL) {

      nodeToRemove->right = deleteAll(nodeToRemove->right);

    }

    delete nodeToRemove;
    return NULL;

  }

  //gets the inorder successor, which is really the leftmost node in the right subtree rooted at the right child of a node that is being deleted
  TreeNode<K, V>* getSuccessor(TreeNode<K, V>* nodeToDelete) {

    TreeNode<K, V>* successorParent = nodeToDelete;
    TreeNode<K, V>* successor = nodeToDelete;
    TreeNode<K, V>* currentNode = nodeToDelete->right;

    while (currentNode != NULL) {

      successorParent = successor;

      //there is another child on the left, update to this one now:
      successor = currentNode;

      //go left to check if there is another left child:
      currentNode = currentNode->left;

    }

    /*

    -Check if the successor is a descendent of the right child
    of the nodeToDelete, in which case this means that the right child of the nodeToDelete
    had a left child that potentially has a right child that needs to be moved up:

    */
    if (successor != nodeToDelete->right) {

      //successor is a descendent of the right child of the nodeToDelete:
      successorParent->left = successor->right;
      successor->right = nodeToDelete->right;

    }

    return successor;

  }

public:

  //default constructor
  BinarySearchTree() {

    root = NULL;

  }

  //overloaded constructor, sets the root key and value to the same thing
  BinarySearchTree(K rootKey) {

    root = new TreeNode<K, V>(rootKey, rootKey);

  }

  //overloaded constructor, sets the root key and value to seperate dataTypes
  BinarySearchTree(K rootKey, V rootValue) {

    root = new TreeNode<K, V>(rootKey, rootValue);

  }

  //destructor
  virtual ~BinarySearchTree() {

    //delete every node in the tree
    if (empty() == false) {

      deleteAll(root);

    }

  }

  //returns a reference to the root node
  TreeNode<K, V>* getRoot() const {

    return root;

  }

  //prints every node in the tree sorted by increasing key value
  void inOrderPrint(TreeNode<K, V>* node) {

    if (node != NULL) {

      inOrderPrint(node->left);
      std::cout<<"Key: "<<node->getKey()<<" | Value: "<<node->getValue()<<std::endl;
      inOrderPrint(node->right);

    }

  }

  //sums up the keys in the tree and returns that value, only for use with numerical keys
  K sumUpKeys(TreeNode<K, V>* node) {

    K sum = 0;

    if (node != NULL) {

      sum += sumUpKeys(node->left);
      sum += node->getKey();
      sum += sumUpKeys(node->right);

    }

    return sum;

  }

  //sums up the values in the tree, only for use with numerical values
  K sumUpValues(TreeNode<K, V>* node) {

    K sum = 0;

    if (node != NULL) {

      sum += sumUpKeys(node->left);
      sum += node->getValue();
      sum += sumUpKeys(node->right);

    }

    return sum;

  }

  //gets the height of the given node, which is the max depth of that node: https://www.geeksforgeeks.org/write-a-c-program-to-find-the-maximum-depth-or-height-of-a-tree/
  unsigned int height(K keyOfNodeToGetHeightOf) throw(NodeNotFoundInTreeException){

    TreeNode<K, V>* nodeToGetHeightOf = root;

    //find the node to get the height of
    while (nodeToGetHeightOf != NULL) {

      if (keyOfNodeToGetHeightOf < nodeToGetHeightOf->getKey()) {

        //go left:
        nodeToGetHeightOf = nodeToGetHeightOf->left;

      }
      else if (keyOfNodeToGetHeightOf > nodeToGetHeightOf->getKey()) {

        //go right:
        nodeToGetHeightOf = nodeToGetHeightOf->right;

      }
      else {

        //node found:
        break;

      }

    }

    if (nodeToGetHeightOf == NULL) {

      throw NodeNotFoundInTreeException("Exception: Cannot take the height of a node that does not exist in the tree.");

    }
    else {

      unsigned int leftHeight;
      unsigned int rightHeight;

      if (nodeToGetHeightOf->left == NULL) {

        leftHeight = 1;
      }
      else {

         leftHeight = 1 + height(nodeToGetHeightOf->left->getKey());

      }

      if (nodeToGetHeightOf->right == NULL) {

        rightHeight = 1;

      }
      else {

        rightHeight = 1 + height(nodeToGetHeightOf->right->getKey());

      }

      if (leftHeight > rightHeight) {

        return leftHeight;

      }

      return rightHeight;

    }

  }

  //gets the depth of a node in the tree, which is the number of ancestors a node has
  unsigned int depth(K keyOfNodeToGetDepthOf) throw(NodeNotFoundInTreeException){

    unsigned int depth = 0;

    if (find(keyOfNodeToGetDepthOf) != NULL) {

      //the node to get the depth of is in the tree:
      TreeNode<K, V>* node = root;

      while (node->getKey() != keyOfNodeToGetDepthOf) {

        depth++;

        if (keyOfNodeToGetDepthOf < node->getKey()) {

          //go left:
          node = node->left;

        }
        else {

          //go right:
          node = node->right;

        }

      }

      return depth;

    }
    else {

      throw NodeNotFoundInTreeException("Exception: cannot find the depth of a node that is not in the tree.");

    }

  }

  //finds a node in the tree
  TreeNode<K, V>* find(K keyOfNodeToFind) {

    if (empty()) {

      return NULL;

    }
    else {

      TreeNode<K, V>* node = root;

      while (node != NULL) {

        if (keyOfNodeToFind < node->getKey()) {

          //go left:
          node = node->left;

        }
        else if (keyOfNodeToFind > node->getKey()) {

          //go right:
          node = node->right;

        }
        else {

          //the node must have been found, return true:
          return node;

        }

      }

      //the node was not found since the loop above went all the way to a leaf:
      return NULL;

    }

  }

  //erases a node from the tree
  void erase(K keyOfNodeToDelete) throw(NodeNotFoundInTreeException, TreeEmptyException){

    if (empty()) {

      //throw a tree is empty exception:
      throw TreeEmptyException("Exception: cannot delete nodes from an empty tree");

    }
    else {

      //find the node to delete in the tree:
      TreeNode<K, V>* parentOfNodeToDelete = NULL;
      TreeNode<K, V>* nodeToDelete = root;
      bool nodeToDeleteIsALeftChild = false;

      while (nodeToDelete != NULL) {

        if (keyOfNodeToDelete < nodeToDelete->getKey()) {

          //go left:
          parentOfNodeToDelete = nodeToDelete;
          nodeToDelete = nodeToDelete->left;
          nodeToDeleteIsALeftChild = true;


        }
        else if (keyOfNodeToDelete > nodeToDelete->getKey()) {

          //go right:
          parentOfNodeToDelete = nodeToDelete;
          nodeToDelete = nodeToDelete->right;
          nodeToDeleteIsALeftChild = false;

        }
        else {

          //we found the node that needs to be deleted:
          break;

        }

      }

      if (nodeToDelete == NULL) {

        //the node to be deleted was not found in the tree:
        throw NodeNotFoundInTreeException("Exception: cannot erase a node that does not exist in the tree.");

      }
      else {

        //time to delete:

        if (nodeToDelete->left == NULL && nodeToDelete->right == NULL) {

          //case 1: the node to be deleted has no children, in which case it can simply be deleted:
          if (nodeToDelete == root) {

            root = NULL;

          }
          else if (nodeToDeleteIsALeftChild) {

            parentOfNodeToDelete->left = NULL;

          }
          else {

            parentOfNodeToDelete->right = NULL;

          }

          delete nodeToDelete;

        }
        else if ((nodeToDelete->left != NULL) && (nodeToDelete->right == NULL)) {

          //case 2: the node to be deleted has a left child:
          if (nodeToDelete == root) {

            root = nodeToDelete->left;

          }
          else if (nodeToDeleteIsALeftChild) {

            //the node to delete is a left child of the parentOfNodeToDelete
            //set the parents left child to the left child of the nodeToDelete, so that essentially this left child is moved up
            parentOfNodeToDelete->left = nodeToDelete->left;

          }
          else {

            //the nodeToDelete is a right child of the parentOfNodeToDelete
            //set the parents right child to the left child of the nodeToDelete, so that essentially this left child is moved up
            parentOfNodeToDelete->right = nodeToDelete->left;

          }

          delete nodeToDelete;

        }
        else if ((nodeToDelete->left == NULL) && (nodeToDelete->right != NULL)) {

          //case 3: the node to be deleted has a right child:
          if (nodeToDelete == root) {

            //set the root to point to its right child
            root = nodeToDelete->right;

          }
          else if (nodeToDeleteIsALeftChild) {

            //the nodeToDelete is a left child of the parentOfNodeToDelete, set the left child of parentOfNodeToDelete to point to the right child of the nodeToDelete:
            parentOfNodeToDelete->left = nodeToDelete->right;

          }
          else {

            //the nodeToDelete is a right child of the parentOfNodeToDelete, set the right child of parentOfNodeToDelete to point to the right child of the nodeToDelete:
            parentOfNodeToDelete->right = nodeToDelete->right;

          }

        }
        else {

          //case 3: the nodeToDelete has 2 children, need to find the inorder successor (can also use inorder predecessor) and set the nodeToDelete to this, and update pointers correctly:
          TreeNode<K, V>* successor = getSuccessor(nodeToDelete);

          if (nodeToDelete == root) {

            root = successor;

          }
          else if (nodeToDeleteIsALeftChild) {

            parentOfNodeToDelete->left = successor;

          }
          else {

            parentOfNodeToDelete->right = successor;

          }

          successor->left = nodeToDelete->left; //the left node of the sucessor is always null, so it is safe to do this, and necessary to preserve the left child of the node being deleted
          delete nodeToDelete;

        }

      }

    }

  }

  //inserts a node into the tree
  void insert(K key, V value) throw(NodeAlreadyExistsInTreeException){

    if (find(key) != NULL) {

      //throw a node already exists in tree exception:
      throw NodeAlreadyExistsInTreeException("Exception: cannot put a node that already exists into tree");

    }
    else if (empty()) {

      //set the root to the new node being inserted:
      root = new TreeNode<K, V>(key, value);
      size++;

    }
    else {

      //find a leaf node, this is where the new node needs to be placed at:
      TreeNode<K, V>* nodeToInsertNewNodeAt = root;
      TreeNode<K, V>* parentOfNodeToInsertNewNodeAt = NULL;
      TreeNode<K, V>* newNodeToInsert = new TreeNode<K, V>(key, value);

      while (true) {

        parentOfNodeToInsertNewNodeAt = nodeToInsertNewNodeAt;

        if (key < nodeToInsertNewNodeAt->getKey()) {

          //go left:
          nodeToInsertNewNodeAt = nodeToInsertNewNodeAt->left;

          if (nodeToInsertNewNodeAt == NULL) {

            //at a leaf node on the left of parentOfNodeToDelete, insert new node here:
            parentOfNodeToInsertNewNodeAt->left = newNodeToInsert;
            break;

          }

        }
        else if (key > nodeToInsertNewNodeAt->getKey()) {

          //go right:
          nodeToInsertNewNodeAt = nodeToInsertNewNodeAt->right;

          if (nodeToInsertNewNodeAt == NULL) {

            //we are at a leaf node on the right of parentOfNodeToDelete, insert new node here:
            parentOfNodeToInsertNewNodeAt->right = newNodeToInsert;
            break;

          }

        }

      }

      size++;

    }

  }

  //gets the node with the smallest key in the tree, which is really just the leftmost node in the tree
  const TreeNode<K, V>* min() throw(TreeEmptyException){

    if (empty()) {

      //throw a treeIsEmptyException
      throw TreeEmptyException("Exception: cannot find the min of an empty tree");

    }
    else {

      //find the minimum node based on the key value, this will be the leftmost node in the tree:
      TreeNode<K, V>* node = root;

      while (node->left != NULL) {

        //keep going left:
        node = node->left;

      }

      return node;

    }

  }

  //gets the node with the max key in the tree, which is really just the rightmost node in the tree
  const TreeNode<K, V>* max() throw(TreeEmptyException){

    if (empty()) {

      //throw a treeIsEmptyException
      throw TreeEmptyException("Exception: cannot find the max of an empty tree");

    }
    else {

      //find the maximum node based on the key value, this will be the rightmost node in the tree:
      TreeNode<K, V>* node = root;

      while (node->right != NULL) {

        //keep going right:
        node = node->right;

      }

      return node;

    }

  }

  //returns the number of nodes currently in the tree
  const unsigned int& getSize() {

    return size;

  }

  //checks if the tree is empty
  bool empty() {

    return (root == NULL);

  }

};

#endif
