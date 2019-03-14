#pragma once

#include "../../../Header Files/Objects/DataBase.h"


DataBase::~DataBase()
{
}
DataBase::DataBase()
{
	/****************************************************************************************************************************************/
	//                                                       CHARACTERS                                                                      //
	/****************************************************************************************************************************************/
	//Characters Stat Blocks: exp, maxHealth, Agility, Precision, MaxEnergy, Precision, Mastery, Actions Remaining

	//Character ID: 0 - nullCharacter
	charactersIndex.insert(pair<string, int>("nullCharacter", 0));
	statBlocks[0].exp = 0;
	statBlocks[0].MaxHealth = 0;
	statBlocks[0].Agility = 0;
	statBlocks[0].Precision = 0;
	statBlocks[0].MaxEnergy = 0;
	statBlocks[0].Mastery = 0;
	statBlocks[0].actionsremaining = 0;

	//Stat Gains Block - Saved as the character's Stat gain block. Also used for level adjustments
	statGainBlocks[0].AgilityGain = 1;
	statGainBlocks[0].MaxActionsGain = 1;
	statGainBlocks[0].MaxEnergyGain = 1;
	statGainBlocks[0].MaxHealthGain = 1;
	statGainBlocks[0].PrecisionGain = 1;

	//Weapons to Equip, Armour to Equip, Abilities
	characterAttachments.push_back({ "Null","null","Billabong","Dark_Satan","Weeee" });
	weaponDropChance.push_back(0);
	armorDropChance.push_back(0);

	//====================================================


	//Character ID: 1 - Demorgan
	charactersIndex.insert(pair<string, int>("Demorgan", 1));
	statBlocks[1].exp = 900;
	statBlocks[1].MaxHealth = 2;
	statBlocks[1].Agility = 50;
	statBlocks[1].Precision = 140;
	statBlocks[1].MaxEnergy = 122;
	statBlocks[1].Mastery = 3;
	statBlocks[1].actionsremaining = 5;

	//Stat Gains Block - Saved as the character's Stat gain block. Also used for level adjustments
	statGainBlocks[1].AgilityGain = 2;
	statGainBlocks[1].MaxActionsGain = 1;
	statGainBlocks[1].MaxEnergyGain = 10;
	statGainBlocks[1].MaxHealthGain = 15;
	statGainBlocks[1].PrecisionGain = 10;

	//Weapons to Equip, Armour to Equip, Abilities
	characterAttachments.push_back({ "Purple","Bag","Billabong","Billabong","Billabong" });
	weaponDropChance.push_back(12);
	armorDropChance.push_back(60);

	//====================================================


	//Character ID: 2 - Uko
	charactersIndex.insert(pair<string, int>("Uko", 2));
	statBlocks[2].exp = 100;
	statBlocks[2].MaxHealth = 11;
	statBlocks[2].Agility = 11;
	statBlocks[2].Precision = 11;
	statBlocks[2].MaxEnergy = 1;
	statBlocks[2].Mastery = 12;
	statBlocks[2].actionsremaining = 1;

	//Stat Gains Block - Saved as the character's Stat gain block. Also used for level adjustments
	statGainBlocks[2].AgilityGain = 11;
	statGainBlocks[2].MaxActionsGain = 1;
	statGainBlocks[2].MaxEnergyGain = 1;
	statGainBlocks[2].MaxHealthGain = 1;
	statGainBlocks[2].PrecisionGain = 1;

	//Weapons to Equip, Armour to Equip, Abilities
	characterAttachments.push_back({ "Null","Bag","null","Dark_Satan","null" });
	weaponDropChance.push_back(213);
	armorDropChance.push_back(1);

	//====================================================

	/****************************************************************************************************************************************/
	//                                                         WEAPONS                                                                        //
	/****************************************************************************************************************************************/
	//weapons.push_back(new WeaponComponent(Type, Name));
	//weapons[id].spawn(element,amplitude,duration,damage,range,masteryReq,classReq,Description);

	weapons.push_back(WeaponComponent(scepter, "Null", 0));
	weapons[0].spawn(harmony, 0, 0, 1, 1, 1, "Villain", "The Null_Weapon");

	weapons.push_back(WeaponComponent(halberd, "Purple", 1));
	weapons[1].spawn(ice, 1, 3, 1, 1, 1, "Villain", "Wooow!");

	/****************************************************************************************************************************************/
	//                                                         ARMORS                                                                        //
	/****************************************************************************************************************************************/
	//Populating Armors DataBase
	//Buffs/Debuffs haven't been included yet.
	//Item ID: 0 - null
	armors.push_back(ArmorComponent("null", 0));
	bodyParts.push_back({ pair<string,bool>("legs",false),pair<string,bool>("rightArm",false),pair<string,bool>("leftArm",false),pair<string,bool>("Head",false) });
	resistances.push_back({ pair<ElementType,int>(fire,0),pair<ElementType,int>(ice,0),pair<ElementType,int>(poison,0),pair<ElementType,int>(dark,0),pair<ElementType,int>(nature,0),pair<ElementType,int>(wind,0),pair<ElementType,int>(light,0),pair<ElementType,int>(harmony,0) });
	armors[0].spawn(resistances[+0], false, "Null Armor Object", bodyParts[0], 1, "Villain", 1, 0);

	//Item ID: 1 - Bag
	armors.push_back(ArmorComponent("Bag", 1));
	bodyParts.push_back({ pair<string,bool>("legs",false),pair<string,bool>("rightArm",false),pair<string,bool>("leftArm",false),pair<string,bool>("Head",false) });
	resistances.push_back({ pair<ElementType,int>(fire,11),pair<ElementType,int>(ice,1),pair<ElementType,int>(poison,3),pair<ElementType,int>(dark,1),pair<ElementType,int>(nature,1),pair<ElementType,int>(wind,1),pair<ElementType,int>(light,1),pair<ElementType,int>(harmony,1) });
	armors[1].spawn(resistances[+1], false, "", bodyParts[1], 1, "Wizard", 1, 1);

}
