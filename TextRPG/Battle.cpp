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
	logger->PrintLog(battleMonster->GetName() + "��(��) �����ߴ�!\n");
	while (!endBattle)
	{
		logger->PrintLog("�÷��̾� ü�� :" + to_string(Player->GetCurrentHP()) + " : " + to_string(Player->GetMaxHP()) + " �÷��̾� ���ݷ� : " + to_string(Player->GetAttackPower())+"\n");
		logger->PrintLog(battleMonster->GetName() + " ü�� : " + to_string(battleMonster->GetHealth()) + " ���ݷ� : " + to_string(battleMonster->GetDamage())+"\n");
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
	logger->PrintLog("������ �ؾ��ұ�?\n1.����\t2.�����ۻ��\n");
	int choice = Input(1, 2);
	switch (choice)
	{
	case 1:
		AttackSystem(Player);
		break;
	case 2:
		logger->PrintLog("�����ۻ��!\n");
		//������
		break;
	default:
		break;
	}
}

void Battle::MonsterAction(Character* Player)
{
	Log* logger = Log::GetInstance();
	
	Player->TakeDamage(battleMonster->GetDamage());
	logger->PrintLog(battleMonster->GetName() + "��(��) �����ߴ�!\n");
	logger->PrintLog("�÷��̾ " + to_string(battleMonster->GetDamage()) + "�� ���ظ� �Ծ���.\n");
	

}

void Battle::LootAction(Character* Player)
{
	Player->TakeExp(battleMonster->GetExperience());
	Player->TakeGold(battleMonster->GetGold());
	//battleMonster.
}

bool Battle::RandomSuccess(int probability)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(1, 100);
	if (dist(gen) <= probability)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Battle::AttackSystem(Character* Player)
{
	Log* logger = Log::GetInstance();
	logger->PrintLog("������� �����ұ�?\n1.�Ӹ�(40%)\t2.����(80%)\n");
	bool flag = false;
	bool isHit;
	while (!flag)
	{
		int choice = Input(1, 2);
		switch (choice)
		{
		case 1:
			isHit = RandomSuccess(40);
			if (isHit)
			{
				battleMonster->TakeDamage(Player->GetAttackPower() * 2);
				logger->PrintLog("�Ӹ� ������ �����ߴ�!\n");
				logger->PrintLog(battleMonster->GetName() + "��(��)"+ to_string(Player->GetAttackPower() * 2)+"�� ġ������ ���ظ� �Ծ���!\n");
			}
			else
			{
				logger->PrintLog("������ ��������.\n");
				logger->PrintLog(battleMonster->GetName() + "��(��) ���ظ� ���� �ʾҴ�.\n");
			}
			
			flag = true;
			//log
			break;
		case 2:
			isHit = RandomSuccess(80);
			if (isHit)
			{
				battleMonster->TakeDamage(Player->GetAttackPower() * 2);
				logger->PrintLog("������ �����ߴ�!\n");
				logger->PrintLog(battleMonster->GetName() + "��(��)" + to_string(Player->GetAttackPower()) + "�� ���ظ� �Ծ���!\n");
			}
			else
			{
				logger->PrintLog("������ ��������.\n");
				logger->PrintLog(battleMonster->GetName() + "��(��) ���ظ� ���� �ʾҴ�.\n");
			}
			flag = true;
			//log
			break;
		default:
			logger->PrintLog("�Է� ���� ���� �ٽ� �����ϼ���.\n");
			break;
		}
	}
	

	
}

void Battle::isEndBattle(Character* Player)
{
	Log* logger = Log::GetInstance();
	if (Player->GetCurrentHP() < 1 || battleMonster->GetHealth()<1)
	{
		endBattle = true;
	}

	if (endBattle)
	{
		if (Player->GetCurrentHP() > 0)//�¸�
		{
			logger->PrintLog("�������� �¸��ߴ�!\n");
			isWin = true;
		}
		else //�й�
		{
			logger->PrintLog("�÷��̾� ���.\n");
			isWin = false;
			Player = nullptr;
		}
	}
}
