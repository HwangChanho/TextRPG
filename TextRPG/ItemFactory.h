#ifndef ITEMFACTORY_H_
#define ITEMFACTORY_H_

#include "Item.h"
#include "ConsumableItem.h"
#include "EquipableItem.h"
#include <iostream>
//#include <vector>
#include <algorithm>
#include <random>

enum ItemList
{
	���谡�����,		// ���۾�����

	�������,
	�����,
	����ǳ����ܰ�,

	��������ǹ���,	//���� ���� ������ ����Ȯ���� ���, ItemType=Archive, ���ݷ� 10 ����
};

class ItemFactory
{
public:
	static ItemFactory& GetInstance();

	map<string, Item*> items;
	Item* GenerateItem(string itemName);
	//Item* GenerateItem(enum ItemList itemList);
	vector<Item*> GenerateRandomItems(int count);

private:
	static ItemFactory* instance;

	ItemFactory();
	~ItemFactory();
	ItemFactory(const ItemFactory&) = delete;
	ItemFactory& operator=(const ItemFactory&) = delete;
};

#endif // !ITEMFACTORY_H_

