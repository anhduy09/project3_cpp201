#pragma once
#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <iostream>
#include <string>
using namespace std;
class Display {

public:
	Display();
	~Display();
	void nhapThongTin_Display();
	void xuatThongTin_Display();
	int get_light_level();
	int get_screen_light_level();
	int get_taplo_light_level();
	void set_light_level(int data);
	void set_screen_light_level(int data);
	void set_taplo_light_level(int data);
	string toStringDisplay();
private:
	int light_level;
	int screen_light_level;
	int taplo_light_level;
};

#endif /* DISPLAY_H_ */
//#pragma once
