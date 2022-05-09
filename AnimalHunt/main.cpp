#include <iostream>
#include <string>
#include "world.h"

using namespace std;

int main() {
	World world;

	cout << "Welcome to Animal Hunt!" << endl << endl;
	cout << "Commands of the game:" << endl << endl;
	cout << "\t help - Shows the commands that you can use to play Animal Hunt" << endl;
	cout << "\t go (direction) - Move the player to the given direction" << endl;
	cout << "\t quit - Closes the game" << endl << endl;
	cout << "\t There are 8 possible directions:" << endl;
	cout << "\t north (n), south (s), east (e), west (w), north-east (ne), north-west (nw), south-east (se), south-west (sw)" << endl << endl;


	cout << "Enter your name:" << endl;
	string name;
	cin >> name;

	cout << endl << "Dear " << name << "," << endl << endl;
	cout << "I am writing to remind you that you have an outstanding debt of 50,000 rupees on your house." << endl;
	cout << "In order to pay the debt, we strongly recommend you to use your skills as a hunter to get furs and sell them in the village store, "
		"otherwise Mr. Smith will personally take care of this matter and you will lose your house." << endl << endl;
	cout << "Best regards," << endl;
	cout << "John Williams. Bank of America." << endl << endl;

	
	string command = "";

	while (command != "quit") {
		cin >> command;
		cout << endl;

		if (command == "help") {
			cout << "Commands of the game:" << endl << endl;
			cout << "\t help - Shows the commands that you can use to play Animal Hunt" << endl;
			cout << "\t go (direction) - Move the player to the given direction" << endl;
			cout << "\t quit - Closes the game" << endl << endl;

			cout << "\t There are 8 possible directions:" << endl;
			cout << "\t north (n), south (s), east (e), west (w), north-east (ne), north-west (nw), south-east (se), south-west (sw)" << endl << endl;
		}
		else if (command == "a a") cout << "entiendo" << endl;
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
				direction == "se" || direction == "south-east") world.sendDirection(direction);
			else cout << "Sorry, I don't understand your command" << endl;
		}
		else if (command != "quit") cout << "Sorry, I don't understand your command" << endl;

		if (command != "quit") cout << endl;
	}

	cout << "Thanks for playing!" << endl;
	return 0;
}