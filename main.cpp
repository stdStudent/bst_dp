#include <iostream>
#include "bst.h"

int main() {
    int TreeKeys[16] = {50, 76, 21, 4, 32, 64, 15, 52, 14, 100, 83, 2, 3, 70, 87, 80};
    bst<int, int> myTree;

    cout << myTree.findSmallest();

    myTree.printInOrder();
    for (int & TreeKey : TreeKeys) {
        myTree.addLeaf(TreeKey);
    }

    myTree.printInOrder();
    myTree.printChildren(4);
    myTree.printChildren(83);
    cout << myTree.findSmallest() << '\n';

    myTree.removeNode(56);
    myTree.printInOrder();

    return 0;
}
