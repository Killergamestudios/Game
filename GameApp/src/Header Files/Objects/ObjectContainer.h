#pragma once
#include <SFML/Graphics.hpp>
#include "../../Header Files/Objects/object.h"

using namespace sf;
using namespace std;

class ObjectContainer {
public:
	ObjectContainer();
	static void SetParty(vector<CharacterObject> &prty);

	static CharacterObject* GetPartyMember(int index);
	static int getAllyVectorInPosition(Vector2i position);
	static vector<CharacterObject>* getParty();

	static void UpdateParty(float dtasseconds);
	static void drowParty();
	static void MovePartyMember(int index, vector<Vector2i> &path);
	static void MovePartyMember(CharacterObject*, vector<Vector2i> &path);
private:
	static ObjectContainer *m_s_Instance;

	vector<CharacterObject> party;
};