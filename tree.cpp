#include "tree.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include<stdio.h>
#include <fstream>
#include <stack>
#include "Nodes_Tree.h"





using namespace std;



void tree::tree_creator(Nodes_Tree * tree, vector<string> *input, vector<string> * vectorXML)
{
    string line;
    Node* LOC_Node;
    stack<Node *> stack;
    int level = 1;

    for (int x = 0; x < input->size(); x++)
    {
        line = input->at(x);

        if (line[0] == '<' && (line[1] == '!' || line[1] == '?'))
        {
            continue;
        }
        if (line[0] == '<' && line[1] != '/')
        {

            int End_Line;
            for (int i = 1; i < line.length(); i++)
            {
                End_Line = i;
                if (line[i] == ' ')
                {
                    break;
                }
            }
            string Tag_Name = line.substr(1, End_Line - 1);
            LOC_Node = new Node(Tag_Name);
            if (stack.size() == 0)
            {
                tree->Add_root_Void(LOC_Node);
                tree->add_level_Void(LOC_Node, level);

                string s;

                for (int i = 0;i < level - 1;i++)
                {
                    s += "    ";
                }
                s += '<' + LOC_Node->Tag_name + ">";
                vectorXML->push_back(s);
                level++;



            }
            else
            {
                tree->Add_Child_Void(stack.top(), LOC_Node);
                tree->add_level_Void(LOC_Node, level);

                string s;

                for (int i = 0; i < level - 1;i++)
                {
                    s += "    ";
                }
                s += '<' + LOC_Node->Tag_name + ">";
                vectorXML->push_back(s);
                level++;


            }
            stack.push(LOC_Node);


        }


        else if (line[0] == '<' && line[1] == '/')
        {
            string s;

            level--;
            for (int i = 0; i < level - 1;i++)
            {
                s += "    ";
            }
            s += "</" + stack.top()->Tag_name + '>' ;
            vectorXML->push_back(s);
            stack.pop();


        }
        else
        {

            string s;

            tree->Set_Data_Void(LOC_Node, line);
            for (int i = 0;i < level - 1;i++)
            {

                s += "    ";
            }
            s += LOC_Node->Tag_value;
            vectorXML->push_back(s);



        }





    }






}

tree::tree()
{
}


tree::~tree()
{
}
