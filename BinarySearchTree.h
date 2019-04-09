#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "TreeNode.h"
#include <iostream>
#include "TreeEmptyException.h"
#include "NodeNotFoundInTreeException.h"
#include "NodeAlreadyExistsInTreeException.h"

template <typename K, typename V>

class BinarySearchTree {

private:
  TreeNode<K, V>* root;
  unsigned int size;

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

  TreeNode<K, V>* getSuccessor(TreeNode<K, V>* nodeToDelete) {

    //gets the inorder successor, which is really the leftmost node in the right subtree rooted at the right child of the nodeToDelete

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

  BinarySearchTree() {

    root = NULL;

  }

  BinarySearchTree(K rootKey) {

    root = new TreeNode<K, V>(rootKey, rootKey);

  }

  BinarySearchTree(K rootKey, V rootValue) {

    root = new TreeNode<K, V>(rootKey, rootValue);

  }

  virtual ~BinarySearchTree() {

    if (empty() == false) {

      deleteAll(root);
      std::cout<<empty()<<std::endl;

    }

  }

  TreeNode<K, V>* getRoot() {

    return root;

  }

  void inOrderPrint(TreeNode<K, V>* node) {

    if (node != NULL) {

      inOrderPrint(node->left);
      std::cout<<"Key: "<<node->getKey()<<" | Value: "<<node->getValue()<<std::endl;
      inOrderPrint(node->right);

    }

  }

  K sumUpKeys(TreeNode<K, V>* node) {

    K sum = 0;

    if (node != NULL) {

      sum += sumUpKeys(node->left);
      sum += node->getKey();
      sum += sumUpKeys(node->right);

    }

    return sum;

  }

  K sumUpValues(TreeNode<K, V>* node) {

    K sum = 0;

    if (node != NULL) {

      sum += sumUpKeys(node->left);
      sum += node->getValue();
      sum += sumUpKeys(node->right);

    }

    return sum;

  }

  unsigned int height(K keyOfNodeToGetHeightOf) throw(NodeNotFoundInTreeException){

    TreeNode<K, V>* nodeToGetHeightOf = root;

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
      //unsigned int leftHeight = 1 + height(nodeToGetHeightOf->left->getKey());
      //unsigned int rightHeight = 1 + height(nodeToGetHeightOf->right->getKey());

      if (leftHeight > rightHeight) {

        return leftHeight;

      }

      return rightHeight;

    }

  }

  unsigned int depth(K keyOfNodeToGetDepthOf) throw(NodeNotFoundInTreeException){

    unsigned int depth = 0;

    if (find(keyOfNodeToGetDepthOf)) {

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

  bool find(K keyOfNodeToFind) {

    if (empty()) {

      return false;

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
          return true;

        }

      }

      //the node was not found since the loop above went all the way to a leaf:
      return false;

    }

  }

  void erase(K keyOfNodeToDelete) throw(NodeNotFoundInTreeException){

    if (empty()) {

      //throw a tree is empty exception:
      throw NodeNotFoundInTreeException("Exception: cannot erase a node that does not exist in the tree.");

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
        //throw a node not found in tree exception
        return;

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

            root = nodeToDelete->right;

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

            //the nodeToDelete is a left child of the parentOfNodeToDelete, set the left child of parentOfNodeToDelete to point to the left child of the nodeToDelete:
            parentOfNodeToDelete->left = nodeToDelete->left;

          }
          else {

            //the nodeToDelete is a right child of the parentOfNodeToDelete, set the right child of parentOfNodeToDelete to point to the left child of the nodeToDelete:
            parentOfNodeToDelete->right = nodeToDelete->left;

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

          successor->left = nodeToDelete->left;
          delete nodeToDelete;

        }

      }

    }

  }

  void insert(K key, V value) throw(NodeAlreadyExistsInTreeException){

    if (find(key)) {

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

  const unsigned int& getSize() {

    return size;

  }

  bool empty() {

    return (root == NULL);

  }

};

#endif
