#pragma once
#ifndef GENERAL_H_
#define GENERAL_H_
#include <vector>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;
class General {
public:
	General();
	~General();
	void xuatThongTin_General();
	string get_language();
	string get_timeZone();
	void set_timeZone(string data);
	void set_language(string data);
	string toStringGeneral();
private:
	string timeZone;
	string language;
};
#endif // !GENERAL_H_


