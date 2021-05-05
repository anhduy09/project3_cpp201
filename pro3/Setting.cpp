#include "Setting.h"
#include <regex>
#include<iostream>
#include<string>
#include<sstream>
Setting::Setting()
{
	general = new General();
	sound = new Sound();
	disp = new Display();
}
Setting::~Setting() {
	delete general;
	delete sound;
	delete disp;
}
void Setting::setGeneral(General* gen)
{
	general = gen;
}
General* Setting::getGeneral()
{
	return general;
}
void Setting::setDisplay(Display* displ)
{
	disp = displ;
}
Display* Setting::getDisplay()
{
	return this->disp;
}
void Setting::setSound(Sound* soun)
{
	this->sound = soun;
}
Sound* Setting::getSound()
{
	return sound;
}
void Setting::copyInfo(Setting* st)
{
	setCarName(st->getCarName());
	setPersonalKey(st->getPersonalKey());
	setODO(st->getODO());
	setEmail(st->getEmail());
	setServiceRemind(st->getServiceRemind());
}
int inputcheck(int n) {		//check if input is a positive number
	regex re_num("(\\+|-)?[0-9]+");
	string s_light_level = "";
	while (1) {
		try {
			string output = "";
			getline(cin, s_light_level);
			for (int i = 0; i < s_light_level.length(); i++) {
				if (s_light_level[i] == ' ') {
					continue;
				}
				else {
					output += s_light_level[i];
				}
			}
			if (!regex_match(output, re_num)) {
				/*cout << "Input value follow number!!!\n";
				cout << "enter again: ";*/
				throw "Input value follow number!!!";
			}
			else if (output[0] == '0') {
				//cout << "enter positive number: \n";
				throw "Possitive number please!!!";
			}
			else {
				n = stoi(output);
				if (n < 0) {
					/*cout << "Input value greater than 0!!!\n";
					cout << "enter again: ";*/
					throw "Input value greater than 0!!!";
				}
				else {
					return n;
				}
			}

		}
		catch (const char* err) {
			cout << err << endl;
			cout << "Enter again: ";
		}
	}

}

void Setting::nhapThongTin()
{
	regex re_mail("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");// Email must be in email@abc.xyz form
	regex re_personal("^[0-9]{8}$");// format 8 digits
	string s;
	while (1) {
		try {
			cout << "Enter car name: ";
			//cin >> s;
			cin.ignore();
			getline(std::cin, s);
			setCarName(s);
			if (getCarName().empty()) {		//do not let name empty
			//cout << "Input a value not null!!!\n";
				throw 1;
			}
			else {
				break;
			}
		}
		catch (...) {
			cout << "Input a value not null!!!\n";
		}

	}
	while (1) {
		try {
			cout << "Enter mail: ";	//enter email, and show caution if email does not follow pattern email@abc.xyz
			cin >> s;
			setEmail(s);
			cin.ignore(0);
			if (!regex_match(getEmail(), re_mail)) {
				//cout << "Input a value follows pattern (emai@abc.xyz)!!!\n";
				throw 1;
			}
			else {
				break;
			}
		}
		catch (...) {
			cout << "Input a value follows pattern (emai@abc.xyz)!!!\n";
		}
	}

	while (1) {
		try {
			cout << "Enter personal key: ";		//enter user key and show warnig if input does not foollow 8 digits
			cin >> s;
			setPersonalKey(s);
			if (!regex_match(getPersonalKey(), re_personal)) {
				//cout << "Input a value follows 8 digits!!!\n";
				throw 1;
			}
			else {

				break;
			}
		}
		catch (...) {
			cout << "Input a value follows 8 digits!!!\n";
		}
	}
	cin.ignore(1);
	cout << "Enter odo: ";
	setODO(inputcheck(0));
	cout << "Enter service: ";
	setServiceRemind(inputcheck(0));
}

void Setting::xuatThongTin()
{
	cout << setw(10) << getCarName() << setw(20) << getEmail() << setw(10) << getPersonalKey() << setw(10) << getODO() << setw(10) << getServiceRemind();
}

string Setting::toStringSetting() {
	stringstream stm;
	stm << "Common:" << getCarName() << "," << getEmail() << "," << getPersonalKey() << "," << getODO() << "," << getServiceRemind() << ";";
	return stm.str();
}