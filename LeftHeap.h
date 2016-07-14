/*
 * 左式堆:对堆中每一结点,其左儿子的零路径长至少与右儿子一样长
 * */
#ifndef LEFTHEAP_H_
#define LEFTHEAP_H_
#include<iostream>

class LeftHeap {  // priority queue by LeftHeap
    private:
        struct LHNode {
            int ele;
            LHNode* left;
            LHNode* right;
            int npl;  // 零路径长
            LHNode(int e, int n) : ele(e), left(NULL), right(NULL), npl(n) {}
        };
        LHNode* root;

    public:
        LeftHeap() : root(NULL) {}
        ~LeftHeap() {
            clear();
        }
        void clear() { Clear(root); }
        void Clear(LHNode* r) {
            if (r == NULL) return;
            Clear(r->left);
            Clear(r->right);
            delete r;
        }

        bool isEmpty() { return root == NULL; }
        int findMin() {
            if (isEmpty()) std::cout << "empty heap!" << std::endl;
            return root->ele;
        }

        LHNode* merge(LHNode* h1, LHNode* h2) {
            if (h1 == NULL) return h2;
            if (h2 == NULL) return h1;
            if (h1->ele < h2->ele)
               return Merge(h1, h2);
            else
               return Merge(h2, h1);
        }
        LHNode* Merge(LHNode* h1, LHNode* h2) {  // merge h1's right child and h2
            if (h1->left == NULL) {  // this means it's a single node, h1->right is already NULL
                h1->left = h2;
            } else {
                h1->right = merge(h1->right, h2);
                if (h1->left->npl < h1->right->npl)  // in order to satisfy character of LeftHeap
                    swapChild(h1);
                h1->npl = h1->right->npl + 1;
            }
            return h1;
        }

        LHNode* insert(int e) {
            LHNode* newNode = new LHNode(e, 0);
            root = merge(newNode, root);  // insert is a condition of merge between a single node and a LeftHeap
            return root;
        }
        int pop() {
            int tmp = findMin();
            LHNode* Left = root->left;
            LHNode* Right = root->right;
            delete root;
            root = merge(Left, Right);
            return tmp;
        }

    private:
        inline void swapChild(LHNode* h) {
            LHNode* t = h->left;
            h->left = h->right;
            h->right = t;
        }
};
#endif

