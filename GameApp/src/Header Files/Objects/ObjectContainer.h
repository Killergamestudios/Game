#pragma once
#include <SFML/Graphics.hpp>
#include "../../Header Files/Objects/object.h"

using namespace sf;
using namespace std;

class ObjectContainer {
public:
	ObjectContainer();
	static void SetParty(vector<CharacterObject> &prty);
	static void setEnemys(vector<CharacterObject> &en);


	static CharacterObject* GetPartyMember(int index);
	static int getAllyVectorInPosition(Vector2i position);
	static vector<CharacterObject>* getParty();

	static void UpdateParty(float dtasseconds);
	static void drowParty();

	static void updateEnemys(float dtasseconds);
	static void drowEnemys();

	static void MovePartyMember(int index, vector<Vector2i> &path);
	static void setPartyMemberPlayed(int index);
	static bool getPartyMemberPlayed(int index);
	static void setPartyTurn();
	static int getPartySize();
private:
	static ObjectContainer *m_s_Instance;
	
	vector<CharacterObject> enemys;
	vector<CharacterObject> party;
};