#include <iostream>
#include "bst.h"

template <typename T, typename D>
void print(const T& key, const D& data) {
    cout << key << ":" << data << " ";
}

int main() {
    colour r = red;
    colour b = black;
    auto colours = {b, b, r, b, b, /*b, /*r, r, b, b, b, b, r, b, b, r*/};

    int TreeKeys[16] = {50, 76, 21, 4, 32, /*64, /*15, 52, 14, 100, 83, 2, 3, 70, 87, 80*/};
    bst<int, colour> myTree;

    int i = 0;
    for (const auto &item: colours) {
        myTree.insert(TreeKeys[i++], item);
    }

    cout << myTree;

    cout << '\n';
    bst<int, colour> newTree = myTree;
    //bst<int, colour> newTree = myTree.assign(newTree);
    cout << newTree << '\n';
    cout << "operator==(): " << (myTree == newTree ? "true" : "false") << '\n';

//    cout << "Test black height:\n";
//    cout << myTree.blackHeight() << '\n';
//    cout << (myTree.isRBT_byData() ? "true" : "false") << '\n';
//    cout << (myTree.isRBT() ? "true" : "false") << '\n';
//    cout << myTree.isRedProperty();

    cout << "\n\n";
    myTree.rotateRight(myTree.getNodePtrPtr(21));
    cout << myTree;
    myTree.rotateLeft(myTree.getNodePtrPtr(21));
    cout << myTree;

    cout << "same_content(): " << (myTree.same_content(newTree) ? "true" : "false") << '\n';
    cout << "operator==(): " << (myTree == newTree ? "true" : "false") << '\n';
    newTree.insert(15, r);
    cout << "same_content(): " << (myTree.same_content(newTree) ? "true" : "false") << '\n';
    myTree.insert(15, r);
    cout << "same_content(): " << (myTree.same_content(newTree) ? "true" : "false") << '\n';


//    for (int & TreeKey : TreeKeys) {
//        myTree.insert(TreeKey, 0);
//    }
//    cout << "\n\ndumpv() test:\n";
//    auto v = myTree.dumpv();
//    for (const auto &item: v) {
//        cout << item.first << ':' << item.second << ' ';
//    }
//
//
//    cout << "\n\nvisitor() test:\n";
//    myTree.visitor(print<int, int>); cout << '\n';
//
//
//    cout << "\n\noutput test:\n";
//    std::cout << myTree;
//
//
//    cout << "\n\nbst by data test:\n";
//    bst<int, int> dataTree;
//    for (int & TreeKey : TreeKeys) {
//        dataTree.insert(TreeKey, TreeKey);
//    }
//    std::cout << "rec: " << dataTree.is_bst_by_secondary_key()
//              << ", stack: " << dataTree.s_is_bst_by_secondary_key()
//              << ", visit: " << dataTree.visit_is_bst_by_secondary_key();
//
//
//    cout << "\n\ngenerate() test:\n";
//    bst<int, string> test;
//    test.generate(4096);
//    cout << test.h() << ", " << "2^12 => 12 * 2.3 = 27.6";
//
//
//    cout << "\n\ntest wrong_keys():\n";
//    int toCorruptTreeKeys[5] = {6, 2, 7, 1, 3};
//    bst<int, int> corTree;
//    for (int & toCorruptTreeKey : toCorruptTreeKeys) {
//        corTree.insert(toCorruptTreeKey, 0);
//    }
//    cout << corTree << '\n';
//    corTree.print_wrong_keys();
//    corTree.replace_node_manually(2, 4);
//    cout << '\n' << corTree << '\n';
//    corTree.print_wrong_keys();

    return 0;
}
