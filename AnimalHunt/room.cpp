#include <iostream>
#include "exit.h"
#include "item.h"
#include "creature.h"
#include "room.h"

Room::Room(const char* title, const char* description) :
	Entity(title, description, NULL) {
	type = ROOM;
}

Room::~Room() {}

void Room::Look() const {
	cout << endl << name << endl;
	cout << description;

	// List exits --
	for (list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it) {
		if ((*it)->type == EXIT) {
			Exit* ex = (Exit*)*it;
			cout << endl << "Direction (" << ex->GetNameFrom(this) << ") you see " << ex->GetDestinationFrom(this)->name << endl;
		}
	}

	// List items --
	for (list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it) {
		if ((*it)->type == ITEM) {
			Item* item = (Item*)*it;
			cout << endl << "There is an item here: " << item->name;
			if (item->container.size() > 0) {
				cout << " (contains ";
				for (list<Entity*>::const_iterator it = item->container.begin(); it != item->container.cend(); ++it) {
					Item* subitem = (Item*)*it;
					cout << subitem->name;
					list<Entity*>::const_iterator it2 = item->container.cend();
					--it2;
					if (it != it2) cout << ", ";
				}
				cout << ")" << endl;
			}
			else cout << endl;
		}
	}

	// List creatures --
	for (list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it) {
		if ((*it)->type == CREATURE) {
			Creature* cr = (Creature*)*it;
			cout << endl << "There is someone else here: " << cr->name;
			if (cr->IsAlive() == false) cout << " (dead)";
			cout << endl;
		}
	}
	cout << endl;
}

Exit* Room::GetExit(const string& direction) const {
	for (list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it) {
		if ((*it)->type == EXIT) {
			Exit* ex = (Exit*)*it;
			if (ex->GetNameFrom(this) == direction) return ex;
		}
	}
	return NULL;
}
