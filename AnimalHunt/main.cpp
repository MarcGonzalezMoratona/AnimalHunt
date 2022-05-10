#include <iostream>
#include <string>
#include "world.h"

using namespace std;

void commandNotValid() {
	cout << "Sorry, I don't understand your command" << endl;
}

int main() {
	cout << "Welcome to Animal Hunt!" << endl << endl;
	// TODO: UPDATE COMMANDS
	cout << "Commands of the game:" << endl << endl;
	cout << "\t help - Shows the commands that you can use to play Animal Hunt" << endl;
	cout << "\t go (direction) - Move the player to the given direction" << endl;
	cout << "\t take (item) - Take an item from the room or inventory" << endl;
	cout << "\t drop (item) - Drop an item from inventory" << endl;
	cout << "\t look (place) - Look into a place to know which items or creatures are there" << endl;
	cout << "\t attack (target) - Attack an animal in order to hunt it" << endl;
	cout << "\t stats - Shows the player stats (HP, attack and Protection)" << endl;
	cout << "\t quit - Closes the game" << endl << endl;

	cout << "\t There are 8 possible directions:" << endl;
	cout << "\t north (n), south (s), east (e), west (w), north-east (ne), north-west (nw), south-east (se), south-west (sw)" << endl << endl;


	cout << "Enter your name:" << endl;
	string name;
	getline(cin, name);
	World world(name);

	cout << endl << "Dear " << name << "," << endl << endl;
	cout << "I am writing to remind you that you have an outstanding debt of 50,000 rupees on your house." << endl;
	cout << "In order to pay the debt, we strongly recommend you to use your skills as a hunter to get furs and sell them in the village store, "
		"otherwise Mr. Smith will personally take care of this matter and you will lose your house." << endl << endl;
	cout << "Best regards," << endl;
	cout << "John Williams. Bank of America." << endl << endl;

	cout << "Press Enter to continue" << endl;
	cin.ignore();
	system("CLS");
	world.SendPlaceToLook("here");
	
	string command = "";
	bool restart = false;

	while (command != "quit" && !restart) {
		cin >> command;
		cout << endl;

		if (command == "help") {
			// TODO: UPDATE COMMANDS
			cout << "Commands of the game:" << endl << endl;
			cout << "\t help - Shows the commands that you can use to play Animal Hunt" << endl;
			cout << "\t go (direction) - Move the player to the given direction" << endl;
			cout << "\t take (item) - Take an item from the room or inventory" << endl;
			cout << "\t drop (item) - Drop an item from inventory" << endl;
			cout << "\t look (place) - Look into a place to know which items or creatures are there" << endl;
			cout << "\t attack (target) - Attack an animal in order to hunt it" << endl;
			cout << "\t stats - Shows the player stats (HP, attack and Protection)" << endl;
			cout << "\t quit - Closes the game" << endl << endl;

			cout << "\t There are 8 possible directions:" << endl;
			cout << "\t north (n), south (s), east (e), west (w), north-east (ne), north-west (nw), south-east (se), south-west (sw)" << endl << endl;
		}
		else if (command == "go") {
			string direction = "";
			cin >> direction;
			if(direction == "n" || direction == "north" || 
				direction == "s" || direction == "south" || 
				direction == "w" || direction == "west" || 
				direction == "e" || direction == "east" || 
				direction == "nw" || direction == "north-west" || 
				direction == "ne" || direction == "north-east" ||
				direction == "sw" || direction == "south-west" ||
				direction == "se" || direction == "south-east") world.SendDirection(direction);
			else commandNotValid();
		}
		else if (command == "take" || command == "pick") {
			string subitem;
			cin >> subitem;
			cout << "is this item inside another item? (Yes/No)" << endl;
			string answer;
			cin >> answer;
			if (answer == "y" || answer == "yes") {
				cout << endl << "take " << subitem << " from ";
				string item;
				cin >> item;
				world.SendItemToTake(item, subitem);
			}
			else if(answer == "n" || answer == "no") world.SendItemToTake("", subitem);
			else commandNotValid();
		}
		else if (command == "stats") {
			world.ShowStats();
		}
		else if (command == "drop" || command == "put") {
			string item;
			cin >> item;
			world.SendItemToDrop(item);
		}
		else if (command == "look") {
			string placeToLook;
			cin >> placeToLook;
			world.SendPlaceToLook(placeToLook);
		}
		else if (command == "attack") {
			string target;
			cin >> target;
			world.SendTargetToAttack(target);
		}
		else if (command != "quit") commandNotValid();
		if (command != "quit") cout << endl;

		restart = !world.PlayerIsAlive();
	}

	if (restart) cout << "You are dead." << endl;
	else system("CLS");
	cout << "Thanks for playing!" << endl;

	return 0;
}