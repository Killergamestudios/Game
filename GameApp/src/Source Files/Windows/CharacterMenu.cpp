#include "../../Header Files/Windows/CharacterMenu.h"

CharacterMenu::CharacterMenu(RenderWindow& window, CharacterObject& selectedCharacter):
	GameMenu(window)
{
	depth = 1;
	this->selectedCharacter = &selectedCharacter;
}


CharacterMenu::~CharacterMenu()
{
	menuTexts.clear();
	drawStack.clear();
	tabOrder.clear();
	delete theme;
	delete backgroundFillColor;
}

void CharacterMenu::init()
{
	backgroundFillColor = new RectangleShape(Vector2f(700.f, 200.f));
	backgroundFillColor->setFillColor(Color(121, 132, 202));
	optionSelected = 0;
	totalTimePassed = 0;
	initLayer();
}

void CharacterMenu::update(float &dtAsSeconds)
{
	if (!Controller::isExecuteSecondary(Controller::CHARACTER_MENU))
	{
		Controller::setSecondaryInitialized(Controller::CHARACTER_MENU, false);
		return;
	}
	totalTimePassed += dtAsSeconds;
}

void CharacterMenu::draw()
{
	m_window->draw(*backgroundFillColor);
	for (pair<int, Drawable*> dr : drawStack)
		m_window->draw(*dr.second);
	m_window->draw(*menuTexts[descriptionIndex + optionSelected]);
}

void CharacterMenu::input() {
	if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
	{
		changeSeletedOption(-1);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
	{
		changeSeletedOption(1);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		actions();
	}
}

void CharacterMenu::actions()
{
	if (optionSelected == tabOrder.size() - 1) {
		if (depth != 1) { // Time travel
			depth-=2; // Temporary Change
			initLayer();
		}
		else if (depth == 1) {
			Controller::setExecuteSecondary(Controller::CHARACTER_MENU, false);
		}
	}
	else if (depth == 1 && optionSelected == 0) 
	{
			// move
	} 
	else if (depth == 1 && optionSelected == 1)
	{	// Stay at current position
		depth+=2;
		initLayer();
	}
	else if (depth == 2 && optionSelected == 2)
	{	// End turn
		Controller::setExecuteSecondary(Controller::CHARACTER_MENU, false);
	}
	else {
		// attack & ability
	}

}

void CharacterMenu::initLayer()
{
	clearTextures();
	optionSelected = 0;
	theme = new CharacterWindow(3, true, true, true);
	if (depth == 1) {
		loadTextGraphics(textLayer1, descLayer1);
	}
	else if (depth == 3) {
		loadTextGraphics(textLayer2, descLayer2);
	}
}

void CharacterMenu::loadTextGraphics(vector<string> btns, vector<string> descriptions)
{
	
	backgroundFillColor->setPosition(theme->setBackground(backgroundFillColor->getSize(),Vector2f(10,10)));
	vector<Vector2f> btnsDimensions, descriptionDimensions;
	for (unsigned int i = 0; i < btns.size(); i++) {
		Text* buffer = new Text(btns[i], font, 24);
		menuTexts.push_back(buffer);
		btnsDimensions.push_back(Vector2f(buffer->getLocalBounds().width, buffer->getLocalBounds().height));
		drawStack[drawStack.size() + 2] = buffer;
		tabOrder[tabOrder.size()] = make_pair("TXT", buffer);
		buffer->setFillColor(Color::White);
	}
	descriptionIndex = btns.size();
	for (unsigned int i = 0; i < descriptions.size(); i++) {
		Text* buffer = new Text(descriptions[i], font, 24);
		menuTexts.push_back(buffer);
		descriptionDimensions.push_back(Vector2f(buffer->getLocalBounds().width, buffer->getLocalBounds().height));
		buffer->setFillColor(Color::White);
	}

	theme->add(btnsDimensions, descriptionDimensions);
	theme->renderRegion();
	vector<Vector2f> btnsPositions = theme->getButtonsPositions();
	vector<Vector2f> descPositions = theme->getDiscriptionPositions();
	for (unsigned int i = 0; i < btns.size(); i++) {
		menuTexts[i]->setPosition(btnsPositions[i]);
		menuTexts[btns.size() + i]->setPosition(descPositions[i]);
	}
	
	menuTexts[0]->setFillColor(Color::Red); //set as default selected
}

void CharacterMenu::clearTextures()
{
	menuTexts.clear();
	drawStack.clear();
	tabOrder.clear();
	delete theme;
}

void CharacterMenu::changeSeletedOption(int direction)
{
	((Text*)tabOrder[optionSelected].second)->setFillColor(Color::White);
	optionSelected += (tabOrder.size() + direction);
	optionSelected = optionSelected % tabOrder.size();
	((Text*)tabOrder[optionSelected].second)->setFillColor(Color::Red);
}
