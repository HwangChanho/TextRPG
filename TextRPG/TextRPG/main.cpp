#include <iostream>

#include "GameManager.h"

using namespace std;

void main() 
{
	using GM = GameManger::GameManger;

	GM& gameManager = GM::GetInstance();

	// ��Ʋ �Ŵ���, �ɸ��� ����
	gameManager.GenerateBattleManager();
	Character player1 = gameManager.GenerateCharacter();

	int menuOption;

	// 1. ���ӽ���, 2. ����
	while (true) 
	{
		cout << "���� �޴�" << endl;
		cout << "1. ���ӽ���" << endl;
		cout << "2. ��������" << endl;
		cin >> menuOption;

		switch (menuOption) {
		case 1:
			gameManager.BeginPlay();
			break;
		case 2:
			cout << "������ �����մϴ�..." << endl;
			return;
			break;
		default:
			cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
		}
	}

	return;
}