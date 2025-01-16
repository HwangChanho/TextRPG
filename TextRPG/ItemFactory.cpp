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
	// Default Item
	string desc = "�� ������ ������ ���谡���� ���޵Ǵ� �⺻ ���. �⺻���� ���ݷ��� �����մϴ�.";
	items.insert(make_pair("���谡�����", new EquipableItem("���谡�����", 300, Rarity::C, "Weapon", { {"Damage", 50} }, 0, BuffStat(10, 0, 0), desc)));

	// Heal Potion
	desc = "�ϱ� ü�� ȸ�� �����̴�. ������� ����";
	items.insert(make_pair("�ϱ�ü��ȸ������", new ConsumableItem("�ϱ�ü��ȸ������", 50, Rarity::C, EffectType::HealCurrentHP, 30, desc)));
	desc = "�߱� ü�� ȸ�� �����̴�. �� ū ��ó�� ȸ���� �� �ִ�.";
	items.insert(make_pair("�߱�ü��ȸ������", new ConsumableItem("�߱�ü��ȸ������", 100, Rarity::R, EffectType::HealCurrentHP, 60, desc)));
	desc = "��� ü�� ȸ�� �����̴�. �ɰ��� ��ó�� ȸ���� �����ϴ�.";
	items.insert(make_pair("���ü��ȸ������", new ConsumableItem("���ü��ȸ������", 200, Rarity::SR, EffectType::HealCurrentHP, 120, desc)));

	//Attack Power Up Potion
	desc = "�ϱ� ���� �ν��ʹ�. TMI : ���ݺν��� �迭�� �ڷ� �����Ѵ�.";
	items.insert(make_pair("�ϱް��ݺν���", new ConsumableItem("�ϱް��ݺν���", 20, Rarity::C, EffectType::DamageUp, 30, 3, desc)));
	desc = "�߱� ���� �ν��ʹ�. ���� �� ���ϰ� ������ �� �ִ�.";
	items.insert(make_pair("�߱ް��ݺν���", new ConsumableItem("�߱ް��ݺν���", 50, Rarity::R, EffectType::DamageUp, 50, 5, desc)));
	desc = "��� ���� �ν��ʹ�. ��� ���� ����÷� ���� ������ �� �ִ�.";
	items.insert(make_pair("��ް��ݺν���", new ConsumableItem("��ް��ݺν���", 100, Rarity::SR, EffectType::DamageUp, 100, 7, desc)));

	// Elixir
	desc = "�ִ� ü���� �÷��ִ� �ϱ� ��������. ������ Ž���ϴ� ���� ������ ���Ҽ� �������̴�.";
	items.insert(make_pair("�ϱ�ü�¿�����", new ConsumableItem("�ϱ�ü�¿�����", 50, Rarity::C, EffectType::IncreaseMaxHP, 20, desc)));
	desc = "�߱� ü�� ��������. ���谡�� ü���� ũ�� ��ȭ�����ش�.";
	items.insert(make_pair("�߱�ü�¿�����", new ConsumableItem("�߱�ü�¿�����", 200, Rarity::R, EffectType::IncreaseMaxHP, 50, desc)));
	desc = "��� ü�� ��������. ��ũ�� ���ݰ��� ü���� �����Ѵ�.";
	items.insert(make_pair("���ü�¿�����", new ConsumableItem("���ü�¿�����", 500, Rarity::SR, EffectType::IncreaseMaxHP, 100, desc)));
	desc = "�ٽŰ�踦 �����ִ� �ϱ� ��������. �Ѿ���̳���.";
	items.insert(make_pair("�ϱޱٷ¿�����", new ConsumableItem("�ϱޱٷ¿�����", 50, Rarity::C, EffectType::IncreaseAttackPower, 120, desc)));
	//��� �����ۺ��̽�
	desc = "������ ����ſ�� ���� �ʴ´ٰ� �Ѵ�. ������ ������ �׻� ������ ���ù޾ƿԾ���...";
	items.insert(make_pair("���ù�������ǰ�", new EquipableItem("���ù�������ǰ�", 3000, Rarity::SSR, "Weapon", { {"Damage", 50} }, 0, BuffStat(50, 0, 0), desc)));
	desc = "������ ����ȭ�� ����. ������ ���ݷ��� �����մϴ�.";
	items.insert(make_pair("��������", new EquipableItem("��������", 1500, Rarity::R, "Weapon", { {"Damage", 60} }, 0, BuffStat(20, 0, 0), desc)));
	desc = "ưư�ϰ� ������ �������� ������� ����. �̵��ϱ� ���ϴ�.";
	items.insert(make_pair("���װ���", new EquipableItem("���װ���", 500, Rarity::C, "Armor", { {"Defense", 10} }, 0, BuffStat(0, 20, 0), desc)));
	desc = "ö�� ���� ����. ������ ������ �����մϴ�.";
	items.insert(make_pair("ü�θ���", new EquipableItem("ü�θ���", 1000, Rarity::R, "Armor", { {"Defense", 20} }, 0, BuffStat(0, 50, 0), desc)));
	desc = "���� ������ ƨ�ܳ��� ���ð� �޸� ����.";
	items.insert(make_pair("���ð���", new EquipableItem("���ð���", 2000, Rarity::SR, "Armor", { {"Defense", 30}, {"Reflect", 5} }, 0, BuffStat(10, 70, 0), desc)));
	desc = "���� ��. �����Ǿ� ���ݷ��� ����.";
	items.insert(make_pair("������", new EquipableItem("������", 150, Rarity::C, "Weapon", { {"Damage", 20} }, 0, BuffStat(5, 0, 0), desc)));

	//������ ��� ����������
	desc = "��������������̴�. ������ ���ݴ� ���Ҽ� �ְ� �ȴ�.";
	items.insert(make_pair("�������������", new ArchiveItem("�������������", 500, Rarity::C, BuffStat(5, 0, 0), desc)));
	desc = "Ʈ���� ����. ������� ��¡�ϴ� �����̴�."; 
	items.insert(make_pair("Ʈ���ǽ���", new ArchiveItem("Ʈ���ǽ���", 1200, Rarity::R, BuffStat(0, 0, 50), desc)));
	desc = "Ʈ��Ʈ�� ����. �ڿ��� ������ ��� �ִ�.";
	items.insert(make_pair("Ʈ��Ʈ�ǿ���", new ArchiveItem("Ʈ��Ʈ�ǿ���", 1500, Rarity::SR, BuffStat(20, 0, 30), desc)));
	desc = "�巡���� �Ӹ��Դϴ�. ������ ������ ���ŷ� �ſ� ����մϴ�.";
	items.insert(make_pair("�巡���ǸӸ�", new ArchiveItem("�巡���ǸӸ�", 5000, Rarity::SSR, BuffStat(0, 0, 100), desc)));

	//���� �� Ư�� �����
	desc = "����� �ʹ�. ��� ��� �Ƿڸ� �ϼ��ϱ����� �� ì����.";
	items.insert(make_pair("�����", new Item("�����", 50, Rarity::C, desc)));
	desc = "��ũ�� �Ӹ���. ���� ������ ����.";
	items.insert(make_pair("��ũ�ǸӸ���", new Item("��ũ�ǸӸ���", 80, Rarity::C, desc)));
	desc = "Ʈ���� �۰���. ������ ������� ��¡�Ѵ�.";
	items.insert(make_pair("Ʈ���Ǽ۰���", new Item("Ʈ���Ǽ۰���", 100, Rarity::R, desc)));
	desc = "������ ����. ��ɲ۵鿡�� �α� �ִ� ����ǰ�̴�.";
	items.insert(make_pair("�������", new Item("�������", 50, Rarity::C)));
	desc = "�������� ������. ��Ư�� ��� ������ �ִ�.";
	items.insert(make_pair("��������������", new Item("��������������", 40, Rarity::C, desc)));
	desc = "��� ���̴��� ����. ����� ����ǰ�̴�.";
	items.insert(make_pair("������̴��Ǿ���", new Item("������̴��Ǿ���", 150, Rarity::R, desc)));
	desc = "Ʈ����� Ʈ���� �ΰ���. ���ù����� �����̴�.";
	items.insert(make_pair("Ʈ�����Ʈ���ǵΰ���", new Item("Ʈ�����Ʈ���ǵΰ���", 200, Rarity::R, desc)));
	desc = "��Ʈ�� ����. ������ ����� ��������.";
	items.insert(make_pair("��Ʈ�Ǿ���", new Item("��Ʈ�Ǿ���", 250, Rarity::SR, desc)));
	//�븻�� �����
	desc = "������ ����. �⺻���� �� ���ۿ� ���ȴ�.";
	items.insert(make_pair("�����ǰ���", new Item("�����ǰ���", 50, Rarity::C, desc)));
	desc = "�μ��� ��. ������ ���ط� Ȱ�� ��ġ�� ����.";
	items.insert(make_pair("�μ�����", new Item("�μ�����", 30, Rarity::C, desc)));
	desc = "������ ��. ������ �ּ� ���� ���ȴ�.";
	items.insert(make_pair("��������", new Item("��������", 100, Rarity::R, desc)));
	//������ �����
	desc = "�β��� ����. �� ���ۿ� �����ϴ�.";
	items.insert(make_pair("�β����", new Item("�β����", 200, Rarity::R, desc)));
	desc = "�ܴ��� ��. �������� ���� �پ��� �뵵�� ���ȴ�.";
	items.insert(make_pair("�ܴ��ѻ�", new Item("�ܴ��ѻ�", 250, Rarity::R, desc)));
	desc = "������ �߰ſ� ��. ������ �ּ� ���� ����ϴ�.";
	items.insert(make_pair("�����Ƕ߰ſ���", new Item("�����Ƕ߰ſ���", 300, Rarity::SR, desc)));
	//�巡�� �����
	desc = "�巡���� ����. �������� �������� �ڶ��Ѵ�.";
	items.insert(make_pair("�巡���ǰ���", new Item("�巡���ǰ���", 3000, Rarity::SSR, desc)));
	desc = "�巡���� ��. ������ ���� ���� �ִ�.";
	items.insert(make_pair("�巡���ǻ�", new Item("�巡���ǻ�", 4000, Rarity::SSR, desc)));
	desc = "�巡���� ��. ������ ������ ����Ǿ� �ִ�.";
	items.insert(make_pair("�巡������", new Item("�巡������", 5000, Rarity::SSR, desc)));


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


