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

	// ��Ʋ �Ŵ���, �ɸ��� ����
	gameManager.GenerateBattleManager();

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
<<<<<<< HEAD
	logger->PrintGameOver(LogEnum::GameEnd);
	return 0;
=======
	logger->PrintGameOver(EGameEnd);
	return;
>>>>>>> e1e55e7f8e65481cf3f2e5a58b12d10f56bb0252
}