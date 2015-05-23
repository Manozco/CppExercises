#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <functional>

#include "binarytreenode.h"

template<typename T>
class BinarySearchTree
{
public:
    typedef std::function<void(const BinaryTreeNode<T> *const)> TraversalFunc;
    BinarySearchTree(T rootData) {
        _root = new BinaryTreeNode<T>(rootData);
    }

    BinarySearchTree(BinaryTreeNode<T> *nodeRoot) {
        _root = nodeRoot;
    }

    BinaryTreeNode<T> *root() const {
        return _root;
    }

    BinaryTreeNode<T> *find(T data) {
        BinaryTreeNode<T> *curNode = _root;
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
        BinaryTreeNode<T> *curNode = _root;
        BinaryTreeNode<T> *parent = nullptr;
        BinaryTreeNode<T> *nodeToInsert = new BinaryTreeNode<T>(data);
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

    bool deleteNode (BinaryTreeNode<T> *nodeToDelete, int counter=0) {
        if (nullptr == nodeToDelete) {
            return false;
        } else {
            if (nullptr == nodeToDelete->left() && nullptr == nodeToDelete->right()) {
                delete nodeToDelete;
                nodeToDelete = nullptr;
                return true;
            } else if (nullptr == nodeToDelete->left() && nullptr != nodeToDelete->right()) {
                nodeToDelete->switchNode(nodeToDelete->right());
                delete nodeToDelete->right();
                nodeToDelete->setRight(nullptr);
                return true;
            } else if (nullptr != nodeToDelete->left() && nullptr == nodeToDelete->right()) {
                nodeToDelete->switchNode(nodeToDelete->left());
                delete nodeToDelete->left();
                nodeToDelete->setLeft(nullptr);
                return true;
            } else {
                BinaryTreeNode<T> *inOrderSuccessor = BinarySearchTree<T>(nodeToDelete->right()).min();
                BinaryTreeNode<T> *inOrderPredecessor = BinarySearchTree<T>(nodeToDelete->left()).max();
                if (inOrderPredecessor && inOrderPredecessor) {
                    if (counter % 2 == 0) {
                        nodeToDelete->setData(inOrderSuccessor->data());
                        this->deleteNode(inOrderSuccessor, ++counter);
                    } else {
                        nodeToDelete->setData(inOrderPredecessor->data());
                        this->deleteNode(inOrderPredecessor, ++counter);
                    }
                } else if (nullptr == inOrderPredecessor && inOrderSuccessor) {
                    nodeToDelete->setData(inOrderSuccessor->data());
                    this->deleteNode(inOrderSuccessor, ++counter);
                } else if (nullptr == inOrderSuccessor && inOrderPredecessor) {
                    nodeToDelete->setData(inOrderPredecessor->data());
                    this->deleteNode(inOrderPredecessor, ++counter);
                }
                return true;
            }
        }
    }

    void preorderTraversal(TraversalFunc func) {
        func(_root);
        if (_root->left())
            BinarySearchTree(_root->left()).preorderTraversal(func);
        if (_root->right())
            BinarySearchTree(_root->right()).preorderTraversal(func);
    }

    void print() {
        auto lambda = [](const BinaryTreeNode<T> *const node) {node->printNode();};
        this->preorderTraversal(lambda);
    }

    BinaryTreeNode<T> *min() {
        BinaryTreeNode<T> *cur_node = _root;
        while (cur_node->left()) {
            cur_node = cur_node->left();
        }
        return cur_node;
    }

    BinaryTreeNode<T> *max() {
        BinaryTreeNode<T> *cur_node = _root;
        while (cur_node->right()) {
            cur_node = cur_node->right();
        }
        return cur_node;
    }


private:
    BinaryTreeNode<T> *_root;
};

#endif // BINARYTREE_H
