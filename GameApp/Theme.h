#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Theme
{
private:
	static Theme* m_s_Instance;
public:
	Theme();
	~Theme();
};

