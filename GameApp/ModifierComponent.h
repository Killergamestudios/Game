#pragma once
#include "component.h"
#include "object.h"

using namespace sf;

class ModifierComponent : public component {
public:
	ModifierComponent(CharacterObject *Prnt, int turns);
	~ModifierComponent();

	bool getIsDead();
	int GetTurnsToDie();

	void setParent(CharacterObject *Prnt);
	void update() override;
	virtual void kill() = 0;
	virtual void aply() = 0;
protected:
	CharacterObject *Parent;
	bool isdead;
	int turnsToDie;
};

class RallyModifier : public ModifierComponent {
public:
	RallyModifier(CharacterObject *Prnt);
	void kill();
	void aply();
};
