////
////  main.cpp
////  StaticData
////
////  Created by Abderrahmane on 03/02/2016.
////  Copyright © 2016 Efficiency Management Consulting. All rights reserved.
////

#include <iostream>
#include <expat.h>
#include "emc_parse_utility.h"
#include <fstream>
#include <unordered_map>
#include <vector>
#include <QHash>
#include <stack>

#define BUFFER_SIZE 100000


using namespace std;

/**
Extract the xml structure in a tree  based on the xml input exemple.
This structure will be used to compare with the xsd structure defined
**/

int o = 0;
Node* root; //root of the tree
ModelXML* model; //xml structure
Node* current_parent; //active parent
Node* current_element; //active tag or element
stack<Node*> open_tags; //tags opened but no closed yet. element at top is the last opened
const string ATTRIBUTE = "Attributes";
QHash<QString, QString> mapping;

void
init(ModelXML *model_, QHash<QString, QString>& map) {
    root = nullptr;
    current_element = nullptr;
    current_parent = nullptr;
    model = model_;
    mapping = map;
}


string findFirstMappedParent(string str) {
    if (mapping.isEmpty())
        return "Mapping not ready";

    QString path_parent = QString::fromStdString(str);
    if (mapping.find(path_parent) != mapping.end()) {
        // found a tag which is mapped
        return str;
    } else {
        size_t pos = str.find_last_of(".");
        if (pos != string::npos) {
            return findFirstMappedParent(str.substr(0, pos));
       } else {
            return str;
        }
    }

}

string path = ""; //initialize empty path

/* first when start element is encountered */
void
start_element(void *data, const char *element, const char **attribute) {
    //we add current element to the string
    if (path.compare("") == 0) {
        //first string to enter, no need for a .
        if (strcmp(element, "items") != 0)
            path = string(element);
    } else {
        path = path + "." + string(element);
    }
    model->incrementOccurence(path);


    if (root == nullptr) {
        //init root node
        root = new Node(nullptr, string(element));
        current_element = root;
        current_parent = root;
    } else {
        //add current tag to the tree
        current_parent = open_tags.top();
        current_element = new Node(current_parent, string(element));

        //add attributes if available
        for (int index = 0 && path != ""; attribute[index]; index += 2) {
            Attribut* att = new Attribut(attribute[index], attribute[index+1]);
            current_element->addAttribute(att);
            //this element has attributes
            string key, value;
            key = path + "." + ATTRIBUTE + "." + attribute[index];
            value = attribute[index+1];
            //update elements from model
            //if (strcmp(""))
            string temp_path = findFirstMappedParent(path);
            cout << temp_path << "///" << path << endl;
//            if (temp_path.compare("") != 0)
                model->pushElement(key, value, model->getOccurrence(temp_path) - 1);
//            else
//                model->pushElement(key, value, model->getOccurrence(path) - 1); //check !!
        }

        current_parent->addChild(current_element);
    }

    //push to the top newly tag
    open_tags.push(current_element);
}

/* decrement the current level of the tree */
void
end_element(void *data, const char *el)
{
    //remove ending tag from the stack
    open_tags.pop();
    //truncate
    string element = ".";

    size_t pos = path.find_last_of(element);
    if (pos != string::npos)
        path = path.substr(0, pos);
    else
        path = "";
}


void
handle_data(void *data, const char *content, int length)
{
    int I = 0;

    //erase parazites from the begining
    for (I; I < length; I++) {
        if (content[I] != ' ' && content[I] != '\t'
                && content[I] != '\n') break;
    }

    if (I < length) {
        //display if != parazites
        string m_value(content);
        m_value = m_value.substr(0, length);
        string key = path + ".Attributes.value";
        current_element->setValue(m_value);
        /* filling the hash table to identify nodes values or attributes by their path name */
        string temp_path = findFirstMappedParent(path);
        //if (temp_path.compare(path) != 0) {
            model->pushElement(key, m_value, model->getOccurrence(temp_path) - 1);
        //} else {
         //   model->pushElement(key, m_value, model->getOccurrence(path) - 1); //check !!
       // }
    }
}


ModelXML*
parse_xml(char *buff, size_t buff_size, const char* file, ModelXML* model_src, QHash<QString, QString> &mapping) {
    init(model_src, mapping);

    FILE           *fp;
    fp = fopen(file, "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return nullptr;
    }

    XML_Parser      parser = XML_ParserCreate(NULL);
    XML_SetElementHandler(parser, start_element, end_element);
    XML_SetCharacterDataHandler(parser, handle_data);

    memset(buff, 0, buff_size);
    //printf("strlen(buff) before parsing: %d\n", (int)strlen(buff));

    size_t          file_size = 0;
    file_size = fread(buff, sizeof(char), buff_size, fp);

    /* parse the xml */
    if (XML_Parse(parser, buff, strlen(buff), XML_TRUE) == XML_STATUS_ERROR) {
        printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));
    }

    fclose(fp);
    XML_ParserFree(parser);

    model_src->root = root;
    return model;
}








