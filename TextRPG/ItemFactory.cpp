#include "ItemFactory.h"
#include "format"

#pragma region ItemDefine

#pragma endregion

ItemFactory* ItemFactory::instance = nullptr;
ItemFactory& ItemFactory::GetInstance()
{
	if (instance == nullptr)
		instance = new ItemFactory();

	return *instance;
}

ItemFactory::ItemFactory()
{
	// Insert Consumable Item
	// Heal Potion
	items.insert(make_pair("�ϱ�ü��ȸ������", new ConsumableItem("�ϱ�ü��ȸ������", 50, Rarity::C, EffectType::HealCurrentHP, 30)));
	items.insert(make_pair("�߱�ü��ȸ������", new ConsumableItem("�߱�ü��ȸ������", 100, Rarity::R, EffectType::HealCurrentHP, 50)));
	items.insert(make_pair("���ü��ȸ������", new ConsumableItem("���ü��ȸ������", 200, Rarity::SR, EffectType::HealCurrentHP, 100)));

	//Attack Power Up Potion
	items.insert(make_pair("�ϱް��ݺν���", new ConsumableItem("�ϱް��ݺν���", 20, Rarity::C, EffectType::DamageUp, 30, 3)));
	items.insert(make_pair("�߱ް��ݺν���", new ConsumableItem("�߱ް��ݺν���", 40, Rarity::R, EffectType::DamageUp, 50, 5)));
	items.insert(make_pair("��ް��ݺν���", new ConsumableItem("��ް��ݺν���", 60, Rarity::SR, EffectType::DamageUp, 100, 7)));

	// Elixir
	items.insert(make_pair("�ϱ޿�����", new ConsumableItem("�ϱ޿�����", 50, Rarity::C, EffectType::IncreaseMaxHP, 100)));
	items.insert(make_pair("�߱޿�����", new ConsumableItem("�߱޿�����", 100, Rarity::R, EffectType::IncreaseMaxHP, 200)));
	items.insert(make_pair("��޿�����", new ConsumableItem("��޿�����", 200, Rarity::SR, EffectType::IncreaseMaxHP, 400)));

	// Default Item

	items.insert(make_pair("���谡�����", new EquipableItem("���谡�����", 300, Rarity::C, "Weapon", { {"Damage", 50} }, 0, BuffStat(10, 0, 0))));

	//��� �����ۺ��̽�
	items.insert(make_pair("���ù�������ǰ�", new EquipableItem("���ù�������ǰ�", 3000, Rarity::SSR, "Weapon", { {"Damage", 50} }, 0, BuffStat(50, 0, 0))));
	items.insert(make_pair("��������", new EquipableItem("��������", 1000, Rarity::R, "Weapon", { {"Damage", 50} }, 0, BuffStat(3, 0, 0))));
	items.insert(make_pair("���װ���", new EquipableItem("���װ���", 300, Rarity::C, "Armor", { {"Damage", 50} }, 0, BuffStat(0, 10, 0))));
	items.insert(make_pair("ü�θ���", new EquipableItem("ü�θ���", 500, Rarity::R, "Armor", { {"Damage", 50} }, 0, BuffStat(0, 20, 0))));
	items.insert(make_pair("���ð���", new EquipableItem("���ð���", 1000, Rarity::SR, "Armor", { {"Damage", 50} }, 0, BuffStat(10, 30, 0))));

	//������ ��� ����������
	items.insert(make_pair("�������������", new ArchiveItem("�������������", 500, Rarity::C, BuffStat(5, 0, 0))));
	items.insert(make_pair("Ʈ���ǽ���", new ArchiveItem("Ʈ���ǽ���", 500, Rarity::C, BuffStat(0, 0, 50))));
	items.insert(make_pair("Ʈ��Ʈ�ǿ���", new ArchiveItem("Ʈ��Ʈ�ǿ���", 500, Rarity::C, BuffStat(0, 0, 50))));
	items.insert(make_pair("�巡���ǸӸ�", new ArchiveItem("�巡���ǸӸ�", 500, Rarity::C, BuffStat(0, 0, 50))));
	//���� �� Ư�� �����
	items.insert(make_pair("�����", new Item("�����", 50, Rarity::C)));
	items.insert(make_pair("��ũ�ǸӸ���", new Item("��ũ�ǸӸ���", 50, Rarity::C)));
	items.insert(make_pair("Ʈ���Ǽ۰���", new Item("Ʈ���Ǽ۰���", 50, Rarity::C)));
	items.insert(make_pair("�������", new Item("�������", 50, Rarity::C)));
	items.insert(make_pair("��������������", new Item("��������������", 50, Rarity::C)));
	items.insert(make_pair("������̴��Ǿ���", new Item("������̴��Ǿ���", 50, Rarity::C)));
	items.insert(make_pair("Ʈ�����Ʈ���ǵΰ���", new Item("Ʈ�����Ʈ���ǵΰ���", 50, Rarity::C)));
	items.insert(make_pair("��Ʈ�Ǿ���", new Item("��Ʈ�Ǿ���", 50, Rarity::C)));
	//�븻�� �����
	items.insert(make_pair("�����ǰ���", new Item("�����ǰ���", 50, Rarity::C)));
	items.insert(make_pair("�μ�����", new Item("�μ�����", 50, Rarity::C)));
	items.insert(make_pair("��������", new Item("��������", 50, Rarity::C)));
	items.insert(make_pair("������", new EquipableItem("������", 150, Rarity::C, "Weapon", { {"Damage", 30} }, 0, BuffStat(10, 0, 0))));
	//������ �����
	items.insert(make_pair("�β����", new Item("�β����", 50, Rarity::C)));
	items.insert(make_pair("�ܴ��ѻ�", new Item("�ܴ��ѻ�", 50, Rarity::C)));
	items.insert(make_pair("�����Ƕ߰ſ���", new Item("�����Ƕ߰ſ���", 50, Rarity::C)));
	//�巡�� �����
	items.insert(make_pair("�巡���ǰ���", new Item("�巡���ǰ���", 50, Rarity::C)));
	items.insert(make_pair("�巡���ǻ�", new Item("�巡���ǻ�", 50, Rarity::C)));
	items.insert(make_pair("�巡������", new Item("�巡������", 50, Rarity::C)));


	/*items.push_back(new LeatherArmor());
	items.push_back(new ChainMail());
	items.push_back(new MetalArmor());*/
}


ItemFactory::~ItemFactory()
{
	for (auto item : items) delete item.second;
}

vector<Item*> ItemFactory::GenerateRandomItems(int count)
{
	vector<Item*> shuffledItems;
	for (auto item : items)
	{
		if (item.second->GetType() == ItemType::Consumable || item.second->GetType() == ItemType::Equipable || item.second->GetType() == ItemType::Archive) {

			shuffledItems.push_back(item.second);
		}
	}
	random_device rd;
	mt19937 gen(rd());
	shuffle(shuffledItems.begin(), shuffledItems.end(), gen);

	vector<Item*>randomItems(shuffledItems.begin(), shuffledItems.begin() + count);
	return randomItems;
}

Item* ItemFactory::GenerateItem(string itemName)
{
	Item* item = nullptr;
	if (items.find(itemName) != items.end())
	{
		item = items[itemName];
	}
	else
	{
		//throw ExceptionHandler(ErrorCode::NullItemKey, format("�����Ϸ��� �������� ������ ��Ͽ� �����ϴ�. ������ �̸� :{}\n", itemName));
	}

	return item;
}

//Item* ItemFactory::GenerateItem(enum ItemList itemList)
//{
//	return nullptr;
//}


