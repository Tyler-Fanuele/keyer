#include <iostream> 
#include "morseBinaryTree.h"

int main (int argc, char** argv)
{
    MorseBinaryTree tree;
    tree.printTree();

    // Example path for "U": "..-" (dot, dot, dash)
    char path[6] = {'.', '.', '-', '\0'};
    char result = tree.parseMorseCode(path);
    std::cout << "Decoded: " << result << std::endl;

    return 0;
}
