#include "charFunctions.h"

char toLower(char c)
{
	if (c < 65 || c > 90)
	{
		return c;
	}

	return c + 32;
}

char toUpper(char c)
{
	if (c < 97 || c > 122)
	{
		return c;
	}

	return c - 32;
}

std::string toLower(std::string string)
{
	for (int i = 0; i < string.length(); i++)
	{
		string[i] = toLower(string[i]);
	}

	return string;
}