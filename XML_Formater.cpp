#include "XML_Formater.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>


using namespace std;

void XML_Formater::xml_cutter(ifstream & input_File, vector<string> * output)
{
    string line, temp,input;
    string d_q = " ";
    int start, end,Start_value=0;
    int Middle_Date_Start,Middle_Bracket_Start;
    int Middle_Date_End, Middle_Bracket_End;
    while (getline(input_File, input)) {
        Start_value = input.find_first_not_of(' ');


        for (int i = Start_value;i < input.length();i++)
        {

            if (input[i] == '<')
            {
                start = i;
                for (i;i < input.length();i++)
                {
                    if (input[i] == '>')
                    {



                        end = i;
                        line = input.substr(start, (end - start) + 1);
                        output->push_back(line);

                        Middle_Bracket_Start= input.find_first_of('<', i + 1);
                        Middle_Bracket_End= input.find_first_of('>', Middle_Bracket_Start);
                        if (Middle_Bracket_Start != -1 && Middle_Bracket_End != -1)
                        {
                            line = input.substr(end+1, (Middle_Bracket_Start - end) -1);
                            output->push_back(line);
                            line = input.substr(Middle_Bracket_Start, (Middle_Bracket_End - Middle_Bracket_Start) + 1);
                            output->push_back(line);





                        }



                        break;
                    }

                }

                break;

            }


            else
            {

                //Start_value= input.find_first_not_of(' ');
                temp = input.substr(Start_value);
                output->push_back(temp);
                break;


            }



        }






        /*else {
            start = i;
            for (i;i<input.length();i++)
            {
                if (input[i] == '<')
                {
                    end = i - 1;
                    i--;
                    break;
                }
                else
                {
                    end = i;
                }

            }
        }
        line = input.substr(start, (end - start + 1));
        if (line[0] != '<')
            for (int i = 0;i<line.length();i++) {
                if (line[i] == '"')
                    line.replace(i, 1, d_q);
            }
        if (line[0] != ' ' || line[1] != ' ' || line[2] != ' ')
            output << line << endl;
            */



            /*}*/
    }

}






XML_Formater::XML_Formater()
{
}


XML_Formater::~XML_Formater()
{
}
