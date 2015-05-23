#ifndef BINARYTREENODE_H
#define BINARYTREENODE_H
#include <string>
#include <iostream>


//class BinarySearchTree;

template<typename T>
class BinaryTreeNode
{
public:
    BinaryTreeNode(T data, BinaryTreeNode<T> *left=nullptr, BinaryTreeNode<T> *right=nullptr, BinaryTreeNode<T> *parent=nullptr)
        : _data(data)
        , _left(left)
        , _right(right)
        , _parent(parent){}
    ~BinaryTreeNode() {
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

    BinaryTreeNode<T> *left() const {
        if (_left)
            return _left;
        return nullptr;
    }

    BinaryTreeNode<T> *right() const {
        if (_right)
            return _right;
        return nullptr;
    }

    void setLeft(BinaryTreeNode<T> *left) {
        _left = left;
    }

    void setRight(BinaryTreeNode<T> *right) {
        _right = right;
    }

    BinaryTreeNode<T> *parent() const{
        return _parent;
    }

    void setParent(BinaryTreeNode<T> *parent){
        _parent = parent;
    }

    bool switchNode(BinaryTreeNode<T> *node) {
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

    BinaryTreeNode<T> *grandParent() {
        if (this->_parent != nullptr)
            return this->_parent->parent();
        else
            return NULL;
    }

    BinaryTreeNode<T> *uncle() {
        BinaryTreeNode<T> *g = grandParent();
        if (g == nullptr)
            return nullptr; // No grandparent means no uncle
        if (this->_parent == g->left())
            return g->right();
        else
            return g->left();
    }


private:
    T _data;
    BinaryTreeNode<T> *_left;
    BinaryTreeNode<T> *_right;
    BinaryTreeNode<T> *_parent;
};

#endif // BINARYTREENODE_H
