#include "Display.h"
#include <regex>
#include <iomanip>
#include<sstream>
Display::Display()
{
	light_level = 0;
	screen_light_level = 0;
	taplo_light_level = 0;
}

Display::~Display() {}

int Display::get_light_level() {
	return this->light_level;
}

int Display::get_screen_light_level() {
	return this->screen_light_level;
}

int Display::get_taplo_light_level() {
	return this->taplo_light_level;
}
void Display::set_light_level(int data) {
	this->light_level = data;
}

void Display::set_screen_light_level(int data) {
	this->screen_light_level = data;
}

void Display::set_taplo_light_level(int data) {
	this->taplo_light_level = data;
}

int checkNum2() {	//chek if input is a positive number
	regex Sound_level("[0-9]+");
	string s = "";
	bool valid = true;
	do {
		getline(cin, s);
		if (!regex_match(s, Sound_level)) {
			cout << "Input value follow number!!!\n";
			cout << "enter again: ";
			valid = false;
		}
		else if (s[0] == '0') {
			cout << "enter positive number: \n";
			valid = false;
		}
		else
		{
			valid = true;
		}

	} while (!valid);
	return stoi(s);
}

void Display::nhapThongTin_Display() {
	cout << "Enter light level: ";
	set_light_level(checkNum2());
	cout << "Enter screen light level: ";
	set_screen_light_level(checkNum2());
	cout << "Enter taplo light level: ";
	set_taplo_light_level(checkNum2());
}

void Display::xuatThongTin_Display() {
	cout << setw(10) << get_light_level() << setw(10) << get_screen_light_level() << setw(10) << get_taplo_light_level();
}

string Display::toStringDisplay() {
	stringstream stm;
	stm << "Display:" << get_light_level() << "," << get_screen_light_level() << "," << get_taplo_light_level();
	return stm.str();
}
