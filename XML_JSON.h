#pragma once
#include "Nodes_Tree.h"
#include <iostream>
#include <fstream>

class XML_JSON
{
public:

    XML_JSON();

    void tree_Void(Nodes_Tree *tree, ifstream & input);
    void Set_Repeated_Tags_Void(Node * Copy_Root);
    void Adjust_Spacing_Levels_Void(Node * Copy_Root);//added
    void Adjust_Spacing_Shifting__Void(Node * Copy_Root);//added

    void Print_JSON_Void(Node * Copy_Root, ofstream&output);


    ~XML_JSON();
};

