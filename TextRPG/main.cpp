#include <iostream>

#include "GameManager.h"
#include "Log.h"
#include "Character.h"
#include "EnumCollection.h"

using namespace std;

<<<<<<< HEAD
void main()
=======
int main() 
>>>>>>> GameManager
{
	using GM = GameManger::GameManger;

	GM& gameManager = GM::GetInstance();

	// ��Ʋ �Ŵ���, �ɸ��� ����
	gameManager.GenerateBattleManager();
<<<<<<< HEAD
	Log* logger = Log::GetInstance();
	Character player1 = *new Character("������");
	player1.DisplayStatus();
=======
	//Character player1 = *new Character("한정혁");
	//player1.DisplayStatus();
>>>>>>> GameManager

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
<<<<<<< HEAD
			isGameStart = true;	//����ȭ�� ���� ����� ����
			isGameRun = true;	//���� ����
			logger->PrintStartMenu(Start);
			break;
		case 2:
			logger->PrintGameOver(LogEnum::GameEnd);	//�÷��̾��� ����� ���� ����� ���� ����� ��¹�
			return;
=======
			gameManager.BeginPlay();
			break;
		case 2:
			cout << "게임을 종료합니다..." << endl;
			return 0;
>>>>>>> GameManager
			break;
		default:
			logger->PrintInputError();	//�߸��� �Է� �ȳ� ���
		}
	}

<<<<<<< HEAD
	//���� ���� �ڵ�
	while (isGameStart)
	{
		break;
	}

	//���� ������ ������ ��
	logger->PrintGameOver(LogEnum::GameEnd);
	return;
=======
	return 0;
>>>>>>> GameManager
}