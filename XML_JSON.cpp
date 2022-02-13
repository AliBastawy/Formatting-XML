#include "XML_JSON.h"
#include "Nodes_Tree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include<stdio.h>
#include <stack>
#include <vector>






XML_JSON::XML_JSON()
{
}

void XML_JSON::tree_Void(Nodes_Tree * tree, ifstream & input)
{

    string line;
    Node* LOC_Node;
    stack<Node *> stack;
    int level = 1;
    int LOC_Flag_Child = 0;
    while (getline(input, line))
    {
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

                tree->Add_Parent_Void(LOC_Node, nullptr);




            }
            else
            {
                tree->Add_Child_Void(stack.top(), LOC_Node);
                                level++;
                tree->add_level_Void(LOC_Node, level);



            }
            stack.push(LOC_Node);

        }


        else if (line[0] == '<' && line[1] == '/')
        {
            //tree->add_level_Void(LOC_Node, level);

            level--;

            stack.pop();






        }
        else
        {

            tree->Set_Data_Void(LOC_Node, line);

        }





    }







}


void XML_JSON::Set_Repeated_Tags_Void(Node * Copy_Root)
{
    vector<Node*> Children_Vector = Copy_Root->children;

    if (Children_Vector.size() != 0)
    {
        if ((Children_Vector.size() > 1) && (Children_Vector[0]->Tag_name == Children_Vector[1]->Tag_name))
        {

            Copy_Root->Repeated_Tags = 1;
            //cout << Copy_Root->Repeated_Tags;
        }
        else
        {
            Copy_Root->Repeated_Tags = 0;
            //cout << Copy_Root->Repeated_Tags;
        }

        for (int i = 0;i < Children_Vector.size();i++)
        {
            Set_Repeated_Tags_Void(Children_Vector[i]);


        }

    }
}

void XML_JSON::Adjust_Spacing_Levels_Void(Node * Copy_Root)
{



        if ((Copy_Root->parent != nullptr) && (Copy_Root->parent->parent != nullptr) && (Copy_Root->parent->children.size() != 0) && (Copy_Root->parent->parent->Repeated_Tags == 1))
        {

            if (Copy_Root->children.size() == 0)
            {

                Copy_Root->level = Copy_Root->level + 1;
            }

                if (Copy_Root->children.size() != 0)
                {

                    Adjust_Spacing_Shifting__Void(Copy_Root);
                }



        }


        for (int i = 0;i < Copy_Root->children.size();i++)
        {
            if (Copy_Root->children.size() != 0)
            {

                Adjust_Spacing_Levels_Void(Copy_Root->children[i]);
            }

        }






}

void XML_JSON::Adjust_Spacing_Shifting__Void(Node * Copy_Root)
{


        Copy_Root->level = Copy_Root->level + 1;









    for (int i = 0;i < Copy_Root->children.size();i++)
    {
        if (Copy_Root->children.size() != 0)
        {

            Adjust_Spacing_Shifting__Void(Copy_Root->children[i]);
        }

    }





}



void XML_JSON::Print_JSON_Void(Node * Copy_Root,ofstream&output)
{

    // O(1)
    if (Copy_Root->parent == nullptr)
    {

        output << '{' << endl;

    }

    // O(N)
    if (Copy_Root->parent != nullptr &&Copy_Root->parent->Repeated_Tags == 1)
    {
        if ((Copy_Root->parent->children[0] == Copy_Root))
        {
            for (int i = 0; i < Copy_Root->level ;i++)
            {
                output << "  ";
            }
            output << '"' << Copy_Root->Tag_name << '"' << " : ";


        }

    }
    else
    {

        for (int i = 0; i < Copy_Root->level;i++)
        {
            output << "  ";
        }

        output << '"' << Copy_Root->Tag_name << '"' << " : ";

    }


    // O(1)
    if ((Copy_Root->parent != nullptr) && (Copy_Root->parent->Repeated_Tags == 1) && (Copy_Root->parent->children[0] == Copy_Root))
    {

        output << '[' << endl;

    }

    // O(N)
    if (Copy_Root->children.size() != 0)
    {
        if ((Copy_Root->parent != nullptr) && (Copy_Root->parent->Repeated_Tags == 1))
        {
            for (int i = 0; i < Copy_Root->level+1 ;i++)
            {
                output << "  ";
            }

        }
        output << '{' << endl;


    }
    else
    {
        if ((Copy_Root->parent != nullptr) && (Copy_Root->parent->Repeated_Tags == 1))
        {
            for (int i = 0; i < Copy_Root->level+1  ;i++)
            {
                output << "  ";
            }

        }
        output << '"' << Copy_Root->Tag_value << '"';
        if ((Copy_Root->parent != nullptr) && (Copy_Root->parent->children[(Copy_Root->parent->children.size()) - 1] == Copy_Root) )
        {
            output << endl;
        }
        else
        {
            output<< ',' << endl;
        }


    }


    for (int i = 0;i < Copy_Root->children.size();i++)
    {

        if (Copy_Root->children.size() != 0)
        {

            Print_JSON_Void(Copy_Root->children[i],output);

        }


    }

    // O(N)
    if ( (Copy_Root->parent != nullptr)  &&  ( Copy_Root->parent->Repeated_Tags == 1 && Copy_Root->parent->children[(Copy_Root->parent->children.size()) - 1] == Copy_Root) )
    {
        for (int i = 0; i < Copy_Root->level ;i++)
        {
            output << "  ";
        }
        output << ']' << endl;

    }

    // O(N)
    if((Copy_Root->parent != nullptr) && ( Copy_Root == Copy_Root->parent->children[( Copy_Root->parent->children.size() ) -1] ) )
    {
        for (int i = 0; i < Copy_Root->level-1 ;i++)
        {
            output << "  ";
        }
        if ((Copy_Root->parent != nullptr) && (Copy_Root->parent->parent != nullptr)&& (Copy_Root->parent->parent->children.size()!=0)  && (Copy_Root->parent != Copy_Root->parent->parent->children[(Copy_Root->parent->parent->children.size()) - 1]))
        {
            output << "}," << endl;

        }
        else
        {
            output << '}' << endl;


        }

    }

    // O(1)
    if (Copy_Root->parent == nullptr)
    {
        output << '}' << endl;
    }

}


XML_JSON::~XML_JSON()
{
}
