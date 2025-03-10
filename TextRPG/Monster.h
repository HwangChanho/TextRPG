#pragma once
#include <string>
#include <map>
#include <vector>
#include <random>
#include <iostream>
#include "Log.h"

using namespace std;

class Monster 
{
public:
	virtual string GetName() = 0;
	virtual int GetHealth() const = 0;
	virtual void SetHealth(int health) = 0;
	virtual int GetDamage() const = 0;
	virtual void SetDamage(int damage) = 0;
	virtual int GetExperience() const = 0;
	virtual void SetExperience(int experience) = 0;
	virtual int GetGold() const = 0;
	virtual void SetGold(int gold) = 0;
	virtual void TakeDamage(int damage) = 0;
	virtual int TakeAction() const = 0;
	virtual string GetRandomItem() const = 0;
	virtual int GetResponseScore(int option) const = 0;
	virtual vector<string> GetcharacterResponseList() const = 0;
};

class BaseMonster : public Monster
{
protected:
	string name;
	int HP;
	int attackPower;
	int experience;
	int gold;
	vector<pair<int, string>> dropTable;
	vector<string> characterResponseList = {};
	virtual void InitializeDropTable() = 0;

public:
	BaseMonster(string n, int hp, int atk, int exp, int g) :
		name(n), HP(hp), attackPower(atk), experience(exp), gold(g) {}
	string GetName() override;
	int GetHealth() const override;
	void SetHealth(int health) override;
	int GetDamage() const override;
	void SetDamage(int damage) override;
	int GetExperience() const override;
	void SetExperience(int experience) override;
	int GetGold() const override;
	void SetGold(int gold) override;
	void TakeDamage(int damage) override;
	string GetRandomItem() const override;
	vector<string> GetcharacterResponseList() const override;
};

class NormalMonster : public BaseMonster 
{
protected:
	void InitializeDropTable() override;

public:
	NormalMonster(string n, int hp, int atk, int exp, int g)
		: BaseMonster(n, hp, atk, exp, g) {InitializeDropTable();}
	int TakeAction() const override;
	int GetResponseScore(int option) const override;
	vector<string> GetcharacterResponseList() const override;

};

class Goblin : public NormalMonster 
{
public:
	Goblin() : NormalMonster("Goblin", 100, 15, 20, 25) { dropTable.push_back({ 10,"고블린귀" }); }
};

class Orc : public NormalMonster 
{
public:
	Orc() : NormalMonster("Orc", 100, 15, 20, 25) { dropTable.push_back({ 10,"오크의머리털" }); }
};

class Troll : public NormalMonster
{
public:
	Troll() : NormalMonster("Troll", 100, 15, 20, 25) { dropTable.push_back({ 10,"트롤의송곳니" }); }
};

class Wolf : public NormalMonster 
{
public:
	Wolf () : NormalMonster("Wolf", 100, 15, 20, 25) { dropTable.push_back({ 10,"늑대발톱" }); }
};

class Slime : public NormalMonster 
{
public:
	Slime() : NormalMonster("Slime", 100, 15, 20, 25) { dropTable.push_back({ 10,"슬라임의점액질" }); }
};

class BossMonster : public BaseMonster 
{
protected:
	vector<string> characterResponseList;
	vector<int> responseResultJudgment;
	/*1 -> Good
	2 -> Soso
	3 -> Bad*/
	void InitializeDropTable() override;

public:
	BossMonster(string n, int hp, int atk, int exp, int g) :
		BaseMonster(n, hp, atk, exp, g) {InitializeDropTable();}
	int TakeAction() const override;
	int GetResponseScore(int option) const override;
	vector<string> GetcharacterResponseList() const override;
};

class GoblinRider : public BossMonster 
{
public:
	GoblinRider() : BossMonster("GoblinRider", 500, 30, 50, 100) {
		
		characterResponseList.clear();
		characterResponseList.push_back("고블린 라이더가 활을 꺼내 시위를 당긴다. 당신의 선택은?\n");
		characterResponseList.push_back("1. 구르며 고블린 라이더에게 접근한다.");
		characterResponseList.push_back("2. 무기로 쳐낸다.");
		characterResponseList.push_back("3. 엎드린다.");
		responseResultJudgment.push_back(1);
		responseResultJudgment.push_back(3);
		responseResultJudgment.push_back(2);
		dropTable.push_back({ 10,"고블린라이더의안장" });
		dropTable.push_back({ 10,"고블린족장의유물" });
	}
};

class TwinHeadTroll : public BossMonster 
{
public:
	TwinHeadTroll() : BossMonster("TwinHeadTroll", 500, 30, 50, 100) {
		
		characterResponseList.clear();
		characterResponseList.push_back("트윈 헤드 트롤이 크게 숨을 들이마신다. 당신의 선택은?\n");
		characterResponseList.push_back("1. 뒤로 돌아 뛴다.");
		characterResponseList.push_back("2. 귀를 막고 트윈 헤드 트롤에게 돌진한다.");
		characterResponseList.push_back("3. 트윈 헤드 트롤에게 빠르게 돌진한다.");
		responseResultJudgment.push_back(2);
		responseResultJudgment.push_back(1);
		responseResultJudgment.push_back(3);
		dropTable.push_back({ 10,"트윈헤드트롤의두개골" });
		dropTable.push_back({ 10,"트롤의심장" });
	}
};

class Treant : public BossMonster 
{
public:
	Treant() : BossMonster("Treant", 500, 30, 50, 100) {
		
		characterResponseList.clear();
		characterResponseList.push_back("트렌트가 온몸에서 가시가 돋아나기 시작했다. 당신의 선택은?\n");
		characterResponseList.push_back("1. 트렌트에게 돌진한다.");
		characterResponseList.push_back("2. 뒤로 빠르게 뛴다.");
		characterResponseList.push_back("3. 주변의 지형지물에 엄폐한다.");
		responseResultJudgment.push_back(3);
		responseResultJudgment.push_back(2);
		responseResultJudgment.push_back(1);
		dropTable.push_back({ 10,"엔트의씨앗" });
		dropTable.push_back({ 10,"트렌트의열매" });
	}
};

class Dragon : public BossMonster 
{
protected:
	void InitializeDropTable() override;

public:
	Dragon() : BossMonster("Dragon", 1000, 50, 777, 777) {
		dropTable.clear();
		characterResponseList.clear();

		InitializeDropTable();
		characterResponseList.push_back("드래곤의 뺨이 부풀어 오르기 시작했다. 당신의 선택은?\n");
		characterResponseList.push_back("1. 드래곤에게 돌진해 턱밑을 찌른다.\n");
		characterResponseList.push_back("2. 몸을 던져 구른다.\n");
		characterResponseList.push_back("3. 주변의 지형지물에 엄폐한다.\n");
		responseResultJudgment.push_back(1);
		responseResultJudgment.push_back(2);
		responseResultJudgment.push_back(3);
	}
};