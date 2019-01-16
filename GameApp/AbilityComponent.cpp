#include "pch.h"
#include "AbilityComponent.h"
#include "Map.h"
/***************************************************************************************ABILITY COMPONENT CLASS *********************************************/
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

Whirlwind::Whirlwind(CharacterObject * Parent):AbilityComponent(nullptr,"Whirlwind")
{
}

Whirlwind::~Whirlwind()
{
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

bool Whirlwind::canUse()
{
	return (parent->getActionsRemaining() >= ActionCost );
}
