#pragma once
#include "GuiElement.h"
class OptionBox : public GuiElement
{
public:
	OptionBox(RenderWindow *window, Text label, Font font, Theme::Regions region, int currentValue, vector<pair<string,string>>);
	~OptionBox();


	void init() override;
	void draw(RenderTarget& target, RenderStates states) const override;
	void update(int) override;
	void setSelected() override;
	void unSelect() override;
	float getValue() override;

	float currentValue;
	Text selected;
	vector<pair<string,string>> options;
};

