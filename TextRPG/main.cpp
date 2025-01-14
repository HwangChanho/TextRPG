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
<<<<<<< HEAD
	player1.DisplayStatus();

	int menuOption;
	bool isGameRun = false;		//������ ���࿩��
	bool isGameStart = false;	//���Ӹ޴� Ż������ ����

	// 1. ���ӽ���, 2. ����
	while (!isGameStart)
	{
		logger->PrintStartMenu(Menu);
		cin >> menuOption;

		switch (menuOption) {
		case 1:
			isGameStart = true;	//����ȭ�� ���� ����� ����
			isGameRun = true;	//���� ����
			logger->PrintStartMenu(Start);
			// gameManager.BeginPlay();
			break;
		case 2:
			logger->PrintGameOver(LogEnum::GameEnd);	//�÷��̾��� ����� ���� ����� ���� ����� ��¹�
			return;
			break;
		default:
			logger->PrintInputError();	//�߸��� �Է� �ȳ� ���
		}
	}

	//���� ���� �ڵ�
	while (isGameStart)
	{
		break;
	}

	//���� ������ ������ ��
	logger->PrintGameOver(LogEnum::GameEnd);
	return 0;
=======
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
>>>>>>> d51d7a740943e94bc67ce11be815a9123be269fa
}