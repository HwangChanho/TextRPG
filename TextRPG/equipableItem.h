#pragma once
#include "BaseEquipableItem.h"
#include "Character.h"
#include <string>
#include<map>

using namespace std;

class EquipableItem :public BaseEquipableItem
{
private:
	string equipType;//����,��
	map<string, int> baseStat;
	int enchantLevel;
	bool isEquipping;
public:
	EquipableItem(string name, int price, int rarity, string equipType, map<string, int>baseStat, int enchantLevel)
		:BaseEquipableItem(name, price, rarity, "EquipableItem"), equipType(equipType), baseStat(baseStat), enchantLevel(enchantLevel) {
	}

	string GetEquipType()
	{
		return equipType;
	}
	map<string, int> GetBaseStat()
	{
		return baseStat;
	}
	int GetEnchantLevel()
	{
		return enchantLevel;
	}
	void SetEnchantLevel(int level)
	{
		enchantLevel = level;
	};

	bool IsEquipping() {
		return isEquipping;
	}
	void SetEquipping(bool equipping) {
		isEquipping = equipping;
	}
	string GetName()override
	{
		return isEquipping ? BaseEquipableItem::GetName() + " (Equipping)" : BaseEquipableItem::GetName();
	}


	void EquipEffect(Character& player)
	{
		//��� ȿ�� ���� BaseStat�� ĳ���Ϳ��� ����
	}


};