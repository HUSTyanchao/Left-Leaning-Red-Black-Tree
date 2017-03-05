#ifndef _RBTREE_H_
#define _RBTREE_H_

#include <functional>
#include <memory>

#define RED	true
#define BLACK	false

template<typename Key, typename Value, typename Func = std::less<Key>> class BST
{
public:
  struct Node;
  using NodePtr = std::shared_ptr < Node > ;

  // find the minimum key
  bool min(Key& key) {
    std::shared_ptr<Node> x = root;
    if (x == nullptr) return false;
    while (x != nullptr) {
      key = x->key;
      x = x->left;
    }
    return true;
  }

  // find the max key
  bool max(Key& key) {
    std::shared_ptr<Node> x = this->root;
    if (x == nullptr) return false;
    while (x != nullptr) {
      key = x->key;
      x = x->right;
    }
    return true;
  }

  bool get(const Key& key, Value& val) {
    auto x = root;
    while (x != nullptr) {
      if (Func()(key, x->key)) x = x->left;
      else if (Func()(x->key, key))  x = x->right;
      else {
        val = x->val;
        return true;
      }
    }
    return false;
  }

  void put(const Key& key, const Value& val) {
    root = insert(root, key, val);
    root->color = BLACK;
  }

private:

  struct Node
  {
    Key key;
    Value val;
    NodePtr left;
    NodePtr right;  // left and right child
    bool color;  // color of incoming link
    Node(Key k, Value v, bool c) :key(k), val(v), color(c) {}
  };

  NodePtr root;  // root node of the BST
  bool isRed(NodePtr x) {
    if (x) return (x->color == RED);
    else return false;
  }

  // insert method
  NodePtr insert(NodePtr h, const Key& key, const Value& val) {
    // insert at the bottom
    if (h == nullptr) {
      return std::make_shared<Node>(key, val, RED);
    }
    // split 4-nodes on the way down
    if (isRed(h->left) && isRed(h->right))
      flipColor(h);
    if (Func()(key, h->key)) h->left = insert(h->left, key, val);
    else if (Func()(h->key, key)) h->right = insert(h->right, key, val);
    else  h->val = val;  // no duplicate keys
    // fix right-leaning reds on the way up
    if (isRed(h->right)) {
      h = rotateLeft(h);
    }
    // fix two red in a row on the way up
    if (isRed(h->left) && isRed(h->left->left)) {
      h = rotateRight(h);
    }
    return h;
  }

  // right child is red link, rotate left
  NodePtr rotateLeft(NodePtr h) {
    NodePtr x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = x->left->color;
    x->left->color = RED;
    return x;
  }

  // left child is red link, rotate right
  NodePtr rotateRight(NodePtr h) {
    NodePtr x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = x->right->color;
    x->right->color = RED;
    return x;
  }

  // flip color
  NodePtr flipColor(NodePtr h) {
    h->color = !h->color;
    h->left->color = !h->left->color;
    h->right->color = !h->right->color;
    return h;
  }


};


#endif // !_RBTREE_H_
