#include "Shop.h"
#include "Item.h"
#include "Enchancer.h"
#include "ItemFactory.h"
#include "Log.h"
#include <format>
#include "Menu.h"
#include "ProcessInput.h"

Log* logger = Log::GetInstance();
Shop::Shop()
{
	shopInven = ItemFactory::GetInstance().GenerateRandomItems(3);
}
Shop::~Shop()
{
	for (auto item : shopInven)
	{
		delete item;
	}
}
void Shop::DisplayItem()
{
	if (shopInven.empty())
	{
		logger->PrintLog("The shop is out of items!", (int)EShop, false);//cout << "\nThe shop is out of items!\n" << endl;
		return;
	}
	for (int i = 0; i < shopInven.size(); i++)
	{
		string logMessage = format("{}. {} - {} gold [{}]", i + 1, shopInven[i]->GetName(), shopInven[i]->GetPrice(), (int)shopInven[i]->GetType());
		logger->PrintLog(logMessage, (int)EShop, false);
		//cout << i + 1 << ". " << shopInven[i]->GetName() << " - " << shopInven[i]->GetPrice() << " gold" << " [" << (int)shopInven[i]->GetType() << "]" << endl;
	}
}
void Shop::BuyItem(Character& player)
{
	int choice;
	string logMessage;

	if (shopInven.empty())
	{
		logger->PrintLog("\n���� ������ �������� �����ϴ�!", (int)EShop, true);
		Sleep(1500);
		return;
	}

	// =============================================================================
	logger->PrintLog("\n������ �������� �������ּ���!\n", (int)EShop, true);
	logger->PrintLog(format("������ {} gold\n\n", player.GetGold()), false);

	logger->PrintLog("===========���� ����===========\n\n", false);
	for (int i = 0; i < shopInven.size(); i++)
	{
		logMessage = format("{}.{} - {} gold\n", i + 1, shopInven[i]->GetName(), shopInven[i]->GetPrice());
		logger->PrintLog(logMessage, false);
	}
	logger->PrintLog("\n==============================\n\n", false);
	logger->PrintLog(format("{}.������\n", shopInven.size() + 1), false);

	logger->PrintLog("\n���� : ", false); 
	// =============================================================================
	// �Է��� ���������� �Ǵ� => �Է��� int�� �ƴϸ� int ���� �޾ƿö����� �ݺ�
	while (!(cin >> choice))
	{
		// Clear Input Buffer
		cin.clear();
		while (std::cin.get() == '\n') continue;

		logger->PrintLog("�߸��� �Է��Դϴ�.�ٽ��Է��ϼ���.\n", (int)EShop, true);
		// =============================================================================
		logger->PrintLog("\n������ �������� �������ּ���!\n", false);
		logger->PrintLog(format("������ {} gold\n\n", player.GetGold()), false);

		logger->PrintLog("===========���� ����===========\n\n", false);
		for (int i = 0; i < shopInven.size(); i++)
		{
			logMessage = format("{}.{} - {} gold\n", i + 1, shopInven[i]->GetName(), shopInven[i]->GetPrice());
			logger->PrintLog(logMessage, false);
		}
		logger->PrintLog("\n==============================\n\n", false);
		logger->PrintLog(format("{}.������\n", shopInven.size() + 1), false);

		logger->PrintLog("\n���� : ", false);
		// =============================================================================
	}

	if (choice == shopInven.size() + 1)
	{
		logger->PrintLog("������ ���Ÿ� �����߽��ϴ�.\n", (int)EShop, true);
		Sleep(1500);
	}
	else if (choice < 1 || choice > shopInven.size() + 1)
	{
		logger->PrintLog(format("�߸��� �����Դϴ�. �Է� : {}", choice), (int)EShop, true);
		Sleep(1500);
	}
	else
	{
		// �������� ���������� ����������
		Item* selectedItem = shopInven[choice - 1];
		if (player.GetGold() >= selectedItem->GetPrice())
		{
			player.BuyItem(selectedItem);

			logMessage = format("[{}]��(��) �����߽��ϴ�!\n\n", selectedItem->GetName());
			logMessage += format("���� ������ {} gold\n", player.GetGold());
			logger->PrintLog(logMessage, (int)EShop, true);
			
			shopInven.erase(shopInven.begin() + (choice - 1));
		}
		else
		{
			logger->PrintLog("\n :( ���� ��尡 �����մϴ�.\n", (int)EShop, false);
		}

		Sleep(1500);
	}

	return;
}

void Shop::SellItem(Character& player)
{
	map<string, class Inventory> inventory = player.GetInventory();
	int choice;
	int index = 1;

	if (inventory.empty())
	{
		logger->PrintLog("�Ǹ� ������ �������� �����ϴ�!\n", (int)EShop, true);
		Sleep(1500);
		return;
	}

	//======================================================================
	logger->PrintLog("�Ǹ��� �������� �������ּ���.\n", (int)EShop, true);
	logger->PrintLog("===========�Ǹ� ����===========\n\n", false);
	vector <Item*> invenItems;
	for (const auto& item : inventory)
	{
		string logMessage = format("{}. {} (x{}) [�ǸŰ� - {} gold]\n", index, item.second.item->GetName(), item.second.Count, item.second.item->GetSellPrice());
		logger->PrintLog(logMessage, false);
		invenItems.push_back(item.second.item);
		index++;
	}
	logger->PrintLog("\n==============================\n\n", false);
	logger->PrintLog(format("{}. ������\n", index), false);

	cout << "���� : ";
	// =============================================================================
	// �Է��� ���������� �Ǵ� => �Է��� int�� �ƴϸ� int ���� �޾ƿö����� �ݺ�
	while (!(cin >> choice))
	{
		// Clear Input Buffer
		cin.clear();
		while (std::cin.get() == '\n') continue;
		logger->PrintLog("�߸��� �Է��Դϴ�.�ٽ��Է��ϼ���.\n", (int)EShop, true);

		//======================================================================
		logger->PrintLog("�Ǹ��� �������� �������ּ���.\n", (int)EShop, true);
		logger->PrintLog("===========�Ǹ� ����===========\n\n", false);
		index = 1;
		vector <Item*> invenItems;
		for (const auto& item : inventory)
		{
			string logMessage = format("{}. {} (x{}) [�ǸŰ� - {} gold]\n", index, item.second.item->GetName(), item.second.Count, item.second.item->GetSellPrice());
			logger->PrintLog(logMessage, false);
			invenItems.push_back(item.second.item);
			index++;
		}
		logger->PrintLog("\n==============================\n\n", false);
		logger->PrintLog(format("{}. ������\n", index), false);
		cout << "���� : ";
		// =============================================================================
	}

	if (choice == index)
	{
		logger->PrintLog("������ �ǸŸ� �����߽��ϴ�.\n", (int)EShop, true);
		Sleep(1500);
	}
	else if (choice < 1 || choice > invenItems.size()) 
	{
		logger->PrintLog("�߸��� �Է��Դϴ�.\n", (int)EShop, true);
		Sleep(1500);
	}
	else
	{
		// ���������� �Ǹ� ������
		Item* selectedItem = invenItems[choice - 1];
		player.SellItem(selectedItem->GetName());

		string logMessage = format("{}��(��) {}gold �� �Ǹ��߽��ϴ�!\n\n", selectedItem->GetName(), selectedItem->GetSellPrice());
		logMessage += format("������ {} gold\n", player.GetGold());
		logger->PrintLog(logMessage, EShop, true);

		Sleep(1500);
	}

	return;
}

void Shop::UseEnchancer(Character& player)
{
	Enchancer enchancer;
	auto inventory = player.GetInventory();
	vector<Item*> enchantableItems = enchancer.GetEnchanceableItems(inventory);
	if (enchantableItems.empty())
	{
		logger->PrintLog("��ȭ�� �� �ִ� �������� �����ϴ�.\n", (int)EShop, true);
		//cout << "\nNo Items for enchancement" << endl;
		int choice;
		cout << "\n�ƹ� Ű�� ���� Ȯ��\n";
		PI::ClearInputBuffer();
		PI::isInputEnabled = true;
		cin >> choice;
		PI::isInputEnabled = false;
		return;
	}
	int enchantPrice = 100;//��ȭ���
	logger->PrintLog(format("������ {} gold\n\n", player.GetGold()), (int)EShop, true);
	//cout << "\nYou have " << player.GetGold() << " gold." << endl;
	logger->PrintLog(format("��ȭ�� �������� �������ּ���! [��ȭ ��� {} gold]\n", enchantPrice), false);
	//cout << "\nSelect an item to Enchance! (Once " << enchantPrice << " gold)\n" << endl;
	logger->PrintLog("===========��ȭ ����===========\n\n", false);
	for (int i = 0; i < enchantableItems.size(); i++)
	{
		string logMessage = format("{}. {} (+{})\n", i + 1, enchantableItems[i]->GetName(), dynamic_cast<EquipableItem*>(enchantableItems[i])->GetEnchantLevel());
		logger->PrintLog(logMessage, false);
		//cout << i + 1 << ". " << enchantableItems[i]->GetName() << "(+" << dynamic_cast<EquipableItem*>(enchantableItems[i])->GetEnchantLevel() << ")" << endl;
	}
	logger->PrintLog("\n==============================\n", false);
	logger->PrintLog(format("{}. ������\n", enchantableItems.size() + 1), false);
	int choice;
	cout << "���� : ";
	PI::ClearInputBuffer();
	PI::isInputEnabled = true;
	cin >> choice;
	PI::isInputEnabled = false;
	if (choice == enchantableItems.size() + 1)
	{
		logger->PrintLog("������ ��ȭ�� �����߽��ϴ�.\n", (int)EShop, true);
		int choice;
		cout << "\n�ƹ� Ű�� ���� Ȯ��\n";
		PI::ClearInputBuffer();
		PI::isInputEnabled = true;
		cin >> choice;
		PI::isInputEnabled = false;
		return;
	}
	if (choice<1 || choice>enchantableItems.size())
	{
		logger->PrintLog("�߸��� �Է��Դϴ�.\n", (int)EShop, true);
		//cout << "Invalid choice!" << endl;
		int choice;
		cout << "\n�ƹ� Ű�� ���� Ȯ��\n";
		PI::ClearInputBuffer();
		PI::isInputEnabled = true;
		cin >> choice;
		PI::isInputEnabled = false;
		return;
	}
	if (player.GetGold() < enchantPrice)
	{
		logger->PrintLog("��尡 �����մϴ�.\n", (int)EShop, true);
		//cout << "Not enough gold to enchant!" << endl;
		int choice;
		cout << "\n�ƹ� Ű�� ���� Ȯ��\n";
		PI::ClearInputBuffer();
		PI::isInputEnabled = true;
		cin >> choice;
		PI::isInputEnabled = false;
		return;
	}
	EquipableItem* itemToEnchant = dynamic_cast<EquipableItem*>(enchantableItems[choice - 1]);
	EquipableItem* enchantedItem = enchancer.EnchanceItem(itemToEnchant);
	for (int i = 0; i < 2; i++)
	{
		logger->PrintLog("\n��ȭ��.\n", (int)EShop, true);
		Sleep(500);
		logger->PrintLog("\n��ȭ��..\n", (int)EShop, true);
		Sleep(500);
		logger->PrintLog("\n��ȭ��...\n", (int)EShop, true);
		Sleep(500);
	}
	if (enchantedItem != itemToEnchant)
	{
		//inventory[itemToEnchant->GetName()].item = enchantedItem;
		player.ReduceInventory(itemToEnchant->GetName());
		player.TakeItem(enchantedItem);
		logger->PrintLog("������ ��ȭ�� �����߽��ϴ�!\n\n", (int)EShop, true);
		//cout << "Item enchanted successfully!" << endl;
		string logMessage = format("{}(+{})\n", enchantedItem->GetName(), dynamic_cast<EquipableItem*>(enchantedItem)->GetEnchantLevel());
		logger->PrintLog(logMessage, false);
		//cout << enchantedItem->GetName() << "(+" << dynamic_cast<EquipableItem*>(enchantedItem)->GetEnchantLevel() << ")" << endl;
	}
	else
	{
		logger->PrintLog("������ ��ȭ�� �����߽��ϴ�.\n\n", (int)EShop, true);
		//cout << "Item enchantment failed! No changes made to the item!" << endl;
		string logMessage = format("{}(+{})\n", enchantedItem->GetName(), dynamic_cast<EquipableItem*>(enchantedItem)->GetEnchantLevel());
		logger->PrintLog(logMessage, false);
		//cout << enchantedItem->GetName() << "(+" << dynamic_cast<EquipableItem*>(enchantedItem)->GetEnchantLevel() << ")" << endl;
	}
	player.TakeGold(-enchantPrice);
	logger->PrintLog(format("\n������ {} gold\n", player.GetGold()), false);
	//cout << "You used " << enchantPrice << " gold for enchant!(Left gold : " << player.GetGold() << ")" << endl;
	int choice3;
	cout << "\n�ƹ� Ű�� ���� Ȯ��\n";
	PI::ClearInputBuffer();
	PI::isInputEnabled = true;
	cin >> choice3;
	PI::isInputEnabled = false;
}