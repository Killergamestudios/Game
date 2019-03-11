#pragma once
#include "../../Header Files/Core/IniWriter.h"
#include <iostream>
#include <Windows.h> 

IniWriter::IniWriter(string absoluteFileName)
{
	this->absoluteFileName = absoluteFileName;
}

void IniWriter::WriteVar(string section, string key, string value)
{
	WritePrivateProfileStringA(section.c_str(), key.c_str(), value.c_str(), absoluteFileName.c_str());
}