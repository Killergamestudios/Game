#include "pch.h"
#include "object.h"


object::object(RenderWindow &window, String Category, String Type, Vector2f Position, Sprite sprite)
{
	m_window = &window;
	type = Type;
	category = Category;
	m_sprite = sprite;
	m_position.x = Position.x; m_position.y = Position.y;
}


object::~object()
{
	category.clear();
	type.clear();
	m_window = NULL;
}

CharacterObject::CharacterObject(String Name, RenderWindow &window, String Category, String Type, Vector2f Position, Sprite sprite) :
	object(window,Category,Type,Position,sprite)
{
	name = Name;

	m_sprite.setOrigin(32, 32);
}

CharacterObject::~CharacterObject()
{
	name.clear();
	equipedWeapon = NULL;
	for (unsigned int i = m_weapons.size()- 1; i >= 0 ; i--) {
		delete m_weapons[i];
		m_weapons[i] = NULL;
		m_weapons.pop_back();
	}
	for (unsigned int i = m_modifiers.size() - 1; i >= 0 ; i--) {
		delete m_modifiers[i];
		m_modifiers[i] = NULL;
		m_modifiers.pop_back();
	}
	for (unsigned int i = m_items.size() - 1; i >= 0 ; i--) {
		delete m_items[i];
		m_items[i] = NULL;
		m_items.pop_back();
	}
	if (m_ability1) delete m_ability1;
	if (m_ability2) delete m_ability2;
	if (m_ability3) delete m_ability3;
	if (m_AI) delete m_AI;

	if (m_head.m_headArmor) delete m_head.m_headArmor;
	if (m_body.m_bodyArmor) delete m_body.m_bodyArmor;
	if (m_righthand.m_RightHandArmor) delete m_righthand.m_RightHandArmor;
	if (m_lefthand.m_LeftHandArmor) delete m_lefthand.m_LeftHandArmor;
	if (m_legs.m_LegArmor) delete m_legs.m_LegArmor;


}

void CharacterObject::Draw()
{
	m_sprite.setPosition(m_position);
	m_window->draw(m_sprite);
}

void CharacterObject::update()
{
	for (unsigned int i = 0; i < m_modifiers.size(); i++)
	{
		//	if (m_modifiers[i].getIsDead) {
		//		m_modifiers.erase(m_modifiers.begin() + i);
		//}
		m_modifiers[i]->update();
	}
}

Stats CharacterObject::getM_stats()
{
	Stats stats;
	stats.level = m_stats.level;
	stats.exp = m_stats.exp;
	stats.health= m_stats.health;
	stats.MaxHealth= m_stats.MaxHealth;
	stats.energy= m_stats.energy;
	stats.MaxEnergy= m_stats.MaxEnergy;
	stats.movement = m_stats.movement;
	stats.MaxMovement= m_stats.MaxMovement;
	stats.attackModifierRight= m_stats.attackModifierRight;
	stats.moveModifier= m_stats.moveModifier;
	stats.attackModifierLeft = m_stats.attackModifierLeft;
	stats.accuracy = m_stats.accuracy;
	return stats;
}

void CharacterObject::LevelUp()
{
	m_stats.level++;
	
	m_stats.MaxHealth += m_statgain.MaxHealthGain;
	m_stats.MaxEnergy += m_stats.level % 5 == 0 ? m_statgain.MaxEnergyGain:0;
	
	m_stats.attackModifierLeft += m_statgain.AttackModifierGain;
	m_stats.attackModifierRight += m_statgain.AttackModifierGain;
	m_stats.accuracy += m_statgain.accuracyGain;

	m_head.magicResistance += m_statgain.MagicResistanceGain * 0.75f;
	m_head.PhysicalResistance += m_statgain.PhysicalResistanceGain * 0.75f;
	m_head.dodgeChance += m_statgain.DodgechanceGain;

	m_body.magicResistance += m_statgain.MagicResistanceGain;
	m_body.PhysicalResistance += m_statgain.PhysicalResistanceGain;
	m_body.dodgeChance += m_statgain.DodgechanceGain ;

	m_legs.magicResistance += m_statgain.MagicResistanceGain * 0.70f;
	m_legs.PhysicalResistance += m_statgain.PhysicalResistanceGain * 0.70f;
	m_legs.dodgeChance += m_statgain.DodgechanceGain;

	m_righthand.magicResistance += m_statgain.MagicResistanceGain * 0.70f;
	m_righthand.PhysicalResistance += m_statgain.PhysicalResistanceGain * 0.70f;
	m_righthand.dodgeChance += m_statgain.DodgechanceGain;

	m_lefthand.magicResistance += m_statgain.MagicResistanceGain * 0.70f;
	m_lefthand.PhysicalResistance += m_statgain.PhysicalResistanceGain * 0.70f;
	m_lefthand.dodgeChance += m_statgain.DodgechanceGain;


}

bool CharacterObject::GiveExp(int exp)
{
	m_stats.exp += exp;
	bool hasLeveledUp = false;
	while (m_stats.exp >= 100) { //leveled up
		m_stats.exp -= 100;
		LevelUp();
		hasLeveledUp = true;
	}
	return hasLeveledUp; 
}

void CharacterObject::spawn(Stats & stats, Head & head, Body & body, Legs & legs, RightHand & righthand, leftHand & lefthand, StatGain &statgain)
{
	m_stats = {stats.level, stats.exp, stats.health, stats.MaxHealth,stats.energy,stats.MaxEnergy,
			   stats.movement,stats.MaxMovement,stats.attackModifierRight,stats.attackModifierLeft,stats.accuracy};

	m_statgain = { statgain.MaxHealthGain,statgain.MaxEnergyGain, statgain.AttackModifierGain,statgain.MagicResistanceGain,statgain.PhysicalResistanceGain,statgain.accuracyGain,statgain.DodgechanceGain };

	m_head = { NULL, head.PhysicalResistance, head.magicResistance, head.damageModifier, 0, head.dodgeChance };

	m_body = { NULL, body.PhysicalResistance, body.magicResistance, body.damageModifier, 0, body.dodgeChance };

	m_legs = { NULL,legs.PhysicalResistance,legs.magicResistance, legs.damageModifier, 0, legs.MaxTimesAttacked, legs.dodgeChance, legs.movementDebuff, legs.MaxmovementDebuff };

	m_righthand = { NULL,righthand.PhysicalResistance, righthand.magicResistance,righthand.damageModifier, 0,righthand.MaxTimesAttacked, righthand.dodgeChance, righthand.RightdamageDebuff, righthand.MaxRightdamageDebuff };

	m_lefthand = { NULL,lefthand.PhysicalResistance, lefthand.magicResistance, lefthand.damageModifier, 0 , lefthand.MaxTimesAttacked, lefthand.dodgeChance, lefthand.LeftdamageDebuff, lefthand.MaxLeftdamageDebuff };


}



void CharacterObject::addWeapon(WeaponComponent * weapon)
{
	m_weapons.push_back(weapon);
}

void CharacterObject::equipWeapon(WeaponComponent * weapon)
{
	for (unsigned int i = 0; i < m_weapons.size(); i++) {
		if (m_weapons[i] == weapon) {
			equipedWeapon = m_weapons[i];
			break;
		}
	}
}

void CharacterObject::equipArmor(String Place, ArmorComponent & armorcomponent)
{
	if (Place == "Body") {
		if (m_body.m_bodyArmor) {
			delete m_body.m_bodyArmor;
		}
		m_body.m_bodyArmor = &armorcomponent;
	}
	else if (Place == "Head") {
		if (m_head.m_headArmor) {
			delete m_head.m_headArmor;
		}
		m_head.m_headArmor = &armorcomponent;
	}
	else if (Place == "Legs") {
		if (m_legs.m_LegArmor) {
			delete m_legs.m_LegArmor;
		}
		m_legs.m_LegArmor = &armorcomponent;
	}
	else if (Place == "RightHand") {
		if (m_righthand.m_RightHandArmor) {
			delete m_righthand.m_RightHandArmor;
		}
		m_righthand.m_RightHandArmor = &armorcomponent;
	}
	else if (Place == "LeftHand") {
		if (m_lefthand.m_LeftHandArmor) {
			delete m_lefthand.m_LeftHandArmor;
		}
		m_lefthand.m_LeftHandArmor = &armorcomponent;
	}
	armorcomponent.ChangeParent(this);

}

int CharacterObject::Attack(CharacterObject *target, String place) // missing the debuffs
{
	srand((int)time(0));
	Stats targetStats = target->getM_stats();
	if (place == "Head") {
		// calculate if the hit is dodged or not
		float ChanceToHit = m_stats.accuracy - target->m_head.dodgeChance; // the chance to hit. we will round it up
		if (rand() % 100 + 1 > int(ChanceToHit + 0.5f)) return -1; // hit misses
		//calculate the hit damage
		float DamageToDeal = m_righthand.timesAttacked < m_righthand.MaxTimesAttacked ? equipedWeapon->getDamage() * m_stats.attackModifierRight : m_lefthand.timesAttacked < m_lefthand.MaxTimesAttacked ?
			equipedWeapon->getDamage() *m_stats.attackModifierLeft : 0;//if both hands are cut damage = 0;
		DamageToDeal *= 2; // double damage is dealt to the head
		//calculate the damage resistance
		float EnemyResistance = target->m_head.m_headArmor->getResistance(equipedWeapon->GetDamageType());
		EnemyResistance += (equipedWeapon->GetDamageType() == "Lighting" || equipedWeapon->GetDamageType() == "Fire" || equipedWeapon->GetDamageType() == "Cold") ?
			target->m_head.magicResistance : target->m_head.PhysicalResistance;
		if (EnemyResistance >= 0.9f) EnemyResistance = 0.9f; // should cap around there
		int DamageDealt = (int)(DamageToDeal*(1 - EnemyResistance));
		target->loseHp(DamageDealt);
		target->m_head.timesAttacked++;
		return DamageDealt;
	}
	else if (place == "Body") {
		float ChanceToHit = m_stats.accuracy - target->m_body.dodgeChance; // the chance to hit. we will round it up
		if (rand() % 100 + 1 > int(ChanceToHit + 0.5f)) return -1; // hit misses
		//calculate the hit damage
		float DamageToDeal = m_righthand.timesAttacked < m_righthand.MaxTimesAttacked ? equipedWeapon->getDamage() * m_stats.attackModifierRight : m_lefthand.timesAttacked < m_lefthand.MaxTimesAttacked ?
			equipedWeapon->getDamage() *m_stats.attackModifierLeft : 0;//if both hands are cut damage = 0;
		DamageToDeal *= 2; // double damage is dealt to the head
		//calculate the damage resistance
		float EnemyResistance = target->m_body.m_bodyArmor->getResistance(equipedWeapon->GetDamageType());
		EnemyResistance += (equipedWeapon->GetDamageType() == "Lighting" || equipedWeapon->GetDamageType() == "Fire" || equipedWeapon->GetDamageType() == "Cold") ?
			target->m_body.magicResistance : target->m_body.PhysicalResistance;
		if (EnemyResistance >= 100) EnemyResistance = 0.9f; // should cap around there
		int DamageDealt = (int)(DamageToDeal*(1 - EnemyResistance));
		target->loseHp(DamageDealt);
		target->m_body.timesAttacked++;
		return DamageDealt;
	}
	else if (place == "Legs") {
		float ChanceToHit = m_stats.accuracy - target->m_legs.dodgeChance; // the chance to hit. we will round it up
		if (rand() % 100 + 1 > int(ChanceToHit + 0.5f)) return -1; // hit misses
		//calculate the hit damage
		float DamageToDeal = m_righthand.timesAttacked < m_righthand.MaxTimesAttacked ? equipedWeapon->getDamage() * m_stats.attackModifierRight : m_lefthand.timesAttacked < m_lefthand.MaxTimesAttacked ?
			equipedWeapon->getDamage() *m_stats.attackModifierLeft : 0;//if both hands are cut damage = 0;
		DamageToDeal *= 2; // double damage is dealt to the head
		//calculate the damage resistance
		float EnemyResistance = target->m_legs.m_LegArmor->getResistance(equipedWeapon->GetDamageType());
		EnemyResistance += (equipedWeapon->GetDamageType() == "Lighting" || equipedWeapon->GetDamageType() == "Fire" || equipedWeapon->GetDamageType() == "Cold") ?
			target->m_legs.magicResistance : target->m_legs.PhysicalResistance;
		if (EnemyResistance >= 100) EnemyResistance = 0.9f; // should cap around there
		int DamageDealt = (int)(DamageToDeal*(1 - EnemyResistance));
		target->loseHp(DamageDealt);
		target->m_legs.timesAttacked++;
		return DamageDealt;
	}
	else if (place == "RightArm") {
		float ChanceToHit = m_stats.accuracy - target->m_righthand.dodgeChance; // the chance to hit. we will round it up
		if (rand() % 100 + 1 > int(ChanceToHit + 0.5f)) return -1; // hit misses
		//calculate the hit damage
		float DamageToDeal = m_righthand.timesAttacked < m_righthand.MaxTimesAttacked ? equipedWeapon->getDamage() * m_stats.attackModifierRight : m_lefthand.timesAttacked < m_lefthand.MaxTimesAttacked ?
			equipedWeapon->getDamage() *m_stats.attackModifierLeft : 0;//if both hands are cut damage = 0;
		DamageToDeal *= 2; // double damage is dealt to the head
		//calculate the damage resistance
		float EnemyResistance = target->m_righthand.m_RightHandArmor->getResistance(equipedWeapon->GetDamageType());
		EnemyResistance += (equipedWeapon->GetDamageType() == "Lighting" || equipedWeapon->GetDamageType() == "Fire" || equipedWeapon->GetDamageType() == "Cold") ?
			target->m_righthand.magicResistance : target->m_righthand.PhysicalResistance;
		if (EnemyResistance >= 100) EnemyResistance = 0.9f; // should cap around there
		int DamageDealt = (int)(DamageToDeal*(1 - EnemyResistance));
		target->loseHp(DamageDealt);
		target->m_righthand.timesAttacked++;
		return DamageDealt;
	}
	else if (place == "LeftArm") {
		float ChanceToHit = m_stats.accuracy - target->m_lefthand.dodgeChance; // the chance to hit. we will round it up
		if (rand() % 100 + 1 > int(ChanceToHit + 0.5f)) return -1; // hit misses
		//calculate the hit damage
		float DamageToDeal = m_righthand.timesAttacked < m_righthand.MaxTimesAttacked ? equipedWeapon->getDamage() * m_stats.attackModifierRight : m_lefthand.timesAttacked < m_lefthand.MaxTimesAttacked ?
			equipedWeapon->getDamage() *m_stats.attackModifierLeft : 0;//if both hands are cut damage = 0;
		DamageToDeal *= 2; // double damage is dealt to the head
		//calculate the damage resistance
		float EnemyResistance = target->m_lefthand.m_LeftHandArmor->getResistance(equipedWeapon->GetDamageType());
		EnemyResistance += (equipedWeapon->GetDamageType() == "Lighting" || equipedWeapon->GetDamageType() == "Fire" || equipedWeapon->GetDamageType() == "Cold") ?
			target->m_lefthand.magicResistance : target->m_lefthand.PhysicalResistance;
		if (EnemyResistance >= 100) EnemyResistance = 0.9f; // should cap around there
		int DamageDealt = (int)(DamageToDeal*(1 - EnemyResistance));
		target->loseHp(DamageDealt);
		target->m_lefthand.timesAttacked++;
		return DamageDealt;
	}
	return 0;
}

void CharacterObject::loseHp(int HpLoss)
{
	m_stats.health -= HpLoss;
	if (m_stats.health < 0) {
		m_stats.health = 0;
		isAlive = false;
	}
}