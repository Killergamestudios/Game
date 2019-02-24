#pragma once
#include <SFML/Graphics.hpp>
#include <map>

using namespace std;
using namespace sf;

class Theme
{
private:
	static Theme* m_s_Instance;
	enum Regions {Background, Logo, MainMenu, OptionsMenu, BackButton, Alerts, Content};
	RenderWindow* m_window;

	void init();
public:
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

	static const Regions BACKGROUND = Regions::Background;
	static const Regions LOGO = Regions::Logo;
	static const Regions MAINMENU = Regions::MainMenu;
	static const Regions OPTIONSMENU = Regions::OptionsMenu;
	static const Regions BACKBUTTON = Regions::BackButton;
	static const Regions ALERTS = Regions::Alerts;
	static const Regions CONTENT = Regions::Content;
};

