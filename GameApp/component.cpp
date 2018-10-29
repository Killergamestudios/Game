#include "pch.h"
#include "component.h"


component::component(object *Parent, String Category)
{
	parent = Parent;
	category = Category;
	isDead = false;
}


component::~component()
{
	parent = NULL;
}


WeaponComponent::WeaponComponent(CharacterObject * Parent,String Name):component(NULL,"Weapon")
{
	name = Name;
	parent = Parent;
}

WeaponComponent::~WeaponComponent()
{
}

void WeaponComponent::update()
{
} // needs work

String WeaponComponent::Gettype()
{
	return type;
}

String WeaponComponent::Getname()
{
	return name;
}

String WeaponComponent::GetDamageType()
{
	return DamageType;
}

int WeaponComponent::GetattackRange()
{
	return attackRange;
}

float WeaponComponent::getDamage()
{
	return Damage;
}

void WeaponComponent::spawn(float damage, int attackrange, String damagetype)
{
	Damage = damage;
	attackRange = attackrange;
	DamageType = damagetype;
}

ArmorComponent::ArmorComponent(CharacterObject * Parent, String Type, String Place) :component(NULL, "Weapon")
{	
	type = Type;
	place = Place;

	parent = Parent;
}

ArmorComponent::~ArmorComponent()
{
	parent = NULL;
}

float ArmorComponent::getResistance(String type)
{
	if (type == "FireResistance") return m_Resistance.FireResistance;
	else if (type == "lightingResistance") return m_Resistance.lightingResistance;
	else if (type == "coldResistance") return m_Resistance.coldResistance;
	else if (type == "piercing") return m_Resistance.piercingResistance;
	else if (type == "slashing") return m_Resistance.slashingResistance;
	else if (type == "Bludgeoning") return m_Resistance.BludgeoningResistance;
	else return 0.0f;
}

void ArmorComponent::update() // needs work
{
}

void ArmorComponent::spawn(Resistance resistance)
{
	m_Resistance.lightingResistance = resistance.lightingResistance;
	m_Resistance.FireResistance = resistance.FireResistance;
	m_Resistance.coldResistance = resistance.coldResistance;
	m_Resistance.piercingResistance = resistance.piercingResistance;
	m_Resistance.slashingResistance = resistance.slashingResistance;
	m_Resistance.BludgeoningResistance = resistance.BludgeoningResistance;
}
