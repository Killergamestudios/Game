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
}

void CharacterObject::Draw()
{
	m_sprite.setPosition(m_position);
	m_window->draw(m_sprite);
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
	
	m_stats.MaxHealth += MaxHealthGain;
	m_stats.MaxEnergy += m_stats.level % 5 == 0 ? MaxEnergyGain:0;
	
	m_stats.attackModifierLeft += AttackModifierGain;
	m_stats.attackModifierRight += AttackModifierGain;
	m_stats.accuracy += accuracyGain;

	m_head.magicResistance += MagicResistanceGain * 0.75f;
	m_head.PhysicalResistance += PhysicalResistanceGain * 0.75f;
	m_head.dodgeChance += DodgechanceGain;

	m_body.magicResistance += MagicResistanceGain;
	m_body.PhysicalResistance += PhysicalResistanceGain;
	m_body.dodgeChance += DodgechanceGain ;

	m_legs.magicResistance += MagicResistanceGain * 0.70f;
	m_legs.PhysicalResistance += PhysicalResistanceGain * 0.70f;
	m_legs.dodgeChance += DodgechanceGain;

	m_righthand.magicResistance += MagicResistanceGain * 0.70f;
	m_righthand.PhysicalResistance += PhysicalResistanceGain * 0.70f;
	m_righthand.dodgeChance += DodgechanceGain;

	m_lefthand.magicResistance += MagicResistanceGain * 0.70f;
	m_lefthand.PhysicalResistance += PhysicalResistanceGain * 0.70f;
	m_lefthand.dodgeChance += DodgechanceGain;


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

int CharacterObject::Attack(CharacterObject * target, String place)
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
		if (EnemyResistance >= 100) EnemyResistance = 0.9f; // should cap around there
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
}

void CharacterObject::loseHp(int HpLoss)
{
	m_stats.health -= HpLoss;
	if (m_stats.health < 0) {
		m_stats.health = 0;
		isAlive = false;
	}
}






