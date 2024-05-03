## OP2 - BSTvAVL - Balanced vs Unbalanced

### Timothy Haxton

### Description Utilizing provided Binary Search and AVL trees, this project compares the performance of a BST that is not actively balanced vs a tree that actively uses rotations to maintain a balanced tree. It will do this by keeping track of comparisons made to perform random insertion, deletion, and/or search operations using differently sized datasets. Experiments will vary between lots of insertions and deletions, lots of searches, and equal amounts of insertions, deletions, and searches.

### Files and Folders

|   #   | File                                                          | Description                                                                  |
| :---: | ------------------------------------------------------------- | ---------------------------------------------------------------------------- |
|   1   | [main.cpp](Assignments/OP2/main.cpp)                          | Main driver of my project that launches the application                      |
|   2   | [binarySearchTree.hpp](Assignments/OP2/binarySearchTree.hpp)  | Binary Search Tree class                                                     |
|   3   | [AVLTree.hpp](Assignments/OP2/AVLTree.hpp)                    | AVL Tree class                                                               |

### Instructions

- This program is designed to run through command line input. After compiling the program, it can be run from the following Linux line template:
- ./main f_minval=0 f_maxval=512 f_nums=512 s_runtype=insertions s_bstdot=bstdot8.512.dot s_avldot=avldot8.512.dot
- I will break down the line above on piece at a time:
- ./main executes the program.
- The numerical values in f_minval=0, f_maxval=512, and f_nums=512 are modifiable floating point values and determine the minimum value number, the maximum value number, and the quantity of numbers input into each search tree.
- s_runtype=insertions is a string value. The recognized runtypes are "insertions", "deletions", "searches", and "randomMix". To change the runtype, input the desired value after the equal sign. For instance, to run a search-heavy experiment, input s_runtype=searches. "insertions" measures only the number of comparisons and tree size of each tree after inserting the number of values specified by f_nums. "deletions" measures the number of comparisons and resulting tree size after inserting the number of values specified by f_nums and then deleting the same quantity of randomly generated numbers. "searches" measures the number of comparisons and resulting tree size after inserting the number of values specified by f_nums and then searching for the same quantity of randomly generated numbers. Finally, "randomMix" measures the number of comparisons and resulting tree size after inserting the number of values specified by f_nums and then searching for and deleting the same quantity of randomly generated numbers.
- s_bstdot=bstdot8.512.dot and s_avldot=avldot8.512.dot are the file naming conventions for the binary search tree and AVL tree dot graph outputs. Change the input after the equal sign to change the name of the file that you want to create. s_bstdot creates a binary search tree dot file, and s_avldot creates an AVL tree dot file. All created files can be copied and pasted into the Graphvis Online tool at the following website: https://dreampuf.github.io/GraphvizOnline/#digraph%20G%20%7B%0A%0A%20%20subgraph%20cluster_0%20%7B%0A%20%20%20%20style%3Dfilled%3B%0A%20%20%20%20color%3Dlightgrey%3B%0A%20%20%20%20node%20%5Bstyle%3Dfilled%2Ccolor%3Dwhite%5D%3B%0A%20%20%20%20a0%20-%3E%20a1%20-%3E%20a2%20-%3E%20a3%3B%0A%20%20%20%20label%20%3D%20%22process%20%231%22%3B%0A%20%20%7D%0A%0A%20%20subgraph%20cluster_1%20%7B%0A%20%20%20%20node%20%5Bstyle%3Dfilled%5D%3B%0A%20%20%20%20b0%20-%3E%20b1%20-%3E%20b2%20-%3E%20b3%3B%0A%20%20%20%20label%20%3D%20%22process%20%232%22%3B%0A%20%20%20%20color%3Dblue%0A%20%20%7D%0A%20%20start%20-%3E%20a0%3B%0A%20%20start%20-%3E%20b0%3B%0A%20%20a1%20-%3E%20b3%3B%0A%20%20b2%20-%3E%20a3%3B%0A%20%20a3%20-%3E%20a0%3B%0A%20%20a3%20-%3E%20end%3B%0A%20%20b3%20-%3E%20end%3B%0A%0A%20%20start%20%5Bshape%3DMdiamond%5D%3B%0A%20%20end%20%5Bshape%3DMsquare%5D%3B%0A%7D

### Experiment

- My experiment involved 24 runs of varying input quantities and values. Each run produced a binary search tree and an AVL tree for comparison. All output files and a summary of all runs are contained in the data folder. 

### Results

- The AVL tree proved superior in all runs, providing a shorter and more complete tree and requiring fewer comparisons in each run type.