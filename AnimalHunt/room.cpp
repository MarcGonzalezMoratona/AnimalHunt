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
			cout << endl << "There is an item here: " << item->name << endl;
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
