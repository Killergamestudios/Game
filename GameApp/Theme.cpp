#include "pch.h"
#include "Theme.h"
#include <assert.h>
#include <iostream>

using namespace std;
Theme* Theme::m_s_Instance = nullptr;

void Theme::init()
{
	counter[BACKGROUND] = 0;
	margin[BACKGROUND] = Vector2f(0, 0);
	elementSeperation[BACKGROUND] = 0;
	regionDimensions[BACKGROUND] = Vector2f(WIN_WIDTH, WIN_HEIGHT);

	counter[LOGO] = 0;
	margin[LOGO] = Vector2f(0, WIN_HEIGHT * 0.03f);
	elementSeperation[LOGO] = 0;
	regionDimensions[LOGO] = Vector2f(0, 0);

	counter[MAINMENU] = 0;
	margin[MAINMENU] = Vector2f(0, 0);
	elementSeperation[MAINMENU] = 0;
	regionDimensions[MAINMENU] = Vector2f(0, 0);
	
	counter[BACKBUTTON] = 0;
	margin[BACKBUTTON] = Vector2f(WIN_WIDTH*0.02f, WIN_HEIGHT * 0.03f);
	elementSeperation[BACKBUTTON] = 0;
	regionDimensions[BACKBUTTON] = Vector2f(0, 0);
	
	counter[OPTIONSMENU] = 0;
	margin[OPTIONSMENU] = Vector2f(0.05f * WIN_WIDTH, WIN_HEIGHT * 0.03f);
	elementSeperation[OPTIONSMENU] = 0;
	regionDimensions[OPTIONSMENU] = Vector2f(0, 0);

	counter[ALERTS] = 0;
	margin[ALERTS] = Vector2f(0, 0);
	elementSeperation[ALERTS] = 0;
	regionDimensions[ALERTS] = Vector2f(WIN_WIDTH, WIN_HEIGHT);
	
	counter[CONTENT] = 0;
	margin[CONTENT] = Vector2f(0, 0);
	elementSeperation[CONTENT] = 0;
	regionDimensions[CONTENT] = Vector2f(WIN_WIDTH, WIN_HEIGHT);
}

Theme::Theme(RenderWindow &window)
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
	m_window = &window;
	WIN_WIDTH = (float)m_window->getSize().x;
	WIN_HEIGHT = (float)m_window->getSize().y;
	init();
}


Theme::~Theme()
{
}

void Theme::clearRegion(Regions region)
{
	m_s_Instance->regionDimensions[region] = Vector2f(0, 0);
	
}

vector<Vector2f> Theme::renderRegion(Regions region, vector<FloatRect> elements)
{
	vector<Vector2f> renderedElements;
	switch (region) {
	case BACKGROUND:
		for (FloatRect element: elements) {
			renderedElements.push_back(Vector2f((m_s_Instance->WIN_WIDTH - element.width) / 2,
								(m_s_Instance->WIN_HEIGHT - element.height) / 2));
		}
		break;
	case BACKBUTTON:
		for (FloatRect element : elements) {
			renderedElements.push_back(Vector2f(m_s_Instance->WIN_WIDTH - element.width - m_s_Instance->margin[LOGO].x,
				m_s_Instance->regionDimensions[LOGO].y + m_s_Instance->regionDimensions[MAINMENU].y + m_s_Instance->margin[BACKBUTTON].y));
			
			m_s_Instance->regionDimensions[BACKBUTTON] = Vector2f(m_s_Instance->WIN_WIDTH, element.height + m_s_Instance->margin[BACKBUTTON].y);
		}
		break;
	case LOGO:
		for (FloatRect element : elements) {
			renderedElements.push_back(Vector2f((m_s_Instance->WIN_WIDTH - element.width) / 2, m_s_Instance->margin[LOGO].y));
			m_s_Instance->regionDimensions[LOGO] = Vector2f(m_s_Instance->WIN_WIDTH, element.height + m_s_Instance->margin[LOGO].y);
		}
		break;
	case MAINMENU:
		int flag = 0;
		for (FloatRect element : elements) {
			
			renderedElements.push_back(Vector2f((m_s_Instance->WIN_WIDTH - element.width) / 2,
				m_s_Instance->regionDimensions[LOGO].y + m_s_Instance->margin[MAINMENU].y
				+ flag * m_s_Instance->elementSeperation[MAINMENU] + m_s_Instance->regionDimensions[MAINMENU].y));
			m_s_Instance->regionDimensions[MAINMENU].x = m_s_Instance->WIN_WIDTH;
			m_s_Instance->regionDimensions[MAINMENU].y +=  m_s_Instance->margin[MAINMENU].y + element.height + flag * m_s_Instance->elementSeperation[MAINMENU];
			flag = 1;
		}
		break;
	}
	return renderedElements;
}

