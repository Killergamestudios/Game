#pragma once
#include "pch.h"
#include "AbilityComponent.h"
#include "Map.h"
#include "ModifierComponent.h"
#include "Algorithms2.h"

/******************************************************ABILITY COMPONENT CLASS *********************************************/
AbilityComponent::AbilityComponent(CharacterObject *Parent, String Name):component(nullptr,"Ability")
{
	parent = Parent;
	name = Name;
}

AbilityComponent::~AbilityComponent()
{
	parent = nullptr;
}

int AbilityComponent::getCost()
{
	return ActionCost;
}
/******************************************************Whirlwind CLASS *********************************************/
Whirlwind::Whirlwind(CharacterObject * Parent):AbilityComponent(Parent,"Whirlwind")
{
	ActionCost = 3;
}

Whirlwind::~Whirlwind()
{
	parent = nullptr;
}

void Whirlwind::update()
{
}

void Whirlwind::use(Vector2i & position, CharacterObject * target)
{
	Vector2i m_position = parent->getMyPosition();
	if (position.x != m_position.x || position.y != m_position.y) throw std::exception("invalid position");
	Map *map = parent->getmap();
	std::vector<Vector2i> enemysToHit;
	CharacterObject *enemy;
	for(int i = -1; i <= 1 ;i++)
		for (int j = -1; j <= 1; j++) {
			if ((i != 0 && j != 0) && map->getEnemyinPosition(Vector2i(i + m_position.x, j + m_position.y)) != 0) 
				enemysToHit.push_back(Vector2i(i + m_position.x, j + m_position.y));
		}
	for (unsigned int i = 0; i < enemysToHit.size(); i++) {
		enemy = &map->getenemy(enemysToHit[i]);
		parent->Attack(enemy, "body");
	}
}

bool Whirlwind::canUse(Vector2i & position, CharacterObject * target)
{
	return (parent->getActionsRemaining() >= ActionCost );
}
/******************************************************Rally CLASS *********************************************/

Rally::Rally(CharacterObject * Parent) :AbilityComponent(Parent, "Rally") 
{
	ActionCost = 6;
}

void Rally::update()
{
}

void Rally::use(Vector2i & position, CharacterObject * target)
{
	Map * map = parent->getmap();
	vector<CharacterObject> party = map->getparty();
	RallyModifier * rally;

	for (unsigned int i = 0; i < party.size(); i++) {
		rally = new RallyModifier(&party[i]);
		party[i].addModifier(rally);
		rally = nullptr;
	}
	vector<CharacterObject> enemys = map->getenemys();
	for (unsigned int i = 0; i < enemys.size(); i++) {
		rally = new RallyModifier(&enemys[i]);
		enemys[i].addModifier(rally);
		rally = nullptr;
	}

}

bool Rally::canUse(Vector2i & position, CharacterObject * target)
{
	return (parent->getActionsRemaining() >= ActionCost);
}


/******************************************************Charge CLASS *********************************************/


Charge::Charge(CharacterObject * Parent):AbilityComponent(Parent,"charge")
{
	ActionCost = 4;
}

void Charge::setNumOfTiles(int n)
{
	numOfTiles = n;
}

void Charge::update()
{
}

void Charge::use(Vector2i & position, CharacterObject * target)
{
	vector<Vector2i> path;
	Vector2i m_position = parent->getMyPosition();
	int temp = 100;
	Map *map = parent->getmap();
	path = getPath(m_position.x, m_position.y, position.x, position.y, temp,*map);
	int travelcoordinate;//0 = up,1 = right, 2 = down, 3=left
	if (m_position.x < position.x) travelcoordinate = 1;
	else if (m_position.x > position.x) travelcoordinate = 3;
	else if (m_position.y < position.y) travelcoordinate = 2;
	else travelcoordinate = 0;
	//attack the target
	switch (travelcoordinate) {
	case 0:
		try {
			CharacterObject* enemy = &map->getenemy(Vector2i(m_position.x, m_position.y - 1));
			parent->Attack(enemy,"body");
		}
		catch (String s) { break; }
		break;
	case 1:
		try {
			CharacterObject* enemy = &map->getenemy(Vector2i(m_position.x+1, m_position.y ));
			parent->Attack(enemy, "body");
		}
		catch (String s) { break; }
		break;
	case 2:
		try {
			CharacterObject* enemy = &map->getenemy(Vector2i(m_position.x, m_position.y + 1));
			parent->Attack(enemy, "body");
		}
		catch (String s) { break; }
		break;
	case 3:
		try {
			CharacterObject* enemy = &map->getenemy(Vector2i(m_position.x - 1, m_position.y));
			parent->Attack(enemy, "body");
		}
		catch (String s) { break; }
		break;
	}
	//move there
	parent->MoveToPosition(path);
}

bool Charge::canUse(Vector2i & position, CharacterObject * target)
{
	bool ret = true;
	//has not enough action points
	if (!(parent->getActionsRemaining() >= ActionCost)) 
		ret = false;
	//can only charge in a straight line
	Vector2i m_position = parent->getMyPosition();
	if (m_position.x != position.x)
		if (m_position.y != position.y)
			ret = false;
	//has not enough movement
	int agility = parent->getAgility();
	int movementcost = 10 / agility;
	//needs more work


	return ret;
}

