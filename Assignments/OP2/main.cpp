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
        auto pos = arg.find('=');
        if (pos == std::string::npos) continue;  // skip if no '=' found

        std::string key = arg.substr(0, pos);
        std::string value = arg.substr(pos + 1);

        if (key.size() < 3) continue;  // minimum length for f_x or s_x

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

    // //vector<int> nums = generateRandomUniqueShuffle(262144,0,262144);
    // vector<int> nums = generateRandomUniqueShuffle(32768,0,32768);
    //./main f_minval=0 f_maxval=256 f_nums=256 s_runtype=randomMix s_output=run0.256.256.txt 
    vector<int> treeNums = generateRandomUniqueShuffle(floatArgs["nums"],floatArgs["minval"],floatArgs["maxval"]);


    // Insert values into BST
    for(int i = 0; i < treeNums.size(); i++){
        bst.insert(treeNums[i]);
        avl.insert(treeNums[i]);
    }

    // Print in-order traversal of the BST
    // std::cout << "Inorder traversal of the BST: ";
    // bst.inorder();
    // std::cout << std::endl;

    // // Search for a key in the BST
    // int key = 40;
    // if (bst.search(key)) {
    //     std::cout << "Element " << key << " found in the BST." << std::endl;
    // } else {
    //     std::cout << "Element " << key << " not found in the BST." << std::endl;
    // }

    cout<<"Height:"<<bst.treeHeight()<<endl;
    cout<<"Height:"<<avl.treeHeight()<<endl;
    
    ofstream foutBST;
    foutBST.open("data/"+stringArgs["bstdot"]);

    ofstream foutAVL;
    foutAVL.open("data/"+stringArgs["avldot"]);

    //cout<<avl.toDotFormat();
    //graphviz online
    foutBST<<bst.toDotFormat();
    foutAVL<<avl.toDotFormat();

    return 0;
}
