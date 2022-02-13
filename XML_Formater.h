#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;


class XML_Formater
{
public:
    void xml_cutter(ifstream & input_File, vector<string> * output);
    XML_Formater();
    ~XML_Formater();
};

