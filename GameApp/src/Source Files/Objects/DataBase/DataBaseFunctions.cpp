#pragma once

#include "../../../Header Files/Objects/DataBase.h"

//Method for acquiring Armor items by ID
ArmorComponent * DataBase::getArmor(int ID)
{
	for (auto i = armors.begin(); i != armors.end(); ++i)
		if (ID == i->getid())
			return i->copySelf();
	throw "404: not found";
	return nullptr;
}

//Method for acquiring Armor items by Name
ArmorComponent * DataBase::getArmor(string Name)
{
	for (auto i = armors.begin(); i != armors.end(); ++i)
		if (Name == i->getname())
			return i->copySelf();
	throw "404: not found";
	return nullptr;
}

//Method for acquiring Weapon item by ID
WeaponComponent * DataBase::getWeapon(int ID)
{
	for (auto i = weapons.begin(); i != weapons.end(); ++i) {
		if (ID == i->getid())
			return i->copySelf();
	}
	throw "404: not found";
	return nullptr;
}

//Method for acquiring Weapon item by Name
WeaponComponent * DataBase::getWeapon(string Name)
{
	for (auto i = weapons.begin(); i != weapons.end(); ++i) {
		if (Name == i->Getname())
			return i->copySelf();
	}
	throw "404: not found";
	return nullptr;
}
CharacterObject * DataBase::getCharacter(int ID, RenderWindow & window, String Category, String Type, Vector2i Position, Texture & texture, int level)
{
	int id = ID;
	string Name = "nullCharacter";
	for (auto &const it : charactersIndex)
	{
		if (it.second == id)
		{
			Name = it.first;
			break;
		}
	}
	Stats temp;
	temp = statBlocks[id];
	temp.Agility += level * statGainBlocks[id].AgilityGain / 5;
	temp.MaxActions += level * statGainBlocks[id].MaxActionsGain;
	temp.MaxEnergy += level * statGainBlocks[id].MaxEnergyGain;
	temp.MaxHealth += level * statGainBlocks[id].MaxHealthGain;
	temp.Precision += level * statGainBlocks[id].PrecisionGain;

	temp.Health = temp.MaxHealth;
	temp.MaxAgility = temp.Agility;
	temp.MaxPrecision = temp.Precision;
	temp.Energy = temp.MaxEnergy;
	temp.MaxActions = temp.actionsremaining;
	temp.level = level;

	CharacterObject * newCharacter = new CharacterObject(Name, window, Category, Type, Position, texture);
	newCharacter->spawn(temp, statGainBlocks[id]);
	newCharacter->equipWeapon(getWeapon(characterAttachments[id][0]));
	newCharacter->equipArmor(getArmor(characterAttachments[id][1]));
	// Somehow includes ability 1 (characterAttachments[id][2])
	// Somehow includes ability 2 (characterAttachments[id][3])
	// Somehow includes ability 3 (characterAttachments[id][4])



	return newCharacter;
}
CharacterObject* DataBase::getCharacter(string Name, RenderWindow & window, String Category, String Type, Vector2i Position, Texture & texture, int level)
{
	int id = charactersIndex.at(Name);
	Stats temp;
	temp = statBlocks[id];
	temp.Agility += level * statGainBlocks[id].AgilityGain / 5;
	temp.MaxActions += level * statGainBlocks[id].MaxActionsGain;
	temp.MaxEnergy += level * statGainBlocks[id].MaxEnergyGain;
	temp.MaxHealth += level * statGainBlocks[id].MaxHealthGain;
	temp.Precision += level * statGainBlocks[id].PrecisionGain;

	temp.Health = temp.MaxHealth;
	temp.MaxAgility = temp.Agility;
	temp.MaxPrecision = temp.Precision;
	temp.Energy = temp.MaxEnergy;
	temp.MaxActions = temp.actionsremaining;
	temp.level = level;

	CharacterObject * newCharacter = new CharacterObject(Name, window, Category, Type, Position, texture);
	newCharacter->spawn(temp, statGainBlocks[id]);
	newCharacter->equipWeapon(getWeapon(characterAttachments[id][0]));
	newCharacter->equipArmor(getArmor(characterAttachments[id][1]));
	// Somehow includes ability 1 (characterAttachments[id][2])
	// Somehow includes ability 2 (characterAttachments[id][3])
	// Somehow includes ability 3 (characterAttachments[id][4])



	return newCharacter;
}