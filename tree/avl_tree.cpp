#include <iostream>
#include <cstring>
#include <cassert>
#include <vector>

struct TreeNode {
    int data;
    int height;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int data, int height = 0) : data(data), height(height), left(nullptr), right(nullptr) {}
};

class AVLTree {
public:
    TreeNode* root;

    void free(TreeNode* r) {
        if (!r)
            return;
        free(r->left); free(r->right);
        delete r;
    }

    void copyFromHelper(TreeNode* curr, TreeNode* other) {
        if (!(other->left || other->right))
            return;

        if (other->left) 
            curr->left = new TreeNode(other->left->data);
        if (other->right)
            curr->right = new TreeNode(other->right->data);
        
        copyFromHelper(curr->left, other->left);
        copyFromHelper(curr->right, other->right);
    }

    void copyFrom(const AVLTree& other) {
        if (!other.root)
            return;
        
        root = new TreeNode(other.root->data);
        copyFromHelper(root, other.root);
    }   

    void printHelper(std::ostream& o, TreeNode* r) {
        if (!r)
            return;

        printHelper(o, r->left);
        o << r->data << " ";
        printHelper(o, r->right);
    }

    void printByLevelHelper(TreeNode* r, int level, std::vector<std::vector<int>>& v) {
        if (!r)
            return;

        if (v.size() == level)
            v.emplace_back();

        v[level].emplace_back(r->data);
        printByLevelHelper(r->left, level + 1, v);
        printByLevelHelper(r->right, level + 1, v);
    }

    int getHeight(TreeNode* r) {
        return r == nullptr ? -1 : r->height;
    }

public:
    AVLTree() : root(nullptr) {}

    AVLTree(const AVLTree& other) { copyFrom(other); }

    AVLTree& operator=(const AVLTree& other) {
        if (this != &other) {
            free(root);
            copyFrom(other);
        }
        return *this;
    }

    ~AVLTree() { free(root); };

    // can add Move semantics as well

    void print(std::ostream& o) { printHelper(o, root); }

    void add(const char* where, int data) { // just for testing
        if (strlen(where) == 0) {
            assert(root == nullptr);
            root = new TreeNode(data);
            return;
        }
    
        assert(root != nullptr);
        TreeNode* iter = root;
        int l = strlen(where);
        for(int i = 0; i < l - 1; ++i) {
            if (!iter)
                throw std::logic_error("Invalid path");
    
            if (where[i] == 'L') 
                iter = iter->left;
            if (where[i] == 'R') 
                iter = iter->right;
        }
    
        if (where[l - 1] == 'L')
            iter->left = new TreeNode(data);
        if (where[l - 1] == 'R')
            iter->right = new TreeNode(data);
    }

    void printByLevel(std::ostream& o) {
        std::vector<std::vector<int>> v;
        printByLevelHelper(root, 0, v);
        for (auto line : v) {
            for (int e : line) 
                o << e << " ";
            o << std::endl;
        }
    }

    void leftRotation(TreeNode*& x) {
        if (!x->right) 
            throw std::logic_error("Impossible to do LR like that");

        TreeNode* A = x->left;
        TreeNode* y = x->right;
        TreeNode* B = y->left;
        TreeNode* C = y->right;

        x->right = B;
        y->left = x;
        x->height = 1 + std::max(getHeight(A), getHeight(B));
        y->height = 1 + std::max(getHeight(x), getHeight(C));

        std::swap(x, y);
    }

    void rightRotation(TreeNode*& x) {
        if (!x->left)
            throw std::logic_error("Impossible to do RR like that");

        TreeNode* C = x->right;
        TreeNode* y = x->left;
        TreeNode* A = y->left;
        TreeNode* B = y->right;

        x->left = B;
        y->right = x;
        x->height = 1 + std::max(getHeight(B), getHeight(C));
        y->height = 1 + std::max(getHeight(A), getHeight(x));
        std::swap(x, y);
    }

    void addHelper(int data, TreeNode*& x) {
        if (!x->left && data < x->data) {
            x->left = new TreeNode(data);
            x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
            return;
        }
        else if (!x->right && data >= x->data) {
            x->right = new TreeNode(data);
            x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
            return;
        }
        else if (data < x->data) 
            addHelper(data, x->left);
        else   
            addHelper(data, x->right);


        // deal with rotations
        int h = getHeight(x->left) - getHeight(x->right);
        if (h == 2) {
            assert(x->left != nullptr);
            int hl = getHeight(x->left->left) - getHeight(x->left->right);

            if (hl == 1 || hl == 0) {
                rightRotation(x);
            }
            if (hl == -1) {
                leftRotation(x->left);
                rightRotation(x);
            }

        }
        if (h == -2) {
            assert(x->right != nullptr);
            int hr = getHeight(x->right->left) - getHeight(x->right->right);

            if (hr == -1 || hr == 0) {
                leftRotation(x);
            }
            if (hr == 1) {
                rightRotation(x->right);
                leftRotation(x);
            }
        }

        x->height = 1 + std::max(getHeight(x->left), getHeight(x->right)); // why do we need this line?
    }

    void add(int data) {
        if (!root) {
            root = new TreeNode(data);
            return;
        }
        addHelper(data, root);
    }
    
};

int main() {

    AVLTree t;
    for (int k = 0; k < 100; ++k)
        t.add(k);


    t.printByLevel(std::cout);

    std::cout << t.root->height;
    return 0;
}