#include <iostream>
#include "room.h"
#include "exit.h"
#include "item.h"

Item::Item(const char* title, const char* description, Entity* parent, ItemType item_type) : Entity(title, description, parent), item_type(item_type) {
	type = ITEM;
	min_value = max_value = 0;
}

Item::~Item() {}

void Item::Look() const{
	cout << endl << name << endl;
	cout << description << endl;

	list<Entity*> stuff;
	FindAll(ITEM, stuff);

	if (stuff.size() > 0) {
		cout << "It contains: " << endl;
		for (list<Entity*>::const_iterator it = stuff.begin(); it != stuff.cend(); ++it)
			cout << (*it)->name << endl;
	}
}

int Item::GetValue() const {
	return rand() % max_value + min_value;
}