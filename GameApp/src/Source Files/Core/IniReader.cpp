#pragma once
#include "../../Header Files/Core/IniReader.h"
#include <iostream>
#include <Windows.h>

IniReader::IniReader(string absoluteFileName)
{
	this->absoluteFileName = absoluteFileName;
}

char* IniReader::ReadVar(string section, string key, string defaultValue)
{
	char* szResult = new char[255];
	GetPrivateProfileStringA(section.c_str(), key.c_str(), defaultValue.c_str(), (LPSTR)szResult, 255, absoluteFileName.c_str());
	return szResult;
}