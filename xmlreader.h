#ifndef XMLREADER_H
#define XMLREADER_H

#include <filereader.h>

class XMLReader : public FileReader
{
public:
    XMLReader();

    void readStructure();
    void readMappingElements(unordered_map<string, vector<int, vector<pair<string, string>>>>& elementsByPath,
                             unordered_map<string, string>& mapping);
private:
    unordered_map<string, vector<int, vector<pair<string, string>>>>* elementsByPath;
};

#endif // XMLREADER_H
