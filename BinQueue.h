/*
 * 二项队列
 * */
#ifndef BINOMIALQUEUE_H_
#define BINOMIALQUEUE_H_
#include<iostream>

const int MAXNUM = 8;  // max capacity of trees
const int capacity = 255;
const int error = -1;
const int maxinum = 9999;

class BinQueue {
    private:
        struct BinNode {
            int ele;
            BinNode* child;
            BinNode* sibling;
            BinNode(int e) : ele(e), child(NULL), sibling(NULL) {}
        };
        struct collection {
            int size;  // number of nodes
            BinNode* trees[MAXNUM];
            collection(int s) : size(s) {
                for (int i = 0; i < MAXNUM; ++i)
                    trees[i] = NULL;
            }
        };
        collection* head;

    public:
        BinQueue() : head(NULL) {
            head = new collection(0);
        }
        ~BinQueue() {
            clear();
            delete head;
        }
        void clear() {
            for (int i = 0; i < MAXNUM; ++i) {
                destroy(head->trees[i]);
                head->trees[i] = NULL;
            }
            head->size = 0;
        }
        void destroy(BinNode* r) {
            if (r == NULL) return;
            destroy(r->child);
            destroy(r->sibling);
            delete r;
        }

        bool isEmpty() {
            return head->size == 0;
        }

        BinNode* CombineTrees(BinNode* b1, BinNode* b2) {  // combine two equal-sized trees
            if (b1->ele > b2->ele)
                return CombineTrees(b2, b1);
            b2->sibling = b1->child;
            b1->child = b2;
            return b1;
        }
        collection* merge(collection* c1, collection* c2) {  // c1 is the new BinQueue
            BinNode* t1, * t2, * carry = NULL;  // carry is a tree we got from last step

            if (c1->size + c2->size > capacity) {
                std::cout << "Merge would exceed capacity!\n";
                return NULL;
            }

            c1->size += c2->size;
            for (int i = 0, j = 1; j <= c1->size; ++i, j *= 2) {
                t1 = c1->trees[i], t2 = c2->trees[i];
                switch (!!t1 + 2 * !!t2 + 4 * !!carry) {
                    case 0:  // no trees
                    case 1:  // only c1, do nothing
                        break;
                    case 2:  // only c2
                        c1->trees[i] = c2->trees[i];
                        c2->trees[i] = NULL;
                        break;
                    case 4:  // only carry
                        c1->trees[i] = carry;
                        carry = NULL;
                        break;
                    case 3:  // c1 and c2
                        carry = CombineTrees(c1->trees[i], c2->trees[i]);
                        c1->trees[i] = c2->trees[i] = NULL;
                        break;
                    case 5:  // c1 and carry
                        carry = CombineTrees(c1->trees[i], carry);
                        c1->trees[i] = NULL;
                        break;
                    case 6:  // c2 and carry
                        carry = CombineTrees(c2->trees[i], carry);
                        c2->trees[i] = NULL; 
                        break;
                    case 7:  // c1, c2 and carry
                        c1->trees[i] = carry;
                        carry = CombineTrees(c2->trees[i], carry);
                        break;
                }
            }
            return c1;
        }
        int pop() {
            if (isEmpty()) {
                std::cout << "empty queue!\n";
                return error;
            }
            int MinData = maxinum, MinIndex = 0;
            for (int i = 0; i < MAXNUM; ++i) {  // find the mininum item
                if (head->trees[i] && head->trees[i]->ele < MinData) {
                    MinData = head->trees[i]->ele;
                    MinIndex = i;  // record its index
                }
            }

            BinNode* deletedTree = head->trees[MinIndex];  // find the tree deleted node is in
            BinNode* oldRoot = deletedTree;
            deletedTree = deletedTree->child;
            delete oldRoot;  // delete the mininum node

            // to make a new BinQueue consists of deleteTree
            // !! a colpleted tree with index i has (1 << i) nodes  !attention!
            collection deletedQueue((1 << MinIndex) - 1);
            for (int i = MinIndex - 1; i >= 0; --i) {
                deletedQueue.trees[i] = deletedTree;
                deletedTree = deletedTree->sibling;
                deletedQueue.trees[i]->sibling = NULL;
            }

            head->trees[MinIndex] = NULL;  // delete the tree from original BinQueue
            head->size -= deletedQueue.size + 1;

            merge(head, &deletedQueue);  // merge them in head
            return MinData;
        }
        void insert(int e) {
            collection temp(1);
            temp.trees[0] = new BinNode(e);
            merge(head, &temp);
        }

};
#endif

