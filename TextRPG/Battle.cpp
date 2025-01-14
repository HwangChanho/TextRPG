#include "Battle.h"
//Common




void Battle::restoreCharacterState(Character* player)
{
	player->SetAttackPower(CharacterData.Power);
	player->SetMaxHP(CharacterData.MaxHP);
}

void Battle::saveCharacterState(Character* player)
{
	CharacterData.Power = player->GetAttackPower();
	CharacterData.CurrentHP = player->GetCurrentHP();
	CharacterData.MaxHP = player->GetMaxHP();
}

void Battle::StageOfDifficulty()
{
}

void Battle::NextTurn()
{
	myTurn = !myTurn;
}

int Battle::Input(int min,int max)
{

	int input;
	cin >> input;
	if (min > input || max < input)
	{
		input = 0;
	}

	return input;
}
void Battle::Fight(Character* Player, BaseMonster* monster, int stage) // ����
{
	Log* logger = Log::GetInstance();
	this->battleMonster = monster;
	saveCharacterState(Player);
	std::string str = battleMonster->GetName() + "��(��) �����Ͽ���!\n";
	logger->PrintLog(str);
	while (!endBattle)
	{
		if (myTurn)
		{
			PlayerAction(Player);
			//�÷��̾���
		}
		else
		{
			MonsterAction(Player);
			//���� ��
		}

		NextTurn();
		isEndBattle(Player);
	}

	if (isWin)
	{
		LootAction(Player);
	}


}



void Battle::PlayerAction(Character* Player)
{
	Log* logger = Log::GetInstance();
	string str ="1.����\t2.�����ۻ��\n";
	logger->PrintLog(str);
	int choice = Input(1, 2);
	switch (choice)
	{
	case 1:
		AttackSystem(Player);
		break;
	case 2:
		//������
		break;
	default:
		break;
	}
}

void Battle::MonsterAction(Character* Player)
{
	Player->TakeDamage(battleMonster->GetDamage());

}

void Battle::LootAction(Character* Player)
{
	Player->TakeExp(battleMonster->GetExperience());
	Player->TakeGold(battleMonster->GetGold());
	//battleMonster.
}

void Battle::AttackSystem(Character* Player)
{
	

	cout << "1.�Ӹ�\t2.����\n";
	bool flag = false;

	while (!flag)
	{
		int choice = Input(1, 2);
		switch (choice)
		{
		case 1:

			battleMonster->TakeDamage(Player->GetAttackPower() * 1.2);
			flag = true;
			//log
			break;
		case 2:
			battleMonster->TakeDamage(Player->GetAttackPower());
			flag = true;
			//log
			break;
		default:
			cout << "�ٽ��Է�" << endl;
			break;
		}
	}
	

	
}

void Battle::isEndBattle(Character* Player)
{
	if (Player->GetCurrentHP() < 1 || battleMonster->GetHealth()<1)
	{
		endBattle = true;
	}

	if (endBattle)
	{
		if (Player->GetCurrentHP() > 0)
		{
			isWin = true;
		}
		else
		{
			isWin = false;
			Player = nullptr;
		}
	}
}
