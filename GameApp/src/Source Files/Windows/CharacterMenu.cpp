#include "../../Header Files/Windows/CharacterMenu.h"

CharacterMenu::CharacterMenu(RenderWindow& window, CharacterObject* selectedCharacter):
	GameMenu(window)
{
	depth = 1;
	this->selectedCharacter = selectedCharacter;
	initialPosition = this->selectedCharacter->getMyPosition();
	initialDirection = this->selectedCharacter->getDirection();
	moved = false;
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
	if (depth == 2 && !moved) {
		InputController::CharacterDiraction(selectedCharacter);
	}

	if (moved && selectedCharacter->isStading()) {
		moved = false;
		depth = 3; // temporary solution needs energy implementation
		initLayer();
	}
}

void CharacterMenu::draw()
{
	if (depth == 1 || depth == 3) {
		m_window->draw(*backgroundFillColor);
		for (pair<int, Drawable*> dr : drawStack)
			m_window->draw(*dr.second);
		m_window->draw(*menuTexts[descriptionIndex + optionSelected]);
	}
	else {
		if (highlighted_tiles.size() != 0) {
			for (unsigned int i = 0; i < highlighted_tiles.size(); i++) {
				m_window->draw(highlighted_tiles[i]);
			}
		}
	}
}

void CharacterMenu::input() {
	if (depth != 2) {
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
}

void CharacterMenu::mouseInput(Vector2i position) 
{
	if (!moved && depth == 2)
	{
		for (unsigned int i = 0; i < availableTiles.size(); i++) {
			if (availableTiles[i].x == position.x && availableTiles[i].y == position.y)
			{
				InputController::MoveCharacter(selectedCharacter);
				moved = true;
				
				highlighted_tiles.clear();
				InputController::UnHiglightSpaces();
				return;
			}
		}
		cout << "You cannot move there: " << position.x << " " << position.y << endl;
	}
}

void CharacterMenu::actions()
{
	if (optionSelected == tabOrder.size() - 1) {
		if (depth != 1) { // Time travel
			selectedCharacter->SetPosition(initialPosition);
			selectedCharacter->SetDirection(initialDirection);
			depth-=2; // Temporary Change
			initLayer();
		}
		else if (depth == 1) {
			Controller::setExecuteSecondary(Controller::CHARACTER_MENU, false);
		}
	}
	else if (depth == 1 && optionSelected == 0) 
	{
 		depth = 2;
		initLayer();
	} 
	else if (depth == 1 && optionSelected == 1)
	{	// Stay at current position
		depth+=2;
		initLayer();
	}
	else if (depth == 3 && optionSelected == 2)
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
	else if (depth == 2) {
		initMoveLayout();
	}
	else if (depth == 3) {
		loadTextGraphics(textLayer2, descLayer2);
	}
}

void CharacterMenu::initMoveLayout() {
	availableTiles = InputController::HighlightSpaces(selectedCharacter);
	highlighted_tiles = InputController::getHighlighted_tyles();
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
	availableTiles.clear();
	delete theme;
}

void CharacterMenu::changeSeletedOption(int direction)
{
	((Text*)tabOrder[optionSelected].second)->setFillColor(Color::White);
	optionSelected += (tabOrder.size() + direction);
	optionSelected = optionSelected % tabOrder.size();
	((Text*)tabOrder[optionSelected].second)->setFillColor(Color::Red);
}
