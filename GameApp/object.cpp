#include "pch.h"
#include "object.h"


object::object(RenderWindow &window, String Category, String Type, Vector2f Position, Sprite sprite)
{
	m_window = &window;
	type = Type;
	category = Category;
	m_sprite = sprite;
	m_position.x = Position.x; m_position.y = Position.y;
}


object::~object()
{
	m_window = NULL;
}

CharacterObject::CharacterObject(String Name, RenderWindow &window, String Category, String Type, Vector2f Position, Sprite sprite) :
	object(window,Category,Type,Position,sprite)
{
	name = Name;

	m_sprite.setOrigin(32, 32);
}

CharacterObject::~CharacterObject()
{
}

void CharacterObject::Draw()
{
	m_sprite.setPosition(m_position);
	m_window->draw(m_sprite);
}


