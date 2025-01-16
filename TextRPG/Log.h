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

class Log
{
private:
	static Log* instance;
	string log;

	//�ܼ� �ڵ� ����
	HWND console = GetConsoleWindow();
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	//�ܼ� ���� ������ ����
	COORD bufferSize;
	//����� �ػ� ��������
	int moniterScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int moniterScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	//Windows �ܼ�â�� �⺻ ��Ʈ�� ���� ũ�� ��(�ȼ�)
	int charWidth = 8;
	int charHeight = 16;
	//â ���δ� �̹����� ���� �ʺ�, ���δ� ����� ������� 4���� 3 ũ�⿡ �������
	int consoleWidth = IMAGE_SIDE_LENGTH*2.1;
	int consoleHeight = static_cast<int>(moniterScreenHeight * 0.75 / charHeight);
	
	//�ܼ� ������ ũ�⸦ ���� ũ��� ������. �̷��� ���ڿ� ���̿� ���� ��ũ�� �߻����� ����(�����̱� ������ ȭ�� ��ũ�� �߻����� �ʵ���)
	SHORT bufferWidth = static_cast<SHORT>(consoleWidth);
	SHORT bufferHeight = static_cast<SHORT>(consoleHeight);
	
	
	//�̹��� ���� ����
	int palette[NUMBER_OF_COLOR][3] = //SetConsoleTextAttribute�� ���� �ε����� ��Ī��
	{
	{0, 0, 0}, {0, 0, 128}, {0, 128, 0}, {0, 128, 128},
	{128, 0, 0}, {128, 0, 128}, {128, 128, 0}, {192, 192, 192},
	{128, 128, 128}, {0, 0, 255}, {0, 255, 0}, {0, 255, 255},
	{255, 0, 0}, {255, 0, 255}, {255, 255, 0}, {255, 255, 255}
	};
	//���ĺ����� ��ȯ�� ���ڿ��� ���� vector<string> ����, ����(32)�� �ε��� ��� �ϳ��� 32�� ����(32x32)
	//ĳ���� �̹���
	vector<string> playerData;
	//���� �̹���
	vector<string> goblinData;
	vector<string> orcData;
	vector<string> trollData;
	vector<string> wolfData;
	vector<string> slimeData;
	vector<string> goblinRiderData;
	vector<string> twinHeadTrollData;
	vector<string> treantData;
	vector<string> dragonData;
	//���� �̹���
	vector<string> buffData;
	vector<string> deBuffData;
	//���� �̹���
	vector<string> shopData;
	//�޽� �̹���
	vector<string> restData;
	//������ �̹���
	vector<string> bagData;

private:
	Log() {};
	~Log() = default;
	Log(const Log&) = delete;
	Log& operator = (const Log&) = delete;
	int CharToIndex(char c);	//�̹��� ����� ���� ���ĺ��� �ε����� ��ȯ������
	vector<string> PNGImageToData(string filePath);
	int GetClosestColorIndex(int r, int g, int b);
public:
	static Log* GetInstance();
	const string& GetLog();
	void Initialize();			//���δ� ����� ũ�� 4���� 3, ���δ� �̹��� �ʺ�ŭ ũ�� ����, �� stringŸ�� ���Ϳ� �̹��� �ؽ�Ʈ �ʱ�ȭ(32X32 PNG������ 0~15�� ���� ���� ���ĺ����� ��ȯ -> �ܼ� ���� ��ȯ�� ����)
	void SetLog(string log);
	void PrintStartMenu(int caseNumber);	//���� ���� �޴� ���
	void PrintInputError();
	void PrintGameOver(int caseNumber);	//1 : ���� ������ ���, 2 : �÷��̾� ����� ���
	void PrintImage(vector<string>& data);
	//�� ��ü�κ��� ����� string���� �ش� Enum �� ����, string�� ������ ��¸�	bool�� ȭ�� Ŭ���� ����
	void PrintLog(string orderLog);
	void PrintLog(string orderLog, int caseNumber);						//�̹����� ���� ���
	void PrintLog(string orderLog, bool clear);
	void PrintLog(string orderLog, int caseNumber, bool clear);
};

#endif