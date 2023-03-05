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
#include <climits>

using namespace std;

enum colour {
    red,
    black
};

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

    int _mh(node *cur)
    {
        // Corner case. Should never be hit unless the code is called on root = nullptr
        if (cur == nullptr)
            return 0;

        // Base case : Leaf Node. This accounts for height = 1.
        if (cur->left == nullptr && cur->right == nullptr)
            return 1;

        int l = INT_MAX, r = INT_MAX;

        // If left subtree is not empty, recur for left subtree
        if (cur->left)
            l = _mh(cur->left);

        // If right subtree is not empty, recur for right subtree
        if (cur->right)
            r =  _mh(cur->right);

        // Height will be minimum of left and right height +1
        return min(l , r) + 1;
    }

    bool _is_bst_by_secondary_key(node* node, int min, int max)
    {
        /* an empty tree is BST */
        if (node == nullptr)
            return true;

        /* false if this node violates
        the min/max constraint */
        if (node->data < min || node->data > max)
            return false;

        /* otherwise check the subtrees recursively,
        tightening the min or max constraint */
        return    _is_bst_by_secondary_key(node->left, min, node->data - 1)
               && _is_bst_by_secondary_key(node->right, node->data + 1, max);
    }

    int _blackHeightByDataNoValidation(node* ptr) {
        if (ptr == nullptr)
            return 0;

        auto currNode = ptr;

        int leftHeight = _blackHeightByDataNoValidation(currNode->left);
        int rightHeight = _blackHeightByDataNoValidation(currNode->right);
        int add = currNode->data == black ? 1 : 0;

        return max(leftHeight, rightHeight) + add;
    }

    int _blackHeightByDataValidation(node* currNode) {
        if (currNode == NULL)
            return 0;

        int leftHeight = _blackHeightByDataValidation(currNode->left);
        int rightHeight = _blackHeightByDataValidation(currNode->right);
        int add = currNode->data == black ? 1 : 0;

        // The current subtree is not a red black tree if and only if
        // one or more of current node's children is a root of an invalid tree
        // or they contain different number of black nodes on a path to a null node.
        if (leftHeight == -1 || rightHeight == -1 || leftHeight != rightHeight)
            return -1;
        else
            //return leftHeight + add;
            return max(leftHeight, rightHeight) + add;
    }

    bool checkRedPoperty(node* ptr) {
        auto currNode = ptr;

        if (currNode == nullptr)
            return true;

        if (currNode->data == red && (currNode->left == nullptr || currNode->right == nullptr))
            return false;

        if (currNode->data == red && (currNode->left->data != black || currNode->right->data != black))
            return false;

        return checkRedPoperty(currNode->left) && checkRedPoperty(currNode->right);
    }

public:
    bst() : root(nullptr), size(0) {}

    bst(bst const& other) : root(nullptr), size(0) {
        std::vector<node const*> remaining;
        node const* cur = other.root;

        while (cur) {
            insert(cur->key, cur->data);
            if (cur->right) {
                remaining.push_back(cur->right);
            }

            if (cur->left) {
                cur = cur->left;
            } else if (remaining.empty()) {
                break;
            } else {
                cur = remaining.back();
                remaining.pop_back();
            }
        }
    }

    void traverse(node *c) {
        if (c != nullptr) {
            this->insert(c->key, c->data);
            traverse(c->left);
            traverse(c->right);
        }
    }

    bst& operator=(const bst& that) {
        if (this != &that) {
            node *c = that.root;
            traverse(c);
        }

        return *this;
    }

    bst& assign(const bst& that) {
        return this->operator=(that);
    }

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

    int mh() {
        return _mh(root);
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

    friend std::ostream &operator<<(std::ostream & ostream, const bst& tree) {
        std::vector<bool> pathesVisited;
        node *current = tree.root;
        bool toRightLeaf = false;
        int cur_h = 0;
        std::stack<std::pair<node*, int>> s;
        s.push(make_pair(nullptr, 0));

        do {
            for (int i = 0; i < pathesVisited.size(); ++i) {
                if (i == 0)
                    ostream << (pathesVisited[i] ? "│" : ""); // for root
                else
                    ostream << (pathesVisited[i] ? "\t│" : "\t");
            }

            if (toRightLeaf and cur_h == pathesVisited.size())
                pathesVisited[cur_h - 1] = false;

            toRightLeaf = false;
            if (current != nullptr) {
                ostream << (current == tree.root ? "" : "── ") << current->key << ':' << current->data << '\n';
                s.push({current->right, cur_h + 1});
                current = current->left;
                ++cur_h;
                pathesVisited.push_back(true);
            } else {
                ostream << "── nil" << std::endl;
                current = s.top().first;
                cur_h = s.top().second;
                s.pop();
                toRightLeaf = true;
                while (cur_h < pathesVisited.size()) {
                    pathesVisited.pop_back();
                }
            }
        } while (current || !s.empty());

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
        visitor([&result](auto key, auto data){
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

        // Use std::unique, as set is slow
        vector<T> randomKeysOrder(randomKeys.begin(), randomKeys.end());
        std::shuffle(randomKeysOrder.begin(), randomKeysOrder.end(), g);

        for (const auto &item: randomKeysOrder) {
            insert(item, D());
        }
    }

    bool is_bst_by_secondary_key() {
        return _is_bst_by_secondary_key(root, INT_MIN, INT_MAX);
    }

    bool s_is_bst_by_secondary_key() {
        stack<node*> Stack;
        node* cur = root;
        node* prev = nullptr;

        while (cur || !Stack.empty()) {
            // Traverse left subtree
            while (cur) {
                Stack.push(cur);
                cur = cur->left;
            }

            cur = Stack.top();
            Stack.pop();

            // If data value of root node less
            // than data value of left subtree
            if (prev && cur->data <= prev->data) {
                return false;
            }

            prev = cur;       // update prev
            cur = cur->right; // traverse right subtree
        }

        return true;
    }

    bool visit_is_bst_by_secondary_key() {
        optional<D> lastData = nullopt;
        bool result = true;
        visitor([&lastData, &result](auto key, auto data){
            if (lastData && lastData.value() >= data) {
                result = false;

            }
            lastData = data;
        });
        return result;
    }

    optional<pair<node*, node*>> wrong_keys() {
        stack<node*> Stack;
        node* cur = root;
        node* prev = nullptr;

        while (cur || !Stack.empty()) {
            // Traverse left subtree
            while (cur) {
                Stack.push(cur);
                cur = cur->left;
            }

            cur = Stack.top();
            Stack.pop();

            // If data value of root node less
            // than data value of left subtree
            if(prev && cur->key <= prev->key) {
                return make_pair(prev, cur);
            }

            prev = cur;       // update prev
            cur = cur->right; // traverse right subtree
        }

        return nullopt;
    }

    /*optional<pair<node*, node*>> visit_wrong_keys() {
        optional<node**> prev = nullopt;
        optional<node**> cur = nullopt;
        optional<pair<node*, node*>> result = nullopt;
        visitor([&prev, &cur, &result, this](auto key, auto data){
            prev = _find(key);
            auto curKey = find_next(key);
            cur = _find(curKey.value());

            if (*prev && (*cur.value())->key <= (*prev.value())->key) {
                result = make_pair((*prev.value()), (*cur.value()));
            }
        });
        return result;
    }*/

    void print_wrong_keys() {
        auto result = wrong_keys();
        if (result == nullopt)
            cout << "Correct tree.\n";
        else
            cout << "Possible wrong keys: "
                 << result.value().first->key  << ':' << result.value().first->data
                 << ", "
                 << result.value().second->key << ':' << result.value().second->data;
    }

    void replace_node_manually(const T& key, const T& new_key, const D& new_data) {
        auto toReplace = _find(key);
        (*toReplace)->key = new_key;
        (*toReplace)->data = new_data;
    }

    void replace_node_manually(const T& key, const T& new_key) {
        auto toReplace = _find(key);
        (*toReplace)->key = new_key;
    }

    int blackHeightByData() {
        return _blackHeightByDataNoValidation(root);
    }

    bool isRBT_byData() {
        if (root->data != black)
            return false;

        if (!checkRedPoperty(root))
            return false;

        if (_blackHeightByDataValidation(root) == -1)
            return false;

        return true;
    }
};

#endif //BST_DP_BST_H
