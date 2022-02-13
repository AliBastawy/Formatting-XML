
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include "tags.h"

using namespace std;


vector<string> Xml_FileCorrection(vector<string>& Xml_File)
{

	int lines_iterator=0;
	int lines_Number=Xml_File.size();
	vector<string> errors_contained;
	string line;
	stack<tags> collector;

		//the file iterator 
		while (lines_iterator < lines_Number)
		{
			line = Xml_File[lines_iterator];
			int character_iterator=0;
			//the line iterator 
			while(line[character_iterator]!='\0')
			{	
				if(line[character_iterator]=='<')
				{
					string tag;
					if(line[character_iterator+1]=='/')
					{
						character_iterator=character_iterator+2;
						while(line[character_iterator-1]!='>')
						{
							tag.push_back(line[character_iterator++]);				
						}	
			CheckOnTag:			
						if(!collector.empty())
						{
							if(tag == (collector.top()).data)
							{
								collector.pop();		
							}			
							else
							{
								bool missing_openingtag=1;
								stack<tags> temp_collector =collector;
								temp_collector.pop();
								while(!(temp_collector.empty()))
								{
									//check if the missing is a closing tag
									if(tag==((temp_collector.top()).data))
									{
										//the correction of the missing closing tag
										tags temp_tag = collector.top();
										collector.pop();
										string temp_line=Xml_File[temp_tag.line];
										temp_tag.data = "</" + temp_tag.data;
										temp_line.insert(temp_tag.end,temp_tag.data);
										Xml_File[temp_tag.line]=temp_line;

                                    

										//sends the error to the GUI window 
										errors_contained.push_back("There Is A Missing Closing Tag "+temp_tag.data);								
										missing_openingtag=0;
										goto CheckOnTag;
									}
									temp_collector.pop();
								}	
								if (missing_openingtag==1)
								{
									//the correction of the missing opening tag
									tags temp_tag = collector.top();
									string temp_line=Xml_File[temp_tag.line];
									tag= "<" + tag;
									temp_line.insert(temp_tag.end,tag);
									Xml_File[temp_tag.line]=temp_line;
									
									//sends the error to the GUI window 
									errors_contained.push_back("There Is A Missing Opening Tag "+tag);
								}				
							}	
						}
						else
						{
							//the correction of the missing opening tag while the stack is empty  
							string temp_line=Xml_File[0];
							tag = "<" + tag;
							temp_line.insert(0,tag);
							Xml_File[0]=temp_line;
							
							//sends the error to the GUI window 
							errors_contained.push_back("There Is A Missing Opening Tag "+tag);
						}	
					}
					else
					{
						if((line[character_iterator+1]!='!')&&(line[character_iterator+2]=='-')&&(line[character_iterator+3]=='-'))
						{		
							//get the opening tag and push it in the stack with all the required data about it
							tags *ptr;			
							int Opening_tag=1;
							character_iterator=character_iterator+1;
							while(line[character_iterator-1]!='>')
							{
								if(line[character_iterator]=='=')
								{
									Opening_tag=0;
									break;
								}	
								tag.push_back(line[character_iterator++]);				
							}	
							if(Opening_tag==1)
							{	
								ptr = new tags(tag,lines_iterator,character_iterator);
								collector.push(*ptr);	
							}	
						}
					}		
				}
				else
				{
					character_iterator++;
				}
			}
			lines_iterator++;
		}
		// handling the missing closing tags of the tags in the stack
		while(!(collector.empty()))
		{
			//the correction of the missing closing tag
			string temp_tag = (collector.top()).data;
			collector.pop();
			temp_tag = "</" + temp_tag;
			Xml_File.push_back(temp_tag);
			
			//sends the error to the GUI window 
			errors_contained.push_back("There Is A Missing Closing Tag "+temp_tag);
			
		}	

		// return a vector containing all the correction done 
	    return errors_contained;
}

vector<string> Xml_FileOpener(string file_path)
{

	string inline1;
	vector<string> openedxmlfile;
	ifstream xmlfile;
	xmlfile.open(file_path);

	if (!xmlfile.fail())
    {
		while(!xmlfile.eof())
		{
			getline(xmlfile,inline1);
			openedxmlfile.push_back(inline1);
		}
		
    }
	xmlfile.close();
	return openedxmlfile; 
}


int main()
{

    string Filepath="sample.xml";
    vector <string> xmlfile;
    xmlfile=Xml_FileOpener(Filepath);

    vector<string> corrections = Xml_FileCorrection(xmlfile);

	
    for(int i =0; i<corrections.size();i++)
    {  
        cout<<corrections[i]<<endl;
    }
	
    return 0;
}
