#pragma once
#include <SFML/Graphics.hpp>

class object;
class CharacterObject;
using namespace sf;
using namespace std;

struct Resistance
{
	float FireResistance;
	float lightingResistance;
	float coldResistance;
	float piercingResistance;
	float slashingResistance;
	float BludgeoningResistance;
};

/********************************************COMPONENT CLASS************************************/
class component
{
public:
	component(object *Parent, String Category);
	~component();
	virtual void update() = 0;
	String getCategory();

protected:
	object *parent;
	String category;
};


/*************************************WEAPON COMPONENT CLASS******************************************/
class WeaponComponent : public component {
public:
	WeaponComponent(CharacterObject * Parent, String name);
	~WeaponComponent();
	
	void spawn();
	

	void update() override;//updating for special weapons (like a waepon that heals etc) a switch will be addet later we'll keep it null for now

	String Gettype();
	String Getname();
	String GetDamageType();
	int GetattackRange();
	int getDamage();
	int getPenetration();

private:
	String type; //sword bow staff etc
	String name;// GreatSword , a special sword that a character has etc
	String DamageType; //physical magic , hybridetc
	String ElementalDamageType;

	int penetration;
	int attackRange; // one tile 2 tiles etc
	int Damage; //
	int ElementalDamage;

	CharacterObject *parent;

};

/**************************************************ARMOR COMPONENT CLASS**************************************************************/
class ArmorComponent :public component {
public:
	ArmorComponent(CharacterObject *Parent, String Type, String Place);
	~ArmorComponent();
	float getResistance(String type);//where type = magic poison or physical
	void update(); // same as before we keep it for special armor effects
	void spawn(std::vector<int> resistances, std::vector<int> modifiers);
	void ChangeParent(CharacterObject *Parent);


private:
	CharacterObject *parent;
	String type; // chainmail, platemail etc


	int m_weight;
	int m_armor;

	// The resistances
	int magicResistance;
	int PoisonResistance;
	int physicalResistance;

	//The resistance modifiers for eatch body part
	int HeadResMod;
	int BodyResMod;
	int LegsResMod;
	int RightHandResMod;
	int LeftHandResMod;
};




