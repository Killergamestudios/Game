#pragma once
#include "GuiController.h"
class OptionBox : public GuiController
{
public:
	OptionBox(RenderWindow *window, Vector2f position, Text label, Font font, int currentValue, vector<pair<string,string>>);
	~OptionBox();


	void init() override;
	void draw() override;
	void update(int) override;
	void setSelected() override;
	void unSelect() override;
	float getValue() override;

	float currentValue;
	Text selected;
	vector<pair<string,string>> options;
};

