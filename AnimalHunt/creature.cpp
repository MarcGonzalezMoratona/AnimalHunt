#include <iostream>
#include "room.h"
#include "exit.h"
#include "item.h"
#include "creature.h"

Creature::Creature(const string name, const char* description, Room* room) : Entity(name, description, (Entity*)room) {
	type = CREATURE;
	hit_points = 1;
	min_damage = max_damage = min_protection = max_protection = 0;
	weapon = armour = NULL;
	combat_target = NULL;
}

Creature::~Creature(){}

void Creature::Look(const vector<string>& args) const {
	if (IsAlive()) {
		cout << name << endl;
		cout << description << endl;
	}
	else cout << name << "'s corpse" << endl;
}

void Creature::Inventory() const {
	list<Entity*> items;
	FindAll(ITEM, items);

	if (items.size() == 0) {
		cout << name << " does not own any items" << endl;
		return;
	}

	cout << endl << name << " owns:" << endl;
	for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it) {
		cout << "- ";
		if (*it == weapon) cout << (*it)->name << " (as weapon)" << endl;
		else if (*it == armour)	cout << (*it)->name << " (as armour)" << endl;
		else cout << (*it)->name << endl;
		cout << endl;
	}
}

bool Creature::AutoEquip() {
	if (!IsAlive()) return false;
	list<Entity*> items;
	FindAll(ITEM, items);

	for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it) {
		Item* i = (Item*)(*it);
		if (i->item_type == WEAPON) weapon = i;
		if (i->item_type == ARMOUR) armour = i;
	}
	return true;
}

Room* Creature::GetRoom() const {
	return (Room*)parent;
}

bool Creature::PlayerInRoom() const {
	return parent->Find(PLAYER) != NULL;
}

bool Creature::IsAlive() const {
	return hit_points > 0;
}

bool Creature::Attack(const string targetName) {
	Creature *target = (Creature*)parent->Find(targetName, CREATURE);

	if (target == NULL) return false;
	combat_target = target;
	cout << endl << name << " attacks " << target->name << "!" << endl;
	return true;
}

void Creature::Attack() {
	MakeAttack();
}

int Creature::MakeAttack() {
	if (!IsAlive() || !combat_target->IsAlive()) {
		combat_target = combat_target->combat_target = NULL;
		return false;
	}

	int result = (weapon) ? rand() % 10 + weapon->GetValue() : rand() % 5;

	if (PlayerInRoom() && result > 0) cout << name << " (" << hit_points << " HP) attacks " << combat_target->name << " for " << result << endl;

	combat_target->ReceiveAttack(result);

	if (combat_target->combat_target == NULL) combat_target->combat_target = this;
	combat_target->Attack();

	return result;
}

int Creature::ReceiveAttack(int damage) {
	int prot = (armour) ? rand() % 4 + armour->GetValue() : rand() % 2;
	int received = damage - prot;

	hit_points -= received;

	if (PlayerInRoom()) {
		if (damage == 0) cout << combat_target->name << "'s attack failed!" << endl;
		else if(received > 0) cout << name << " is hit for " << received << " damage (" << prot << " blocked)" << endl;
		else cout << name << " blocked the attack!" << endl;
	}
	if (!IsAlive()) Die();
	return received;
}

void Creature::Die() {
	if (PlayerInRoom())	cout << name << " dies." << endl;
}

void Creature::Stats() const {
	cout << "Hit Points: " << hit_points;
	cout << endl << "Attack: (" << ((weapon) ? weapon->name : "no weapon") << ") ";
	cout << ((weapon) ? weapon->min_value : min_damage) << "-" << ((weapon) ? weapon->max_value : max_damage);
	cout << endl << "Protection: (" << ((armour) ? armour->name : "no armour") << ") ";
	cout << ((armour) ? armour->min_value : min_protection) << "-" << ((armour) ? armour->max_value : max_protection);
	cout << endl;
}