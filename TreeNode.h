#include <iostream>

template <typename K, typename V>

class TreeNode {

private:
  K key;
  V value;

public:
  TreeNode<K, V>* left;
  TreeNode<K, V>* right;

  TreeNode() {

    left = NULL;
    right = NULL;

  }

  TreeNode(K key) {

    this->key = key;
    this->value = key;
    left = NULL;
    right = NULL;

  }

  TreeNode(K key, V value) {

    this->key = key;
    this->value = value;
    left = NULL;
    right = NULL;

  }

  virtual ~TreeNode() {
  }

  void setKey(K key) {

    this->key = key;

  }

  const K& getKey() {

    return this->key;

  }

  void setValue(V value) {

    this->value = value;

  }

  const V& getValue() {

    return this->value;

  }

};
