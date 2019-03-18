#pragma once
#include "GuiElement.h"
class ValueBar : public GuiElement
{
public:
	ValueBar(RenderWindow *window, Text label, Font font, Theme::Regions region, float currentValue, float max=100.0f, float min=0.0f, float step=5.0f);
	~ValueBar();

	void init() override;
	void draw(RenderTarget& target, RenderStates states) const override;
	void update(int) override;
	void setPosition(Vector2f newPositions, Vector2f camOffset) override;
	Vector2f getDimensions() override;
	void setSelected() override;
	void unSelect() override;
	float getValue() override;

private:
	float maxValue;
	float minValue;
	float step;
	float currentValue;
	Sprite valueBar;
	Sprite valuePoint;
};

