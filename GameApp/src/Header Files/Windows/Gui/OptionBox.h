#pragma once
#include "GuiElement.h"
class OptionBox : public GuiElement
{
public:
	OptionBox(RenderWindow *window, Text label, Font font, Theme *theme, int currentValue, vector<pair<string,string>>);
	~OptionBox();


	void init() override;
	void draw(RenderTarget& target, RenderStates states) const override;
	void update(int) override;
	void setPosition(Vector2f newPositions) override;
	Vector2f getDimensions() override;
	void setSelected() override;
	void unSelect() override;
	float getValue() override;

private:
	float currentValue;
	Text selected;
	vector<pair<string,string>> options;
};

