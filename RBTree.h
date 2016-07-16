#ifndef RBTREE_H_
#define RBTREE_H_
#include<iostream>

typedef int ElementType;
class RBTree {
    private:
        enum ColorType { red, black};
        struct RBNode {
            ElementType ele;
            ColorType color;
            RBNode* left;
            RBNode* right;
            RBNode* parent;
        };
        typedef RBNode* RBtree;
    private: 
        RBtree root;
        RBtree nil;
    public:
        RBTree() {
            nil = new RBNode();
            nil->left = nil->right = nil->parent = nil;
            nil->color = black;
            root = nil;
        }
        ~RBTree() { destroy(); }
        void destroy() {
            Destroy(root);
            root = nil;
        }
        void Destroy(RBtree r) {
            if (r == nil) return;
            Destroy(r->left);
            Destroy(r->right);
            delete r;
        }

        void LeftRotate(RBtree x) {
            RBtree y = x->right;
            x->right = y->left;
            if (y->left != nil)
                y->left->parent = x;
            y->parent = x->parent;
            if (x->parent == nil)
                root = y;
            else if (x->parent->left == x)
                x->parent->left = y;
            else
                x->parent->right = y;
            y->left = x;
            x->parent = y;
        }
        void RightRotate(RBtree x) {
            RBtree y = x->left;
            x->left = y->right;
            if (y->right != nil)
                y->right->parent = x;
            y->parent = x->parent;
            if (x->parent == nil)
                root = y;
            else if (x->parent->left == x)
                x->parent->left = y;
            else
                x->parent->right = y;
            y->right = x;
            x->parent = y;
        }

        bool insert(ElementType e) {
            RBtree p = nil;  // p 指向要插入位置的父节点
            RBtree x = root;
            while (x != nil) {
                p = x;
                if (e > x->ele)
                    x = x->right;
                else if (e < x->ele)
                    x = x->left;
                else
                    return false;
            }
            RBtree newNode = new RBNode();  // 新建结点,默认为红色
            newNode->ele = e;
            newNode->color = red;
            newNode->left = newNode->right = nil;
            if (p->ele < e)
                p->right = newNode;
            else
                p->left = newNode;
            newNode->parent = p;  // link new node
            insert_fixup(newNode);
            return true;
        }
        void insert_fixup(RBtree x) {
            while (x->parent->color == red) {
                if (x->parent == x->parent->parent->left) {
                    RBtree u = x->parent->parent->right;  // u is x's uncle
                    if (u->color == red) {  // condition 1: uncle is red
                        u->color = x->parent->color = black;
                        x->parent->parent->color = red;
                        x = x->parent->parent;
                    } else {  // uncle is black
                        if (x == x->parent->right) {  // condition 2: uncle is black and x is a left child
                            x = x->parent;
                            LeftRotate(x);  // after rotate, condition 2 becomes condition 3
                        }
                        // condition 3: uncle is black and x is a right child
                        x->parent->color = black;
                        x->parent->parent->color = red;
                        RightRotate(x->parent->parent);
                    }
                } else {
                    RBtree u = x->parent->parent->left;
                    if (u->color == red) {
                        u->color = x->parent->color = black;
                        u->parent->color = red;
                        x = x->parent->parent;
                    } else{
                        if (x == x->parent->left) {
                            x = x->parent;
                            RightRotate(x);
                        }
                        x->parent->color = black;
                        x->parent->parent->color = red;
                        LeftRotate(x->parent->parent);
                    }
                }
            }
            root->color = black;
        }

        bool empty() {
            if (root == nil) return true;
            else return false;
        }
        RBtree maxinum(RBtree r) {
            if (r == nil) return nil;
            while (r->right != nil) r = r->right;
            return r;
        }
        RBtree mininum(RBtree r) {
            if (r == nil) return nil;
            while (r->left != nil) r = r->left;
            return r;
        }
        RBtree find(ElementType e) {
            RBtree tmp = root;
            while (tmp != nil && tmp->ele != e) {
                if (e > tmp->ele)
                    tmp = tmp->right;
                else
                    tmp = tmp->left;
            }
            return tmp;
        }

        void transplant(RBtree x, RBtree y) {  // link y and x->parent, let x becomes a single node
            if (x->parent == nil)
                root = y;
            else if (x == x->parent->left)
                x->parent->left = y;
            else
                x->parent->right = y;
        }
        bool remove(ElementType e) {
            RBtree z = find(e);  // z is the deleted node
            if (z == nil) return false;
            RBtree y = z;
            ColorType oldColor = z->color;
            RBtree z_child;  // z's child, replace z's original position
            if (z->left == nil) {
                z_child = z->right;
                transplant(z, z->right);
            } else if (z->right == nil) {
                z_child = z->left;
                transplant(z, z->left);
            } else {
                // 用要删除的节点的后继来代替该节点,即用y代替z
                y = mininum(z->right);
                oldColor = y->color;
                z_child = y->right;
                if (y->parent == z) {  // y->right doesn't change
                    z_child->parent = y;
                } else {  // y->right becomes z->right
                    transplant(y, y->right);
                    y->right = z->right;  // link y and z->right
                    y->right->parent = y;
                }
                transplant(z, y);  // link y and z->parent, so we can delete z
                y->left = z->left;  // link y and z->left
                y->left->parent = y;
                y->color = z->color;
            }
            delete z;
            if (oldColor == black)
                remove_fixup(z_child);
            return true;
        }
        void remove_fixup(RBtree x) {
            RBtree w;
            while (x != root && x->color == black) {
                // x is black
                if (x == x->parent->left) {
                    w = x->parent->right;  // w always is x's sibling
                    if (w->color == red) {  // condition 1
                        w->color = black;
                        x->parent->color = red;
                        LeftRotate(x->parent);
                        w = x->parent->right;  // let w become x's new sibling 
                    }
                    if (w->left->color == black && w->right->color == black) {  // condition 2
                        w->color = red;
                        x = x->parent;
                    } else if (w->right->color == black) {  // condition 3
                        w->left->color = black;
                        w->color = red;
                        RightRotate(w);
                        w = x->parent->right;
                    }
                    // condition 4
                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->right->color = black;
                    LeftRotate(x->parent);
                    x = root;
                } else {
                    w = x->parent->left;
                    if (w->color == red) {
                        w->color = black;
                        x->parent->color = red;
                        RightRotate(x->parent);
                        w = x->parent->left;
                    }
                    if (w->left->color == black && w->right->color == black) {
                        w->color = red;
                        x = x->parent;
                    } else if (w->left->color == black) {
                        w->right->color = black;
                        w->left->color = red;
                        LeftRotate(x->parent);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->left->color = black;
                    RightRotate(x->parent);
                    x = root;
                }
            }
            x->color = black;
        }

        void preOrder() { PreOrder(root); }
        void PreOrder(RBtree r) {
            if (r == nil) return;
            std::cout << r->ele << ' ';
            PreOrder(r->left);
            PreOrder(r->right);
        }
        void inOrder() { InOrder(root); }
        void InOrder(RBtree r) {
            if (r == nil) return;
            InOrder(r->left);
            std::cout << r->ele << ' ';
            InOrder(r->right);
        }
        void postOrder() { PostOrder(root); }
        void PostOrder(RBtree r) {
            if (r == nil) return;
            PostOrder(r->left);
            PostOrder(r->right);
            std::cout << r->ele << ' ';
        }
};
#endif

