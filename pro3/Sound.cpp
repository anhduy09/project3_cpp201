#include "Sound.h"
#include <regex>
#include<sstream>
Sound::Sound() {
	media_level = 0;
	call_level = 0;
	navi_level = 0;
	notification_level = 0;
}

Sound::~Sound() {}

int checkNum(int n) {
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
				throw "Input value follow number!!!";
			}
			else if (output[0] == '0') {
				throw "Possitive number please!!!";
			}
			else {
				n = stoi(output);
				if (n < 0) {
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

void Sound::nhapThongTin_Sound() {

	cout << "Enter media_level: ";
	set_media_level(checkNum(0));//su dung ham set
	cout << "Enter call_level: ";
	set_call_level(checkNum(0));
	cout << "Enter navi_level: ";
	set_navi_level(checkNum(0));
	cout << "Enter notification_level: ";
	set_notification_level(checkNum(0));
}

void Sound::xuatThongTin_Sound() {
	cout << setw(10) << get_media_level() << setw(10) << get_call_level() << setw(10) << get_navi_level() << setw(10) << get_notification_level();
}

string Sound::toStringSound() {
	stringstream stm;
	stm << "Sound:" << get_media_level() << "," << get_call_level() << "," << get_navi_level() << "," << get_notification_level() << ";";
	return stm.str();
}

int Sound::get_media_level() {
	return this->media_level;
}

int Sound::get_call_level() {
	return this->call_level;

}

int Sound::get_navi_level() {
	return this->navi_level;
}

int Sound::get_notification_level() {
	return this->notification_level;
}

void Sound::set_media_level(int data) {
	this->media_level = data;
}

void Sound::set_call_level(int data) {
	this->call_level = data;
}

void Sound::set_navi_level(int data) {
	this->navi_level = data;
}

void Sound::set_notification_level(int data) {
	this->notification_level = data;
}
