#pragma once
#ifndef Car_H_
#define Car_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <regex>
using namespace std;

class Car {
	string car_name;
	string personal_key; 	// Chuoi 8 ky tu so
	string email;			// email format abc@xyz.com
	int odo;
	int service_remind;
public:
	Car();
	~Car();
	virtual void nhapThongTin();
	virtual void xuatThongTin();
	string getCarName();
	string getPersonalKey();
	int getODO();
	string getEmail();
	int getServiceRemind();
	void setCarName(string data);
	void setPersonalKey(string data);
	void setODO(int data);
	void setEmail(string data);
	void setServiceRemind(int data);

};

#endif /* Car_H_ */
#pragma once
