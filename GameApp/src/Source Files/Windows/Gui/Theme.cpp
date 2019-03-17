#pragma once
#include "../../../Header Files/Windows/Gui/Theme.h"
#include <assert.h>
#include <iostream>
#include <math.h>

using namespace std;
Theme* Theme::m_s_Instance = nullptr;


void Theme::initBackground()
{
	margin[Background] = Vector2f(0, 0);
	regionDimensions[Background] = Vector2f(VIEW_WIDTH, VIEW_HEIGHT);
}

void Theme::initLogo()
{
	margin[Logo] = Vector2f(0, VIEW_HEIGHT * 0.03f);
	regionDimensions[Logo] = Vector2f(VIEW_WIDTH, 0);
}

void Theme::initMainMenu()
{
	margin[MainMenu] = Vector2f(0, 0);
	regionDimensions[MainMenu] = Vector2f(VIEW_WIDTH, 0);
	mainMenuFlag = 0;
}

void Theme::initBackButton()
{
	margin[BackButton] = Vector2f(VIEW_WIDTH*0.02f, VIEW_HEIGHT * 0.03f);
	regionDimensions[BackButton] = Vector2f(0, 0);
}

void Theme::initContent()
{
	margin[Content] = Vector2f(0, 0);
	regionDimensions[Content] = Vector2f(VIEW_WIDTH, VIEW_HEIGHT);
}

void Theme::initNewWindow()
{
	margin[NewWindow] = Vector2f(VIEW_WIDTH*0.02f, VIEW_HEIGHT * 0.05f);
	regionDimensions[NewWindow] = Vector2f(0, 0);
	mainMenuFlag = 0;
}



Theme::Theme(RenderWindow &window)
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
	m_window = &window;
	VIEW_WIDTH = (float)m_window->getView().getSize().x;
	VIEW_HEIGHT = (float)m_window->getView().getSize().y;
	clear();
}


Theme::~Theme()
{
}

void Theme::clearRegion(Regions region)
{
	switch (region) {
	case Background:
		m_s_Instance->initBackground();
		break;
	case Logo:
		m_s_Instance->initLogo();
		break;
	case MainMenu:
		m_s_Instance->initMainMenu();
		break;
	case BackButton:
		m_s_Instance->initBackButton();
		break;
	case Content:
		m_s_Instance->initContent();
		break;
	case NewWindow:
		m_s_Instance->initNewWindow();
		break;
	}
}

void Theme::clear()
{
	m_s_Instance->initBackground();
	m_s_Instance->initLogo();
	m_s_Instance->initMainMenu();
	m_s_Instance->initBackButton();
	m_s_Instance->initContent();
	m_s_Instance->initNewWindow();
}

vector<Vector2f> Theme::renderRegion(Regions region, vector<Vector2f> elements, int position)
{
	vector<Vector2f> renderedElements;
	float LOCAL_VIEW_WIDTH = m_s_Instance->VIEW_WIDTH;
	float LOCAL_VIEW_HEIGHT = m_s_Instance->VIEW_HEIGHT;
	int flag = m_s_Instance->mainMenuFlag;
	float elementSeperation;
	switch (region) {
	case Background:
		for (Vector2f element: elements) {
			renderedElements.push_back(Vector2f(ceil((LOCAL_VIEW_WIDTH - element.x) / 2),
								ceil((LOCAL_VIEW_HEIGHT - element.y) / 2)));
		}
		break;
	case BackButton:
		for (Vector2f element : elements) {
			renderedElements.push_back(Vector2f(ceil((LOCAL_VIEW_WIDTH - element.x) / 2.f),
				ceil(LOCAL_VIEW_HEIGHT - element.y - m_s_Instance->margin[BackButton].y)));
			
			m_s_Instance->regionDimensions[BackButton] = Vector2f(LOCAL_VIEW_WIDTH, element.y + m_s_Instance->margin[BackButton].y);
		}
		break;
	case Logo:
		for (Vector2f element : elements) {
			renderedElements.push_back(Vector2f(ceil((LOCAL_VIEW_WIDTH - element.x) / 2), ceil(m_s_Instance->margin[Logo].y)));
			m_s_Instance->regionDimensions[Logo] = Vector2f(LOCAL_VIEW_WIDTH, element.y + m_s_Instance->margin[Logo].y);
		}
		break;
	case MainMenu:
		LOCAL_VIEW_HEIGHT = min(LOCAL_VIEW_HEIGHT - m_s_Instance->regionDimensions[Logo].y - m_s_Instance->margin[Logo].y, LOCAL_VIEW_HEIGHT*0.7f);
		elementSeperation = (LOCAL_VIEW_HEIGHT - elements.size() * elements[0].y) / (elements.size() - 1); // calculate element sepearation
		for (Vector2f element : elements) {		
			renderedElements.push_back(Vector2f(ceil((LOCAL_VIEW_WIDTH - element.x) / 2), ceil(flag*elementSeperation + m_s_Instance->regionDimensions[MainMenu].y)));
			m_s_Instance->regionDimensions[MainMenu].x = LOCAL_VIEW_WIDTH;
			m_s_Instance->regionDimensions[MainMenu].y += flag * elementSeperation + m_s_Instance->margin[MainMenu].y + element.y;
			flag = 1;
		}
		break;
	case NewWindow:
		// first FloatRect is the background of the new window
		float xOrg = 1 / 2; // By default origin is set to center
		float yOrg = 1 / 2; //
		if (position < 4 && position >= 0) {
			xOrg = (float)(position / 2); // if position is not center then change origin
			yOrg = (float)(position % 2); // 
		}

		// get the new origin based on the dimensions of the first element (background - container)
		Vector2f origin((LOCAL_VIEW_WIDTH - elements[0].x)*xOrg, (LOCAL_VIEW_HEIGHT - elements[0].y)*yOrg);  
		renderedElements.push_back(origin);
		LOCAL_VIEW_WIDTH = elements[0].x; // save dimenstion of container
		LOCAL_VIEW_HEIGHT = elements[0].y; // 
		elements.erase(elements.begin()); // erase the background from the list in order to have only elements to process
		elementSeperation = (LOCAL_VIEW_HEIGHT - elements.size() * elements[0].y) / (elements.size() + 1) ; // calculate element sepearation
		for (Vector2f element : elements) {
			renderedElements.push_back(Vector2f(ceil((origin.x + LOCAL_VIEW_WIDTH - element.x) / 2),
				ceil(origin.y + elementSeperation + m_s_Instance->regionDimensions[NewWindow].y)));
			m_s_Instance->regionDimensions[NewWindow].x = LOCAL_VIEW_WIDTH;
			m_s_Instance->regionDimensions[NewWindow].y += element.y + elementSeperation;
		}
		break;
	}
	return renderedElements;
}

float Theme::getRegionXDimension(Regions region)
{
	return m_s_Instance->regionDimensions[region].x;
}

