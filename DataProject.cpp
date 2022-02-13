
#include <iostream>
#include <string>
#include <vector>


using namespace std;

struct Table_Keys
{
	char key;
	string data;
};

void minifying(vector<string>& arrString)
{
	int FirstPos = 0;
	int SecondPos = 0;
	int iterator = 0;
	for(int x = 0; x < arrString.size(); x++)
	{
		FirstPos = 0;
		SecondPos = 0;
		iterator = 0;
		while(arrString[x][iterator] == ' ')
		{
			FirstPos++;
			iterator++;
		}
		SecondPos = FirstPos ;
		while(arrString[x][iterator] != '\0')
		{
			SecondPos++;
			iterator++;
		}
		arrString[x] = arrString[x].substr(FirstPos, (SecondPos-FirstPos+1));
	}
}

void stringtochar(vector<string>& arrString, vector<char>& arrChar)
{
	int y =0;
	for(int x = 0; x < arrString.size(); x++)
	{
		y = 0;
		while(arrString[x][y] != '\0')
		{
			arrChar.push_back(arrString[x][y]);
			y++;
		}
		arrChar.push_back(' ');
	}	
}

void convertToString(vector<char>& arrChar, vector<string>& newarrString, int size)
{
	newarrString.clear();
    int y = 0;
    string s = "";
    for(int x = 0; x < size; x++)
	{
		s = "";
		while(arrChar[y] != ' ')
		{
			s.push_back(arrChar[y]);
			y++;
		}
		newarrString.push_back(s);
		y++;
    }
}

void compression(vector<string>& StringArr, struct Table_Keys table[ ], int length_of_table)        //length = 15
{
	vector<char> arr;
	char array[15] = {33,35,36,37,38,42,43,45,59,61,94,123,124,125,126};

	for(int i = 0; i < length_of_table; i++)
	{
		table[i].key = array[i];
	}

	minifying(StringArr);

	stringtochar(StringArr, arr);

	int x1 = 0;
	int y1 = 1;
	int x2 = 0;
	int y2 = 0;
	int x = 0;
	int iterator = 0;
	int flag;

	while((y1 < (arr.size() - 2)) && (iterator < 15))
	{
		x2 = 0;
		y2 = 0;
		x = 2;
		flag = 0;
		
		while(y2 < (arr.size()-1))
		{	
			x2 = x1 + x;
			y2 = y1 + x;
			if((arr[x1] == arr[x2]) && (arr[y1] == arr[y2]))
			{
				arr[x2] = array[iterator];
				arr[y2] = array[iterator];
				arr.erase(arr.begin() + y2);
				flag = 1;
			}
			
			x++;
		}
		
		if(flag)
		{
			table[iterator].data = table[iterator].data + arr[x1] + arr[y1];
			arr[x1] = array[iterator];
			arr[y1] = array[iterator];
			arr.erase(arr.begin() + y1);
			iterator++;
		}
		x1++;
		y1++;
	}

	convertToString(arr, StringArr, StringArr.size());
}