//
//  emc_parse_utility.hpp
//  StaticData
//
//  Created by Abderrahmane on 08/02/2016.
//  Copyright © 2016 Efficiency Management Consulting. All rights reserved.
//

#ifndef emc_parse_utility_hpp
#define emc_parse_utility_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "unordered_map"

using namespace std;

struct Attribut {
    string name;
    string value;
    string type;

    Attribut();
    Attribut(string name, string value) {
        this->name = name;
        this->value = value;
    }
};

struct Node {
    string tagName;
    string value;
    Node* parent;
    vector<Attribut*> *attributes;
    vector<Node*> *childs;

    /* constructors*/
    Node ();
    Node (Node* parent, string tagName);

    /* setters and getters */
    void addChild (Node* n) {
        if (childs == nullptr) {
            childs = new vector<Node*>();
        }
        childs->push_back(n);
    }
    void addAttribute(Attribut* att) {
        if (attributes == nullptr)
            attributes = new vector<Attribut*>();
        if (att != nullptr)
            attributes->push_back(att);
    }
    void setTag (string tagName) {
        this->tagName = tagName;
    }
    void setValue (string value) {
        this->value = value;
    }
    void setParent (Node* n) {
        this->parent = n;
    }
    string getTag () {
        return tagName;
    }
    string getValue () {
        return value;
    }


};

struct ModelXML {
    Node* root;
    unordered_map<string, unordered_map<int, string>> elements;
    unordered_map<string, int> occurence;
    string type;

    ModelXML() {
    }

    ModelXML (Node* root, string type) {
        //this->root = root;
        root = nullptr;
        this->type = type;

    }
    void incrementOccurence(string str) {
        ++occurence[str];
    }

    int getOccurrence(string str) {
        if (occurence.find(str) != occurence.end())
            return occurence[str];
        else
            return 0;
    }

    void pushElement (string path, string str, int position) {
        // we suppose tags are NOT unique to retrieve the node
        elements[path][position] = str;
    }
};

#endif /* emc_parse_utility_hpp */
