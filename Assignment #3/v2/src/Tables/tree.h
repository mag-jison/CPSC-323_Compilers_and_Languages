#pragma once

#include <iostream> 
#include <string>
#include <vector>
#include <iterator>
#include <fstream>

using namespace std;

template <class T>
struct Node {
    T value;
    bool visit;
    size_t depth;
    Node<T>* parent;
    vector<Node<T>*> child;

    Node (T v) : value(v), visit(false), depth(0)
    {
       child.push_back(nullptr);
    }

    Node (T v, vector<T> rhs) : value(v), visit(false), depth(0)
    {
        for (T e : rhs) {
            Node<T>* temp = new Node<T>(e); // assigns every child node with its own value
            child.push_back(temp);
        }
    }
};

template <class T>
class Tree {
private:
    Node<T>* root;
    size_t depth;
    ofstream output;

public:
    Tree() : root(nullptr), depth(0) {}
    
    const Node<T>* const getRoot() const { return root; }
    void printTree();
    void preOrderTraversal(Node<T>*);
    void setDepth(Node<T>*);
    void makeTree(T, const vector<T>&);
    void makeTreeRecursive(Node<T>*, Node<T>*, Node<T>*);
};

template <class T>
void Tree<T>::printTree(){
    output.open("files/out.txt");
    output << "+--Parse Tree--+" << endl;

    if (!root)
        output << "EMPTY TREE!";
    else
        preOrderTraversal(root);

    output << "\n+--------------+\n";
    output.close();
}

template <class T>
void Tree<T>::preOrderTraversal(Node<T>* curr){
    for (size_t i = 0; i < curr->depth; ++i)
        curr->value = "|\t" + curr->value;

    output << endl << curr->value;

    for (size_t i = 0; i < curr->child.size(); ++i) {
        if (curr->child[i] != nullptr)
            preOrderTraversal(curr->child[i]);
    }
}

template <class T>
void Tree<T>::makeTree(T n, const vector<T>& rhs){
    Node<T>* curr = new Node<T>(n, rhs);

    if (!root)
        root = curr;
    else
        makeTreeRecursive(root, root, curr);
        
    setDepth(root);
}

template <class T>
void Tree<T>::makeTreeRecursive(Node<T>* curr, Node<T>* prev, Node<T>* key){
    for (size_t i = 0; i < curr->child.size(); ++i) {
        curr->parent = prev;
        if (curr->child[i] == nullptr)
            return;
        else if (curr->child[i]->value == key->value && !curr->child[i]->visit) {
            curr->child[i] = key;
            curr->child[i]->visit = true;
        }
        else
            makeTreeRecursive(curr->child[i], curr, key);
    }
}

template <typename T> 
void Tree<T>::setDepth(Node<T>* curr) {
    for (size_t i = 0; i < curr->child.size(); ++i) {
        if (!curr->child[i])
            curr->depth = depth;
        else {
            curr->child[i]->depth = ++depth;
            setDepth(curr->child[i]);
            depth--;
        }
    }
}