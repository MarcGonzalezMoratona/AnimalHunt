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
	else {
		cout << name << "'s corpse" << endl;
		cout << "Here lies dead: " << description << endl;
	}
}

//bool Creature::Go(const vector<string>& args) {
	//if (!IsAlive()) return false;

	//Exit* exit = GetRoom()->GetExit(args[1]);

	//if (exit == NULL)
	//	return false;

	//if (PlayerInRoom())
	//	cout << name << "goes " << args[1] << "..." << endl;

	//ChangeParentTo(exit->GetDestinationFrom((Room*)parent));

	//return true;
//}

//bool Creature::Take(const vector<string>& args)
//{
	//if (!IsAlive())
	//	return false;

	//Item* item = (Item*)parent->Find(args[1], ITEM);

	//if (args.size() > 1)
	//{
	//	// we could pick something from a container in our inventory ...
	//	if (item == NULL)
	//		item = (Item*)Find(args[1], ITEM);

	//	if (item == NULL)
	//		return false;

	//	Item* subitem = (Item*)item->Find(args[3], ITEM);

	//	if (subitem == NULL)
	//		return false;

	//	if (PlayerInRoom())
	//		cout << name << " looks into " << item->name << "...\n";

	//	item = subitem;
	//}

	//if (item == NULL)
	//	return false;

	//if (PlayerInRoom())
	//	cout << name << " takes " << item->name << ".\n";

	//item->ChangeParentTo(this);

	//return true;
//}

//void Creature::Inventory() const {
	/*list<Entity*> items;
	FindAll(ITEM, items);

	if (items.size() == 0)
	{
		cout << name << " does not own any items\n";
		return;
	}

	cout << "\n" << name << " owns:\n";
	for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
	{
		if (*it == weapon)
			cout << (*it)->name << " (as weapon)\n";
		else if (*it == armour)
			cout << (*it)->name << " (as armour)\n";
		else
			cout << (*it)->name << "\n";
	}*/
//}

//bool Creature::Equip(const vector<string>& args) {
	/*if (!IsAlive())
		return false;

	Item* item = (Item*)Find(args[1], ITEM);

	if (item == NULL)
		return false;

	switch (item->type)
	{
	case WEAPON:
		weapon = item;
		break;

	case ARMOUR:
		armour = item;
		break;

	default:
		return false;
	}

	if (PlayerInRoom())
		cout << name << " equips " << item->name << "...\n";

	return true;*/
//}

//bool Creature::UnEquip(const vector<string>& args) {
	/*if (!IsAlive())
		return false;

	Item* item = (Item*)Find(args[1], ITEM);

	if (item == NULL)
		return false;

	if (item == weapon)
		weapon = NULL;
	else if (item == weapon)
		armour = NULL;
	else
		return false;

	if (PlayerInRoom())
		cout << name << " un-equips " << item->name << "...\n";

	return true;*/
//}


//bool Creature::AutoEquip() {
	/*if (!IsAlive()) return false;

	list<Entity*> items;
	FindAll(ITEM, items);

	for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
	{
		Item* i = (Item*)(*it);

		if (i->item_type == WEAPON)
			weapon = i;
		if (i->item_type == ARMOUR)
			armour = i;
	}

	return true;*/
//}

//bool Creature::Drop(const vector<string>& args) {
	//if (!IsAlive())
	//	return false;

	//Item* item = (Item*)Find(args[1], ITEM);

	//if (item == NULL)
	//	return false;

	//if (PlayerInRoom())
	//	cout << name << " drops " << item->name << "...\n";

	//item->ChangeParentTo(parent);

	//return true;
//}

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

	if (PlayerInRoom() && result > 0) cout << name << " ("<<hit_points << " HP) attacks " << combat_target->name << " for " << result << endl;

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

//bool Creature::Loot(const vector<string>& args) {
//	Creature *target = (Creature*)parent->Find(args[1], CREATURE);
//
//	if (target == NULL && target->IsAlive() == false)
//		return false;
//
//	list<Entity*> items;
//	target->FindAll(ITEM, items);
//
//	for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it) {
//		Item* i = (Item*)(*it);
//		i->ChangeParentTo(this);
//	}
//
//	cout << endl << name << " loots " << target->name << "'s corpse" << endl;
//
//	return true;
//}

void Creature::Stats() const {
	cout << "Hit Points: " << hit_points;
	cout << endl << "Attack: (" << ((weapon) ? weapon->name : "no weapon") << ") ";
	cout << ((weapon) ? weapon->min_value : min_damage) << "-" << ((weapon) ? weapon->max_value : max_damage);
	cout << endl << "Protection: (" << ((armour) ? armour->name : "no armour") << ") ";
	cout << ((armour) ? armour->min_value : min_protection) << "-" << ((armour) ? armour->max_value : max_protection);
	cout << endl;
}