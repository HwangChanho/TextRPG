#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include "EnumCollection.h"

using namespace std;
using namespace Enums;

class Log
{
private:
	static Log* instance;
	string log;
public:

private:
	Log() {};
	~Log() = default;
	Log(const Log&) = delete;
	Log& operator = (const Log&) = delete;
public:
	static Log* GetInstance();
	void SetScreen();
	string GetLog();
	void SetLog(string log);
	void PrintLog(string orderLog, int enumCase);
	void PrintStartMenu(int caseNumber);	//���� ���� �޴� ���
	void PrintInputError();
	void PrintGameOver(int caseNumber);	//1 : ���� ������ ���, 2 : �÷��̾� ����� ���
	void PrintBattle(); //BattlePrint, StatusPrint, ShopRoomPrint, RestRoomPrint, BuffDebuffRoomPrint
	void PrintStatus();
	void PrintShopRoom();
	void PrintRestRoom();
	void PrintBuffDebuffRoom();
};

#endif