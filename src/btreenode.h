#ifndef BINARYTREENODE_H
#define BINARYTREENODE_H
#include <string>
#include <iostream>

template<typename T>
class BTreeNode
{
public:
    BTreeNode(T data=nullptr, BTreeNode<T> *left=nullptr, BTreeNode<T> *right=nullptr, BTreeNode<T> *parent=nullptr)
        : _data(data)
        , _left(left)
        , _right(right)
        , _parent(parent){}
    ~BTreeNode() {
        if (_parent) {
            if (_parent->left() == this)
                _parent->setLeft(nullptr);
            else if (_parent->right() == this)
                _parent->setRight(nullptr);
        }
    }

    T data() const {
        return _data;
    }

    void setData(const T data) {
        _data = data;
    }

    BTreeNode<T> *left() const {
        if (_left)
            return _left;
        return nullptr;
    }

    BTreeNode<T> *right() const {
        if (_right)
            return _right;
        return nullptr;
    }

    void setLeft(BTreeNode<T> *left) {
        _left = left;
    }

    void setRight(BTreeNode<T> *right) {
        _right = right;
    }

    BTreeNode<T> *parent() const{
        return _parent;
    }

    void setParent(BTreeNode<T> *parent){
        _parent = parent;
    }

    bool switchNode(BTreeNode<T> *node) {
        if (nullptr == node)
            return false;
        _data = node->data();
        _left = node->left();
        _right = node->right();
        return true;
    }

    void printNode() const{
        std::string left = ((_left == nullptr) ? std::string("LNULL") : std::to_string(_left->data()));
        std::string right = ((_right == nullptr) ? std::string("RNULL") : std::to_string(_right->data()));
        std::cout << _data
                  << " -- "
                  << left
                  << " -- "
                  << right
                  << std::endl;
    }

    BTreeNode<T> *grandParent() {
        if (this->_parent != nullptr)
            return this->_parent->parent();
        else
            return NULL;
    }

    BTreeNode<T> *uncle() {
        BTreeNode<T> *g = grandParent();
        if (g == nullptr)
            return nullptr; // No grandparent means no uncle
        if (this->_parent == g->left())
            return g->right();
        else
            return g->left();
    }


protected:
    T _data;
    BTreeNode<T> *_left;
    BTreeNode<T> *_right;
    BTreeNode<T> *_parent;
};

#endif // BINARYTREENODE_H
