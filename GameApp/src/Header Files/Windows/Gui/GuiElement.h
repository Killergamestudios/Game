#pragma once
#include "SFML/Graphics.hpp"
#include "../../Core/textureHolder.h"
#include "../../Core/Controller.h"
#include "Theme.h"

using namespace sf;
class GuiElement : public Drawable
{
public:
	GuiElement(RenderWindow *window , Text label, Font font, Theme::Regions region);
	~GuiElement();

	virtual void init() = 0;
	virtual void draw(RenderTarget& target, RenderStates states) const = 0;
	virtual void update(int) = 0;

	virtual void setSelected() = 0;
	virtual void unSelect() = 0;
	virtual float getValue() = 0;

	Text label;
	Vector2f padding;
	Theme::Regions renderedRegion;
	Font font;
	Vector2f offset;
	RenderWindow* m_window; // DONT DELETE

	// pseudo constants
	float VIEW_HEIGHT;
	float VIEW_WIDTH;
};

