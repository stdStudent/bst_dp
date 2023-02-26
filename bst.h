#ifndef BST_DP_BST_H
#define BST_DP_BST_H

#include <iostream>
#include <vector>
#include <stack>
#include <sstream>
#include <string>
#include <optional>
#include <functional>
#include <random>
#include <set>

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
    size_t size;

    void _addLeaf(T& key, D& data, node* ptr) {
        if (root == nullptr) {
            root = createLeaf(key, data);
        } else if (key < ptr->key) {
            if (ptr->left != nullptr) {
                _addLeaf(key, data, ptr->left);
            } else {
                ptr->left = createLeaf(key, data);
            }
        } else if (key > ptr->key) {
            if (ptr->right != nullptr) {
                _addLeaf(key, data, ptr->right);
            } else {
                ptr->right = createLeaf(key, data);
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

            cout << ptr->key << ':' << ptr->data << ' ';

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

            //cout << "Deleted node with key: " << ptr->key << '\n';
            delete ptr;
        }
    }

    vector<pair<T, D>> _dump(node* ptr) const {
        vector<pair<T, D>> result;

        if (root != nullptr) {
            if (ptr->left != nullptr) {
                _dump(ptr->left);
            }

            result.push_back(make_pair(ptr->key, ptr->data));

            if (ptr->right != nullptr) {
                _dump(ptr->right);
            }
        } else {
            cout << "The BST is empty.";
        }

        return result;
    }

    int _h(node* ptr) {
        if (ptr == nullptr)
            return 0;

        return 1 + max(_h(ptr->left), _h(ptr->right));
    }

    void _print(node* ptr, int tabs) {
        if (ptr == nullptr) {
            for (int i = -1; i < tabs; ++i) {
                cout << "\t\t";
            }
            cout << "nil\n";
            return;
        }

        ++tabs;
        _print(ptr->right, tabs);

        for (int i = 0; i < tabs; ++i) {
            cout << "\t\t";
        }
        cout << ptr->key << ':' << ptr->data << '\n';

        _print(ptr->left, tabs);
    }

    node** _find(const T& key) const {
        node** current = (node**)(&root);
        while (*current && (*current)->key != key) {
            current = (*current)->key < key ? &((*current)->right) : &((*current)->left);
        }
        return current;
    }

public:
    bst() : root(nullptr), size(0) {}

    ~bst() {
        removeSubtree(root);
    }

    node* createLeaf(T& key, D& data) {
        node* n = new node;
        n->key = key;
        n->data = data;
        n->left = nullptr;
        n->right = nullptr;

        return n;
    }

    void addLeaf(T& key, D data) {
        _addLeaf((int &) key, data, root);
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

    vector<pair<T, D>> dump() const {
        return _dump(root);
    }

    int h() {
        return _h(root);
    }

    size_t sh() const {
        int h = 0, cur_h = 1;
        stack<pair<node*, int>> s;
        node* cur = root;

        while (cur || s.size()) {
            if (cur != nullptr) {
                s.push(make_pair(cur, cur_h));
                cur = cur->left;
                ++cur_h;
            } else {
                cur_h = s.top().second + 1;
                h = max(h, s.top().second);
                cur = s.top().first->right;
                s.pop();
            }
        }

        return h;
    }

    void print() {
        _print(root, -1);
    }

    optional<reference_wrapper<D>> find(const T& key) {
        auto node = _find(key);
        if (*node == nullptr) {
            return nullopt;
        }
        return (*node)->data;
    }

    bool insert(const T& key, const D& data) {
        node** n = _find(key);
        if (*n != nullptr) {
            (*n)->data = data;
        } else {
            *n = new node{key, data};
            ++size;
            return true;
        }
        return false;
    }

    bool remove(const T& key) {
        node** n = _find(key);
        if (*n == nullptr) {
            return false;
        }

        if ((*n)->left == nullptr) {
            node* tmp = *n;
            *n = tmp->right;
            delete tmp;
        } else if ((*n)->right == nullptr) {
            node* tmp = *n;
            *n = tmp->left;
            delete tmp;
        } else {
            node** tmp = &(*n)->right;
            while (*tmp != nullptr) {
                tmp = &(*tmp)->left;
            }
            (*n)->data = (*tmp)->data;
            (*n)->key = (*tmp)->key;
            node* delPtr = *tmp;
            *tmp = delPtr->right;
        }
        --size;
        return true;
    }

    optional<T> find_next(const T& key) const {
        node** current = (node**)(&root);
        node** lastLeft = nullptr;
        while (*current && (*current)->key != key) {
                                                                     // must be the same type for ','
            current = (*current)->key < key ? &((*current)->right) : (lastLeft = current, &((*current)->left));
        }

        if (*current == nullptr || (*current)->right == nullptr) {
            if (lastLeft == nullptr)
                return nullopt;
            else
                return (*lastLeft)->key;
        } else {
            current = &(*current)->right;
            while ((*current)->left != nullptr) {
                current = &(*current)->left;
            }
            return (*current)->key;
        }
        return nullopt;
    }

    friend ostream &operator<<(ostream &ostream, const bst& tree) {
        int cur_h = 0;
        stack<pair<node*, int>> s;
        node* cur = tree.root;

        while (cur || !s.empty()) {
            for (int i = 0; i < cur_h; ++i) {
                cout << (i == 0 ? "│" : "\t\t│"); // for root
            }

            if (cur != nullptr) {
                cout << (cur == tree.root ? "" : "├───── ") << cur->key << ':' << cur->data << '\n';
                s.push(make_pair(cur, cur_h));
                cur = cur->left;
                ++cur_h;
            } else {
                cout << "├───── nil" << '\n';
                cur_h = s.top().second + 1;
                cur = s.top().first->right;
                s.pop();
            }
        }

        return ostream;
    }

    void visitor(function<void(const T&, const D&)> worker) const {
        if (root == nullptr)
            return;

        stack<node*> s;
        node* cur = root;

        while (cur || s.size()) {
            if (cur != nullptr) {
                s.push(cur);
                cur = cur->left;
            } else {
                cur = s.top()->right;
                worker(s.top()->key, s.top()->data);
                s.pop();
            }
        }
    }

    vector<pair<T, D>> dumpv() const {
        vector <pair<T, D>> result;
        visitor([&](auto key, auto data){
            result.push_back(make_pair(key, data));
        });
        return result;
    }

    void generate(const int numOfElems) {
        std::random_device rd;
        std::mt19937 g(rd());

        set<T> randomKeys;
        while (randomKeys.size() != numOfElems) {
            randomKeys.insert(g());
        }

        vector<T> randomKeysOrder(randomKeys.begin(), randomKeys.end());
        std::shuffle(randomKeysOrder.begin(), randomKeysOrder.end(), g);

        for (const auto &item: randomKeysOrder) {
            insert(item, D());
        }
    }

};

#endif //BST_DP_BST_H
