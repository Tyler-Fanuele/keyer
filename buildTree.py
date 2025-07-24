


# Efficient Morse code binary tree generator and C++ array printer

# Morse code mapping: char -> morse string
MORSE_CODE = {
    'A': '.-',    'B': '-...',  'C': '-.-.',  'D': '-..',   'E': '.',
    'F': '..-.',  'G': '--.',   'H': '....',  'I': '..',    'J': '.---',
    'K': '-.-',   'L': '.-..',  'M': '--',    'N': '-.',    'O': '---',
    'P': '.--.',  'Q': '--.-',  'R': '.-.',   'S': '...',   'T': '-',
    'U': '..-',   'V': '...-',  'W': '.--',   'X': '-..-',  'Y': '-.--',
    'Z': '--..',
    '1': '.----', '2': '..---', '3': '...--', '4': '....-', '5': '.....',
    '6': '-....', '7': '--...', '8': '---..', '9': '----.', '0': '-----',
}

import math

def tree_size(depth):
    return 2 ** depth - 1

# Find the max depth needed for the tree
max_depth = max(len(code) for code in MORSE_CODE.values()) + 1  # +1 for root
TREE_SIZE = tree_size(max_depth)

# Build the tree as a list
tree = ['\0'] * TREE_SIZE
tree[0] = ''  # root is empty string

for char, code in MORSE_CODE.items():
    idx = 0
    for c in code:
        if c == '.':
            idx = idx * 2 + 1
        elif c == '-':
            idx = idx * 2 + 2
    tree[idx] = char


def print_cpp_array(tree):
    print('// C++ Morse code binary tree array')
    print('const char _tree[%d] = {' % len(tree))
    line = '    '
    for i, v in enumerate(tree):
        if v == '\0' or v == '':
            s = "'\\0'"
        else:
            s = f"'{v}'"
        end = ',' if i < len(tree) - 1 else ''
        line += f'{s}{end} '
        if (i + 1) % 8 == 0 or i == len(tree) - 1:
            print(line)
            line = '    '
    print('};')


# Print the tree sideways, root on the left, children indented right






def print_tree(tree, idx=0, level=0, placeholder='.', branch=''):
    if idx >= len(tree):
        return
    # Print right child first (so it appears on top)
    print_tree(tree, idx * 2 + 2, level + 1, placeholder, branch='/-- ')
    # Print current node (show root as [root] if empty string, placeholder for blank)
    if tree[idx] == '\0':
        val = placeholder
    elif tree[idx] == '':
        val = '[root]'
    else:
        val = tree[idx]
    print('    ' * level + branch + f'{val}')
    # Always print children
    print_tree(tree, idx * 2 + 1, level + 1, placeholder, branch='\\-- ')

if __name__ == '__main__':
    print_cpp_array(tree)
    print('\nMorse Code Tree (file system style):')
    print_tree(tree)