#include <iostream>
#include "bst.h"

int main() {
    int TreeKeys[16] = {50, 76, 21, 4, 32, 64, 15, 52, 14, 100, 83, 2, 3, 70, 87, 80};
    bst<int, int> myTree;

    //cout << myTree.findSmallest();

    myTree.printInOrder();
    for (int & TreeKey : TreeKeys) {
        cout << myTree.sh() << ' ' << myTree.h() << '\n';
        myTree.insert(TreeKey, 0);
    }

    myTree.print();
    //cout << myTree.find(4).key;

    myTree.printInOrder();
    myTree.printChildren(4);
    myTree.printChildren(83);
    cout << myTree.findSmallest() << '\n';

    auto v = myTree.dump();
    for (const auto &item: v) {
        cout << item.first << ':' << item.second << ' ';
    }

    cout << '\n';

    myTree.remove(52);
    myTree.printInOrder();

    return 0;
}
