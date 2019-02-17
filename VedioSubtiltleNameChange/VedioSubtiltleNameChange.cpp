// VedioSubtiltleNameChange.cpp : This file contains the 'main' function. Program execution begins and ends there.

/*****************************************************/
/***********    Auther: MonNaG        ****************/
/***********    Finished Time:¡@2019.2.17 ************/
/*****************************************************/
#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <experimental/filesystem> // C++ standard header file name 
#include <filesystem> // Microsoft-specific implemenatal header file name
#include <exception>

using namespace std::experimental::filesystem;
using namespace std;

int main()
{
	path vedioPath, subtitlePath; //The path class stores an object of type string_type
	string newName, oldName, temp, deputy;// variable for file name (old, new)
	int commaIdx, slashIdx, num, times = 0;
	string::size_type st, idx, deputyIdx; // alias of size_t 
	cout << "Please enter the vedio path: "; // enter the veido folder path
	cin >> vedioPath;
	if (exists(vedioPath)) // check whether the vedio path exists 
	{
		subtitlePath = vedioPath;
		subtitlePath = subtitlePath.append("\\¦r¹õ");
		cout << "Succeed to find the subtilte path: " << vedioPath << endl;
	}
	else
	{
		return -1;
	}

	/********************************/
	/*   deal with the vedio file   */
	/********************************/

	directory_iterator endIter, tempIter;
	for (directory_iterator i(vedioPath); i != endIter; i++)
	{
		oldName = i->path().string();
		commaIdx = oldName.find_last_of('.');
		if (oldName.substr(commaIdx + 1).compare("mkv") == 0 | oldName.substr(commaIdx + 1).compare("mp4") == 0) // identify the file whether is vedio type 
		{
			cout << i->path().string() << endl;
			slashIdx = oldName.find_last_of('\\'); // vedio name
			newName = oldName.substr(slashIdx + 1, commaIdx - slashIdx - 1);
			oldName = newName;
			idx = oldName.find_first_of(']'); //[VCB-Studio] Nanatsu no Taizai [06][Hi10p_1080p][x264_flac]
			times = 0; // initialize after the first loop
			while (idx != string::npos)
			{
				times = times + 1;
				temp = oldName.substr(oldName.find_first_of('[') + 1, idx - oldName.find_first_of('[') - 1);
				try {
					num = stoi(temp, &st);
					if (st == temp.length()) // atoi (stoi)
						break;
				}
				catch (exception &anyException) {
					// donot do anything
				}
				oldName = oldName.substr(idx + 1);

				idx = oldName.find(']');
			}


			/*******************************/
			/* deal with the subtilte file */
			/*******************************/
			for (directory_iterator j(subtitlePath); j != tempIter; j++)
			{
				oldName = j->path().string();
				deputyIdx = oldName.find_first_of('.');

				
				slashIdx = oldName.find_last_of('\\'); // vedio name
				temp = oldName;
				temp = temp.substr(slashIdx + 1, deputyIdx - slashIdx - 1);
				
				for (int z = 1; z < times; z++) // find the same place of the vedio sequence number
				{
					idx = temp.find_first_of(']');
					temp = temp.substr(idx + 1);
				}
				idx = temp.find_first_of(']');
				temp = temp.substr(temp.find_first_of('[') + 1, idx - temp.find_first_of('[') - 1);			
				try {
					if (stoi(temp) == num) // compare the seuence number
					{
						temp = oldName;
						newName = temp.replace(slashIdx + 1, deputyIdx - slashIdx - 1, newName);
						rename(oldName, newName); // rename the subtilte filename 
						break;
					}
				}
				catch(exception &anyexception)
				{
					// donot do anything
				}

			}
		}

	}


   
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
