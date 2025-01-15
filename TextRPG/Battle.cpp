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

void Battle::StageOfDifficulty(int stage)
{
	float multiple = 0.05*stage;
	multiple = multiple + 1.0f;
	battleMonster->SetHealth(battleMonster->GetHealth() * multiple);
	battleMonster->SetExperience(battleMonster->GetExperience() * multiple);
	battleMonster->SetDamage(battleMonster->GetDamage() * multiple);
	battleMonster->SetGold(battleMonster->GetGold() * multiple);
}

void Battle::NextTurn()
{

	myTurn = !myTurn;
}

int Battle::Input(int min,int max)
{
	Log* logger = Log::GetInstance();
	int input;
	cin >> input;
	if (min > input || max < input)
	{
		input = 0;
		logger->PrintLog("�Է� ���� ���� �ٽ� �����ϼ���.\n", false);

	}

	return input;
}
void Battle::Fight(Character* Player, BaseMonster* monster, int stage) // ����
{
	Log* logger = Log::GetInstance();
	BattleManager* BM = BattleManager::GetInstance();
	this->battleMonster = monster;
	StageOfDifficulty(stage);
	saveCharacterState(Player);
	logger->PrintLog(battleMonster->GetName() + "��(��) �����ߴ�!\n", BM->getMonsterImage(), false);
	Sleep(1000);
	while (!endBattle)
	{
		//logger->PrintLog();
		logger->PrintLog("", BM->getMonsterImage(), true);
		logger->PrintLog("�÷��̾� ü�� :" + to_string(Player->GetCurrentHP()) + " : " + to_string(Player->GetMaxHP()) + " �÷��̾� ���ݷ� : " + to_string(Player->GetAttackPower())+"\n",false);
		logger->PrintLog(battleMonster->GetName() + " ü�� : " + to_string(battleMonster->GetHealth()) + " ���ݷ� : " + to_string(battleMonster->GetDamage())+"\n",false);
		if (myTurn)
		{
			PlayerAction(Player);
			Sleep(2000);

			//�÷��̾���
		}
		else
		{
			Sleep(1500);

			MonsterAction(Player);
			//���� ��
			Sleep(2500);
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
	logger->PrintLog("������ �ؾ��ұ�?\n1.����\t2.�����ۻ��\n",false);
	int choice = Input(1, 2);
	switch (choice)
	{
	case 1:
		AttackSystem(Player);
		break;
	case 2:
		logger->PrintLog("�����ۻ��!\n",false);
		//������
		break;
	default:
		break;
	}
}

void Battle::MonsterAction(Character* Player)
{
	Log* logger = Log::GetInstance();
	
	
	//logger->PrintLog(battleMonster->GetName() + "��(��) �����ߴ�!\n",false);

	state = (MonsterState)battleMonster->TakeAction();
	switch (state)
	{
	case Enums::EAttack:
		Player->TakeDamage(battleMonster->GetDamage());
		logger->PrintLog("�÷��̾ " + to_string(battleMonster->GetDamage()) + "�� ���ظ� �Ծ���.\n", false);

		break;
	case Enums::EDefence:

		break;

	case Enums::EMonsterSkill:
		MonsterSkill(Player);
		break;

	default:
		break;
	}
	//logger->PrintLog();

	

}

void Battle::MonsterSkill(Character* Player) // Ư������
{
	Log* logger = Log::GetInstance();
	int choice = Input(1, 3);
	while (choice==0)
	{
		choice = Input(1, 3);
	}

	int result = battleMonster->GetResponseScore(choice);
	if (result==1)
	{
		battleMonster->TakeDamage(Player->GetAttackPower() * 3);
		logger->PrintLog("���� �����̾���!\n", false);
		logger->PrintLog(battleMonster->GetName() + "��(��)" + to_string(Player->GetAttackPower() * 3) + "�� ġ������ ���ظ� �Ծ���!\n", false);

	}
	else if (result == 2)
	{
		logger->PrintLog("������ ���� �����̾���!\n", false);
		logger->PrintLog(battleMonster->GetName() + " ���� ���ظ� ���� �ʾҴ�.\n", false);

	}
	else
	{
		Player->TakeDamage(battleMonster->GetDamage()*2);
		logger->PrintLog("���� �����̾���.\n", false);
		logger->PrintLog("�÷��̾ " +battleMonster->GetName()+" "+ to_string(battleMonster->GetDamage()*2) + "�� ġ������ ���ظ� �Ծ���.\n", false);

	}

	
}

void Battle::LootAction(Character* Player)
{
	Player->TakeExp(battleMonster->GetExperience());
	Player->TakeGold(battleMonster->GetGold());
	string item = battleMonster->GetRandomItem();
	//Player->TakeItem()
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
	logger->PrintLog("������� �����ұ�?\n1.�Ӹ�(40%)\t2.����(80%)\n",false);
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
				logger->PrintLog("�Ӹ� ������ �����ߴ�!\n",false);
				logger->PrintLog(battleMonster->GetName() + "��(��)"+ to_string(Player->GetAttackPower() * 2)+"�� ġ������ ���ظ� �Ծ���!\n",false);
			}
			else
			{
				logger->PrintLog("������ ��������.\n",false);
				logger->PrintLog(battleMonster->GetName() + "��(��) ���ظ� ���� �ʾҴ�.\n",false);
			}
			
			flag = true;
			//log
			break;
		case 2:
			isHit = RandomSuccess(80);
			if (isHit)
			{
				battleMonster->TakeDamage(Player->GetAttackPower() * 2);
				logger->PrintLog("������ �����ߴ�!\n",false);
				logger->PrintLog(battleMonster->GetName() + "��(��)" + to_string(Player->GetAttackPower()) + "�� ���ظ� �Ծ���!\n",false);
			}
			else
			{
				logger->PrintLog("������ ��������.\n",false);
				logger->PrintLog(battleMonster->GetName() + "��(��) ���ظ� ���� �ʾҴ�.\n",false);
			}
			flag = true;
			//log
			break;
		default:
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
			logger->PrintLog("�������� �¸��ߴ�!\n", false);
			isWin = true;
			Sleep(2000);

		}
		else //�й�
		{
			logger->PrintLog("�÷��̾� ���.\n",false);
			isWin = false;
			Player = nullptr;
			Sleep(2000);

		}
	}
}
