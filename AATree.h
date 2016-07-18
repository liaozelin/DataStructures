/*
 * AA树：带附加条件的红黑树：一个节点最多有一个红儿子
 *      设只有右儿子才能是红节点
 * */
#ifndef AATREE_H_
#define AATREE_H_
#include<iostream>

typedef int ElementType;
class AATree {
    private:
        struct AANode {
            ElementType ele;
            int level;
            AANode* left;
            AANode* right;
            AANode() {}
            AANode(ElementType e, int l, AANode* le = NULL, AANode* ri = NULL)
                : ele(e), level(l), left(le), right(ri) {}
        };
        AANode* root;
        AANode* nil;
    public:
        AATree() : root(NULL) {
            nil = new AANode();
            nil->left = nil->right = nil;
            nil->level = 0;
        }
        ~AATree() {}

        AANode* SingleRotateWithRight(AANode* k1) {  // 左旋
            AANode* k2 = k1->right;
            k1->right = k2->left;
            k2->left = k1;
            return k2;
        }
        AANode* SingleRotateWithLeft(AANode* k1) {  // 右旋
            AANode* k2 = k1->left;
            k1->left = k2->right;
            k2->right = k1;
            return k2;
        }
        AANode* Skew(AANode* node) {
            // 如果有水平左链接，则进行右旋以消除水平左链接
            if (node->left->level == node->level)
                node = SingleRotateWithLeft(node);
            return node;
        }
        AANode* Split(AANode* node) {
            //　如果有两个连续的水平右链接，进行左旋以消除掉一个水平右链接
            if (node->right->right->level == node->level)
                node = SingleRotateWithRight(node);
            return node;
        }

        AANode* find(ElementType e) {
            AANode* tmp = root;
            while (tmp != nil) {
                if (e < tmp->ele)
                    tmp = tmp->left;
                else if (e > tmp->ele)
                    tmp = tmp->right;
                else
                    break;
            }
            return tmp;
        }

        void insert(ElementType e) {
            root = Insert(e, root);
        }
        AANode* Insert(ElementType e, AANode* node) {
            if (node == nil) {
                node = new AANode(e, 1, nil, nil);
            } else {
                if (e > node->ele)
                    node->left = Insert(e, node->right);
                else if (e < node->ele)
                    node->right = Insert(e, node->right);
                else
                    return node;
                // 插入成功之后,检查是否需要旋转
                node = Skew(node);
                node = Split(node);
            }
            return node;
        }

        void remove(ElementType e) {
            root = Remove(e, root);
        }
        AANode* Remove(ElementType e, AANode* node) {
            static AANode* deletePtr;
            static AANode* lastPtr;
            if (node != nil) {
                lastPtr = node;  // lastPtr指向了最底层的节点
                if (e < node->ele) {
                    node->left = Remove(e, node->left);
                } else {
                    deletePtr = node;  // deletePtr为要删除的节点
                    node->right = Remove(e, node->right);
                }
                // 如果在最底层 并且找到了要删除的元素, 则删除它
                // (用底层的元素代替要删除的节点的元素,删除底层的节点)
                if (node == lastPtr) {  // 检查是否在最底层
                    if (deletePtr != nil && e == deletePtr->ele) {  // 检查是否找到要删除的元素
                        deletePtr->ele = node->ele;
                        deletePtr = nil;
                        node = node->right;
                        delete lastPtr;
                    }
                } else {  // 删除结束后重新平衡层数
                    if (node->left->level < node->level - 1 ||
                            node->right->level < node->level - 1) {
                        if (node->right->level > --node->level)
                            node->right->level = node->level;
                        node = Skew(node);
                        node->right = Skew(node->right);
                        node->right->right = Skew(node->right->right);
                        node = Split(node);
                        node->right = Split(node->right);
                    }
                }
            }
            return node;
        }
};
#endif

