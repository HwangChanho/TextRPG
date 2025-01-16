#include <iostream>
#include <string>

#include <windows.h>
#include <thread>
#include <format>

#include "GameManager.h"
#include "Log.h"
#include "Character.h"
#include "EnumCollection.h"
#include "shop.h"
#include "ProcessInput.h"
#include "HotKeyHandler.h"

using namespace std;

int main() 
{
	//SetConsoleOutputCP(CP_UTF8); // CMD �⺻ ���ڵ� ����
	std::thread inputThread(PI::ProcessInput);
	PI::isInputEnabled = false;

	try {
		using GM = GameManger::GameManger;
		GM& gameManager = GM::GetInstance();

		Log* logger = Log::GetInstance();
		logger->Initialize();

		// Debug
		//Character player1 = *new Character("���ǵ� ���");
		//Shop shop;
		//gameManager.VisitShop(&player1);

		int menuOption;
		bool isGameRun = false;		//������ ���࿩��
		bool isGameStart = false;	//���Ӹ޴� Ż������ ����
		string characterName;

		bool namingFlag = false;

		while (true) {
			if (namingFlag)
			{
				logger->PrintLog("���� �ȵǴ� �̸��Դϴ�....\n����� �����Դϱ�?\n");
			}
			else
			{
				logger->PrintLog("... ����� �����Դϱ�?\n");
			}

			PI::ClearInputBuffer();
			PI::isInputEnabled = true;
			getline(cin, characterName);
			PI::isInputEnabled = false;

			if (characterName.length() > 0 && characterName.length() <= 10) {
				logger->PrintLog("���� �̸���? " + characterName + "\n");
				break;
			}
			else
			{
				namingFlag = true;
			}

			// system("pause"); TODO: ���� �̻ڰ� �ϱ����� ���
		}

		Character player1 = *new Character(characterName);
		std::thread hotkeyThread(HotkeyHandler, std::ref(player1));

		// 1. ���ӽ���, 2. ����
		while (!isGameStart)
		{
			logger->PrintStartMenu(EMenu);
			PI::ClearInputBuffer();
			PI::isInputEnabled = true;
			cin >> menuOption;
			PI::isInputEnabled = false;
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

		PI::isRunning = false;
		inputThread.join();
		hotkeyThread.join();
	}
	catch (...) {
		// ������ ����� ������ ����
		PI::isRunning = false;
		inputThread.join();
	}

	

	return 0;
}