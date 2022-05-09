#include <iostream>
#include "room.h"
#include "Exit.h"

Exit::Exit(const char* name, const char* opposite_name, const char* description, Room* origin, Room* destination) :
	Entity(name, description, (Entity*)origin), key(NULL), one_way(one_way), destination(destination), opposite_name(opposite_name) {
	type = EXIT;
	destination->container.push_back(this);
}

Exit::~Exit() {}

void Exit::Look() const {
	cout << name << " to " << opposite_name << endl;
	cout << description << endl;
}

const string& Exit::GetNameFrom(const Room* room) const {
	if (room == parent) return name;
	if (room == destination) return opposite_name;
	return name;
}

Room* Exit::GetDestinationFrom(const Room* room) const {
	if (room == parent) return destination;
	if (room == destination) return (Room*)parent;
	return NULL;
}