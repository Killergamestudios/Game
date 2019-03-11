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
	int mainMenuFlag;
	void initBackground();
	void initLogo();
	void initMainMenu();
	void initBackButton();
	void initContent();
	void initNewWindow();
public:
	enum Regions { Background, Logo, MainMenu, BackButton, Content, NewWindow };
	Theme(RenderWindow &window);
	~Theme();

	static void clearRegion(Regions region);
	static void clear();
	// position:
	// 0 : upper-left corner;
	// 1 : lower-left corner;
	// 2 : upper-right corner;
	// 3 : lower-right corner;
	// 4 : center;
	static vector<Vector2f> renderRegion(Regions region, vector<Vector2f> elements, int position = 4);
	static float getRegionXDimension(Regions region);

	//map<Regions,int> counter;
	map<Regions, Vector2f> margin;
	map<Regions, Vector2f> regionDimensions;

	float VIEW_WIDTH;
	float VIEW_HEIGHT;
};

