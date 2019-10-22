//
// Created by alvaro on 28/9/19.
//

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include "File.h"

#define EQUAL_CHAR '='
#define KEY_POSITION 0
#define VALUE_POSITION 1

File::File(const std::string& fileName) {
    this->openFile(fileName);
}

void File::openFile(const std::string& openingFile){
    this->readingFile.open(openingFile, std::ios::in | std::ios::binary);

    if(!readingFile)
        throw std::runtime_error("Error from Opening file.");
}

std::unordered_map<std::string, std::string> File::createMap(){
    std::string T;
    std::string line;
    std::vector<std::string> strings;
    std::unordered_map<std::string, std::string> map;

    while (std::getline(this->readingFile, line)){
        std::stringstream fullLine(line);

        while(getline(fullLine, T, EQUAL_CHAR)){
            strings.push_back(T);
        }

        std::string key = strings.at(KEY_POSITION);
        std::string value = strings.at(VALUE_POSITION);
        strings.clear();
        map[key] = value;
    }

    return std::move(map);
}

File::~File() {
    this->readingFile.close();
}