#include <iostream>

#include "GameManager.h"
#include "Log.h"
#include "Character.h"
#include "EnumCollection.h"

using namespace std;

int main() 
{
	using GM = GameManger::GameManger;

	GM& gameManager = GM::GetInstance();

	Log* logger = Log::GetInstance();
	logger->Initialize();
	Character player1 = *new Character("������");
	//player1.DisplayStatus();

	int menuOption;
	bool isGameRun = false;		//������ ���࿩��
	bool isGameStart = false;	//���Ӹ޴� Ż������ ����

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
			break;
		case 2:
			logger->PrintGameOver(EGameEnd);	//�÷��̾��� ����� ���� ����� ���� ����� ��¹�
			return;
			break;
		default:
			logger->PrintInputError();	//�߸��� �Է� �ȳ� ���
		}
	}

	//���� ���� �ڵ�
	while (isGameStart)
	{
		gameManager.BeginBattle(&player1, 1);
		break;
	}
	
	//���� ������ ������ ��
	logger->PrintGameOver(LogEnum::EGameOver);
	return 0;
}