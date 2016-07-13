#ifndef SPLAYTREE_H_
#define SPLAYTREE_H_
#include<iostream>
using namespace std;

template <typename T>
class SplayTree {  // from up to bottom
    private:
        struct SplayNode {
            T ele;
            SplayNode* left;
            SplayNode* right;
            SplayNode(T e) : ele(e), left(NULL), right(NULL) {}
        };
        SplayNode* root;
        SplayNode* NullNode;
    public:
        SplayTree() : root(NULL) {
            NullNode = new SplayNode();
            NullNode->left = NullNode->right = NullNode;
        }
        ~SplayTree() {
            clear();
        }
        void clear() {
            Clear(root);
            root = NULL;
        }
        void Clear(SplayNode* r) {
            if (r == NullNode) return;
            CLear(r->left);
            CLear(r->right);
            delete r;
        }

        SplayNode* SingleRotateWithRight(SplayNode* k1) {
            SplayNode* k2 = k1->right;
            k1->right = k2->left;
            k2->left = k1;
            // calcluate height, can't change follow order
            return k2;  // return new root after rotate
        }
        SplayNode* SingleRotateWithLeft(SplayNode* k1) {
            SplayNode* k2 = k1->left;
            k1->left = k2->right;
            k2->right = k1;
            return k2;  // return new root after rotate
        }
        SplayNode* Splay(T e, SplayNode* r) {
            SplayNode header;
            // header.left is the right tree, header.right is the left tree
            header.left = header.right = NullNode;
            // left tree and right tree, at firse ther are empty, regard as header
            SplayNode* LeftTreeMax = &header;
            SplayNode* RightTreeMin = &header;

            NullNode->ele = e;  // 
            while (e != r->ele) {
                if (e < r->ele) {
                    if (e < r->left->ele)
                        r = SingleRotateWithLeft(r);
                    if (r->left == NullNode) break;
                    // last line means can't find e in the tree,
                    // so break and link the new tree
                    RightTreeMin->left = r;
                    RightTreeMin = r;
                    r = r->left;
                } else {
                    if (e > r->right->ele)
                        r = SingleRotateWithRight(r);
                    if (r->right == NULL) break;
                    LeftTreeMax->right = r;
                    LeftTreeMax = r;
                    r = r->right;
                }
            }
            // it doesdn't matter whether find e in the tree or not,  link the new tree
            LeftTreeMax->right = r->left;
            RightTreeMin->left = r->right;
            r->left = header.right;
            r->right = header.left;
            return r;
        }
        SplayNode* insert(T e) {
            SplayNode* newnode = new SplayNode(e);
            if (root == NULL) {  // empty tree
                root = newnode;
                root->left = root->right = NullNode;  // remember this
            } else {
                root = Splay(e, root);  // splay
                if (e < root->ele) {  // e is not in tree and e < root->ele
                    newnode->left = root->left;
                    newnode->right = root;
                    root->left = NullNode;
                    root = newnode;
                } else if (e > root->ele) {  // e is not in tree and e > root->ele
                    newnode->right = root->right;
                    newnode->left = root;
                    root->right = NullNode;
                    root = newnode;
                }  // else e is in tree, so return root directly
            }
            return root;
        }
        SplayNode* remove(T e) {
            SplayNode* newtree;
            if (root != NULL) {
                root = Splay(e, root);  // let the element that will be deleted become new root
                if (e == root->ele) {  // find it!
                    if (root->left == NullNode) {  // let root->right be the newtree directly
                        newtree = root->right;
                    } else {
                        newtree = root->left;
                        newtree = Splay(e, newtree);
                        newtree->right = root->right;
                    }
                    delete root;
                    root = newtree;
                }
            }
            return root;
        }

        SplayNode* find(T e) {
            if (root == NULL) return NULL;
            SplayNode* temp = root;
            NullNode->ele = e;
            while (temp != NullNode && e != temp->ele) {
                if (e > temp->ele)
                    temp = temp->right;
                else
                    temp = temp->left;
            }
            if (temp != NullNode) root = Splay(e, root);
            return temp;
        }
        SplayNode* findMax() {
            if (root == NULL) return NULL;
            SplayNode* temp = root;
            NullNode->ele = 0;
            while (temp->right != NullNode) {
                temp = temp->right;
            }
            return temp;
        }
        SplayNode* findMin() {
            if (root == NULL) return NULL;
            SplayNode* temp = root;
            NullNode->ele = 0;
            while (temp->left != NullNode) {
                temp = temp->left;
            }
            return temp;
        }

        void preOrder() { PreOrder(root); }
        void PreOrder(SplayNode* r) {
            if (r == NullNode) return;
            cout << r->ele << ' ';
            PreOrder(r->left);
            PreOrder(r->right);
        }
        void inOrder() { InOrder(root); }
        void InOrder(SplayNode* r) {
            if (r == NullNode) return;
            InOrder(r->left);
            cout << r->ele << ' ';
            InOrder(r->right);
        }
        void postOrder() { PostOrder(root); }
        void PostOrder(SplayNode* r) {
            if (r == NullNode) return;
            PostOrder(r->left);
            PostOrder(r->right);
            cout << r->ele << ' ';
        }
};
#endif
