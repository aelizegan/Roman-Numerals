//Roman Numerals
//main.cpp
//Program to convert modern numbers to roman numerals and vice versa

//Abigail Egan
//6 March 2020

#include <iostream>
#include <string>

using std::endl;
using std::cout;
using std::cin;
using std::string;

const string NUMERALS = "MDCLXVI";

int numeralValue(char numeral) { //Returns value of single roman numeral
	if (numeral == 'I') return 1;
	else if (numeral == 'V') return 5;
	else if (numeral == 'X') return 10;
	else if (numeral == 'L') return 50;
	else if (numeral == 'C') return 100;
	else if (numeral == 'D') return 500;
	else if (numeral == 'M') return 1000;
	else throw "ERROR: Erroneous characters";
}

int toModernNumber(string numeral) { //Converts to modern numbers from roman numerals
	int number = 0;
	if (numeral.size() == 1) return numeralValue(numeral.at(0));
	for (unsigned int i = 0; i < numeral.size(); ++i) {
		if (i == numeral.size() - 1 || NUMERALS.find(numeral.at(i)) <= NUMERALS.find(numeral.at(i + 1))) { //Subtractive notation not used
			number += numeralValue(numeral.at(i));
		}
		else { //Subtractive notation used
			number += numeralValue(numeral.at(i + 1)) - numeralValue(numeral.at(i));
			++i;
		}
	}
	return number;
}

string greaterNumerals(int placeValue) { //Returns the larger roman numeral for the corresponding place value
	if (placeValue == 1) return "V";
	else if (placeValue == 2) return "L";
	else if (placeValue == 3) return "D";
	else throw "ERROR: Invalid place value";
}

string lowerNumerals(int placeValue) {//Returns the smaller roman numeral for the corresponding place value
	if (placeValue == 0) return "ERROR";
	else if (placeValue == 1) return "I";
	else if (placeValue == 2) return "X";
	else if (placeValue == 3) return "C";
	else if (placeValue >= 4) return "M";
	else throw "ERROR: Invalid place value";
}

int numeralPlaceValue(char numeral) {//Returns place value of roman numeral
	if (numeral == 'I') return 1;
	else if (numeral == 'V') return 1;
	else if (numeral == 'X') return 2;
	else if (numeral == 'L') return 2;
	else if (numeral == 'C') return 3;
	else if (numeral == 'D') return 3;
	else if (numeral == 'M') return 4;
	else throw "ERROR: Invalid roman numeral";
}

string valueAsNumeral(string number, int placeValue) {
	string numeral;
	int value = stoi(number);
	if (value == 4 && placeValue < 4) { //Subtractive notation is needed
		numeral.append(lowerNumerals(placeValue));
		numeral.append(greaterNumerals(placeValue));
	}
	else if (value == 9 && placeValue < 4) { //Subtractive notation is needed
		numeral.append(lowerNumerals(placeValue));
		numeral.append(lowerNumerals(placeValue + 1));
	}
	else {
		for (int i = 0; i < value; ++i) {
			if (value >= 5 && placeValue < 4) {
				value -= 4;
				numeral.append(greaterNumerals(placeValue));
			}
			else {
				numeral.append(lowerNumerals(placeValue));
			}
		}
	}
	return numeral;
}

string toRomanNumeral(string number) { //Convert modern numbers to roman numerals
	string numeral;
	for (unsigned int i = 0; i < number.size(); ++i) {
		try {
			int placeValue = number.size() - i;
			numeral.append(valueAsNumeral(number.substr(i, 1), placeValue));
		}
		catch (...) {
			return "Not a number.";
		}
	}
	return numeral;
}

bool validRomanNumeral(string numeral) { //Assure that roman numeral is valid
	for (unsigned int i = 0; i < numeral.size(); ++i) {
		if (NUMERALS.find(numeral.at(i)) < 5 && i != 0) {
			if (numeralPlaceValue(numeral.at(i)) - numeralPlaceValue(numeral.at(i - 1)) > 1) return 0;
		}
	}
	return 1;
}

int main() {
	//Present menu of options
	cout << "ROMAN NUMERAL CONVERTER" << endl;
	cout << "Select an option:" << endl;
	cout << "Exit - exit the program." << endl;
	cout << "1 - Convert roman numerals to modern numbers." << endl;
	cout << "2 - Convert modern numbers to roman numerals." << endl;

	//Read selection and execute option
	string option;
	cin >> option;
	while (option != "Exit") {
		if (option == "1") { //Convert numeral to number
			cout << "Enter 'Menu' at any time to present the menu again." << endl;
			string numeral;
			while (numeral != "Menu") {
				try {
					cout << "Please enter roman numeral:" << endl;
					cin >> numeral;
					if (numeral != "Menu") {
						if (!validRomanNumeral(numeral)) throw "Invalid roman numeral.";
						cout << numeral << " = " << toModernNumber(numeral) << endl;
					}
				}
				catch (const char* error) {
					cout << error << endl;
				}
			}

			//Present menu again
			cout << endl << "Select an option:" << endl;
			cout << "Exit - exit the program." << endl;
			cout << "1 - Convert roman numerals to modern numbers." << endl;
			cout << "2 - Convert modern numbers to roman numerals." << endl;
			cin >> option;
		}
		else if (option == "2") { //Convert number to numeral';
			cout << "Enter 'Menu' at any time to present the menu again." << endl;
			string number;
			while (number != "Menu") {
				try {
					cout << "Please enter number:" << endl;
					cin >> number;
					if (number != "Menu") cout << number << " = " << toRomanNumeral(number) << endl;
				}
				catch (const char* error) {
					cout << error << endl;
				}
			}

			//Present menu again
			cout << endl << "Select an option:" << endl;
			cout << "Exit - exit the program." << endl;
			cout << "1 - Convert roman numerals to modern numbers." << endl;
			cout << "2 - Convert modern numbers to roman numerals." << endl;
			cin >> option;
		}
		else { //Input not understood
			cout << "Incorrect option. Please try again." << endl;
			cout << endl << "Select an option:" << endl;
			cout << "Exit - exit the program." << endl;
			cout << "1 - Convert roman numerals to modern numbers." << endl;
			cout << "2 - Convert modern numbers to roman numerals." << endl;
			cin >> option;
		}
	}
}