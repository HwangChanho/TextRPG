﻿#include "Character.h"
#include "Item.h"
#include "ItemFactory.h"
#include "ConsumableItem.h"
#include "EquipableItem.h"
#include "Log.h"
#include <format>
#include <iostream>

using namespace std;

Character::Character(const string& name)
{
	this->name = name;
	DisplayStatus();
	InitEquipMentItem();
	//DisplayStatus();

	//cout << "캐릭터 " << name << " 생성 완료!";
	//cout << " 레벨 : " << level << ", 체력 : " << currentHP << " / " << maxHP << ", 공격력 : " << attackPower << endl;
}

void Character::InitEquipMentItem()
{
	Item* startItem = ItemFactory::GetInstance().GenerateItem("모험가의장검");
	TakeItem(startItem);
	EquipItem(dynamic_cast<EquipableItem*>(startItem));
	DisplayStatus();

	//Item* archiveItem = ItemFactory::GetInstance().GenerateItem("고블린족장의유물");
	//TakeItem(archiveItem);
	//DisplayStatus();

	//Item* trollsBlood = ItemFactory::GetInstance().GenerateItem("트롤의심장");
	//TakeItem(trollsBlood);
	//DisplayStatus();

	//Item* lowAttackBooster = ItemFactory::GetInstance().GenerateItem("LowAttackPotion");
	//Item* middleAttackBooster = ItemFactory::GetInstance().GenerateItem("MiddleAttackPotion");

	//TakeItem(lowAttackBooster);
	//TakeItem(middleAttackBooster);

	//UseItem("LowAttackPotion");
}

Character::~Character() {}

void Character::DisplayStatus()
{
	Log::GetInstance()->PrintLog(GetCharacterStatusString(), false);
}

const string Character::GetCharacterStatusString()
{
	string returnValue;
	returnValue += format("이름 : {}\n", name);
	returnValue += format("레벨 : {}\n", level);
	returnValue += format("HP : {}/{}\n", currentHP, GetMaxHP());
	returnValue += format("공격력 : {}\n", GetAttackPower());
	//returnValue += format("방어력 : {}\n", armor);
	returnValue += format("Gold : {}\n", gold);
	returnValue += format("경험치 : {}/{}\n", currentExp, requiredLevelUpExp);

	return returnValue;
}


const int& Character::GetCurrentHP() { return this->currentHP; }
const int& Character::GetMaxHP()
{
	int calculateMaxHP = this->maxHP + equipmentBuffStat.maxHP + archiveBuffStat.maxHP + buffStat.maxHP;
	return calculateMaxHP;
}

const int& Character::GetAttackPower()
{
	int calculateAP = this->attackPower + equipmentBuffStat.attackPower + archiveBuffStat.attackPower + buffStat.attackPower;
	return calculateAP;
}
const int& Character::GetRequiredLevelUpExp() { return this->requiredLevelUpExp; }

void Character::SetCurrentHP(int hp)
{
	if (hp > maxHP)
	{
		this->currentHP = maxHP;
	}
	else
	{
		this->currentHP = hp;
	}
}
void Character::SetMaxHP(int hp)
{
	this->maxHP = hp;
}
void Character::AddMaxHP(int amount)
{
	this->maxHP += amount;
}
void Character::SetAttackPower(int attackPower)
{
	this->attackPower = attackPower;
}
void Character::AddAttackPower(int amount)
{
	this->attackPower += amount;
}

void Character::TakeDamage(const int& damage)
{
	// TODO : 방어력에 대한 데미지 계산식 적용
	currentHP -= damage;
}

void Character::TakeExp(const int& exp)
{
	currentExp += exp;
	if (currentExp >= requiredLevelUpExp)
	{
		LevelUp();
	}
}

void Character::TakeGold(const int& gold)
{
	this->gold += gold;
}


// ========== 인벤토리 및 아이템 상점관련 ==========
map<string, class Inventory> Character::GetInventory()
{
	return this->inventory;
}

vector<Inventory> Character::GetInventoryItems(enum class ItemType type)
{
	vector<Inventory> inventoryItems;

	switch (type)
	{
	case ItemType::Unknown:
		for (auto inventory : inventory)
		{
			inventoryItems.push_back(inventory.second);
		}
		break;
	case ItemType::Equipable:
	case ItemType::Consumable:
	case ItemType::Archive:
	case ItemType::Default:
		for (auto inventory : inventory)
		{
			if (inventory.second.itemType == type)
			{
				inventoryItems.push_back(inventory.second);
			}
		}
		break;
	default:
		break;
	}
	return inventoryItems;
}

void Character::DisplayInventory()
{
	//Log* logger = Log::GetInstance();
	//Log::GetInstance()->PrintLog("The shop is out of items!\n", (int)EShop, false);

	//cout << "======= 인벤토리 목록 =======" << endl;
	int index = 1;
	for (auto item : inventory)
	{
		cout << format("{}. {}, 수량:{}", index, item.second.item->name, item.second.Count) << endl;
		index++;
	}

}

const int& Character::GetGold() { return this->gold; }

void Character::TakeItem(Item* item)
{
	string itemName = item->GetName();
	if (inventory.find(itemName) == inventory.end())
	{
		inventory[itemName] = Inventory(item, item->GetType(), 1);

		if (inventory[itemName].itemType == ItemType::Archive)
		{
			archiveBuffStat += dynamic_cast<ArchiveItem*>(item)->GetBuffStat();
			Log::GetInstance()->PrintLog("Archive 아이템이 추가됐습니다.\n", false);
		}

		//cout << format("신규 아이템이 추가됐습니다!! 아이템 이름 : {}, 개수 : {}", itemName, inventory[itemName].Count) << endl;
	}
	else
	{
		inventory[itemName].Count++;
		if (inventory[itemName].itemType == ItemType::Archive)
		{
			archiveBuffStat += dynamic_cast<ArchiveItem*>(item)->GetBuffStat();
		}
		//cout << format("기존 아이템 개수가 추가됐습니다!! 아이템 이름 : {}, 개수 : {}", itemName, inventory[itemName].Count) << endl;
	}
}

void Character::UseItem(const string& itemKey)
{
	if (inventory.find(itemKey) == inventory.end())
	{
		throw ExceptionHandler(ErrorCode::Unknown, "아이템이 없습니다.");
	}
	else
	{
		Inventory selectedItem = inventory[itemKey];
		if (selectedItem.itemType == ItemType::Consumable)
		{
			ConsumableItem* cosumableItem = dynamic_cast<ConsumableItem*>(selectedItem.item);
			cosumableItem->ConsumeEffect(*this);

			ReduceInventory(itemKey);
		}
		else
		{
			throw ExceptionHandler(ErrorCode::Unknown, "소비 아이템이 아닙니다.");
		}
	}
}

void Character::BuyItem(Item* item)
{
	if (gold < item->GetPrice())
	{
		// cout << "소지 골드가 부족합니다"
	}
	else
	{
		gold -= item->GetPrice();
		TakeItem(item);
	}
}

void Character::SellItem(string itemKey)
{
	if (inventory.find(itemKey) == inventory.end())
	{
		throw ExceptionHandler(ErrorCode::Unknown, "아이템이 없습니다.");
	}
	else
	{
		Inventory selectedItem = inventory[itemKey];
		gold += selectedItem.item->GetPrice();

		ReduceInventory(itemKey);
	}
}

void Character::ReduceInventory(const string& itemKey)
{
	Inventory& selectedItem = inventory[itemKey];
	selectedItem.Count--;

	//cout << "인벤토리의 아이템이 감소됐습니다!\n"
	//	<< format("이름 : {}, 수량 : {}", selectedItem.item->GetName(), selectedItem.Count) << endl;

	if (selectedItem.Count == 0)
	{
		inventory.erase(itemKey);
		//cout << "인벤토리에서 아이템 항목을 제거합니다!" << endl;
	}
}

void Character::TurnEnd()
{
	TryRemoveBuff();
}

void Character::TryAddBuff(BuffBase& buffBase)
{
	// Log::GetInstance()->PrintLog(format("Buff가 발동했습니다! 지속시간 : {}\n", buffBase.duration), false);
	if (buffBase.duration == 0)
	{
		// Log::GetInstance()->PrintLog(format("Buff가 아무런 도움이 되지 않습니다.\n"), false);
	}
	else
	{
		buffContainer.push_back(buffBase);
		buffStat += buffBase.buffStat;

		string temp = format("Buff 효과 발동!!\n");
		if (buffBase.buffStat.attackPower != 0)
		{
			temp += format("Attack Power Up!! : {}\n", buffBase.buffStat.attackPower);
		}

		if (buffBase.buffStat.armor != 0)
		{
			temp += format("Armor Up!! : {}\n", buffBase.buffStat.armor);
		}

		if (buffBase.buffStat.maxHP != 0)
		{
			temp += format("Max HP Up!! : {}\n", buffBase.buffStat.maxHP);
		}

		// Log::GetInstance()->PrintLog(temp, false);
		DisplayStatus();
	}
}

void Character::TryRemoveBuff()
{
	for (auto it = buffContainer.begin(); it != buffContainer.end(); )
	{
		it->duration--;
		if (it->duration <= 0)
		{
			auto removedBuff = *it;
			buffStat -= removedBuff.buffStat;

			Log::GetInstance()->PrintLog(format("Buff의 지속시간이 끝났습니다!\n"), false);
			DisplayStatus();

			it = buffContainer.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Character::EquipItem(EquipableItem* equipableItem)
{
	if (equipItemContainer.size() > 0)
	{
		for (auto equipedItem : equipItemContainer)
		{
			if (equipItemContainer.find(equipedItem.first) == equipItemContainer.end())
			{

			}
			else
			{
				equipedItem.second->SetEquipping(false);
				equipmentBuffStat -= equipedItem.second->GetBuffStat();
				equipItemContainer.erase(equipedItem.first);
			}

			equipItemContainer[equipableItem->GetType()] = equipableItem;
			equipmentBuffStat += equipableItem->GetBuffStat();
			equipableItem->SetEquipping(true);
		}
	}
	else
	{
		equipItemContainer[equipableItem->GetType()] = equipableItem;
		equipmentBuffStat += equipableItem->GetBuffStat();
		equipableItem->SetEquipping(true);
		Log::GetInstance()->PrintLog("장비아이템이 장착됐습니다!\n", false);
	}
}

int Character::GetEquipAddAmount()
{
	return 0;
}



void Character::LevelUp()
{
	if (level < maxLevel)
	{
		currentExp -= requiredLevelUpExp;

		IncreaseMaxHP(level);
		IncreaseAttackPower(level);
		IncreaseRequireLevelUpExp(level);

		level++;
		if (level == maxLevel)
		{
			currentExp = requiredLevelUpExp;
			//cout << "최대 레벨에 도달했습니다." << endl;
		}
	}
	else
	{

	}
}

void Character::IncreaseMaxHP(const int& level)
{
	maxHP += level * 20;
}

void Character::IncreaseAttackPower(const int& level)
{
	attackPower += level * 5;
}

void Character::IncreaseRequireLevelUpExp(const int& level)
{
	requiredLevelUpExp += level * 10;
}

