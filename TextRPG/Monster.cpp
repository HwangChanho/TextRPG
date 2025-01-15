#include "Monster.h"

static int GetRandomNumber(int n)
{
	//0 ~ n ������ ���� ��ȯ
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(1, n);
	int randomNumber = dist(gen);
	return randomNumber;
}

string BaseMonster::GetRandomItem() const
{
	if (dropTable.empty())
	{
		return "";
	}

	int totalProbabiility = 0;

	for (const auto& item : dropTable) 
	{
		totalProbabiility += item.first;
	}

	int randomValue = GetRandomNumber(totalProbabiility);
	int cumulativeProbability = 0;

	for (const auto& item : dropTable) 
	{
		cumulativeProbability += item.first;
		if (randomValue <= cumulativeProbability) 
		{
			return item.second;
		}
	}
	return "";
}

string BaseMonster::GetName()
{
	return this->name;
}

int BaseMonster::GetHealth() const
{
	return this->HP;
}

void BaseMonster::SetHealth(int health)
{
	this->HP = health;
}

int BaseMonster::GetDamage() const
{
	return this->attackPower;
}

void BaseMonster::SetDamage(int damage)
{
	this->attackPower = damage;
}

int BaseMonster::GetExperience() const
{
	return this->experience;
}

void BaseMonster::SetExperience(int experience)
{
	this->experience = experience;
}

int BaseMonster::GetGold() const
{
	return this->gold;
}

void BaseMonster::SetGold(int gold)
{
	this->gold = gold;
}

void BaseMonster::TakeDamage(int damage)
{
	this->HP -= damage;
	if (this->HP <= 0) {
		this->HP = 0;
	}
}

void NormalMonster::InitializeDropTable()
{
	dropTable.push_back({ 50,"Portion" });
	dropTable.push_back({ 50,"Rare Sword" });
}

void BossMonster::InitializeDropTable()
{
	dropTable.push_back({ 50,"Epic Sword" });
	dropTable.push_back({ 50,"Elixir" });
}

void Dragon::InitializeDropTable()
{
	dropTable.push_back({ 10,"Dragon Sword" });
	dropTable.push_back({ 10,"Dragon Heart" });
	dropTable.push_back({ 40,"Dragon Bone" });
	dropTable.push_back({ 40,"Dragon Skin" });
}

int NormalMonster::TakeAction() const
{
	// 1 -> ����
	// 2 -> ���
	Log* log = Log::GetInstance();
	int option = GetRandomNumber(2);
	string temp;

	if (option == 1)
	{
		//���� ���� ���
		temp = this->name;
		temp += "��(��) ������ �ɴϴ�.\n";
		log->PrintLog(temp, EJustString);
		return 1;
	}
	else if (option == 2)
	{
		//��� ���� ���
		temp = this->name;
		temp += "��(��) ������ ���Ƴ��� �մϴ�.\n";
		log->PrintLog(temp, EJustString);
		return 2;
	}
	return 0;
}

int BossMonster::TakeAction() const
{
	// 1 -> ����
	// 2 -> ���
	// 3 -> Ư�� ����
	Log* log = Log::GetInstance();
	int option = GetRandomNumber(3);
	string temp;

	if (option == 1)
	{
		//���� ���� ���
		temp = this->name;
		temp += "��(��) ������ �ɴϴ�.\n";
		log->PrintLog(temp,EJustString);
		return 1;
	}
	else if (option == 2)
	{
		//��� ���� ���
		temp = this->name;
		temp += "��(��) ������ ���Ƴ��� �մϴ�.\n";
		log->PrintLog(temp, EJustString);
		return 2;
	}
	else if (option == 3)
	{
		//Ư�� ���� ������ ���
		for (string s : characterResponseList) {
			temp += s;
		}
		log->PrintLog(temp, EJustString);
		return 3;
	}
}

int BossMonster::GetResponseScore(int option) const
{
	//�÷��̾��� ������ �Է� ���� �޾� �׿� ���� ���� ��ȯ
	return responseResultJudgment.at(option-1);
}

