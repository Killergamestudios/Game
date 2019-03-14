#pragma once
#include "component.h"


using namespace std;

class DataBase
{
public:
	DataBase();
	~DataBase();
	ArmorComponent* getArmor(int ID);
	ArmorComponent* getArmor(string Name);

	WeaponComponent* getWeapon(int ID);
	WeaponComponent* getWeapon(string Name);

	CharacterObject getCharacter(int ID, RenderWindow &window, String Category, String Type, Vector2i Position, Texture &texture, int level = 0); //Not Complete, creates character based on Database values.
	CharacterObject getCharacter(string Name, RenderWindow &window, String Category, String Type, Vector2i Position, Texture &texture, int level = 0); //Not Complete, creates character based on Database values.


private:
	vector<ArmorComponent> armors;
	vector<vector<pair<string, bool>>>bodyParts;
	vector<vector<pair<ElementType, int>>> resistances;

	vector<WeaponComponent> weapons;

	//For characters
	vector<Stats> statBlocks;
	vector<StatGain> statGainBlocks;
	map<string, int> charactersIndex;
	vector<vector<string>> characterAttachments;
	vector<int> weaponDropChance;
	vector<int> armorDropChance;
};

