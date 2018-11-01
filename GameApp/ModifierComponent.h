#pragma once
#include "component.h"

using namespace sf;

class ModifierComponent : public component {
public:
	ModifierComponent(CharacterObject *Prnt);
	~ModifierComponent();

	bool getIsDead();


protected:
	CharacterObject *Parent;
	bool isdead;
};

