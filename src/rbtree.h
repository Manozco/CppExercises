#ifndef RBTREE_H
#define RBTREE_H
#include <iostream>
#include <functional>
#include "rbtreenode.h"

template<typename T>
class RBTree
{
public:
    typedef std::function<void(const RBTreeNode<T> *const)> RBTraversalFunc;
    RBTree() {
        _root = nullptr;
    }

    RBTree(T rootData) {
        this->_root = new RBTreeNode<T>(rootData);
        this->_root->setColor(BLACK);
    }

    RBTree(RBTreeNode<T> *root) {
        _root = root;
    }

    RBTreeNode<T> *root() {
        RBTreeNode<T> *ret = static_cast<RBTreeNode<T> *>(this->_root);
        return ret;
    }

    int maxHeight() const{
        if (!_root)
            return 0;
        int leftH = RBTree(_root->left()).maxHeight();
        int rightH = RBTree(_root->right()).maxHeight();
        return (leftH > rightH) ? leftH +1 : rightH +1;
    }

    RBTreeNode<T> *find(T data) {
        RBTreeNode<T> *curNode = _root;
        while (nullptr != curNode) {
            if (curNode->data() == data)
                return curNode;
            else if (data >= curNode->data())
                curNode = curNode->right();
            else if (data <= curNode->data())
                curNode = curNode->left();
        }
        return nullptr;
    }

    bool insert(T data) {
        RBTreeNode<T> *nodeToInsert = new RBTreeNode<T>(data);
        bool res = _insert(nodeToInsert);
        if (!res) {
            delete nodeToInsert;
            return res;
        }
        res = _insertCase1(nodeToInsert);
        return res;
    }

    bool deleteNode (RBTreeNode<T> *N) {
        if (nullptr == N) {
            return false;
        } else {
            if (nullptr == N->left() && nullptr == N->right()) {
                delete N;
                N = nullptr;
                return true;
            } else if (nullptr == N->left() && nullptr != N->right()) {
                N->switchNode(N->right());
                delete N->right();
                N->setRight(nullptr);
                return true;
            } else if (nullptr != N->left() && nullptr == N->right()) {
                N->switchNode(N->left());
                delete N->left();
                N->setLeft(nullptr);
                return true;
            } else {
                RBTreeNode<T> *inOrderPredecessor = RBTree<T>(N->left()).max();
                N->setData(inOrderPredecessor->data());
                this->deleteNode(inOrderPredecessor);
                return true;
            }
        }

        assert(N->left() == nullptr || N->right() == nullptr);
        RBTreeNode<T> *child = (N->right() == nullptr) ? N->left() : N->right();
        if (N->color() == BLACK) {
            N->setColor(child->color());
            _deleteCase1(N);
        }
        replaceNode(N, child);
        if (N->parent() == nullptr && child != nullptr) // root should be black
            child->setColor(BLACK);

        delete(N);
        N = nullptr;
        return true;
    }

    void preorderTraversal(RBTraversalFunc func) {
        func(_root);
        if (_root->left())
            RBTree(_root->left()).preorderTraversal(func);
        if (_root->right())
            RBTree(_root->right()).preorderTraversal(func);
    }

    void print() {
        auto lambda = [](const RBTreeNode<T> *const node) {node->printNode();};
        this->preorderTraversal(lambda);
    }

    RBTreeNode<T> *min() {
        RBTreeNode<T> *cur_node = _root;
        while (cur_node->left()) {
            cur_node = cur_node->left();
        }
        return cur_node;
    }

    RBTreeNode<T> *max() {
        RBTreeNode<T> *cur_node = _root;
        while (cur_node->right()) {
            cur_node = cur_node->right();
        }
        return cur_node;
    }

    void replaceNode(RBTreeNode<T> *old, RBTreeNode<T> *newn) {
        if (old->parent() == nullptr) {
            _root = newn;
        } else {
            if (old == old->parent()->left())
                old->parent()->setLeft(newn);
            else
                old->parent()->setRight(newn);
        }
        if (newn != nullptr)
            newn->setParent(old->parent());
    }

    void rotateRight(RBTreeNode<T> *n) {
        RBTreeNode<T> *l = n->left();
        replaceNode(n, l);
        n->setLeft(l->right());
        if (l->right() != nullptr)
            l->right()->setParent(n);
        l->setRight(n);
        n->setParent(l);
    }

    void rotateLeft(RBTreeNode<T> *n) {
        RBTreeNode<T> *r = n->right();
        replaceNode(n, r);
        n->setRight(r->left());
        if (r->left() != nullptr)
            r->left()->setParent(n);
        r->setLeft(n);
        n->setParent(r);
    }

protected:
    bool _insert(RBTreeNode<T> *nodeToInsert) {
        RBTreeNode<T> *curNode = _root;
        RBTreeNode<T> *parent = nullptr;
        T data = nodeToInsert->data();
        if (curNode == nullptr) {
            _root = nodeToInsert;
            return true;
        }
        while (nullptr != curNode) {
            // We insert on the left if it is equal
            if (data == curNode->data()) {
                nodeToInsert->setLeft(curNode->left());
                nodeToInsert->setParent(curNode);
                curNode->setLeft(nodeToInsert);
                return true;
            } else if (data >= curNode->data()) {
                parent = curNode;
                curNode = curNode->right();
            } else if (data <= curNode->data()) {
                parent = curNode;
                curNode = curNode->left();
            }
        }
        if (parent) {
            if (data <= parent->data()) {
                parent->setLeft(nodeToInsert);
                nodeToInsert->setParent(parent);
            } else {
                parent->setRight(nodeToInsert);
                nodeToInsert->setParent(parent);
            }
        }
        return true;
    }

    bool _insertCase1(RBTreeNode<T> *N) {
        if (_root == N) {
            N->setColor(BLACK);
            return true;
        } else {
            return _insertCase2(N);
        }
    }

    bool _insertCase2(RBTreeNode<T> *N) {
        if (N->parent()->color() == BLACK) {
            return true;
        } else {
            return _insertCase3(N);
        }
    }

    bool _insertCase3(RBTreeNode<T> *N) {
        if(N->uncle() && N->uncle()->color() == RED) {
            N->parent()->setColor(BLACK);
            N->uncle()->setColor(BLACK);
            RBTreeNode<T> *g = N->grandParent();
            g->setColor(RED);
            _insertCase1(g);
            return true;
        } else {
            return _insertCase4(N);
        }
    }

    bool _insertCase4(RBTreeNode<T> *N) {
        if (N == N->parent()->right() &&
            N->parent() == N->grandParent()->left()) {
            rotateLeft(N->parent());
            N = N->left();
        } else if (N == N->parent()->left() &&
                   N->parent() == N->grandParent()->right()) {
            rotateRight(N->parent());
            N = N->right();
        }
        return _insertCase5(N);
    }

    bool _insertCase5(RBTreeNode<T> *N) {
        N->parent()->setColor(BLACK);
        N->grandParent()->setColor(RED);
        if (N == N->parent()->left() &&
            N->parent() == N->grandParent()->left()) {
            rotateRight(N->grandParent());
        } else if (N == N->parent()->right() &&
                   N->parent() == N->grandParent()->right()) {
            rotateLeft(N->grandParent());
        }
        return true;
    }


    bool _deleteCase1(RBTreeNode<T>*N) {
        if (N->parent() == nullptr)
            return true;
        else
            return _deleteCase2(N);
    }

    bool _deleteCase2(RBTreeNode<T> *N) {
        assert(N->sibling());
        if (N->sibling() && N->sibling()->color() == RED) {
            N->parent()->setColor(RED);
            N->sibling()->setColor(BLACK);
            if (N->isLeftOfItsParent())
                rotateLeft(N->parent());
            else
                rotateRight(N->parent());
        }
        return _deleteCase3(N);
    }

    bool _deleteCase3(RBTreeNode<T> *N) {
        assert(N->sibling());
        assert(N->sibling()->left());
        assert(N->sibling()->right());
        if (N->parent()->color() == BLACK &&
                N->sibling() &&
                N->sibling()->color() == BLACK &&
                N->sibling()->left() &&
                N->sibling()->left()->color() == BLACK &&
                N->sibling()->right() &&
                N->sibling()->right()->color() == BLACK) {
            N->sibling()->setColor(RED);
            return _deleteCase1(N->parent());
        } else {
            return _deleteCase4(N);
        }
    }

    bool _deleteCase4(RBTreeNode<T> *N) {
        assert(N->sibling());
        assert(N->sibling()->left());
        assert(N->sibling()->right());
        if (N->parent()->color() == RED &&
                N->sibling() &&
                N->sibling()->color() == BLACK &&
                N->sibling()->left() &&
                N->sibling()->left()->color() == BLACK &&
                N->sibling()->right() &&
                N->sibling()->right()->color() == BLACK) {
            N->sibling()->setColor(RED);
            N->parent()->setColor(BLACK);
            return true;
        } else {
            return _deleteCase5(N);
        }
    }

    bool _deleteCase5(RBTreeNode<T> *N) {
        assert(N->sibling());
        assert(N->sibling()->left());
        assert(N->sibling()->right());
        if (N->isLeftOfItsParent() &&
                N->sibling() && N->sibling()->color() == BLACK &&
                N->sibling()->left() && N->sibling()->left()->color() == RED &&
                N->sibling()->right() && N->sibling()->right()->color() == BLACK) {
            N->sibling()->setColor(RED);
            N->sibling()->left()->setColor(BLACK);
            rotateRight(N->sibling());
        } else if (N->isRightOfItsParent() &&
                   N->sibling() && N->sibling()->color() == BLACK &&
                   N->sibling()->left() && N->sibling()->left()->color() == BLACK &&
                   N->sibling()->right() && N->sibling()->right()->color() == RED) {
            N->sibling()->setColor(RED);
            N->sibling()->right()->setColor(BLACK);
            rotateLeft(N->sibling());
        }
        return _deleteCase6(N);
    }

    bool _deleteCase6(RBTreeNode<T> *N) {
        assert(N->sibling());
        N->parent()->setColor(BLACK);
        if (N->isLeftOfItsParent()) {
            assert(N->sibling()->right());
            assert(N->sibling()->right()->color() == RED);
            N->sibling()->right()->setColor(BLACK);
            rotateLeft(N->parent());
        } else {
            assert(N->sibling()->left());
            assert(N->sibling()->left()->color() == RED);
            N->sibling()->left()->setColor(BLACK);
            rotateRight(N->parent());
        }
        return true;
    }

protected:
    RBTreeNode<T> *_root;
};


#endif // RBTREE_H

