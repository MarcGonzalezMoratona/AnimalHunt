#include <iostream>
#include "room.h"
#include "exit.h"
#include "item.h"
#include "player.h"

Player::Player(const char* title, const char* description, Room* room) :
	Creature(title, description, room)
{
	type = PLAYER;
}

Player::~Player()
{
}

//void Player::Look(const vector<string>& args) const {
//	if (args.size() > 1)
//	{
//		for (list<Entity*>::const_iterator it = parent->container.begin(); it != parent->container.cend(); ++it)
//		{
//			if (Same((*it)->name, args[1]) || ((*it)->type == EXIT && Same(args[1], ((Exit*)(*it))->GetNameFrom((Room*)parent))))
//			{
//				(*it)->Look();
//				return;
//			}
//		}
//
//		if (Same(args[1], "me"))
//		{
//			cout << "\n" << name << "\n";
//			cout << description << "\n";
//		}
//	}
//	else
//	{
//		parent->Look();
//	}
//}

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


//bool Player::Take(const vector<string>& args) {
//	if (args.size() == 4)
//	{
//		Item* item = (Item*)parent->Find(args[3], ITEM);
//
//		// we could pick something from a container in our inventory ...
//		if (item == NULL)
//			item = (Item*)Find(args[3], ITEM);
//
//		if (item == NULL)
//		{
//			cout << endl << "Cannot find '" << args[3] << "' in this room or in your inventory.\n";
//			return false;
//		}
//
//		Item* subitem = (Item*)item->Find(args[1], ITEM);
//
//		if (subitem == NULL)
//		{
//			cout << endl << item->name << " does not contain '" << args[1] << "'." << endl;
//			return false;
//		}
//
//		cout << endl << "You take " << subitem->name << " from " << item->name << "." << endl;
//		subitem->ChangeParentTo(this);
//	}
//	else if (args.size() == 2)
//	{
//		Item* item = (Item*)parent->Find(args[1], ITEM);
//
//		if (item == NULL)
//		{
//			cout << endl << "There is no item here with that name." << endl;
//			return false;
//		}
//
//		cout << endl << "You take " << item->name << "." << endl;
//		item->ChangeParentTo(this);
//	}
//
//	return false;
//}

//void Player::Inventory() const
//{
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
//
//	cout << "\n";
//}

//bool Player::Drop(const vector<string>& args) {
//	if (args.size() == 2)
//	{
//		Item* item = (Item*)Find(args[1], ITEM);
//
//		if (item == NULL)
//		{
//			cout << endl << "There is no item on you with that name." << endl;
//			return false;
//		}
//
//		cout << endl << "You drop " << item->name << "..." << endl;
//		item->ChangeParentTo(parent);
//
//		return true;
//	}
//	else if (args.size() == 4)
//	{
//		Item* item = (Item*)Find(args[1], ITEM);
//
//		if (item == NULL)
//		{
//			cout << endl << "Can not find '" << args[1] << "' in your inventory." << endl;
//			return false;
//		}
//
//		Item* container = (Item*)parent->Find(args[3], ITEM);
//
//		if (container == NULL)
//		{
//			container = (Item*)Find(args[3], ITEM);
//			cout << endl <<"Can not find '" << args[3] << "' in your inventory or in the room." << endl;
//			return false;
//		}
//
//		cout << endl << "You put " << item->name << " into " << container->name << "." << endl;
//		item->ChangeParentTo(container);
//
//		return true;
//	}
//
//	return false;
//}

//bool Player::Equip(const vector<string>& args) {
//	Item* item = (Item*)Find(args[1], ITEM);
//
//	if (item == NULL)
//	{
//		cout << endl << "Cannot find '" << args[1] << "' is not in your inventory." << endl;
//		return false;
//	}
//
//	switch (item->item_type)
//	{
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
//
//	return true;
//}

//bool Player::UnEquip(const vector<string>& args) {
//	if (!IsAlive())
//		return false;
//
//	Item* item = (Item*)Find(args[1], ITEM);
//
//	if (item == NULL)
//	{
//		cout << endl << item->name << " is not in your inventory." << endl;
//		return false;
//	}
//
//	if (item == weapon)
//		weapon = NULL;
//	else if (item == armour)
//		armour = NULL;
//	else
//	{
//		cout << endl << item->name << " is not equipped." << endl;
//		return false;
//	}
//
//	cout  << endl << "You unequip " << item->name << "..." << endl;
//
//	return true;
//}

//bool Player::Examine(const vector<string>& args) const {
//	Creature *target = (Creature*)parent->Find(args[1], CREATURE);
//
//	if (target == NULL)
//	{
//		cout << endl << args[1] << " is not here." << endl;
//		return false;
//	}
//
//	target->Inventory();
//	target->Stats();
//
//	return true;
//}

//bool Player::Attack(const vector<string>& args) {
//	Creature *target = (Creature*)parent->Find(args[1], CREATURE);
//
//	if (target == NULL)
//	{
//		cout  << endl << args[1] << " is not here.";
//		return false;
//	}
//
//	combat_target = target;
//	cout  << endl << "You attack " << target->name << "!" << endl;
//	return true;
//}

//bool Player::Loot(const vector<string>& args) {
//	Creature *target = (Creature*)parent->Find(args[1], CREATURE);
//
//	if (target == NULL)
//	{
//		cout  << endl << args[1] << " is not here." << endl;
//		return false;
//	}
//
//	if (target->IsAlive() == true)
//	{
//		cout << endl << target->name << " cannot be looted until it is killed." << endl;
//		return false;
//	}
//
//	list<Entity*> items;
//	target->FindAll(ITEM, items);
//
//	if (items.size() > 0)
//	{
//		cout  << endl<< "You loot " << target->name << "'s corpse:" << endl;
//
//		for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
//		{
//			Item* i = (Item*)(*it);
//			cout << "You find: " << i->name << "\n";
//			i->ChangeParentTo(this);
//		}
//	}
//	else
//		cout  << endl<< "You loot " << target->name << "'s corpse, but find nothing there." << endl;
//
//	return true;
//}
