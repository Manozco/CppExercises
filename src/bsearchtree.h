#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <functional>
#include "btreenode.h"

template<typename T>
class BSearchTree
{
public:
    typedef std::function<void(const BTreeNode<T> *const)> TraversalFunc;
    BSearchTree() {
        _root = nullptr;
    }
    BSearchTree(T rootData) {
        _root = new BTreeNode<T>(rootData);
    }

    BSearchTree(BTreeNode<T> *nodeRoot) {
        _root = nodeRoot;
    }

    BTreeNode<T> *root() const {
        return _root;
    }

    BTreeNode<T> *find(T data) {
        BTreeNode<T> *curNode = _root;
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
        BTreeNode<T> *nodeToInsert = new BTreeNode<T>(data);
        return _insert(nodeToInsert);
    }

    bool deleteNode (BTreeNode<T> *nodeToDelete, int counter=0) {
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
                BTreeNode<T> *inOrderSuccessor = BSearchTree<T>(nodeToDelete->right()).min();
                BTreeNode<T> *inOrderPredecessor = BSearchTree<T>(nodeToDelete->left()).max();
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
            BSearchTree(_root->left()).preorderTraversal(func);
        if (_root->right())
            BSearchTree(_root->right()).preorderTraversal(func);
    }

    void print() {
        auto lambda = [](const BTreeNode<T> *const node) {node->printNode();};
        this->preorderTraversal(lambda);
    }

    BTreeNode<T> *min() {
        BTreeNode<T> *cur_node = _root;
        while (cur_node->left()) {
            cur_node = cur_node->left();
        }
        return cur_node;
    }

    BTreeNode<T> *max() {
        BTreeNode<T> *cur_node = _root;
        while (cur_node->right()) {
            cur_node = cur_node->right();
        }
        return cur_node;
    }

protected:
    bool _insert(BTreeNode<T> *nodeToInsert) {
        BTreeNode<T> *curNode = _root;
        BTreeNode<T> *parent = nullptr;
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

protected:
    BTreeNode<T> *_root;
};

#endif // BINARYTREE_H
