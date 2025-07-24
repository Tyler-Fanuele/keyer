#include "morseBinaryTree.h"
#include <iostream> 

MorseBinaryTree::MorseBinaryTree()
{
    
}

char MorseBinaryTree::parseMorseCode(const int path[5])
{
    int index = 0; // Start at the root of the tree
    for (int i = 0; i < 5; ++i)
    {
        if (path[i] == 0)
        {
            index = 2 * index + 1; // Go left (dit)
        }
        else if (path[i] == 1)
        {
            index = 2 * index + 2; // Go right (dah)
        }
        else
        {
            // Invalid input, return null character
            return '\0';
        }
        // Optional: Check bounds
        if (index >= TREESIZE)
            return '\0';
    }
    return _tree[index];
}

int MorseBinaryTree::printTree()
{
    std::cout << "\n";

    for (int i = 0; i < TREESIZE; i++)
    {
        if (_tree[i] != '\0')
        {
            std::cout << _tree[i];
        }
        else
        {
            std::cout << "-";
        }
    }
    return 0;
}
