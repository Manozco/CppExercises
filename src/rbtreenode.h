#ifndef RRBTreeNode_H
#define RRBTreeNode_H
#include <string>
#include <iostream>
#include <assert.h>
#include "utils.h"

//typedef bool Color;
//const Color BLACK = false;
//const Color RED = true;
enum Color {
    BLACK,
    RED
};

template<typename T>
class RBTreeNode
{
public:
    RBTreeNode(T data=nullptr, Color color=RED, RBTreeNode<T> *left=nullptr, RBTreeNode<T> *right=nullptr, RBTreeNode<T> *parent=nullptr)
        : _data(data)
        , _color(color)
        , _left(left)
        , _right(right)
        , _parent(parent){}

    ~RBTreeNode() {
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

    Color color() const {
        return _color;
    }

    void setColor(Color color) {
        _color = color;
    }

    RBTreeNode<T> *left() const {
        return _left;
    }

    RBTreeNode<T> *right() const {
        return _right;
    }

    void setLeft(RBTreeNode<T> *left) {
        _left = left;
    }

    void setRight(RBTreeNode<T> *right) {
        _right = right;
    }

    RBTreeNode<T> *parent() const{
        return _parent;
    }

    void setParent(RBTreeNode<T> *parent){
        _parent = parent;
    }

    bool switchNode(RBTreeNode<T> *node) {
        assert(node);
        if (nullptr == node)
            return false;
        _data = node->data();
        _left = node->left();
        _right = node->right();
        return true;
    }

    void printNode2() const{
        std::string left = ((_left == nullptr) ? std::string("LNULL") : std::to_string(_left->data()));
        std::string right = ((_right == nullptr) ? std::string("RNULL") : std::to_string(_right->data()));
        std::string color = (_color ? "RED" : "BLACK");
        std::cout << color
                  << " -- "
                  <<_data
                  << " -- "
                  << left
                  << " -- "
                  << right
                  << std::endl;
    }

    void printNode() const {
        std::string color = (_color ? "RED" : "BLACK");
        std::string left = "NULL";
        std::string right = "NULL";
        if (_left) {
            left = std::to_string(_left->data());
            left += std::string("-");
            left += (_left->color() == BLACK ? std::string("B") : std::string("R"));
        }
        if (_right) {
            right = std::to_string(_right->data());
            right += std::string("-");
            right += (_right->color() == BLACK ? std::string("B") : std::string("R"));
        }
        std::cout << left
                  << "<--"
                  << color
                  << "-"
                  << _data
                  <<"-->"
                  << right
                  <<std::endl;
    }

    inline
    RBTreeNode<T> *grandParent() {
        if (this->_parent != nullptr)
            return this->_parent->parent();
        else
            return NULL;
    }

    inline
    RBTreeNode<T> *uncle() {
        RBTreeNode<T> *g = grandParent();
        if (g == nullptr)
            return nullptr; // No grandparent means no uncle
        if (this->_parent == g->left())
            return g->right();
        else
            return g->left();
    }


    inline
    bool isLeftOfItsParent() {
        if (!parent())
            return false;
        if (this == parent()->left())
            return true;
        return false;
    }

    inline
    bool isRightOfItsParent() {
        if (!parent())
            return false;
        return !isLeftOfItsParent();
    }

    inline
    RBTreeNode<T> *sibling() {
        if (!parent())
            return nullptr;
        if (isLeftOfItsParent())
            return parent()->right();
        else
            return parent()->left();
    }

protected:
    T _data;
    Color _color;
    RBTreeNode<T> *_left;
    RBTreeNode<T> *_right;
    RBTreeNode<T> *_parent;
};
#endif // RRBTreeNode_H

