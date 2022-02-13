#include "Nodes_Tree.h"
#include <string>
#include <stdlib.h>
#include<stdio.h>
#include <iostream>
#include <fstream>
using namespace std;







Nodes_Tree::Nodes_Tree() {
        this->root = nullptr;
    }


    string Nodes_Tree::Get_Data_String(Node * LOC_Node) {
        return LOC_Node->Tag_value;
    }
    vector <Node *> Nodes_Tree:: Get_Childern_Vector(Node *LOC_Node) {
        return LOC_Node->children;
    }
    Node * Nodes_Tree:: Get_Root_Node() {
        return this->root;
    }

    void Nodes_Tree:: Add_Child_Void(Node * LOC_Parent, Node * LOC_Child) {
        LOC_Parent->children.push_back(LOC_Child);
        (LOC_Parent->index) ++;

        LOC_Child->parent = LOC_Parent;
    }
    void Nodes_Tree:: Add_root_Void(Node * LOC_Root) {
        this->root = LOC_Root;
    }
    void Nodes_Tree:: Set_Data_Void(Node * LOC_Node, string LOC_Data) {
        LOC_Node->Tag_value = LOC_Data;
    }

    int Nodes_Tree::Get_Index_Int(Node * LOC_Node)
    {
        return LOC_Node->index;
    }

    int Nodes_Tree::Get_Repeated_Tags_Int(Node * LOC_Node)
    {
        return LOC_Node->Repeated_Tags;
    }

    void Nodes_Tree::Set_Repeated_Tags_Int(Node * LOC_Node, int repeated_levels)
    {
        LOC_Node->Repeated_Tags = repeated_levels;
    }

    void Nodes_Tree::Add_Parent_Void(Node * Copy_Node, Node * Copy_Parent)
    {
        Copy_Node->parent = Copy_Parent;
    }



    void Nodes_Tree::add_level_Void(Node * LOC_Node, int LOC_level)
    {
        LOC_Node->level = LOC_level;
    }

    Nodes_Tree::~Nodes_Tree()
    {
    }






/* void  Nodes_Tree::Print_XML(Nodes_Tree * node)
{
     int spacesflag = node->children.size();
     int spacesflag2 = node->children.size();


     cout << "<" << node->Tag_name << ">" << "\n";


     while (spacesflag)
     {
         cout << "    ";
         spacesflag--;

     }

     if (node->Tag_value != "")
     {

         cout << node->Tag_value;
         cout << "\n";

         while (spacesflag)
         {
             cout << "    ";
             spacesflag--;

         }


     }





        for (int NumberOfChildren = 0;NumberOfChildren < ( node->children.size());NumberOfChildren++)
        {

            if (  ! (node->children.empty() )   )
            {

                //cout << "    ";
                spacesflag++;
                Print_XML(node->children[NumberOfChildren]);
            }


        }


        while (spacesflag2)
            {
                cout << "    ";
                spacesflag2--;

            }
        cout << "</" << node->Tag_name << ">" << "\n";



}
*/

//Nodes_Tree::~Nodes_Tree()
//{
//}
