#include "pch.h"
#include "ModifierComponent.h"


ModifierComponent::ModifierComponent(CharacterObject *Prnt, int turns):component(NULL, "modifier"),turnsToDie(turns)
{
	Parent = Prnt;
	isdead = false;
}


ModifierComponent::~ModifierComponent()
{
	if (Parent) Parent = NULL;
}

bool ModifierComponent::getIsDead()
{
	return isdead;
}

int ModifierComponent::GetTurnsToDie()
{
	return turnsToDie;
}

void ModifierComponent::setParent(CharacterObject * Prnt)
{
	Parent = Prnt;
}

void ModifierComponent::update()
{

		turnsToDie--;
		aply();
		if (turnsToDie == 0) {
			isdead = true;
			kill();
		}
}

RallyModifier::RallyModifier(CharacterObject * Prnt):ModifierComponent(Prnt,3)
{
}

void RallyModifier::kill()
{
	if (!isdead) return;
	Stats s;
	if (Parent->getCategory() == "friendly") {
		s = { 0,0,0,-1,-1,0,-3,-5,-1,0 ,0,0,0 };
	}
	else if (Parent->getCategory() == "enemy") {
		s = { 0,0,0,1,1,0,3,5,1,0 ,0,0,0 };
	}
	Parent->UpdateStats(s);
}
void RallyModifier::aply()
{
	if (!(turnsToDie == 3)) return;
	Stats s;
	if (Parent->getCategory() == "friendly") {
		s = { 0,0,0,1,1,0,3,5,1,0 ,0,0,0};
	}
	else if (Parent->getCategory() == "enemy") {
		s = { 0,0,0,-1,-1,0,-3,-5,-1,0 ,0,0,0};
	}
	Parent->UpdateStats(s);
}
