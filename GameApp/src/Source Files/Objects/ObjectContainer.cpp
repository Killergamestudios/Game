#include "..\..\Header Files\Objects\ObjectContainer.h"
#include <assert.h>
#include <windows.h>
ObjectContainer* ObjectContainer::m_s_Instance = nullptr;


ObjectContainer::ObjectContainer()
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

void ObjectContainer::SetParty(vector<CharacterObject>& prty)
{
	m_s_Instance->party = prty;
}

void ObjectContainer::setEnemys(vector<CharacterObject>& en)
{
	m_s_Instance->enemys= en;
}

CharacterObject * ObjectContainer::GetPartyMember(int index)
{
	return &m_s_Instance->party[index];
}

int ObjectContainer::getAllyVectorInPosition(Vector2i position)
{
	for (unsigned int i = 0; i < m_s_Instance->party.size(); i++) {
		if (position.x == m_s_Instance->party[i].getMyPosition().x && position.y == m_s_Instance->party[i].getMyPosition().y)
			return i;
	}
	return -1;
}

vector<CharacterObject>* ObjectContainer::getParty()
{
	return &m_s_Instance->party;
}

void ObjectContainer::UpdateParty(float dtasseconds)
{
	for (unsigned int i = 0; i < m_s_Instance->party.size(); i++) {
		m_s_Instance->party[i].update(dtasseconds);
	}
}

void ObjectContainer::drowParty()
{
	for (unsigned int i = 0; i < m_s_Instance->party.size(); i++) {
		m_s_Instance->party[i].Draw();
	}
}

void ObjectContainer::updateEnemys(float dtasseconds)
{
	for (unsigned int i = 0; i < m_s_Instance->enemys.size(); i++) {
		m_s_Instance->enemys[i].update(dtasseconds);
	}
}

void ObjectContainer::drowEnemys()
{
	for (unsigned int i = 0; i < m_s_Instance->enemys.size(); i++) {
		m_s_Instance->enemys[i].Draw();
	}
}

void ObjectContainer::MovePartyMember(int index, vector<Vector2i> &path)
{
	m_s_Instance->party[index].MoveToPosition(path);
}

void ObjectContainer::setPartyMemberPlayed(int index)
{
	m_s_Instance->party[index].setHasMoved(true);
}

bool ObjectContainer::getPartyMemberPlayed(int index)
{
	return m_s_Instance->party[index].getHasMoved();
}

void ObjectContainer::setPartyTurn()
{
	for (unsigned int i = 0; i < m_s_Instance->party.size(); i++)
		m_s_Instance->party[i].setHasMoved(false);
}

int ObjectContainer::getPartySize()
{
	return m_s_Instance->party.size();
}
