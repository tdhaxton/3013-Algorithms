#include "AVLTree.hpp"
#include "binarySearchTree.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

std::map<std::string, float> floatArgs;
std::map<std::string, std::string> stringArgs;

/**
 * @brief  This function parses the command line arguments and stores them in the floatArgs and stringArgs maps
 * @note   
 * @param  argc: 
 * @param  argv: 
 * @retval None - uses the global vectors floatArgs and stringArgs
 */
void parseArguments(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        auto pos = arg.find('=');  // gets position of '=' in the string
        if (pos == std::string::npos) continue;  // skip if no '=' found

        std::string key = arg.substr(0, pos);  // gets the substring from first character of string to pos
        std::string value = arg.substr(pos + 1);    // gets the substring from pos to end of string/null (\0) character

        if (key.size() < 3) continue;  // minimum length for f_x or s_x

        // reads f_ or s_ to determine if it's a string or a float type
        std::string typePrefix = key.substr(0, 2);
        std::string actualKey = key.substr(2);

        if (typePrefix == "f_") {
            std::stringstream ss(value);
            float fvalue;
            ss >> fvalue;
            if (!ss.fail() && ss.eof()) {  // Ensure it's a valid float
                floatArgs[actualKey] = fvalue;
            } else {
                std::cerr << "Invalid float for key " << actualKey << std::endl;
            }
        } else if (typePrefix == "s_") {
            stringArgs[actualKey] = value;
        }
    }
}

/**
 * @brief   This function generates a vector of N unique random numbers between Low and High
 * @note   
 * @param  int N: how many numbers to generate 
 * @param  int Low: lowest value
 * @param  int High: highest value
 * @retval 
 */
std::vector<int> generateRandomUniqueShuffle(int N, int Low, int High) {
    std::vector<int> numbers;
    for (int i = Low; i <= High; ++i) {
        numbers.push_back(i);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(numbers.begin(), numbers.end(), g);

    numbers.resize(N);
    return numbers;
}


int main(int argc, char** argv) {
    parseArguments(argc, argv);

    // Output for verification
    std::cout << "Float arguments:\n";
    for (const auto& p : floatArgs) {
        std::cout << p.first << " = " << p.second << std::endl;
    }

    std::cout << "String arguments:\n";
    for (const auto& p : stringArgs) {
        std::cout << p.first << " = " << p.second << std::endl;
    }

    /*
    * Place checks here to make sure the arguments are valid and exit if they are not
    * Each experiment should have a certain number of arguments that are required
    * 
    */


    BinarySearchTree bst;
    AVLTree avl;

    // bst.insert(8);                   //! Lines 101 - 130 added for troubleshooting
    // bst.insert(6);
    // bst.insert(7);
    // bst.insert(5);
    // bst.insert(3);
    // bst.insert(0);
    // bst.insert(9);

    // avl.insert(8);
    // avl.insert(6);
    // avl.insert(7);
    // avl.insert(5);
    // avl.insert(3);
    // avl.insert(0);
    // avl.insert(9);

    // if (bst.search(9))
    //     cout << "9 is in the bst\n";
    // else
    //     cout << "9 is not in the bst\n";
    
    // if (avl.search(9))
    //     cout << "9 is in the avl\n";
    // else
    //     cout << "9 is not in the avl\n";

    // bst.remove(8);

    // avl.remove(8);
    

    //vector<int> nums = generateRandomUniqueShuffle(262144,0,262144);
    // vector<int> treeNums = generateRandomUniqueShuffle(32768,0,32768); //! Cut this
    //./main f_minval=0 f_maxval=256 f_nums=256 s_runtype=randomMix s_bstdot=bstdot.256.dot s_avldot=avldot.256.dot //! Command line template
    
    // Generate random numbers for each tree
    vector<int> treeNums = generateRandomUniqueShuffle(floatArgs["nums"],floatArgs["minval"],floatArgs["maxval"]); //! readd 135 - 142

    // Generate random numbers to search for in each tree
    vector<int> treeSearches = generateRandomUniqueShuffle(floatArgs["nums"],floatArgs["minval"],floatArgs["maxval"]);

    // Generate random numbers delete from each tree, if found
    vector<int> treeDeletions = generateRandomUniqueShuffle(floatArgs["nums"],floatArgs["minval"],floatArgs["maxval"]);

    // Insert values into BST and AVL Tree
    for(int i = 0; i < treeNums.size(); i++) {
        bst.insert(treeNums[i]);
        avl.insert(treeNums[i]);
    }

    // //! Loop to output treeNums to console for troubleshooting
    // cout << "Contents of treeNums vector: " << endl;
    // for(int i = 0; i < treeNums.size(); i++) {
    //     cout << treeNums[i] << " ";
    // }
    // cout << endl;

    // bst.insert(32769);  //! Lines 150 - 151 added for troubleshooting
    // avl.insert(32769);

    // Logic for randomMix, max insertions, max deletions, and max searches
    if (stringArgs["runtype"] == "randomMix") {
        
       // Search each tree for random values
        for(int i = 0; i < treeSearches.size(); i++){
            bst.search(treeSearches[i]);
            avl.search(treeSearches[i]);
        }

        // Delete random values from each tree
        for(int i = 0; i < treeDeletions.size(); i++){
            bst.remove(treeDeletions[i]);
            avl.remove(treeDeletions[i]);
        }

    } else if (stringArgs["runtype"] == "deletions") {

        // Delete random values from each tree
        for(int i = 0; i < treeDeletions.size(); i++){
            bst.remove(treeDeletions[i]);
            avl.remove(treeDeletions[i]);
        }

    } else if (stringArgs["runtype"] == "searches") {

        // Search each tree for random values
        for(int i = 0; i < treeSearches.size(); i++){
            bst.search(treeSearches[i]);
            avl.search(treeSearches[i]);
        }

    }

    // // Print in-order traversal of the BST
    // std::cout << "Inorder traversal of the BST: ";
    // bst.inorder();
    // std::cout << std::endl;

    // cout<<bst.toDotFormat();    //! Added for troubleshooting
    // cout<<avl.toDotFormat();    //! Added for troubleshooting

    // Search for a key in the BST
    // int key = 40;
        
    // while (key != 0) {
    //     if (bst.search(key)) {
    //         std::cout << "Element " << key << " found in the BST." << std::endl;
    //         bst.remove(key);
    //     } else {
    //         std::cout << "Element " << key << " not found in the BST." << std::endl;
    //     }

    //     if (avl.search(key)) {
    //         std::cout << "Element " << key << " found in the AVL." << std::endl;
    //         avl.remove(key);
    //     } else {
    //         std::cout << "Element " << key << " not found in the AVL." << std::endl;
    //     }
    //     bst.inorder();
    //     cout << endl;
    //     avl.inorder();
    //     cout << endl;

    //     cout << "Enter a key: ";
    //     cin >> key;
    // }

    cout << "BST Height:" << bst.treeHeight()<<endl;
    cout << "AVL Height:"<< avl.treeHeight()<<endl;
    cout << "BST Comparisons:" << bst.getComps()<<endl;
    cout << "AVL Comparisons:" << avl.getComps()<<endl;
    
    ofstream foutBST;
    foutBST.open("data/"+stringArgs["bstdot"]);

    ofstream foutAVL;
    foutAVL.open("data/"+stringArgs["avldot"]);

    //cout<<avl.toDotFormat();
    //graphviz online
    foutBST << bst.toDotFormat();
    foutAVL << avl.toDotFormat();
    return 0;
}
