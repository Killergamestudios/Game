#pragma once
#include <SFML/Graphics.hpp>
#include <utility>
#include "../../Header Files/Objects/object.h"


class object;
class CharacterObject;
class ModifierComponent;

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

enum ElementType {none,fire,ice,poison,dark,nature,wind,light,harmony};
enum WeaponType {longsword,halberd,knife,bow,scepter,staff,dagger};



/****************************************************************************************************************************************/
//                                                   The Component Class                                                                 //
/****************************************************************************************************************************************/
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


/****************************************************************************************************************************************/
//                                                   The Weapon Class                                                                    //
/****************************************************************************************************************************************/
class WeaponComponent : public component {
public:
	WeaponComponent(WeaponType type, String name, int ID, CharacterObject * Parent = nullptr);
	~WeaponComponent();
	
	void spawn(ElementType Element, float amplitude, int duration, int damage, int range, int mastery, string classrequirment, string Description);
	bool canEquip(CharacterObject * Parent);
	void equip(CharacterObject * Parent);

	void update() override;
	WeaponComponent* copySelf();

	WeaponType Gettype();
	String Getname();
	ElementType getElement();
	float getAmplitude();
	int getDamage();
	int getRange();
	int getduration();
	string getDescription();
	int getid();

private:
	WeaponType type; //sword bow staff etc
	String name;// GreatSword , a special sword that a character has etc
	ElementType element;
	float elementAmplitude;
	int elementDuration;
	int Damage;
	int range;
	int id;

	int MasteryRequirment;
	string ClassRequirment;
	string Description;
	CharacterObject *parent;

};

/****************************************************************************************************************************************/
//                                                   The Armor Class                                                                     //
/****************************************************************************************************************************************/
class ArmorComponent :public component {
public:
	ArmorComponent(String name, int id = 0, CharacterObject *Parent = nullptr);
	~ArmorComponent();
	void spawn(vector<pair< ElementType, int>> Resistance , bool Isdropable, string description, vector<pair<string,bool>> coverage, int mastery, string Class, int physicalresistance,int upgradeSlots);
	bool canEquip(CharacterObject * Parent);

	void equip(CharacterObject * Parent);
	void unequip();

	void update() override;
	ArmorComponent* copySelf(); // NOT READY YET Modifier not ready

	string getname();
	float getResistance(ElementType element);
	bool isDropable();
	string getDescription();
	bool getcoverage(string place);
	int getid();
	int getPhysicalResistance();

private:
	CharacterObject *parent;
	int id;
	String name; // chainmail, platemail etc
	pair<ElementType, float> elementResistance[9];
	bool isdropable;
	string Description;
	pair<string, bool> coverage[5];
	vector<ModifierComponent*> Modifiers;
	int physicalResistance;
	int upgrades;

	int MasteryRequirment;
	string ClassRequirment;
};

/****************************************************************************************************************************************/
//                                                   The Modifier Class                                                                  //
/****************************************************************************************************************************************/

class ModifierComponent : public component {
public:
	ModifierComponent(CharacterObject *Prnt, int turns, std::string type);
	~ModifierComponent();

	bool getIsDead();
	int GetTurnsToDie();
	string getType();

	void setisDead();
	void setParent(CharacterObject *Prnt);
	void update() override; //call at the end of the characters turn;
	virtual void kill() = 0; // undoes the effects of the modifier
	virtual void aply() = 0; // trigers the effects of the modifier
protected:
	CharacterObject *Parent;
	bool isdead;
	int turnsToDie;
	string type;
};

/****************************************************************************************************************************************/
//                                                   The Buff Class                                                                      //
/****************************************************************************************************************************************/
class BuffModifierComponent : public ModifierComponent {
public:
	BuffModifierComponent(CharacterObject *Prnt, int turns, string atribute, int amplitude,string bufftype);
	~BuffModifierComponent();
	void update() override;
	void kill() override;
	void aply() override;
private:
	int amplitude;
	string atribute;
	int previousValue;// how much was it before the debuff - how much it is now
};

/****************************************************************************************************************************************/
//                                                   The Damage over time Class                                                          //
/****************************************************************************************************************************************/

class DamageOverTimeModifier : public ModifierComponent {
public:
	DamageOverTimeModifier(CharacterObject *Prnt, int turns, string dmgtype, int Amplitude);
	~DamageOverTimeModifier();
	void kill() override;
	void aply() override;
private:
	int amplitude;
	string damagetype;
};

/****************************************************************************************************************************************/
//                                                   The Rally Modifier Class                                                            //
/****************************************************************************************************************************************/

class RallyModifier : public ModifierComponent {
public:
	RallyModifier(CharacterObject *Prnt, int mastery);
	void kill();
	void aply();
private:
	int Mastery;
};



/****************************************************************************************************************************************/
//                                                   The Ability Component Class                                                         //
/****************************************************************************************************************************************/

class AbilityComponent :public component {
public:
	AbilityComponent(CharacterObject *Parent, String Name);
	~AbilityComponent();
	void ChangeParent(CharacterObject *prnt);
	
	string getName();

	virtual void update() = 0;
	virtual void use(Vector2i &position, CharacterObject *target) = 0;
	virtual bool canUse(Vector2i & position, CharacterObject * target) = 0;
	int getCost();


protected:
	CharacterObject *parent;
	String name;
	String description;
	int ActionCost;
	Sprite m_sprite;
	int range;
};


/****************************************************************************************************************************************/
//                                                   The Whirldwind Class                                                                //
/****************************************************************************************************************************************/
class Whirlwind : public AbilityComponent {
public:
	Whirlwind(CharacterObject *Parent);
	~Whirlwind();
	Whirlwind *copyself();

	void update() override;
	void use(Vector2i &position, CharacterObject *target = nullptr) override;
	bool canUse(Vector2i & position, CharacterObject * target) override;
};


/****************************************************************************************************************************************/
//                                                   The Rally Class                                                                     //
/****************************************************************************************************************************************/
class Rally : public AbilityComponent {
public:
	Rally(CharacterObject *Parent);
	Rally *copyself();

	void update() override;
	void use(Vector2i &position, CharacterObject *target = nullptr) override;
	bool canUse(Vector2i & position, CharacterObject * target) override;
};

/****************************************************************************************************************************************/
//                                                   The charge Class                                                                    //
/****************************************************************************************************************************************/



class Charge : public AbilityComponent {
public:
	Charge(CharacterObject *Parent);
	Charge *copyself();
	void setmastery();

	void setNumOfTiles(int n);
	void update() override;
	void use(Vector2i &position, CharacterObject *target) override;
	bool canUse(Vector2i & position, CharacterObject * target) override;
private:
	int numOfTiles = 0;
	int mastery;

};


AbilityComponent *readAbility(string &s, CharacterObject *object);