#include "./headers/json.hpp" // Make sure this points to the correct path of json.hpp
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

using json = nlohmann::json;

void saveWords(json j) {
    ofstream fout;
    
    // opens json data file
    fout.open("./data/dictionary.json");

    for (auto &element : j.items()) {
        string key = element.key();
        fout << key << "\n";
    }
}

json loadJsonFile(string filePath) {

    // Load JSON object
    ifstream fileStream(filePath);
    string partialKey = " ";
    json myJson;
    if (fileStream.is_open()) {
        fileStream >> myJson;
        fileStream.close();
    } else {
        cerr << "Failed to open file: " << filePath << endl;
        return 1;
    }

    return myJson;
}