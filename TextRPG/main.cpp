#include <iostream>

#include "GameManager.h"
#include "Log.h"
#include "Character.h"
#include "EnumCollection.h"

using namespace std;

void main()
{
	using GM = GameManger::GameManger;

	GM& gameManager = GM::GetInstance();

	// ��Ʋ �Ŵ���, �ɸ��� ����
	gameManager.GenerateBattleManager();
	Log* logger = Log::GetInstance();
	logger->Initialize();
	Character player1 = *new Character("������");
	string playerStatus = player1.GetCharacterStatusString();
	logger->PrintLog(playerStatus, player1);
	logger->PrintGameOver(GameEnd);
	return;

	//int menuOption;
	//bool isGameRun = false;		//������ ���࿩��
	//bool isGameStart = false;	//���Ӹ޴� Ż������ ����

	//logger->SetScreen();
	//// 1. ���ӽ���, 2. ����
	//while (!isGameStart)
	//{
	//	logger->PrintStartMenu(Menu);
	//	cin >> menuOption;

	//	switch (menuOption) {
	//	case 1:
	//		isGameStart = true;	//����ȭ�� ���� ����� ����
	//		isGameRun = true;	//���� ����
	//		logger->PrintStartMenu(Start);
	//		break;
	//	case 2:
	//		logger->PrintGameOver(LogEnum::GameEnd);	//�÷��̾��� ����� ���� ����� ���� ����� ��¹�
	//		return;
	//		break;
	//	default:
	//		logger->PrintInputError();	//�߸��� �Է� �ȳ� ���
	//	}
	//}

	////���� ���� �ڵ�
	//while (isGameStart)
	//{
	//	break;
	//}
	//���� ������ ������ ��
	//logger->PrintLog("")
	//logger->PrintGameOver(LogEnum::GameEnd);
	//return;
}