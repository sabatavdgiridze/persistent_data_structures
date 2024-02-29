#include <iostream>

#include <vector>
#include <utility>
#include <algorithm>

class Node {
public:
  int value;
  std::vector<std::pair<int, Node*>> left, right;
  
  Node(int timestamp, int value, Node *left, Node *right) {
    this->value = value;

    (this->left).push_back(std::make_pair(timestamp, nullptr));
    (this->right).push_back(std::make_pair(timestamp, nullptr));
  }

  Node *get_last_left() {
    if ((this->left).size() == 0) {
      return nullptr;
    }
    return ((this->left)[(this->left).size() - 1]).second;
  }
  Node *get_last_right() {
    if ((this->right).size() == 0) {
      return nullptr;
    }
    return ((this->right)[(this->right).size() - 1]).second;
  }
};

class Tree {
public:
  Node *root;
  int current_version;

  Tree() {
    this->root = nullptr;
    this->current_version = 0;
  }
  void insert(int value) {
    this->current_version++;
    this->root = insert(this->root, this->current_version, value);
  }
  bool find(int timestamp, int value) {
    return find(this->root, timestamp, value);
  }
private:
  Node *insert(Node *node, int timestamp, int value) {
    if (node == nullptr) {
      return new Node(timestamp, value, nullptr, nullptr);
    } else {
      if (value < node->value) {

        node->left.push_back(std::make_pair(timestamp, insert(node->get_last_left(), timestamp, value)));
      } else { // value > node->value
        node->right.push_back(std::make_pair(timestamp, insert(node->get_last_right(), timestamp, value)));
      }
      return node;
    }
  }

  bool find(Node *node, int timestamp, int value) {
    if (node == nullptr) {
      return false;
    } else {
      if (node->value == value) {
        return true;
      } else {
        if (value < node->value) {
          auto it = std::upper_bound((node->left).begin(), (node->left).end(), std::make_pair(timestamp, nullptr));
          return find((*std::prev(it)).second, timestamp, value);
        } else { // value > node->value
          auto it = std::upper_bound((node->right).begin(), (node->right).end(), std::make_pair(timestamp, nullptr));
          return find((*std::prev(it)).second, timestamp, value);
        }
      }
    }
  }
};



int main() {
  
  return 0;
}