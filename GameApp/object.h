#pragma once
#include <SFML/Graphics.hpp>
#include "textureHolder.h"
#include "component.h"

using namespace sf;

//most of the components later will get replaced by dedicated classes than inherit the component class

struct Stats
{
	int level;
	int exp;
	int health;
	int MaxHealth;
	int energy;
	int MaxEnergy;
	int movement;
	int MaxMovement;
	float attackModifierRight;// starts at 1.00f and decreases or increases based on current buffs or damage at the right hand
	float moveModifier;// starts at 1.00f and decreases or increases based on current buffs or damage at the legs
	float attackModifier;// starts at 0.75f and decreases or increases based on current buffs or damage at the left hand
};
struct Head
{
	component *m_headArmor;
	float PhysicalResistance; // base depending on character changes with armor and buffs
	float magicResistance;
	float damageModifier; //base of 2.0f
	int timesAttacked;
	int dodgeChance; // 0 - 100 
};
struct Body
{
	component *m_bodyArmor;
	float PhysicalResistance;
	float magicResistance;
	float damageModifier;
	int timesAttacked;
	int dodgeChance;
};
struct RightHand
{
	component *m_RightHandArmor;
	float PhysicalResistance;
	float magicResistance;
	float damageModifier;
	int timesAttacked;
	int MaxTimesAttacked;// if you attack it for the max times it gets cut
	int dodgeChance;
	float RightdamageDebuff; // every time you attack it increases. starts from .0f
	float MaxRightdamageDebuff; // you cant give him more debuff than the max.
	//if you continue to hit him after the max untill the max times attacked he will lose his right hand

};
struct leftHand
{
	component *m_LeftHandArmor;
	float PhysicalResistance;
	float magicResistance;
	float damageModifier;
	int timesAttacked;
	int MaxTimesAttacked;
	int dodgeChance;
	float LeftdamageDebuff;
	float MaxLeftdamageDebuff;

};
struct Legs
{
	component *m_LegArmor;
	float PhysicalResistance;
	float magicResistance;
	float damageModifier;
	int timesAttacked;
	int MaxTimesAttacked; // when legs are choped
	int dodgeChance;
	float movementDebuff; // as you hit the legs he can move less
	float MaxmovementDebuff; 
};

class object
{
public:
	object(RenderWindow &window, String Category, String Type, Vector2f Position, Sprite sprite);
	~object();
	virtual void Draw() = 0;
	//virtual void update() = 0;


protected:
	String category;//friendly enemy misc
	String type; //the obj type: scout warrior etc(for enemys) , ballistra chest etc(for misc)
	Sprite m_sprite;
	RenderWindow *m_window;
	Vector2f m_position;
};

class CharacterObject : public object {
public:
	CharacterObject(String Name, RenderWindow &window, String Category, String Type, Vector2f Position, Sprite sprite);
	~CharacterObject();
	void Draw() override;
	//void update() override;
	void spawn();
	//rest of the funcions. whatever we will need later



private:
	bool isAlive;
	bool hasMoved;
	String name; //the objects name

	Stats m_stats;

	vector<WeaponComponent*> m_weapons; // the weapons of each character
	vector<component*> m_modifiers; // buffs or debuffs that need to be removed added or aply
	vector<component*> m_items; // items like potions etc
	
	component *m_ability1; // starts at null gets unlocked at some point
	bool ability1isActive; // if it was used it gets on couldown and we use ints to know the passed time
						   //or maybe charges and we use charges we will decide later
	component *m_ability2;
	bool ability2isActive;
	component *m_ability3;
	bool ability3isActive;


	Head m_head;
	Body m_body;
	RightHand m_righthand;
	leftHand m_lefthand;
	Legs m_legs;
	
	component *m_AI; // null for playable characters .will expand later



};

