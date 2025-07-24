#include <iostream> 
#include "morseBinaryTree.h"

int main (int argc, char** argv)
{
    MorseBinaryTree tree;
    tree.printTree();

    int path[5] = {0, 1, 0, 1, 0}; // Example path for "U"
    char result = tree.parseMorseCode(path);
    std::cout << "U"

    return 0;
}
