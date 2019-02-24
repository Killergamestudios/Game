#pragma once
#include <iostream>

#ifndef INIWRITER_H
#define INIWRITER_H

using namespace std;
class IniWriter
{
public:
	IniWriter(string absoluteFileName);
	void WriteVar(string szSection, string szKey, string szValue);
private:
	string absoluteFileName;
};
#endif //INIWRITER_H