#pragma once
#include "SFML/Graphics.hpp"
#include "textureHolder.h"
#include "Controller.h"

using namespace sf;
class GuiElement : public Drawable
{
public:
	GuiElement(RenderWindow *window, Vector2f position, Text label, Font font);
	~GuiElement();

	virtual void init() = 0;
	virtual void draw(RenderTarget& target, RenderStates states) const = 0;
	virtual void update(int) = 0;

	virtual void setSelected() = 0;
	virtual void unSelect() = 0;
	virtual float getValue() = 0;

	Vector2f offset;
	Text label;
	Vector2f padding;
	
	Font font;
	RenderWindow* m_window; // DONT DELETE

	// pseudo constants
	float WIN_HEIGHT;
	float WIN_WIDTH;
};

