#pragma once
#include "../../Header Files/Core/textureHolder.h"
#include <SFML/Graphics.hpp>
#include "../../Header Files/Objects/object.h"
#include "../../Header Files/Core/Engine.h"
#include "../../Header Files//Objects/ObjectContainer.h"
#include "fstream"
#include <iostream>
#include <sstream>




using namespace sf;
using namespace std;
// this func gets a string like: "name = int" and returns the int
int getStringNumber(string &s) {
	string tmps;
	char tmpc;
	int ret;
	std::stringstream ss;
	ss << s;
	ss >> tmps >> tmpc >> ret;
	return ret;
}




CharacterObject* Map::SpawnCharacter(Vector2i position, string savefilename,string Name, string Class) {

	string texture = "./graphics/Sprites/" + Class + ".png";
	CharacterObject *Character = new CharacterObject(Name, *m_window, "friendly", "warrior", position, TextureHolder::GetTexture(texture));
	string filename;
	ifstream myfile;
	filename = "savefiles/" + savefilename + "Characters/" + Class + ".txt";
	myfile.open(filename);
	
	// read the stats and call the spawn func
	int *filereadints;
	string line;
	filereadints = new int[10];
	char tempc;
	getline(myfile, line);
	for (int i = 0; i < 10; i++) {
		getline(myfile, line);
		filereadints[i] = getStringNumber(line);
	}
	Stats stats = {filereadints[0],filereadints[1] ,filereadints[2] ,filereadints[3] ,filereadints[4] ,filereadints[5] 
					,filereadints[6] ,filereadints[7],filereadints[2],filereadints[3],filereadints[4],filereadints[8],filereadints[9]};
	delete filereadints;
	getline(myfile, line);
	filereadints = new int[5];
	for (int i = 0; i < 5; i++) {
		getline(myfile, line);
		filereadints[i] = getStringNumber(line);
	}
	myfile >> tempc;
	StatGain statgain = { filereadints[0],filereadints[1],filereadints[2],filereadints[3],filereadints[4]};
	delete filereadints;
	myfile >> tempc;

	Character->spawn(stats, statgain);


	//The abilities
	getline(myfile, line);
	getline(myfile,line);
	AbilityComponent *ability = readAbility(line, Character);
	Character->AddAbility1(ability);

	getline(myfile, line);
	ability = readAbility(line, Character);
	Character->AddAbility2(ability);

	getline(myfile, line);
	ability = readAbility(line, Character);
	Character->AddAbility3(ability);


	//The Weapon

	// The Armor

	
	// The items

	myfile.close();
	return Character;
}


//warrior = 1. healer = 2. archer = 3. tank = 4. ranger = 5. mage = 6. doctor = 7.
//load the whole party
void Map::loadParty(Map *map, string savefilename){
	//get the position of every character.
    vector<Vector3i> pos;
	vector<CharacterObject> party;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (m_friendlyCharacters[i][j] != 0) {
				switch (m_friendlyCharacters[i][j]) {
				case 1:
					party.push_back(*SpawnCharacter(Vector2i(i, j), savefilename, "nathan", "warrior"));
					break;
				case 2:
					party.push_back(*SpawnCharacter(Vector2i(i, j), savefilename, "name2", "healer"));
					break;
				case 3:
					party.push_back(*SpawnCharacter(Vector2i(i, j), savefilename, "name3", "archer"));
					break;
				case 4:
					party.push_back(*SpawnCharacter(Vector2i(i, j) ,savefilename, "name4", "tank"));
					break;
				case 5:
					party.push_back(*SpawnCharacter(Vector2i(i, j),  savefilename, "name5", "ranger"));
					break;
				case 6:
					party.push_back(*SpawnCharacter(Vector2i(i, j), savefilename, "name 6", "mage"));
					break;
				case 7:
					party.push_back(*SpawnCharacter(Vector2i(i, j), savefilename, "name 7", "doctor"));
					break;
				}
			}
		}
	}
	ObjectContainer::SetParty(party);

}

/*vector<CharacterObject> & Map::getparty() {
	return party;
}*/

vector<CharacterObject>& Map::getenemys()
{
	return m_enemys;
}
