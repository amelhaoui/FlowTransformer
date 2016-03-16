#include "emc_parse_utility.h"


Node::Node() {
    parent = nullptr;
    value = "";
    tagName = "";
    childs = nullptr;
    attributes = nullptr;
}

Node:: Node (Node* parent, string tagName) {
    this->parent = parent;
    this->tagName = tagName;
    childs = new vector<Node*>();
    value = "";
    attributes = new vector<Attribut*>();
}
