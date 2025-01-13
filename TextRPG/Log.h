#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <time.h>
#include <type_traits>
#include "EnumCollection.h"

#define IMAGE_SIDE_LENGTH 32	//���Ǵ� �̹��������� ������ 32X32 �ȼ� ����� ���
#define NUMBER_OF_COLOR 16

using namespace std;
using namespace Enums;

class Log
{
private:
	static Log* instance;
	string log;
	//����� �ػ� ��������
	int moniterScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int moniterScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	//����� �ػ� ���μ����� ���ݸ�ŭ�� �ܼ�â�� ũ�Ⱑ �ǵ��� ��(â ũ��� ������� 1/4
	int consoleWidth = moniterScreenWidth / 2;
	int consoleHeight = moniterScreenHeight / 2;
	//Windows �ܼ�â�� �⺻ ��Ʈ(Raster Fonts)�� ���� ũ�� ��(�ȼ�)  ���� 8�ȼ�  ���� 16�ȼ�
	int charWidth = 8;
	int charHeight = 16;
	//�ܼ� ������ ũ�⸦ ���� ũ��� ������. �̷��� ���ڿ� ���̿� ���� ��ũ�� �߻����� ����(�����̱� ������ ȭ�� ��ũ�� �߻����� �ʵ���)
	int bufferWidth = consoleWidth / charWidth;
	int bufferHeight = consoleHeight / charHeight;
	//�ܼ� �ڵ� ����
	HWND console = GetConsoleWindow();
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	vector<string> playerData;
	vector<string> goblinData;
	vector<string> orcData;
	vector<string> trollData;
	vector<string> wolfData;
	vector<string> slimeData;
	vector<string> goblinRiderData;
	vector<string> twinHeadTrollData;
	vector<string> treantData;
	vector<string> dragonData;

private:
	Log() {};
	~Log() = default;
	Log(const Log&) = delete;
	Log& operator = (const Log&) = delete;
	int CharToIndex(char c);	//�̹��� ����� ���� ���ĺ��� �ε����� ��ȯ������
public:
	static Log* GetInstance();
	const string& GetLog();
	void Initialize();			//����� ũ���� 4���� 1 ũ��� �ܼ� â ũ�⸦ �����ϰ� ����� ����� �����, �� stringŸ�� ���Ϳ� �̹��� �ؽ�Ʈ �ʱ�ȭ(32X32 PNG������ 0~15�� ���� ���� ���ĺ����� ��ȯ -> �ܼ� ���� ��ȯ�� ����)
	void SetLog(string log);
	template<typename T>
	void PrintLog(string orderLog, const T& object);	//�� ��ü�κ��� ����� string���� ������ ��������� �Ǻ��ϴ� Enum�� ���ڷ� �޾� ȭ�� ���
	void PrintStartMenu(int caseNumber);	//���� ���� �޴� ���
	void PrintInputError();
	void PrintGameOver(int caseNumber);	//1 : ���� ������ ���, 2 : �÷��̾� ����� ���
	void PrintBattle(); //BattlePrint, StatusPrint, ShopRoomPrint, RestRoomPrint, BuffDebuffRoomPrint
	void PrintStatus();
	void PrintShopRoom();
	void PrintRestRoom();
	void PrintBuffDebuffRoom();
	void TestPrint();
};

#endif