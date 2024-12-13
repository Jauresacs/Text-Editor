#include "fileHandler.h"
#include <fstream>
#include <string>
#include <fstream>
#include <iostream>

FileHandler::FileHandler(QObject *parent)
    : QObject(parent)
{}

bool FileHandler::openFile(const std::string& filePath){
    std::ifstream file(filePath, std::ios::in);
    if (!file.is_open()){
        std::cout << "Error opening file: "<< filePath << std::endl;
        return 1;
    }

    std::string fileContent;
    file.seekg(0, std::ios::beg);
    file >> fileContent;

    std::cout << "File contents: " << fileContent << std::endl;

    file.close();
    return 0;
}

bool FileHandler::newFile(){
    return true;
}

bool FileHandler::quit(){
    return true;
}
