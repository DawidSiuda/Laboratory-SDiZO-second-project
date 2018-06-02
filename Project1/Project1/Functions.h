#pragma once

#include <string>
#include <iostream>

using namespace std;
//
// function cut first word from text
//

std::string getWord(std::string *text)
{
	std::string word;

	if (text->empty() == true)
	{
		return word;
	}

	int counter = 0;

	while (counter < text->size())
	{
		switch (text[0][counter])
		{
			case '\n':
			case ' ' :
			case '\t':
				word = text->substr(0, counter);
				text->erase(0, counter + 1);
				counter = text->size();
		}
		
		if (counter + 1 == text->size())
		{
			word = text->substr(0, counter+1);
			text->clear();
		}

		counter++;
	}
	
	return word;
}
