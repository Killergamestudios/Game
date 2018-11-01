#pragma once
#include <SFML/Graphics.hpp>

class object;
class CharacterObject;
using namespace sf;

struct Resistance
{
	float FireResistance;
	float lightingResistance;
	float coldResistance;
	float piercingResistance;
	float slashingResistance;
	float BludgeoningResistance;
};


class component
{
public:
	component(object *Parent, String Category);
	~component();
	virtual void update() = 0;

protected:
	object *parent;
	String category;
};

class WeaponComponent : public component {
public:
	WeaponComponent(CharacterObject * Parent, String name);
	~WeaponComponent();
	void update() override;//updating for special weapons (like a waepon that heals etc) a switch will be addet later we'll keep it null for now
	String Gettype();
	String Getname();
	String GetDamageType();
	int GetattackRange();
	float getDamage();
	void spawn(float damage, int attackrange, String damagtype);



private:
	String type; //sword bow staff etc
	String name;// GreatSword , a special sword that a character has etc
	String DamageType; //piercing slasing magic etc
	int attackRange; // one tile 2 tiles etc
	float Damage; //
	CharacterObject *parent;
};


class ArmorComponent :public component {
public:
	ArmorComponent(CharacterObject *Parent, String Type, String Place);
	~ArmorComponent();
	float getResistance(String type);
	void update(); // same as before we keep it for special armor effects
	void spawn(Resistance resistance);
	void ChangeParent(CharacterObject *Parent);

private:
	CharacterObject *parent;
	String place; // head,body etc
	String type; // chainmail, platemail etc
	Resistance m_Resistance;
};



