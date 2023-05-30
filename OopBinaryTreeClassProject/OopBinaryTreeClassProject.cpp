#include <iostream>
#include "BinaryTree.h"

int main()
{
    BinaryTree<int> tree;

    tree.AddNodeReq(20);
    tree.AddNodeReq(10);
    tree.AddNodeReq(25);
    tree.AddNodeReq(5);
    tree.AddNodeReq(16);
    tree.AddNodeReq(22);
    tree.AddNodeReq(30);
    tree.AddNodeReq(13);
    tree.AddNodeReq(17);
    tree.AddNodeReq(14);
    tree.AddNodeReq(15);

    tree.Print();
    std::cout << "\n";

    Node<int>* curr = tree.Find(16);

    /*
    tree.DeleteNode(curr);

    tree.Print();
    std::cout << "\n";

    std::cout << tree.Root()->value;*/

    tree.DeleteBranch(curr);
    tree.Print();
    std::cout << "\n";


}
