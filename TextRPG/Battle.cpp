#include "Battle.h"
//Common

void Battle::NextTrun(bool& turn)
{
	turn = !&turn;
}



//Normal


void NormalBattle::Fight(Character* Player, NormalMonster* monster, int stage)
{
//	Data = monster;

	while (!endBattle)
	{
		if (myTurn)
		{
			PlayerAction();
			//�÷��̾���
		}
		else
		{
			//���� ��
		}


	}


	cout << "�Ϲ� ����" << endl;
	Player->TakeExp(10);

}

void NormalBattle::PlayerAction()
{
}

void NormalBattle::MonsterAction()
{
}




//Named

void NamedBattle::Fight(Character* Player, NormalMonster* monster, int stage)
{
	cout << "���ӵ� ����" << endl;
	Player->TakeExp(20);

}



//Boss
//
//void BossBattle::Fight(Character* Player, NormalMonster* monster, int stage)
//{
//
//	cout << "���� ����" << endl;
//	Player->TakeExp(30);
//
//}
