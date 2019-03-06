#pragma once
#include <SFML/Graphics.hpp>
#include "../Core/textureHolder.h"
#include "../Core/Map.h"
#include "component.h"

using namespace sf;
using namespace std;

class Map;
class component;
class AbilityComponent;
class ModifierComponent;
class WeaponComponent;
class ArmorComponent;

enum Move {standing,left,right,up,down,};
enum FacingDirection{front,back,fleft,fright};
enum ElementType;

//most of the components later will get replaced by dedicated classes than inherit the component class
struct StatGain
{
	int MaxHealthGain;
	int MaxEnergyGain;
	int MaxActionsGain;
	int AgilityGain;  // every 5 levels
	int PrecisionGain;
};
struct Stats
{
	// The Level Stats
	int level;
	int exp;

	//The Constant Resourse stats
	int MaxHealth;
	int MaxEnergy;
	int MaxActions;

	//The Constant Stats
	int Agility;
	int Precision;
	int Mastery;

	// The temp Resourse stats
	int Health;
	int Energy;
	int actionsremaining;
};



/****************************************************************************************************************************************/
//                                                   The Object Class                                                                   //
/****************************************************************************************************************************************/

class object
{
public:
	object(RenderWindow &window, String Category, String Type, Vector2i Position, Texture &texture);
	~object();
	virtual void Draw() = 0;
	virtual void update(float dtAsseconds) = 0;

protected:
	String category;//friendly enemy misc
	String type; //the obj type: scout warrior etc(for enemys) , ballistra chest etc(for misc)
	Texture* m_texture;
	VertexArray vertarr;
	RenderWindow *m_window;
	Vector2i m_position;
};


/****************************************************************************************************************************************/
//                                                   The CharacterObject Class                                                          //
/****************************************************************************************************************************************/

class CharacterObject : public object {
public:
	CharacterObject(String Name, RenderWindow &window, String Category, String Type, Vector2i Position, Texture &texture);
	~CharacterObject();

	//Draw and Update Functions
	void Draw() override;
	void update(float dtAsseconds) override;
	
	//Move Functions
	void MoveAdj(Vector2i newPos);
	void MoveToPosition(vector<Vector2i> &path);

	//Getters
	const Stats & getM_stats();
	Vector2i getMyPosition();
	int getActionsRemaining();
	string getCategory();
	int getEnergy();
	int getAgility();
	int getLegsTimesHit();
	String getType();
	int getMastery();
	int getPrecision();

	//setters
	void UpdateStats(Stats &s);
	void addModifier(ModifierComponent *m);
	void setAgility(int agi);
	void setPrecision(int prec);

	//Leveling up
	void LevelUp();	
	bool GiveExp(int exp); // true if the character leveled up
	void LevelMastery();

	//To spawn a Characetr: call the constructor, call the spawn func, add weapon and armor with those functions 
	//Spawn functions
	void spawn(Stats &stats, StatGain &statgain);
	void equipWeapon(WeaponComponent *weapon);
	void equipArmor(ArmorComponent *armorcomponent);
	void AddAbility1(AbilityComponent *ability);


	//combat related functions
	int Attack(CharacterObject *target, String place); // return the damage, -1 if attack dodged. place is body,head etc
	int isAttackedPhysical(string place, int damage);
	int isAttackedMagic(float amplitude, ElementType element, int duration, int PhysicalDamage = 0);
	void loseHp(int HpLoss);
	void gainHp(int HpGain, CharacterObject *target = nullptr);
	void gainActions(int ActionGain);
	bool AttackRegisters(string place,CharacterObject *target);
	void usedAction(int used);
	
	//rest of the funcions. whatever we will need later
	//Abilitys

	void UseAbility1(Vector2i &position,CharacterObject *target);
	

private:
	Move move;
	bool isAlive;
	bool hasMoved;
	String name; //the objects name


	//Variables for the movement
	int pixelscrossed = 0;
	float lastupdated = 0.0f;
	int movingquad = 0;
	FacingDirection facingdir = FacingDirection::front;
	bool isMoving = false;
	vector<Vector2i> m_path;
	void moveupdate(float dtAsSeconds);
	//end of movement variables
	
	//items weapons and armor
	//vector<component> m_items; // items like potions etc
	WeaponComponent* m_weapon; // shows what weapon from the m_weapons vector is curently equiped
	ArmorComponent* m_Armor;
	//end

	// buffs or debuffs that need to be removed added or aply
	vector<ModifierComponent*> m_modifiers; 

	//abilities
	AbilityComponent *m_ability1; // starts at null gets unlocked at some point

	AbilityComponent* m_ability2;

	AbilityComponent* m_ability3;

	// end of abilities



	//The Stats
	Stats m_stats;
	StatGain m_statGain; // at every level

	int HeadTimesHit = 0;
	int BodyTimesHit = 0;
	int RightHandTimesHit = 0;
	int LeftHandTimesHit = 0;
	int LegsTimeHit = 0;
	int MaxRightHandTimesHit = 3;
	int MaxLeftHandTimesHit = 3;
	int MaxLegsTimesHit = 3;


	//the stats it upgrades every lavel up
	//StatGain m_statgain;
};

