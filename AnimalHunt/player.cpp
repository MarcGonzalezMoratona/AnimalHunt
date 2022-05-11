#include <iostream>
#include "room.h"
#include "exit.h"
#include "item.h"
#include "player.h"

Player::Player(const string name, const char* description, Room* room) : Creature(name, description, room) {
	type = PLAYER;
}

Player::~Player() {}

void Player::Look(const string placeToLook) const {
	if (placeToLook == "here") parent->Look();
	else if (placeToLook == "me") {
		cout << endl << name << endl;
		cout << description << endl << endl;
	}
	else {
		for (list<Entity*>::const_iterator it = parent->container.begin(); it != parent->container.cend(); ++it) {
			if ((*it)->name == placeToLook || ((*it)->type == EXIT && placeToLook == ((Exit*)(*it))->GetNameFrom((Room*)parent))) {
				(*it)->Look();
				return;
			}
		}
		cout << "Sorry, I don't see what you are looking for" << endl;
	}
}

void Player::RecoverHP(){
	if (parent->name == "Fountain") {
		for (int i = hit_points; i < 25; ++i) {
			hit_points = i+1;
			cout << "The water from the magic fountain is healing your wounds... (" << hit_points << " HP)" << endl;
		}
	}
	else cout << "You can not swim here" << endl;
}

bool Player::PayDebt() {
	if (parent->name == "Bank") {
		Item* fur = (Item*)Find("fur", ITEM);
		Item* skin = (Item*)Find("skin", ITEM);
		Item* feathers = (Item*)Find("feathers", ITEM);
		if (fur != NULL && skin != NULL && feathers != NULL) return true;
		cout << "You do not have all the items to pay the debt" << endl;
		return false;
	}
	else cout << "This is not a bank" << endl;
	return false;
}


bool Player::Go(string direction) {
	Exit* exit = GetRoom()->GetExit(direction);

	if (exit == NULL) {
		cout << endl << "There is no exit at '" << direction << "'."<< endl;
		return false;
	}

	cout << endl << "You take direction " << exit->GetNameFrom((Room*)parent) << "..." << endl;
	ChangeParentTo(exit->GetDestinationFrom((Room*)parent));
	parent->Look();

	return true;
}

bool Player::Take(string itemName, string subitemName) {
	if (itemName != "") {
		Item* item = (Item*)parent->Find(itemName, ITEM);

		// we could pick something from a container in our inventory ...
		if (item == NULL) item = (Item*)Find(itemName, ITEM);

		if (item == NULL) {
			cout << endl << "Cannot find '" << itemName << "' in this room or in your inventory." << endl;
			return false;
		}

		Item* subitem = (Item*)item->Find(subitemName, ITEM);

		if (subitem == NULL) {
			cout << endl << item->name << " does not contain '" << subitemName << "'." << endl;
			return false;
		}

		cout << endl << "You take " << subitem->name << " from " << item->name << "." << endl;
		subitem->ChangeParentTo(this);
		return true;
	}
	else {
		Item* item = (Item*)parent->Find(subitemName, ITEM);
		if (item == NULL) return false;
		cout << endl << "You take " << item->name << "." << endl;
		item->ChangeParentTo(this);
		return true;
	}
	return false;
}

void Player::Inventory() const {
	list<Entity*> items;
	FindAll(ITEM, items);

	if (items.size() == 0) {
		cout << endl <<"You do not own any item." << endl;
		return;
	}

	for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it) {
		if (*it == weapon) cout << endl << (*it)->name << " (as weapon)";
		else if (*it == armour) cout << endl << (*it)->name << " (as armour)";
		else cout << endl << (*it)->name;
	}
	cout << endl;
}

bool Player::Drop(const string itemName, const string subitemName) {
	if (itemName == "") {
		Item* item = (Item*)Find(subitemName, ITEM);
		// we could pick something from a container in our inventory ...
		if (item == NULL) item = (Item*)Find(subitemName, ITEM);
		if (item == NULL) return false;
		Unequip(item->name);
		cout << endl << "You drop " << item->name << "..." << endl;
		item->ChangeParentTo(parent);
		return true;
	}
	else {
		Item* item = (Item*)Find(subitemName, ITEM);
		if (item == NULL) return false;
		Item* container = (Item*)parent->Find(itemName, ITEM);

		if (container == NULL) {
			container = (Item*)Find(subitemName, ITEM);
			cout << endl <<"Cannot find '" << subitemName << "' in your inventory or in the room." << endl;
			return false;
		}

		cout << endl << "You put " << item->name << " into " << container->name << "." << endl;
		item->ChangeParentTo(container);
		return true;
	}
	return false;
}

bool Player::Equip(const string itemName) {
	Item* item = (Item*)Find(itemName, ITEM);

	if (item == NULL) {
		cout << endl << "Cannot find '" << itemName << "' is not in your inventory." << endl;
		return false;
	}

	switch (item->item_type) {
	case WEAPON:
		weapon = item;
		break;

	case ARMOUR:
		armour = item;
		break;

	default:
		cout << endl << item->name << " cannot be equipped." << endl;
		return false;
	}

	cout << endl << "You equip " << item->name << "..." << endl;
	return true;
}

bool Player::Unequip(const string itemName) {
	if (!IsAlive()) return false;

	Item* item = (Item*)Find(itemName, ITEM);

	if (item == NULL) {
		cout << endl << item->name << " is not in your inventory." << endl;
		return false;
	}

	if (item == weapon) weapon = NULL;
	else if (item == armour) armour = NULL;
	else {
		cout << endl << item->name << " is not equipped." << endl;
		return false;
	}
	cout  << endl << "You unequip " << item->name << "..." << endl;
	return true;
}

bool Player::Examine(const string targetName) const {
	Creature *target = (Creature*)parent->Find(targetName, CREATURE);

	if (target == NULL) {
		cout << endl << targetName << " is not here." << endl;
		return false;
	}

	target->Inventory();
	target->Stats();
	return true;
}

bool Player::Attack(const string targetName) {
	Creature *target = (Creature*)parent->Find(targetName, CREATURE);

	if (target == NULL) {
		cout  << endl << targetName << " is not here.";
		return false;
	}

	combat_target = target;

	if (combat_target != NULL) {
		if (parent->Find(combat_target) == true) MakeAttack();
		else combat_target = NULL;
	}
	return true;
}

bool Player::Loot(const string targetName) {
	Creature *target = (Creature*)parent->Find(targetName, CREATURE);

	if (target == NULL) {
		cout  << endl << targetName << " is not here." << endl;
		return false;
	}

	if (target->IsAlive() == true) {
		cout << endl << target->name << " cannot be looted until it is killed." << endl;
		return false;
	}

	list<Entity*> items;
	target->FindAll(ITEM, items);

	if (items.size() > 0) {
		cout  << endl<< "You loot " << target->name << "'s corpse:" << endl;

		for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it) {
			Item* i = (Item*)(*it);
			cout << "You find: " << i->name << endl;
			i->ChangeParentTo(this);
		}
	}
	else cout  << endl << "You loot " << target->name << "'s corpse, but find nothing there." << endl;
	return true;
}
