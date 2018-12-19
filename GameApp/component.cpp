#include "pch.h"
#include "component.h"


component::component(object *Parent, String Category)
{
	parent = Parent;
	category = Category;
}



component::~component()
{
	if (parent) parent = NULL;
}

String component::getCategory()
{
	return category;
}


/****************************************************************************************************************************************/
//                                                   The Weapon Class                                                                    //
/****************************************************************************************************************************************/




WeaponComponent::WeaponComponent(CharacterObject * Parent,String Name):component(NULL,"Weapon")
{
	name = Name;
	parent = Parent;
}

WeaponComponent::~WeaponComponent()
{
	if (parent) parent = NULL;
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

int WeaponComponent::getDamage()
{
	return Damage;
}

int WeaponComponent::getPenetration()
{
	return penetration;
}

void WeaponComponent::spawn()
{
}

/****************************************************************************************************************************************/
//                                                   The Armor Class                                                                    //
/****************************************************************************************************************************************/





ArmorComponent::ArmorComponent(CharacterObject * Parent, String Type, String Place) :component(NULL, "Weapon")
{	
	type = Type;

	parent = Parent;
}

ArmorComponent::~ArmorComponent()
{
	parent = NULL;
}

float ArmorComponent::getResistance(String type)
{
	return 0;
}

void ArmorComponent::update() // needs work
{
}

void ArmorComponent::spawn(std::vector<int> resistances, std::vector<int> modifiers)
{
}

void ArmorComponent::ChangeParent(CharacterObject * Parent)
{
	//may cause a seg fault if used wrong. we will see
	parent = Parent;
}

