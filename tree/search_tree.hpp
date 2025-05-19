#include <iostream>
#include <cstring>
#include <cassert>


template <typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(T data): data(data), left(nullptr), right(nullptr) {};
};


template <typename T>
class SearchTree {
private:
    TreeNode<T>* root;

    void free(TreeNode<T>* node);
    void copyFromHelper(TreeNode<T>*& oursNode, TreeNode<T>* othersNode);
    void copyFrom(const SearchTree& other);
    void printInOrder(std::ostream& o, TreeNode<T>* node) const;

public:
    SearchTree();
    SearchTree(const SearchTree& other);
    SearchTree& operator=(const SearchTree& other);
    ~SearchTree();

    SearchTree(SearchTree&& other);
    SearchTree& operator=(SearchTree&& other);

    void add(T data);
    bool containsHelper (T data, TreeNode<T>* node) const;
    bool contains(T data) const;

    void print(std::ostream& o) const;
};


template <typename T>
void SearchTree<T>::free(TreeNode<T>* node) {
    if (!node)
        return;

    free(node->left); free(node->right);
    delete node;
}

template <typename T>
void SearchTree<T>::copyFromHelper(TreeNode<T>*& oursNode, TreeNode<T>* othersNode) {
    if (!othersNode)
        return;

    oursNode = new TreeNode(othersNode->data);
    copyFromHelper(oursNode->left, othersNode->left);
    copyFromHelper(oursNode->right, othersNode->right);
}

template <typename T>
void SearchTree<T>::copyFrom(const SearchTree& other) {
    copyFromHelper(root, other.root);
}

template <typename T>
SearchTree<T>::SearchTree() : root(nullptr) { }

template <typename T>
SearchTree<T>::SearchTree(const SearchTree& other) {
    copyFrom(other);
}

template <typename T>
SearchTree<T>& SearchTree<T>::operator=(const SearchTree<T>& other) {
    if (this != &other) {
        free(root);
        copyFrom(other);
    }
    return *this;
}

template <typename T>
SearchTree<T>::~SearchTree() {
    free(root);
}

template <typename T>
SearchTree<T>::SearchTree(SearchTree<T>&& other) {
    free(root);
    root = other.root;
    other.root = nullptr;
}

template <typename T>
SearchTree<T>& SearchTree<T>::operator=(SearchTree<T>&& other) {
    if (this != &other) {
        free(root);
        root = other.root;
        other.root = nullptr;
    }
    return *this;
}

template <typename T>
void SearchTree<T>::printInOrder(std::ostream& o, TreeNode<T>* node) const {
    if (!node)
    return;

    printInOrder(o, node->left);
    o << node->data << " ";
    printInOrder(o, node->right);
}

template <typename T>
void SearchTree<T>::print(std::ostream& o) const {
    printInOrder(o, root);
}  

template <typename T>
void SearchTree<T>::add(T data) {
    if (!root) {
        root = new TreeNode<T> (data);
        return;
    }

    TreeNode<T>* iter = root;
    while (true) {
        if (iter->left == nullptr && data < iter->data){
            iter->left = new TreeNode<T>(data);
            break;
        }
        if (iter->right == nullptr && data >= iter->data){
            iter->right = new TreeNode<T>(data);
            break;
        }
        if (data < iter->data)
            iter = iter->left;
        else   
            iter = iter->right;
    }

}

template <typename T>
bool SearchTree<T>::containsHelper(T data, TreeNode<T>* node) const {
    if (!node)
        return false;
    if(node->data == data)
        return true;
    
    if (data < node->data)
        return containsHelper(data, node->left);
    else   
        return containsHelper(data, node->right);
}

template <typename T>
bool SearchTree<T>::contains(T data) const {
    return containsHelper(data, root);
}
