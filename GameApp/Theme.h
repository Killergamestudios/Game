#pragma once
#include <SFML/Graphics.hpp>
#include <map>

using namespace std;
using namespace sf;

class Theme
{
private:
	static Theme* m_s_Instance;
	RenderWindow* m_window;

	void init();
public:
	enum Regions { Background, Logo, MainMenu, OptionsMenu, BackButton, Alerts, Content };
	Theme(RenderWindow &window);
	~Theme();

	static void clearRegion(Regions region);
	static void clear();
	static vector<Vector2f> renderRegion(Regions region, vector<FloatRect> elements);


	map<Regions,int> counter;
	map<Regions, Vector2f> margin;
	map<Regions, float> elementSeperation;
	map<Regions, Vector2f> regionDimensions;

	float WIN_WIDTH;
	float WIN_HEIGHT;
};

