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

void ModifierComponent::update()
{
	turnsToDie--;
	if (turnsToDie == 0) isdead = true;
}


