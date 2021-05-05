#include "General.h"
#include "CommonInfo.h"
#include <sstream>
using namespace std;
General::General()
{
	timeZone = "(GMT+07:00)";
	language = "English";
}

General::~General() {}

void General::xuatThongTin_General() {
	cout << setw(15) << get_timeZone() << setw(15) << get_language();
}

string General::get_language() {
	return this->language;
}

string General::get_timeZone() {
	return this->timeZone;
}

void General::set_timeZone(string data) {
	this->timeZone = data;
}

void General::set_language(string data) {
	this->language = data;
}

string General::toStringGeneral() {
	stringstream stm;
	stm << "General:" << get_timeZone() << "," << get_language() << ";";
	return stm.str();
}