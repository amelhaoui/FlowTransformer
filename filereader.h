#ifndef FILEREADER_H
#define FILEREADER_H


#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <utility>
#include <string>

#include <QDebug>

using namespace std;

class FileReader
{
public:
    FileReader();
    FileReader(std::string  file_path, std::string file_type);

    virtual void readStructure() = 0;
    virtual void readMappingElements(unordered_map<string,
                            vector<int, vector<pair<string, string>>>> elementsByPath) = 0;

};

#endif // FILEREADER_H
