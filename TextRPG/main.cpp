#include <iostream>

#include "GameManager.h"
#include "Log.h"
#include "Character.h"
#include "EnumCollection.h"

using namespace std;

int main() 
{
	SetConsoleOutputCP(CP_UTF8); // CMD �⺻ ���ڵ� ����

	// �������� �ε�

	using GM = GameManger::GameManger;

	GM& gameManager = GM::GetInstance();

	Log* logger = Log::GetInstance();
	logger->Initialize();
	Character player1 = *new Character("���ǵ� ���");

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