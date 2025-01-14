#ifndef LOG_H
#define LOG_H

#include "stb_image.h"
#include "EnumCollection.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <time.h>
#include <type_traits>


#define IMAGE_SIDE_LENGTH 32	//���Ǵ� �̹��������� ������ 32X32 �ȼ� ����� ���
#define NUMBER_OF_COLOR 16
using namespace std;
using namespace Enums;

class Character;

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
	//�̹��� ���� ����
	int palette[NUMBER_OF_COLOR][3] = //SetConsoleTextAttribute�� ���� �ε����� ��Ī��
	{
	{0, 0, 0}, {0, 0, 128}, {0, 128, 0}, {0, 128, 128},
	{128, 0, 0}, {128, 0, 128}, {128, 128, 0}, {192, 192, 192},
	{128, 128, 128}, {0, 0, 255}, {0, 255, 0}, {0, 255, 255},
	{255, 0, 0}, {255, 0, 255}, {255, 255, 0}, {255, 255, 255}
	};
	//���ĺ����� ��ȯ�� ���ڿ��� ���� vector<string> ����, ����(32)�� �ε��� ��� �ϳ��� 32�� ����(32x32)
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
	vector<string> PNGImageToData(string filePath);
	int GetClosestColorIndex(int r, int g, int b);
	//void ProcessPNG(string filePath);
public:
	static Log* GetInstance();
	const string& GetLog();
	void Initialize();			//����� ũ���� 4���� 1 ũ��� �ܼ� â ũ�⸦ �����ϰ� ����� ����� �����, �� stringŸ�� ���Ϳ� �̹��� �ؽ�Ʈ �ʱ�ȭ(32X32 PNG������ 0~15�� ���� ���� ���ĺ����� ��ȯ -> �ܼ� ���� ��ȯ�� ����)
	void SetLog(string log);
	void PrintStartMenu(int caseNumber);	//���� ���� �޴� ���
	void PrintInputError();
	void PrintGameOver(int caseNumber);	//1 : ���� ������ ���, 2 : �÷��̾� ����� ���
	//void PrintBattle(BattleManager& object); //BattlePrint, StatusPrint, ShopRoomPrint, RestRoomPrint, BuffDebuffRoomPrint
	void PrintStatus();
	void PrintShopRoom();
	void PrintRestRoom();
	void PrintBuffDebuffRoom();
	void PrintImage(vector<string>& data);

	template<typename T>
	void PrintLog(string orderLog, const T& object)	//�� ��ü�κ��� ����� string���� ��ü�� ����
	{
		this->SetLog(orderLog);				//�� ��ü���� SetLog�� ���� ȣ���ϱ⺸��, PrintLog�� ȣ�⿡�� Set�� ����� ���ÿ� �̷�������� ��

		//PrintImage(dragonData);	�̹������ �׽�Ʈ��

		if constexpr (is_same_v<T, Character>)	//���� ��ü�� ���� Print �ٸ��� ��
		{
			this->PrintStatus();
		}
		/*else if constexpr (is_same_v<T, BattleManager>)
		{
			this->PrintBattle(object);
		}*/
		cout << this->log;
	}
};

#endif