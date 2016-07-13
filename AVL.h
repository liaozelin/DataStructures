#ifndef AVL_H_
#define AVL_H_
#include<iostream>
using namespace std;

template <typename T>
class AVLTree {
    private:
        struct AvlNode{
            T ele;
            int height;
            AvlNode* left;
            AvlNode* right;
            AvlNode(T e, int h, AvlNode* l = NULL, AvlNode* r = NULL)
                : ele(e), height(h), left(l), right(r) {}
        };

        AvlNode* root;
    public:
        AVLTree() : root(NULL) {}
        ~AVLTree() { destroy(); }
        void destroy() {
            clear(root);
            root = NULL;
        }
        void clear(AvlNode* r) {
            if (r == NULL) return;
            clear(r->left);
            clear(r->right);
            delete r;
        }

        AvlNode* find(T e) {
            AvlNode* temp = root;
            while (temp != NULL && e != temp->ele) {
                if (e > temp->ele)
                    temp = temp->right;
                else
                    temp = temp->left;
            }
            return temp;
        }
        AvlNode* findMax() {
            if (root == NULL) return NULL;
            AvlNode* temp = root;
            while (temp->right != NULL) {
                temp = temp->right;
            }
            return temp;
        }
        AvlNode* findMin() {
            if (root == NULL) return NULL;
            AvlNode* temp = root;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            return temp;
        }
        AvlNode* findMax(AvlNode* node) {
            if (node == NULL) return NULL;
            AvlNode* temp = node;
            while (temp->right != NULL) {
                temp = temp->right;
            }
            return temp;
        }
        AvlNode* findMin(AvlNode* node) {
            if (node == NULL) return NULL;
            AvlNode* temp = node;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            return temp;
        }

        int height(AvlNode* node) {  // return height of a node
            if (node == NULL) return -1;
            else return node->height;
        }
        int max(int a, int b) {  // choose the larger number of two
            return a > b ? a : b;
        }
        AvlNode* SingleRotateWithRight(AvlNode* k1) {
            AvlNode* k2 = k1->right;
            k1->right = k2->left;
            k2->left = k1;
            // calcluate height, can't change follow order
            k1->height = max(height(k1->left), height(k1->right)) + 1;
            k2->height = max(height(k2->left), height(k2->right)) + 1;
            return k2;  // return new root after rotate
        }
        AvlNode* SingleRotateWithLeft(AvlNode* k1) {
            AvlNode* k2 = k1->left;
            k1->left = k2->right;
            k2->right = k1;
            k1->height = max(height(k1->left), height(k1->right)) + 1;
            k2->height = max(height(k2->left), height(k2->right)) + 1;
            return k2;  // return new root after rotate
        }
        AvlNode* DoubleRotateWithRight(AvlNode* root_node) {
            root_node->right = SingleRotateWithLeft(root_node->right);
            return SingleRotateWithRight(root_node);
        }
        AvlNode* DoubleRotateWithLeft(AvlNode* root_node) {
            root_node->left = SingleRotateWithRight(root_node->left);
            return SingleRotateWithLeft(root_node);
        }

        void insert(int e) {
            root = Insert(e, root);
        }
        AvlNode* Insert(int e, AvlNode* node) {
            if (node == NULL) {
                node = new AvlNode(e, 0);
            } else {
                if (e > node->ele) {
                    node->right = Insert(e, node->right);
                    if (height(node->right) - height(node->left) == 2) {
                        if (e > node->right->ele)
                            node = SingleRotateWithRight(node);
                        else
                            node = DoubleRotateWithRight(node);
                    }
                } else if (e < node->ele) {
                    node->left = Insert(e, node->left);
                    if (height(node->left) - height(node->right) == 2) {
                        if (e < node->left->ele)
                            node = SingleRotateWithLeft(node);
                        else
                            node = DoubleRotateWithLeft(node);
                    }
                }
            }
            // adjust height of the node
            node->height = max(height(node->left), height(node->right)) + 1;
            return node;
        }
        void remove(int e) {
            AvlNode* node_d = find(e);
            root = Remove(root, node_d);
        }
        AvlNode* Remove(AvlNode* root_, AvlNode* node_d) {
            if (root_ == NULL || node_d == NULL)
                return NULL;
            if (node_d->ele > root_->ele) {  // node that will be deleted is located in right
                root_->right = Remove(root_->right, node_d);
                if (root_->left->height - root_->right->height == 2) {
                    if (height(root_->left->right) > height(root_->left->left))
                        root_ = DoubleRotateWithLeft(root_);
                    else
                        root_ = SingleRotateWithLeft(root_);
                }
            } else if (node_d->ele < root_->ele) {  // node that will be deleted is located in left
                root_->left = Remove(root_->left, node_d);
                if (height(root_->right) - height(root_->left) == 2) {
                    if (height(root_->right->left) >
                            height(root_->right->right))
                        root_ = DoubleRotateWithRight(root_);
                    else
                        root_ = SingleRotateWithRight(root_);
                }
            } else {  // find node that will be deleted
                if (root_->left != NULL && root_->right != NULL) {  // two children
                    if (height(root_->left) > height(root_->right)) {
                        AvlNode* max = findMax(root_->left);
                        root_->ele = max->ele;
                        root_->left = Remove(root_->left, max);
                    } else {
                        AvlNode* min = findMin(root_->right);
                        root_->ele = min->ele;
                        root_->left = Remove(root_->left, min);
                    }
                } else {
                    AvlNode* temp = root_;
                    root_ = temp->left == NULL ? temp->right : temp->left;
                    delete temp;
                }
            }
            return root_;
        }

        void preOrder() { PreOrder(root); }
        void PreOrder(AvlNode* r) {
            if (r == NULL) return;
            cout << r->ele << ' ';
            PreOrder(r->left);
            PreOrder(r->right);
        }
        void inOrder() { InOrder(root); }
        void InOrder(AvlNode* r) {
            if (r == NULL) return;
            InOrder(r->left);
            cout << r->ele << ' ';
            InOrder(r->right);
        }
        void postOrder() { PostOrder(root); }
        void PostOrder(AvlNode* r) {
            if (r == NULL) return;
            PostOrder(r->left);
            PostOrder(r->right);
            cout << r->ele << ' ';
        }
        int height() { return root->height; }
        int minimum() { return findMin()->ele; }
        int maximum() { return findMax()->ele; }
        
};
#endif

