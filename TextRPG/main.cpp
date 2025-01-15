#include <iostream>
#include <string>

#include "GameManager.h"
#include "Log.h"
#include "Character.h"
#include "EnumCollection.h"
#include "shop.h"

using namespace std;

int main() 
{
	//SetConsoleOutputCP(CP_UTF8); // CMD �⺻ ���ڵ� ����

	using GM = GameManger::GameManger;
	GM& gameManager = GM::GetInstance();

	Log* logger = Log::GetInstance();
	logger->Initialize();
	
	// Debug
	// Character player1 = *new Character("���ǵ� ���");
	// Character player1 = *new Character("aaa");
	// Shop shop;
	// gameManager.VisitShop(&player1);

	int menuOption;
	bool isGameRun = false;		//������ ���࿩��
	bool isGameStart = false;	//���Ӹ޴� Ż������ ����
	string characterName;

	while (true) {
		logger->PrintLog("... ����� �����Դϱ�?\n");
		getline(cin, characterName);

		if (characterName.length() >= 0 && characterName.length() <= 10) {
			logger->PrintLog("���� �̸���? " + characterName + "\n");
			break;
		}
		else {
			logger->PrintLog("���� �ȵǴ� �̸��Դϴ�.\n");
		}
	}

	Character player1 = *new Character(characterName);
	// 1. ���ӽ���, 2. ����
	while (!isGameStart)
	{
		logger->PrintStartMenu(EMenu);
		cin >> menuOption;
		switch (menuOption) {
		case 1:
			isGameStart = true;	//����ȭ�� ���� ����� ����
			isGameRun = true;	//���� ����
			logger->PrintStartMenu(EStart);
			gameManager.BeginPlay(&player1);
			break;
		case 2:
			logger->PrintGameOver(EGameEnd);	//�÷��̾��� ����� ���� ����� ���� ����� ��¹�
			return 0;
			break;
		default:
			logger->PrintInputError();	//�߸��� �Է� �ȳ� ���
		}
	}

	//���� ������ ������ ��
	logger->PrintGameOver(EGameEnd);
	return 0;
}