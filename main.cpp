#include <iostream>
#include "bst.h"

template <typename T, typename D>
void print(const T& key, const D& data) {
    cout << key << ":" << data << " ";
}

int main() {
    int TreeKeys[16] = {50, 76, 21, 4, 32, 64, 15, 52, 14, 100, 83, 2, 3, 70, 87, 80};
    bst<int, int> myTree;
    for (int & TreeKey : TreeKeys) {
        myTree.insert(TreeKey, 0);
    }


    cout << "\n\ndumpv() test:\n";
    auto v = myTree.dumpv();
    for (const auto &item: v) {
        cout << item.first << ':' << item.second << ' ';
    }


    cout << "\n\nvisitor() test:\n";
    myTree.visitor(print<int, int>); cout << '\n';


    cout << "\n\noutput test:\n";
    std::cout << myTree;


    cout << "\n\nbst by data test:\n";
    bst<int, int> dataTree;
    for (int & TreeKey : TreeKeys) {
        dataTree.insert(TreeKey, TreeKey);
    }
    std::cout << "rec: " << dataTree.is_bst_by_secondary_key() << ", stack: " << dataTree.s_is_bst_by_secondary_key();


    cout << "\n\ngenerate() test:\n";
    bst<int, string> test;
    test.generate(256);
    cout << static_cast<float>((test.h() + test.mh()) / 2);


    return 0;
}
