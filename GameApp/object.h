#pragma once
#include <SFML/Graphics.hpp>
#include "textureHolder.h"
#include "Map.h"
#include "AbilityComponent.h"
#include "component.h"
#include "ModifierComponent.h"

using namespace sf;
using namespace std;

class Map;
class AbilityComponent;
class ModifierComponent;

enum Move {standing,left,right,up,down,};
enum FacingDirection{front,back,fleft,fright};
//most of the components later will get replaced by dedicated classes than inherit the component class
struct StatGain
{
	int MaxHealthGain;
	int AgilityGain;  // every 5 levels
	int PrecisionGain;
	int MagicResistanceGain;
	int ArmorGain;
};
struct Stats
{
	// The constant stats
	int level;
	int exp;
	int MaxHealth;
	int Agility;
	int Precision;
	int MaxEnergy;
	int MagicResistance;
	int Armor;
	int Mastery;
	int actions;

	// The temp
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
	object(RenderWindow &window, String Category, String Type, Vector2i Position, Texture &texture,Map *map);
	~object();
	virtual void Draw() = 0;
	virtual void update(float dtAsseconds) = 0;
	Map * getmap();

protected:
	String category;//friendly enemy misc
	String type; //the obj type: scout warrior etc(for enemys) , ballistra chest etc(for misc)
	Texture* m_texture;
	VertexArray vertarr;
	RenderWindow *m_window;
	Vector2i m_position;
	Map *m_map;
};


/****************************************************************************************************************************************/
//                                                   The CharacterObject Class                                                          //
/****************************************************************************************************************************************/

class CharacterObject : public object {
public:
	CharacterObject(String Name, RenderWindow &window, String Category, String Type, Vector2i Position, Texture &texture,Map *map);
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
	Map * getmap();
	int getEnergy();
	int getAgility();
	int getLegsTimesHit();


	//Setters
	void UpdateStats(Stats &s);
	void addModifier(ModifierComponent *m);

	//Leveling up
	void LevelUp();	
	bool GiveExp(int exp); // true if the character leveled up

	//To spawn a Characetr: call the constructor, call the spawn func, add weapon and armor with those functions 
	//Spawn functions
	void spawn(Stats &stats, StatGain &statgain);
	void equipWeapon(WeaponComponent *weapon);
	void equipArmor(ArmorComponent *armorcomponent);
	void AddAbility1(AbilityComponent *ability);


	//combat related functions
	int Attack(CharacterObject *target, String place); // return the damage, -1 if attack dodged. place is body,head etc
	int isAttacked(string place, int damage, string damageType, int Penetration);
	void loseHp(int HpLoss);
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

	AbilityComponent* m_passiveAbility;

	// end of abilities

	//NEEDS WORK
	//Head m_head;
	//Body m_body;
	//RightHand m_righthand;
	//leftHand m_lefthand;
	//Legs m_legs;
	
	//The Ai
	component *m_AI; // null for playable characters .will expand later


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
