#include <iostream>
#include"Setting.h"
#include "CommonInfo.h"
#include <fstream>
#include <regex>
#include <algorithm>
#include <string>
#include<sstream>
#include <exception>
#include<map>
#include"BST.h"
using namespace std;
int timezone_index = 0;
int laguagelist_index = 0;
ifstream f("Setting.txt");
BST Carlist;
vector<CommonInfo> timezoneList;
vector<CommonInfo> languageList;
void NhapThongTinCaiDat();
void XuatThongTinCaiDat();
void XuatThongTinCaiDat_Sound();
void XuatThongTinCaiDat_General();
void XuatThongTinCaiDat_Display();
void XuatThongTatCaTinCaiDat();
void NhapThongTinCaiDat_Sound();
void NhapThongTinCaiDat_General();
void NhapThongTinCaiDat_Display();
void downloadTimeZone();
void downloadLanguage();
bool isNumber(const string& str);
void menu();
char checkYorN();
void showTimeZones();
void showLanguagesList();
vector<string> alphabaticallySort(vector<string> a);
void swapObj(CommonInfo& obj1, CommonInfo& obj2);
int checkInput(int len);
void LoadData();
string EnterKey();
string EnterName();
template <typename A, typename B>
void zip(
	const std::vector<A>& a,
	const std::vector<B>& b,
	std::vector<std::pair<A, B>>& zipped)
{
	for (size_t i = 0; i < a.size(); ++i)
	{
		zipped.push_back(std::make_pair(a[i], b[i]));
	}
}

template <typename A, typename B>
void unzip(
	const std::vector<std::pair<A, B>>& zipped,
	std::vector<A>& a,
	std::vector<B>& b)
{
	for (size_t i = 0; i < a.size(); i++)
	{
		a[i] = zipped[i].first;
		b[i] = zipped[i].second;
	}
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char** argv) {
	LoadData();
	downloadLanguage();
	downloadTimeZone();
	menu();
	return 0;
}

void menu() {	// show menu with 3 options: information setting, information printing and exit
	//system("cls");
	int selection;
	cout << "---SELECT MENU---\n";
	cout << "1. Input Setting Information\n"
		<< "2. Print Setting Information\n"
		<< "3. Exit\n"
		<< "Your Selection: ";
	string str;
	do {
		try {
			cout << ">> ";
			cin >> str;
			if (str.length() > 1 || !isNumber(str) || stoi(str) > 3 || stoi(str) <= 0) {		// check input before coming to switch
				system("cls");
				throw "INVALID, PLEASE ENTER A NUMBER FORM 1 TO 3!";

			}
			selection = stoi(str);	// convert into integer
			switch (selection) {
			case 1:
				system("cls");
				NhapThongTinCaiDat();
				break;
			case 2:
				XuatThongTinCaiDat();
				break;
			case 3:
				system("cls");
				cout << "GOOD BYE--- SEE YOU LATER ^^";
				exit(0);
				break;
			default:
				break;
			}
		}
		catch (const char* err) {
			cout << err << endl;
			menu();
		}
	} while (selection != 3);
}

void NhapThongTinCaiDat() {		// another menu that show user 4 option of setting: display, sound,general and exit
	int selection;
	cout << "---SELECT MENU---\n"
		<< "1. Display setting\n"
		<< "2. Sound setting\n"
		<< "3. General setting\n"
		<< "0. Exit\n"
		<< "Your selection: ";
	bool isvalid = true;
	string str;
	do {
		try {
			cout << ">> ";
			cin >> str;
			if (str.length() > 1 || !isNumber(str) || stoi(str) > 3) {
				system("cls");
				throw "INVALID, PLEASE ENTER A NUMBER FORM 1 TO 3!";
			}
			selection = stoi(str);
			switch (selection) {
			case 1:
				NhapThongTinCaiDat_Display(); //enter 1 for setting display information
				break;
			case 2:
				NhapThongTinCaiDat_Sound();	// enter 2 for setting sound information
				break;
			case 3:
				NhapThongTinCaiDat_General();	// enter 3 for setting general information
				break;
			case 0:
				menu();
			default:
				break;
			}
		}
		catch (const char* err) {
			cout << err << endl;
			NhapThongTinCaiDat();
		}
	} while (selection != 0);
}

void NhapThongTinCaiDat_Sound()	//Sound setting function
{
	char continues = 'n';
	do {
		cout << "---Input Sound Setting---\n"
			<< "Car index: " << Carlist.sizeTree() + 1 << endl;
		Setting* tempCar = new Setting;
		tempCar->nhapThongTin();	//enter personal information (name, email,...)
		if (Carlist.sizeTree() > 0) {	//check thie size of tree to show whether this is the first car or not
			if (Carlist.searchNodeInKey(tempCar->getPersonalKey()) != nullptr) {	//check if userkey existed or not
				cout << "This car " << Carlist.sizeTree() + 1 << " already existed, data will be overitten\n";
				Carlist.searchNodeInKey(tempCar->getPersonalKey())->data->copyInfo(tempCar);		//coppy infor from tempcar  into data of node
				Carlist.searchNodeInKey(tempCar->getPersonalKey())->data->getSound()->nhapThongTin_Sound();		// call Sound object from Setting obj and access nhapThongTin_Sound()				
			}
			else {
				cout << "This car " << Carlist.sizeTree() + 1 << " data will be appended to your list\n";
				tempCar->getSound()->nhapThongTin_Sound();	// call Sound object from Setting obj and access nhapThongTin_Sound()
				Carlist.InsertNode(tempCar);		//add node into binaray tree (object of binary tree here is Carlist 
			}
		}
		else {
			cout << "This is the first car\n";
			tempCar->getSound()->nhapThongTin_Sound();			// call Sound object from Setting obj and access nhapThongTin_Sound()
			Carlist.InsertNode(tempCar);
		}
		Carlist.SaveDataOfNodes();
		cout << "WILL YOU INPUT FOR CAR " << Carlist.sizeTree() + 1 << " ? (y/n): ";	// ask if user wanna append the list of car or not	
		continues = checkYorN();
		cout << endl;
	} while (continues == 'y');
	system("cls");
	menu();
}

void NhapThongTinCaiDat_General()	//General setting 
{
	char continues = 'n';
	do {
		Setting* tempCar = new Setting;
		cout << "---Input General Setting---\n"
			<< "Car index: " << Carlist.sizeTree() + 1 << endl;
		tempCar->nhapThongTin();	//enter personal information (name, email,...)
		string s = tempCar->getPersonalKey();
		if (Carlist.sizeTree() + 1 > 0) {
			if (Carlist.searchNodeInKey(s) != nullptr) {
				cout << "This car " << Carlist.sizeTree() + 1 << " already existed, data will be overitten\n";
				Carlist.searchNodeInKey(s)->data->copyInfo(tempCar);
				showTimeZones();		//show list of timezones
				cout << "---YOUR SELECTION: \n";
				timezone_index = checkInput(timezoneList.size());			//chose timezones by entering a number on the list
				Carlist.searchNodeInKey(s)->data->getGeneral()->set_timeZone(timezoneList[timezone_index - 1].getNumber());	// set timezones according to the number entered above
				showLanguagesList();		// show language list and similar to timezone.....
				cout << "---YOUR SELECTION: \n";
				laguagelist_index = checkInput(languageList.size());
				Carlist.searchNodeInKey(s)->data->getGeneral()->set_language(languageList[laguagelist_index - 1].getName());	//set language according to the number entered above
			}
			else {
				cout << "This car " << Carlist.sizeTree() + 1 << " data will be appended to your list\n";
				showTimeZones();		//show list of timezones
				cout << "---YOUR SELECTION: \n";
				timezone_index = checkInput(timezoneList.size());			//chose timezones by entering a number on the list
				tempCar->getGeneral()->set_timeZone(timezoneList[timezone_index - 1].getNumber());	// set timezones acording to the number entered above
				showLanguagesList();		// show language list and similar to timezone.....
				cout << "---YOUR SELECTION: \n";
				laguagelist_index = checkInput(languageList.size());
				tempCar->getGeneral()->set_language(languageList[laguagelist_index - 1].getName());
				Carlist.InsertNode(tempCar);
			}
		}
		else {
			cout << "This is the first car\n";
			showTimeZones();		//show list of timezones
			cout << "---YOUR SELECTION: \n";
			timezone_index = checkInput(timezoneList.size());			//chose timezones by entering a number on the list
			tempCar->getGeneral()->set_timeZone(timezoneList[timezone_index - 1].getNumber());	// set timezones acording to the number entered above
			showLanguagesList();		// show language list and similar to timezone.....
			cout << "---YOUR SELECTION: \n";
			laguagelist_index = checkInput(languageList.size());
			tempCar->getGeneral()->set_language(languageList[laguagelist_index - 1].getName());
			Carlist.InsertNode(tempCar);
		}
		Carlist.SaveDataOfNodes();
		cout << "WILL YOU INPUT FOR CAR " << Carlist.sizeTree() + 1 << " ? (y/n): ";
		continues = checkYorN();
		cout << endl;
	} while (continues == 'y');
	system("cls");
	menu();
}

void NhapThongTinCaiDat_Display()	// Display setting, the algorithm of this function is simalar to NhapThongTinCaiDat_Sound()
{
	char continues = 'n';
	do {
		Setting* tempCar = new Setting;
		cout << "---Input Displaying Setting---\n"
			<< "Car index: " << Carlist.sizeTree() + 1 << endl;
		tempCar->nhapThongTin();	//enter personal information (name, email,...), simalar to Sound setting
		int n;
		if (Carlist.sizeTree() > 0) {
			if (Carlist.searchNodeInKey(tempCar->getPersonalKey()) != nullptr) {			//check if userkey existed or not
				cout << "This car " << Carlist.sizeTree() + 1 << " already existed, data will be overitten\n";
				Carlist.searchNodeInKey(tempCar->getPersonalKey())->data->copyInfo(tempCar);
				Carlist.searchNodeInKey(tempCar->getPersonalKey())->data->getDisplay()->nhapThongTin_Display();
			}
			else {
				cout << "This car " << Carlist.sizeTree() + 1 << " data will be appended to your list\n";
				tempCar->getDisplay()->nhapThongTin_Display();
				Carlist.InsertNode(tempCar);
			}
		}
		else {
			cout << "This is the first car\n";
			tempCar->getDisplay()->nhapThongTin_Display();			// call Sound object from Setting obj and access nhapThongTin_Display()
			Carlist.InsertNode(tempCar);
		}
		Carlist.SaveDataOfNodes();
		cout << "WILL YOU INPUT FOR CAR " << Carlist.sizeTree() + 1 << " ? (y/n): ";
		continues = checkYorN();
		cout << endl;
	} while (continues == 'y');
	system("cls");
	menu();
}

void XuatThongTinCaiDat() {	//menu which show printing options
	int selection;
	bool isvalid = true;
	string str;
	do {
		cout << "---SELECT MENU---\n"
			<< "1. Print Display setting information\n"
			<< "2. print Sound setting information\n"
			<< "3. Print General setting information\n"
			<< "4. Print all setting information\n"
			<< "5. Exit\n"
			<< "Your Selection: ";
		try {
			cout << ">> ";
			cin >> str;
			if (str.length() > 1 || !isNumber(str) || stoi(str) > 5 || stoi(str) <= 0) {
				system("cls");
				throw "KHONG HOP LE, XIN HAY NHAP 1 SO TU 1 DE 5";
			}
			selection = stoi(str);
			switch (selection) {
			case 1:
				XuatThongTinCaiDat_Display();	// print Display information on the console
				break;
			case 2:
				XuatThongTinCaiDat_Sound();		// print Sound information on the console
				break;
			case 3:
				XuatThongTinCaiDat_General();	// print General information on the console
				break;
			case 4:
				system("cls");
				XuatThongTatCaTinCaiDat();		// print all information including personnal info, Display, General, Sound
				break;
			case 5:
				menu();
				break;
			default:
				break;
			}
		}
		catch (const char* err) {
			cout << err << endl;
			XuatThongTinCaiDat();	//print personal info
		}
	} while (selection != 5);
}

const vector<string> explode(const string& s, const char& c)	// function to erase a char of a string, and return to vector type
{
	string buff{ "" };
	vector<string> v;

	for (auto n : s)
	{
		if (n != c)
			buff += n;
		else if (n == c && buff != "")
		{
			v.push_back(buff);
			buff = "";
		}
	}
	if (buff != "")
		v.push_back(buff);

	return v;
}

void downloadTimeZone() {	// function to read timezone data from file.txt
	string s;
	CommonInfo com;
	vector<string> temp_commoninfo;
	try {
		ifstream f("timezones.txt");
		if (f.is_open()) {		// chekc if file open
			while (getline(f, s)) {	//read file into s
				temp_commoninfo = explode(s, ' /');	//erase '/' of a string then, store 2 elements and assigned to the vector temp_commoninfo
				com.setName(temp_commoninfo[1]);
				com.setNumber(temp_commoninfo[0]);
				timezoneList.push_back(com);		//add an element following the last element in vector timezoneList
			}
			f.close();
		}
		else {
			throw exception();
		}
	}
	catch (const exception& e) {
		cerr << "Unable to open file to read " << "timezones.txt" << endl;
	}
	vector<int> names;
	vector<string> utc;
	for (int i = 0;i < timezoneList.size();i++) {
		utc = explode(timezoneList[i].getNumber(), ':');
		names.push_back(stoi(utc[0].substr(4)));	// coppy data of timezoneList into vector names
	}
	vector<pair<CommonInfo, int>> zipped;
	zip(timezoneList, names, zipped);
	sort(begin(zipped), end(zipped),
		[&](const auto& a, const auto& b)
		{
			return a.second < b.second;
		});
	unzip(zipped, timezoneList, names);
}

void downloadLanguage() {	// read language data, similar to dowloadTimezones.....
	string s;
	CommonInfo com;
	vector<string> temp_commoninfo;
	ifstream f("languages.txt");
	try {
		if (f.is_open()) {
			while (getline(f, s)) {
				temp_commoninfo = explode(s, '/');
				com.setNumber(temp_commoninfo[0]);
				com.setName(temp_commoninfo[1]);
				languageList.push_back(com);
			}
			f.close();
		}
		else {
			throw exception();
		}
	}
	catch (const exception& e) {
		cerr << "Unable to open file to read " << "languages.txt" << endl;
	}
	vector<string> names;
	for (int i = 0;i < languageList.size();i++) {
		names.push_back(languageList[i].getName());
	}
	names = alphabaticallySort(names);
	for (int j = 0;j < names.size();j++) {
		for (int i = 0;i < languageList.size();i++) {
			if (names[j] == languageList[i].getName()) {
				swapObj(languageList[j], languageList[i]);
			}
		}
	}
}

void XuatThongTinCaiDat_Sound() {	//print Sound information
	system("cls");
	if (Carlist.sizeTree() > 0) {
		//		Sort_Selection();
		char n = 'n';
		do {
			cout << "---Sound setting---\n";
			string s = EnterKey();
			cout << setw(10) << "TEN CHU XE" << setw(20) << "Email" << setw(10) << "MSC" << setw(10) << "ODO" << setw(10) << "SEVICES" << setw(10) << "Media" << setw(10) << "Call" << setw(10) << "Navi" << setw(10) << "Notify" << endl;
			Carlist.searchNodeInKey(s)->data->xuatThongTin();
			Carlist.searchNodeInKey(s)->data->getSound()->xuatThongTin_Sound();
			cout << "\nWILL YOU WANNA DISPLAY ANOTHER CAR ? (y/n): ";	// ask if user wanna display other cars or not	
			n = checkYorN();
			cout << endl;
		} while (n == 'y');
	}
	else {
		cout << "THERE IS NO DATA IN FILE\n";
	}
}

void XuatThongTinCaiDat_General() {	//print Sound information
	system("cls");
	if (Carlist.sizeTree() > 0) {
		//	Sort_Selection();
		char n = 'n';
		do {
			cout << "---General setting---\n";
			string s = EnterKey();
			cout << setw(10) << "TEN CHU XE" << setw(20) << "Email" << setw(10) << "MSC" << setw(10) << "ODO" << setw(10) << "SEVICES" << setw(15) << "TimeZone" << setw(15) << "Language" << endl;
			Carlist.searchNodeInKey(s)->data->xuatThongTin();
			Carlist.searchNodeInKey(s)->data->getGeneral()->xuatThongTin_General();
			cout << "\nWILL YOU WANNA DISPLAY ANOTHER CAR ? (y/n): ";	// ask if user wanna display other cars or not	
			n = checkYorN();
			cout << endl;
		} while (n == 'y');
	}
	else {
		cout << "THERE IS NO DATA IN FILE\n";
	}
}

void XuatThongTinCaiDat_Display() {		// print Display information
	system("cls");
	//	Sort_Selection();
	if (Carlist.sizeTree() > 0) {
		char n = 'n';
		do {
			cout << "---Display setting---\n";
			string s = EnterKey();
			cout << setw(10) << "TEN CHU XE" << setw(20) << "Email" << setw(10) << "MSC" << setw(10) << "ODO" << setw(10) << "SEVICES" << setw(10) << "Light" << setw(10) << "Taplo" << setw(10) << "Screen" << endl;
			Carlist.searchNodeInKey(s)->data->xuatThongTin();
			Carlist.searchNodeInKey(s)->data->getDisplay()->xuatThongTin_Display();
			cout << "\nWILL YOU WANNA DISPLAY ANOTHER CAR ? (y/n): ";	// ask if user wanna display other cars or not	
			n = checkYorN();
			cout << endl;
		} while (n == 'y');
	}
	else {
		cout << "THERE IS NO DATA IN FILE\n";
	}
}

void XuatThongTatCaTinCaiDat() {	// print all
	if (Carlist.sizeTree() > 0) {
		system("cls");
		int selection = 0;
		string s = "";
		cout << "---All Setting---\n";
		cout << "1. Enter name to show user's data\n"
			<< "2. Enter personal key show get user's data\n"
			<< "3. Show data of all users\n";
		selection = checkInput(3);
		switch (selection) {
		case 1:
			system("cls");
			cout << "Get data by car name\n";
			s = EnterName();
			cout << setw(10) << "TEN CHU XE" << setw(20) << "Email" << setw(10) << "MSC" << setw(10) << "ODO" << setw(10) << "SEVICES" << setw(10) << "Light" << setw(10) << "Taplo" << setw(10) << "Screen"
				<< setw(10) << "Media" << setw(10) << "Call" << setw(10) << "Navi" << setw(10) << "Notify"
				<< setw(15) << "TimeZone" << setw(15) << "Language" << endl;
			for (int i = 0;i < Carlist.searchNodeInName(s).size();i++) {
				Carlist.searchNodeInName(s)[i]->data->xuatThongTin();
				Carlist.searchNodeInName(s)[i]->data->getDisplay()->xuatThongTin_Display();
				Carlist.searchNodeInName(s)[i]->data->getSound()->xuatThongTin_Sound();
				Carlist.searchNodeInName(s)[i]->data->getGeneral()->xuatThongTin_General();
				cout << endl;
			}
			break;
		case 2:
			system("cls");
			cout << "Get data by personal key\n";
			s = EnterKey();
			cout << setw(10) << "TEN CHU XE" << setw(20) << "Email" << setw(10) << "MSC" << setw(10) << "ODO" << setw(10) << "SEVICES" << setw(10) << "Light" << setw(10) << "Taplo" << setw(10) << "Screen"
				<< setw(10) << "Media" << setw(10) << "Call" << setw(10) << "Navi" << setw(10) << "Notify"
				<< setw(15) << "TimeZone" << setw(15) << "Language" << endl;
			Carlist.searchNodeInKey(s)->data->xuatThongTin();
			Carlist.searchNodeInKey(s)->data->getDisplay()->xuatThongTin_Display();
			Carlist.searchNodeInKey(s)->data->getSound()->xuatThongTin_Sound();
			Carlist.searchNodeInKey(s)->data->getGeneral()->xuatThongTin_General();
			cout << endl;
			break;
		case 3:
			system("cls");
			cout << setw(10) << "TEN CHU XE" << setw(20) << "Email" << setw(10) << "MSC" << setw(10) << "ODO" << setw(10) << "SEVICES" << setw(10) << "Light" << setw(10) << "Taplo" << setw(10) << "Screen"
				<< setw(10) << "Media" << setw(10) << "Call" << setw(10) << "Navi" << setw(10) << "Notify"
				<< setw(15) << "TimeZone" << setw(15) << "Language" << endl;
			Carlist.inorder_print(4);
		default:
			break;
		}
	}
	else {
		cout << "THERE IS NO DATA IN FILE\n";
	}
}

char checkYorN() {		//function to if check input is yes or no
	string s;
	char a;
	bool isvalid = true;
	do {
		try {
			cin >> s;
			if ((s.length() > 1) || isNumber(s)) {	//no entering more than 1 charater or numeric character
				isvalid = false;
				throw "please only enter y/n: ";
				//continue;
			}
			else {
				isvalid = true;
			}
			a = s[0];
			if ((a == 'Y') || (a == 'y')) {				//convert uppercase in to lowercase
				a = 'y';
			}
			else if ((a == 'n') || (a == 'N')) {
				a = 'n';
			}
			else {
				isvalid = false;
				throw "please only enter y/n: ";
			}
		}
		catch (const char* err) {
			cout << err;
		}
	} while (!isvalid);
	return a;
}

void showTimeZones() {	//funtion to show list of timezones
	for (int i = 0;i < timezoneList.size();i++) {
		cout << i + 1 << " : " << timezoneList[i].getNumber() << "-" << timezoneList[i].getName() << endl;
	}
}

void showLanguagesList() {		//function to show list of language 
	for (int i = 0;i < languageList.size();i++) {
		cout << i + 1 << languageList[i].getName() << endl;
	}
}

bool isNumber(const string& str)			// function to check that character is a numeric character or not
{
	for (char const& c : str) {
		if (std::isdigit(c) == 0) return false;
	}
	return true;
}

bool mycomp(string a, string b) {	// funtion returns true if a,b is in alphabetically order
	return a < b;
}

vector<string> alphabaticallySort(vector<string> a) {	//sort elements of vector in alphabetically order
	sort(a.begin(), a.end(), mycomp);
	return a;
}

void swapObj(CommonInfo& obj1, CommonInfo& obj2) {	// swap 2 CommInfo objs
	CommonInfo temp_obj;
	temp_obj = obj1;
	obj1 = obj2;
	obj2 = temp_obj;
}

int checkInput(int n) {
	int m = 0;
	regex num("^[0-9]*$");
	string s = "";
	while (1) {
		try {
			cin >> s;
			if (!regex_match(s, num)) {
				throw "Input value follow number!!!\n";
				//cout << "Enter again: ";
			}
			else if (s[0] == '0') {
				throw "Enter positive number: \n";
			}
			else {
				m = stoi(s);
				if (m > n) {
					throw "Do not surpass the range!!!\n";
					//cout << "enter again: ";
				}
				else {
					return m;
					break;
				}
			}
		}
		catch (const char* err) {
			cout << err;
			cout << "Enter again: ";
		}
	}
}

void LoadData() {	//read data from file.txt
	string s;
	ifstream file1("Setting.txt");
	string arrS[13];

	try {
		if (file1.is_open()) {
			while (getline(file1, s)) {
				Setting* temp = new Setting;
				vector<string>vect_s;
				vect_s = explode(s, ';');
				vector<string> vect_common = explode(vect_s[0], ':');
				vector<string>vect_gen = explode(vect_s[1], ':');
				vector<string>vect_sou = explode(vect_s[2], ':');
				vector<string>vect_disp = explode(vect_s[3], ':');
				vector<string>sub_common = explode(vect_common[1], ',');
				vector<string>sub_gen = explode(vect_gen[2], ',');
				vector<string>sub_sou = explode(vect_sou[1], ',');
				vector<string>sub_disp = explode(vect_disp[1], ',');
				temp->setCarName(sub_common[0]);
				temp->setEmail(sub_common[1]);
				temp->setPersonalKey(sub_common[2]);
				temp->setODO(stoi(sub_common[3]));
				temp->setServiceRemind(stoi(sub_common[4]));
				temp->getGeneral()->set_timeZone(vect_gen[1] + ":" + sub_gen[0]);
				temp->getGeneral()->set_language(sub_gen[1]);
				temp->getSound()->set_call_level(stoi(sub_sou[0]));
				temp->getSound()->set_media_level(stoi(sub_sou[1]));
				temp->getSound()->set_navi_level(stoi(sub_sou[2]));
				temp->getSound()->set_notification_level(stoi(sub_sou[3]));
				temp->getDisplay()->set_light_level(stoi(sub_disp[0]));
				temp->getDisplay()->set_screen_light_level(stoi(sub_disp[1]));
				temp->getDisplay()->set_taplo_light_level(stoi(sub_disp[2]));
				Carlist.InsertNode(temp);		// add it into the array elements_ of private of List
			}
		}
		else {
			throw exception();
		}
	}
	catch (const exception& e) {
		cerr << "Unable to open file to read " << "Setting.txt" << endl;
	}
}

string EnterKey() {
	regex re_personal("^[0-9]{8}$");// format 8 digits;
	string s;
	while (1) {
		try {
			cout << "Enter personal key: ";		//enter user key and show warnig if input does not foollow 8 digits
			cin >> s;
			if (!regex_match(s, re_personal)) {
				//cout << "Input a value follows 8 digits!!!\n";
				throw "Input a value follows 8 digits!!!\n";
			}
			else if (Carlist.searchNodeInKey(s) == nullptr) {
				throw "This personal key does not exist\n";
			}
			else {
				break;
			}
		}
		catch (const char* err) {
			cout << err;
			cout << "Enter again: ";
		}
	}
	return s;
}

string EnterName() {
	string s = "";
	while (1) {
		try {
			cout << "Enter car name: ";
		//	cin.ignore();
			getline(std::cin, s);
			if (s.empty()) {		//do not let name empty
			//cout << "Input a value not null!!!\n";
				throw "Input a value not null!!!\n";
			}
			else if (Carlist.searchNodeInName(s).empty()) {
				throw "This name does not exist\n";
			}
			else {
				break;
			}
		}
		catch (const char* err) {
			cout << err;
			cout << "Enter again:...\n";
		}
	}
	return s;
}
