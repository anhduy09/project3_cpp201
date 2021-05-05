#pragma once
#ifndef SETTING_H_
#define SETTING_H_
#include <iostream>
#include <iomanip>
#include "Car.h"
#include "Display.h"
#include "General.h"
#include "Sound.h"
using namespace std;
class Setting : public Car {
public:
	Setting();
	~Setting();
	void nhapThongTin();
	void xuatThongTin();
	void setGeneral(General* gen);
	General* getGeneral();
	void setDisplay(Display* displ);
	Display* getDisplay();
	void setSound(Sound* soun);
	Sound* getSound();
	void copyInfo(Setting* s);
	string toStringSetting();
private:
	General* general;
	Sound* sound;
	Display* disp;

};
#endif /* SETTING_H_ */
#pragma once
