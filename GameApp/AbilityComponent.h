#pragma once
#include <SFML/Graphics.hpp>
#include "component.h"
#include <stdexcept>
#include "object.h"
#include "Map.h"

using namespace sf;
using namespace std;
/***************************************************************************************ABILITY COMPONENT CLASS *********************************************/


class AbilityComponent :public component {
public:
	AbilityComponent(CharacterObject *Parent, String Name);
	~AbilityComponent();
	virtual void update() = 0;
	virtual void use(Vector2i &position, CharacterObject *target) = 0;
	virtual bool canUse() = 0;
	int getCost();

protected:
	CharacterObject *parent;
	String name;
	String description;
	int ActionCost;
	Sprite m_sprite;
	int range;
};



class Whirlwind : public AbilityComponent {
public:
	Whirlwind(CharacterObject *Parent);
	~Whirlwind();

	void update() override;
	void use(Vector2i &position, CharacterObject *target = nullptr) override;
	bool canUse() override;
private:

};