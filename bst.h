#ifndef BST_DP_BST_H
#define BST_DP_BST_H

#include <iostream>

using namespace std;

template <class T, class D>
class bst {
private:
    struct node {
        T key;
        D data;
        node* left;
        node* right;
    };

    node* root;

    void _addLeaf(T& key, node* ptr) {
        if (root == nullptr) {
            root = createLeaf(key);
        } else if (key < ptr->key) {
            if (ptr->left != nullptr) {
                _addLeaf(key, ptr->left);
            } else {
                ptr->left = createLeaf(key);
            }
        } else if (key > ptr->key) {
            if (ptr->right != nullptr) {
                _addLeaf(key, ptr->right);
            } else {
                ptr->right = createLeaf(key);
            }
        } else {
            cout << key << "is already in the bst.\n";
        }
    }

    void _printInOrder(node* ptr) {
        if (root != nullptr) {
            if (ptr->left != nullptr) {
                _printInOrder(ptr->left);
            }

            cout << ptr->key << ' ';

            if (ptr->right != nullptr) {
                _printInOrder(ptr->right);
            }
        } else {
            cout << "The BST is empty.";
        }
    }

    node* _returnNode(T& key, node* ptr) {
        if (ptr != nullptr) {
            if (ptr->key == key) {
                return ptr;
            } else {
                if (key < ptr->key) {
                    return _returnNode(key, ptr->left);
                } else {
                    return _returnNode(key, ptr->right);
                }
            }
        } else {
            return nullptr;
        }
    }

    T _findSmallest(node* ptr) {
        if (root == nullptr) {
            cout << "The bst is empty.\n";
            return T();
        } else {
            if (ptr->left != nullptr) {
                return _findSmallest(ptr->left);
            } else {
                // Found smallest key, as the right key is always bigger.
                return ptr->key;
            }
        }
    }

    void removeRootMatch() {
        if (root != nullptr) {
            node* delPtr = root;
            //T rootKey = root->key;

            if (root->left == nullptr && root->right == nullptr) {
                // 0 children
                root = nullptr;
                delete delPtr;
            } else if (root->left == nullptr && root->right != nullptr) {
                // 1 right children
                root = root->right;
                delPtr->right = nullptr;
                delete delPtr;
                cout << "New root: " << root->key << '\n';
            } else if (root->left != nullptr && root->right == nullptr) {
                // 1 left children
                root = root->left;
                delPtr->left = nullptr;
                delete delPtr;
                cout << "New root: " << root->key << '\n';
            } else {
                // 2 children
                T smallestInRightSubtree = _findSmallest(root->right);
                _removeNode(smallestInRightSubtree, root);
                root->key = smallestInRightSubtree;
                cout << "New root: " << root->key << '\n';
            }
        } else {
            cout << "The tree is empty.\n";
        }
    }

    void removeMatch(node* parent, node* match, bool isLeft) {
        // if isLeft == true then match is the left child
        if (root != nullptr) {
            node* delPtr;
            T matchKey = match->key;
            T smallestInRightSubtree;

            if (match->left == nullptr && match->right == nullptr) {
                // 0 children
                delPtr = match;
                isLeft ? parent->left = nullptr : parent->right = nullptr;
                delete delPtr;
                cout << "Removed matched key: " << matchKey << '\n';
            } else if (match->left == nullptr && match->right != nullptr) {
                // 1 right child
                isLeft ? parent->left = match->right : parent->right = match->right;
                match->right = nullptr;
                delPtr = match;
                delete delPtr;
                cout << "Removed matched key: " << matchKey << '\n';
            } else if (match->left != nullptr && match->right == nullptr) {
                // 1 right child
                isLeft ? parent->left = match->left : parent->right = match->left;
                match->left = nullptr;
                delPtr = match;
                delete delPtr;
                cout << "Removed matched key: " << matchKey << '\n';
            } else {
                // 2 children
                smallestInRightSubtree = _findSmallest(match->right);
                _removeNode(smallestInRightSubtree, match);
                match->key = smallestInRightSubtree;
            }
        } else {
            cout << "The tree is empty.\n";
        }
    }

    void _removeNode(T& key, node* parent) {
        if (root != nullptr) {
            if (root->key == key) {
                removeRootMatch(); // delete root node and reconstruct
            } else {
                if (key < parent->key && parent->left != nullptr) {
                    parent->left->key == key ? removeMatch(parent, parent->left, true)
                                             : _removeNode(key, parent->left);
                } else if (key > parent->key && parent->right != nullptr) {
                    parent->right->key == key ? removeMatch(parent, parent->right, false)
                                             : _removeNode(key, parent->right);
                } else {
                    cout << "The key was not found: " << key << '\n';
                }
            }
        } else {
            cout << "The BST is empty.\n";
        }
    }

    void removeSubtree(node* ptr) {
        if (ptr != nullptr) {
            if (ptr->left != nullptr) {
                removeSubtree(ptr->left);
            }

            if (ptr->right != nullptr) {
                removeSubtree(ptr->right);
            }

            cout << "Deleted node with key: " << ptr->key << '\n';
            delete ptr;
        }
    }

public:
    bst() {
        root = nullptr;
    }

    ~bst() {
        removeSubtree(root);
    }

    node* createLeaf(T& key) {
        node* n = new node;
        n->key = key;
        n->left = nullptr;
        n->right = nullptr;

        return n;
    }

    void addLeaf(T& key) {
        _addLeaf(key, root);
    }

    void printInOrder() {
        _printInOrder(root);
        cout << '\n';
    }

    node* returnNode(T& key) {
        return _returnNode(key, root);
    }

    T returnRootKey() {
        if (root != nullptr) {
            return root->key;
        } else {
            cout << "No root found.\n";
            return T();
        }
    }

    void printChildren(T key) {
        node* ptr = returnNode(key);
        if (ptr != nullptr) {
            cout << "Parent node: " << ptr->key << '\n';
            ptr->left == nullptr ? cout << "Left child: null\n" : cout << "Left child: " << ptr->left->key << '\n';
            ptr->right == nullptr ? cout << "Left child: null\n" : cout << "Left child: " << ptr->right->key << '\n';
        } else {
            cout << "No such key: " << key << '\n';
        }
    }

    T findSmallest() {
        return _findSmallest(root);
    }

    void removeNode(T key) {
        _removeNode(key, root);
    }

};

#endif //BST_DP_BST_H