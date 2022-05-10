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
	}
	else {
		Item* item = (Item*)parent->Find(subitemName, ITEM);

		if (item == NULL) {
			cout << endl << "There is no item here with that name." << endl;
			return false;
		}

		cout << endl << "You take " << item->name << "." << endl;
		item->ChangeParentTo(this);
	}

	return false;
}

//void Player::Inventory() const {
//	list<Entity*> items;
//	FindAll(ITEM, items);
//
//	if (items.size() == 0)
//	{
//		cout << endl <<"You do not own any item." << endl;
//		return;
//	}
//
//	for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
//	{
//		if (*it == weapon)
//			cout << endl << (*it)->name << " (as weapon)";
//		else if (*it == armour)
//			cout << endl << (*it)->name << " (as armour)";
//		else
//			cout << endl << (*it)->name;
//	}
//	cout << "\n";
//}

//bool Player::Drop(const vector<string>& args) {
//	if (args.size() == 2) {
//		Item* item = (Item*)Find(args[1], ITEM);
//
//		if (item == NULL) {
//			cout << endl << "There is no item on you with that name." << endl;
//			return false;
//		}
//
//		cout << endl << "You drop " << item->name << "..." << endl;
//		item->ChangeParentTo(parent);
//
//		return true;
//	}
//	else if (args.size() == 4) {
//		Item* item = (Item*)Find(args[1], ITEM);
//
//		if (item == NULL) {
//			cout << endl << "Cannot find '" << args[1] << "' in your inventory." << endl;
//			return false;
//		}
//
//		Item* container = (Item*)parent->Find(args[3], ITEM);
//
//		if (container == NULL) {
//		container = (Item*)Find(args[3], ITEM);
//			cout << endl <<"Cannot find '" << args[3] << "' in your inventory or in the room." << endl;
//			return false;
//		}
//
//		cout << endl << "You put " << item->name << " into " << container->name << "." << endl;
//		item->ChangeParentTo(container);
//
//		return true;
//	}
//	return false;
//}

//bool Player::Equip(const vector<string>& args) {
//	Item* item = (Item*)Find(args[1], ITEM);
//
//	if (item == NULL) {
//		cout << endl << "Cannot find '" << args[1] << "' is not in your inventory." << endl;
//		return false;
//	}
//
//	switch (item->item_type) {
//	case WEAPON:
//		weapon = item;
//		break;
//
//	case ARMOUR:
//		armour = item;
//		break;
//
//	default:
//		cout << endl << item->name << " cannot be equipped." << endl;
//		return false;
//	}
//
//	cout << endl << "You equip " << item->name << "..." << endl;
//	return true;
//}

//bool Player::UnEquip(const vector<string>& args) {
//	if (!IsAlive()) return false;
//
//	Item* item = (Item*)Find(args[1], ITEM);
//
//	if (item == NULL) {
//		cout << endl << item->name << " is not in your inventory." << endl;
//		return false;
//	}
//
//	if (item == weapon) weapon = NULL;
//	else if (item == armour) armour = NULL;
//	else {
//		cout << endl << item->name << " is not equipped." << endl;
//		return false;
//	}
//	cout  << endl << "You unequip " << item->name << "..." << endl;
//	return true;
//}

//bool Player::Examine(const vector<string>& args) const {
//	Creature *target = (Creature*)parent->Find(args[1], CREATURE);
//
//	if (target == NULL) {
//		cout << endl << args[1] << " is not here." << endl;
//		return false;
//	}
//
//	target->Inventory();
//	target->Stats();
//
//	return true;
//}

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

//bool Player::Loot(const vector<string>& args) {
//	Creature *target = (Creature*)parent->Find(args[1], CREATURE);
//
//	if (target == NULL) {
//		cout  << endl << args[1] << " is not here." << endl;
//		return false;
//	}
//
//	if (target->IsAlive() == true) {
//		cout << endl << target->name << " cannot be looted until it is killed." << endl;
//		return false;
//	}
//
//	list<Entity*> items;
//	target->FindAll(ITEM, items);
//
//	if (items.size() > 0) {
//		cout  << endl<< "You loot " << target->name << "'s corpse:" << endl;
//
//		for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
//		{
//			Item* i = (Item*)(*it);
//			cout << "You find: " << i->name << "\n";
//			i->ChangeParentTo(this);
//		}
//	}
//	else cout  << endl << "You loot " << target->name << "'s corpse, but find nothing there." << endl;
//	return true;
//}
