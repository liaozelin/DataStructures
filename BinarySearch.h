#ifndef BINARYSEARCH_H_
#define BINARYSEARCH_H_
#include<iostream>
using namespace std;

class BinarySearchTree {
    private:
        struct BSTNode {
            int ele;
            BSTNode* left;
            BSTNode* right;
            BSTNode(int e, BSTNode* l = NULL, BSTNode* r = NULL)
                : ele(e), left(l), right(r) {}
        };

        BSTNode* root;
    public:
        BinarySearchTree() : root(NULL) {}
        ~BinarySearchTree() {
            clear();
        }
        void clear() {
            Clear(root);
            root = NULL;
        }
        void Clear(BSTNode* node) {
            if (node == NULL) return;
            Clear(node->left);
            Clear(node->right);
            delete node;
        }
        BSTNode* find(int e) {
            if (root != NULL) {
                BSTNode* temp = root;
                while (temp != NULL && e != temp->ele) {
                    if (e > temp->ele) temp = temp->right;
                    else temp = temp->left;
                }
                return temp;
            }
            return NULL;
        }
        BSTNode* findMin() {
            if (root != NULL) {
                BSTNode* temp = root;
                while (temp->left != NULL)
                    temp = temp->left;
                return temp;
            }
            return NULL;
        }
        BSTNode* findMax() {
            if (root != NULL) {
                BSTNode* temp = root;
                while (temp->right != NULL)
                    temp = temp->right;
                return temp;
            }
            return NULL;
        }
        bool insert(int e) {
            if (root == NULL) {
                root = new BSTNode(e);
                return true;
            } else {
                BSTNode* temp = root;
                while (e != temp->ele) {
                    if (e > temp->ele) {
                        if (temp->right == NULL) {
                            temp->right = new BSTNode(e);
                            return true;
                        } else {
                            temp = temp->right;
                        }
                    } else {
                        if (temp->left == NULL) {
                            temp->left = new BSTNode(e);
                            return true;
                        } else {
                            temp = temp->left;
                        }
                    }
                }
                return false;
            }
        }
        bool remove(int e) {  // only traversal tree once
            BSTNode* parent = NULL;
            BSTNode* node = root;  // node reprent the node to be deleted
            if (node != NULL) {  // not empty tree
                while (node != NULL && e != node->ele) {
                    if (e > node->ele) {
                        parent = node;
                        node = node->right;
                    } else {
                        parent = node;
                        node = node->left;
                    }
                }
                if (node == NULL) return false;
                if (node->left && node->right) {  // two children
                    BSTNode* parent_ = node;
                    BSTNode* node_ = node->right;
                    while (node->left != NULL) {
                        parent_ = node_;
                        node_ = node_->left;
                    }
                    parent_->left = node_->right;
                    node->ele = node_->ele;
                    delete node_;
                } else if (node->left == NULL) {  // only right child
                    if (node == parent->left)
                        parent->left = node->right;
                    else
                        parent->right = node->right;
                    delete node;
                } else if (node->right == NULL) {  // only left child
                    if (node == parent->left)
                        parent->left = node->left;
                    else
                        parent->left = node->left;
                    delete node;
                } else {  // no children
                    if (node == parent->left)
                        parent->left = NULL;
                    else
                        parent->right = NULL;
                    delete node;
                }
                return true;
            } else {  // empty tree
                return false;
            }
        }

        void preOrder() { PreOrder(root); }
        void PreOrder(BSTNode* r) {
            if (r == NULL) return;
            cout << r->ele << ' ';
            PreOrder(r->left);
            PreOrder(r->right);
        }
        void inOrder() { InOrder(root); }
        void InOrder(BSTNode* r) {
            if (r == NULL) return;
            InOrder(r->left);
            cout << r->ele << ' ';
            InOrder(r->right);
        }
        void postOrder() { PostOrder(root); }
        void PostOrder(BSTNode* r) {
            if (r == NULL) return;
            PostOrder(r->left);
            PostOrder(r->right);
            cout << r->ele << ' ';
        }
};

#endif

