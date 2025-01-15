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
	//SetConsoleOutputCP(CP_UTF8); // CMD 기본 인코딩 설정

	using GM = GameManger::GameManger;
	GM& gameManager = GM::GetInstance();

	Log* logger = Log::GetInstance();
	logger->Initialize();
	
	// Debug
	//Character player1 = *new Character("정의된 용사");
	//Shop shop;
	//gameManager.VisitShop(&player1);
	
	int menuOption;
	bool isGameRun = false;		//게임의 실행여부
	bool isGameStart = false;	//게임메뉴 탈출조건 위함
	string characterName;

	while (true) {
		logger->PrintLog("... 당신은 누구입니까?\n");
		getline(cin, characterName);

		if (characterName.length() >= 0 && characterName.length() <= 10) {
			logger->PrintLog("너의 이름은? " + characterName + "\n");
			break;
		}
		else {
			logger->PrintLog("말도 안되는 이름입니다.\n");
		}
	}

	Character player1 = *new Character(characterName);
	// 1. 게임시작, 2. 종료
	while (!isGameStart)
	{
		logger->PrintStartMenu(EMenu);
		cin >> menuOption;
		switch (menuOption) {
		case 1:
			isGameStart = true;	//시작화면 루프 벗어나기 위함
			isGameRun = true;	//게임 시작
			logger->PrintStartMenu(EStart);
			gameManager.BeginPlay(&player1);
			break;
		case 2:
			logger->PrintGameOver(EGameEnd);	//플레이어의 사망과 게임 재시작 여부 물어보는 출력문
			return 0;
			break;
		default:
			logger->PrintInputError();	//잘못된 입력 안내 출력
		}
	}

	//게임 실행이 끝났을 때
	logger->PrintGameOver(EGameEnd);
	return 0;
}