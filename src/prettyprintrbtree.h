#ifndef PRETTY_PRINT_RB_TREE
#define PRETTY_PRINT_RB_TREE
#include <fstream>
#include <iostream>
#include <deque>
#include <iomanip>
#include <sstream>
#include <string>
#include <math.h>
#include "rbtree.h"
#include "rbtreenode.h"

// Convert an integer value to string
template<typename T>
std::string nodeToString(RBTreeNode<T> *n) {
    std::ostringstream ss;
    if (n) {
        ss << (n->color() == BLACK ? "B": "R") << "-" << std::to_string(n->data());
    }
    return ss.str();
}

// Print the arm branches (eg, /    \ ) on a line
template<typename T>
void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<RBTreeNode<T> *>& nodesQueue, std::ostream& out) {
    typename std::deque<RBTreeNode<T>*>::const_iterator iter = nodesQueue.begin();
    for (int i = 0; i < nodesInThisLevel / 2; i++) {
        out << ((i == 0) ? std::setw(startLen-1) : std::setw(nodeSpaceLen-2)) << "" << ((*iter++) ? "/" : " ");
        out << std::setw(2*branchLen+2) << "" << ((*iter++) ? "\\" : " ");
    }
    out << std::endl;
}

// Print the branches and node (eg, ___10___ )
template<typename T>
void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<RBTreeNode<T> *>& nodesQueue, std::ostream& out) {
    typename std::deque<RBTreeNode<T>*>::const_iterator iter = nodesQueue.begin();
    for (int i = 0; i < nodesInThisLevel; i++, iter++) {
        out << ((i == 0) ? std::setw(startLen) : std::setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->left()) ? std::setfill('_') : std::setfill(' '));
        out << std::setw(branchLen+2) << ((*iter) ? nodeToString((*iter)) : "");
        out << ((*iter && (*iter)->right()) ? std::setfill('_') : std::setfill(' ')) << std::setw(branchLen) << "" << std::setfill(' ');
    }
    out << std::endl;
}

// Print the leaves only (just for the bottom row)
template<typename T>
void printLeaves(int indentSpace, int level, int nodesInThisLevel, const std::deque<RBTreeNode<T> *>& nodesQueue, std::ostream& out) {
    typename std::deque<RBTreeNode<T>*>::const_iterator iter = nodesQueue.begin();
    for (int i = 0; i < nodesInThisLevel; i++, iter++) {
        out << ((i == 0) ? std::setw(indentSpace+2) : std::setw(2*level+2)) << ((*iter) ? nodeToString((*iter)) : "");
    }
    out << std::endl;
}

// Pretty formatting of a binary tree to the output stream
// @ param
// level  Control how wide you want the tree to sparse (eg, level 1 has the minimum space between nodes, while level 2 has a larger space between nodes)
// indentSpace  Change this to add some indent space to the left (eg, indentSpace of 0 means the lowest level of the left node will stick to the left margin)
template<typename T>
void printPretty(RBTree<T> *rootTree, int level, int indentSpace, std::ostream& out) {
    int h = rootTree->maxHeight();
    int nodesInThisLevel = 1;

    int branchLen = 2*((int)pow(2.0,h)-1) - (3-level)*(int)pow(2.0,h-1);  // eq of the length of branch for each node of each level
    int nodeSpaceLen = 2 + (level+1)*(int)pow(2.0,h);  // distance between left neighbor node's right arm and right neighbor node's left arm
    int startLen = branchLen + (3-level) + indentSpace;  // starting space to the first node to print of each level (for the left most node of each level only)

    std::deque<RBTreeNode<T>*> nodesQueue;
    nodesQueue.push_back(rootTree->root());
    for (int r = 1; r < h; r++) {
        printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
        branchLen = branchLen/2 - 1;
        nodeSpaceLen = nodeSpaceLen/2 + 1;
        startLen = branchLen + (3-level) + indentSpace;
        printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);

        for (int i = 0; i < nodesInThisLevel; i++) {
            RBTreeNode<T> *currNode = nodesQueue.front();
            nodesQueue.pop_front();
            if (currNode) {
                nodesQueue.push_back(currNode->left());
                nodesQueue.push_back(currNode->right());
            } else {
                nodesQueue.push_back(NULL);
                nodesQueue.push_back(NULL);
            }
        }
        nodesInThisLevel *= 2;
    }
    printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
    printLeaves(indentSpace, level, nodesInThisLevel, nodesQueue, out);
}
#endif //PRETTY_PRINT_RB_TREE
