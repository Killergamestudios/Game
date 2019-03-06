#pragma once
#include <iostream>
#ifndef INIREADER_H
#define INIREADER_H
using namespace std;
class IniReader
{
public:
	IniReader(string absoluteFileName);
	char* ReadVar(string section, string key, string defaultValue);
private:
	string absoluteFileName;
};
#endif