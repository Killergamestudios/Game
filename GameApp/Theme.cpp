#include "pch.h"
#include "Theme.h"
#include <assert.h>
#include <iostream>

using namespace std;
Theme* Theme::m_s_Instance = nullptr;

void Theme::init()
{
	counter[Background] = 0;
	margin[Background] = Vector2f(0, 0);
	elementSeperation[Background] = 0;
	regionDimensions[Background] = Vector2f(WIN_WIDTH, WIN_HEIGHT);

	counter[Logo] = 0;
	margin[Logo] = Vector2f(0, WIN_HEIGHT * 0.03f);
	elementSeperation[Logo] = 0;
	regionDimensions[Logo] = Vector2f(0, 0);

	counter[MainMenu] = 0;
	margin[MainMenu] = Vector2f(0, 0);
	elementSeperation[MainMenu] = 0;
	regionDimensions[MainMenu] = Vector2f(0, 0);
	
	counter[BackButton] = 0;
	margin[BackButton] = Vector2f(WIN_WIDTH*0.02f, WIN_HEIGHT * 0.03f);
	elementSeperation[BackButton] = 0;
	regionDimensions[BackButton] = Vector2f(0, 0);
	
	counter[OptionsMenu] = 0;
	margin[OptionsMenu] = Vector2f(0.05f * WIN_WIDTH, WIN_HEIGHT * 0.03f);
	elementSeperation[OptionsMenu] = 0;
	regionDimensions[OptionsMenu] = Vector2f(0, 0);

	counter[Alerts] = 0;
	margin[Alerts] = Vector2f(0, 0);
	elementSeperation[Alerts] = 0;
	regionDimensions[Alerts] = Vector2f(WIN_WIDTH, WIN_HEIGHT);
	
	counter[Content] = 0;
	margin[Content] = Vector2f(0, 0);
	elementSeperation[Content] = 0;
	regionDimensions[Content] = Vector2f(WIN_WIDTH, WIN_HEIGHT);
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

void Theme::clear()
{
	int();
}

vector<Vector2f> Theme::renderRegion(Regions region, vector<FloatRect> elements)
{
	vector<Vector2f> renderedElements;
	switch (region) {
	case Background:
		for (FloatRect element: elements) {
			renderedElements.push_back(Vector2f((m_s_Instance->WIN_WIDTH - element.width) / 2,
								(m_s_Instance->WIN_HEIGHT - element.height) / 2));
		}
		break;
	case BackButton:
		for (FloatRect element : elements) {
			renderedElements.push_back(Vector2f(m_s_Instance->WIN_WIDTH - element.width - m_s_Instance->margin[BackButton].x,
				m_s_Instance->WIN_HEIGHT - element.height - m_s_Instance->margin[BackButton].y));
			
			m_s_Instance->regionDimensions[BackButton] = Vector2f(m_s_Instance->WIN_WIDTH, element.height + m_s_Instance->margin[BackButton].y);
		}
		break;
	case Logo:
		for (FloatRect element : elements) {
			renderedElements.push_back(Vector2f((m_s_Instance->WIN_WIDTH - element.width) / 2, m_s_Instance->margin[Logo].y));
			m_s_Instance->regionDimensions[Logo] = Vector2f(m_s_Instance->WIN_WIDTH, element.height + m_s_Instance->margin[Logo].y);
		}
		break;
	case MainMenu:
		int flag = 0;
		for (FloatRect element : elements) {
			
			renderedElements.push_back(Vector2f((m_s_Instance->WIN_WIDTH - element.width) / 2,
				m_s_Instance->regionDimensions[Logo].y + m_s_Instance->margin[Logo].y
				+ flag * m_s_Instance->elementSeperation[MainMenu] + m_s_Instance->regionDimensions[MainMenu].y));
			m_s_Instance->regionDimensions[MainMenu].x = m_s_Instance->WIN_WIDTH;
			m_s_Instance->regionDimensions[MainMenu].y +=  m_s_Instance->margin[MainMenu].y + element.height + flag * m_s_Instance->elementSeperation[MainMenu];
			flag = 1;
		}
		break;
	}
	return renderedElements;
}

