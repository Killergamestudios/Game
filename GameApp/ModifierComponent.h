#pragma once
#include "component.h"

using namespace sf;

class ModifierComponent : public component {
public:
	ModifierComponent(CharacterObject *Prnt, int turns);
	~ModifierComponent();

	bool getIsDead();
	int GetTurnsToDie();

	void update() override;

protected:
	CharacterObject *Parent;
	bool isdead;
	int turnsToDie;
};

