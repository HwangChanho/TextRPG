#include "Shop.h"
#include "Item.h"
#include "Enchancer.h"
#include "ItemFactory.h"
#include "Log.h"
#include <format>

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
	if (shopInven.empty())
	{
		logger->PrintLog("�������� �����ϴ�!", (int)EShop, true);
		//cout << "\nThe shop is out of items!" << endl;
		return;
	}

	logger->PrintLog("������ �������� �������ּ���!\n\n", false);
	logger->PrintLog(format("������ {} gold\n\n", player.GetGold()), (int)EShop, true);
	//cout << "You have " << player.GetGold() << "gold\n" << endl;
	//cout << "Select the items you want to buy!" << endl;
	logger->PrintLog("===========���� ����===========\n\n", false);
	for (int i = 0; i < shopInven.size(); i++)
	{
		if (shopInven[i] != nullptr)
		{
			string logMessage = format("{}.{} - {} gold [{}]\n", i + 1, shopInven[i]->GetName(), shopInven[i]->GetPrice(), (int)shopInven[i]->GetType());
			logger->PrintLog(logMessage, false);
			//cout << i + 1 << ". " << shopInven[i]->GetName() << " - " << shopInven[i]->GetPrice() << " gold [" << (int)shopInven[i]->GetType() << "]" << endl;
		}
		else
		{
			string logMessage = format("{}. �߸��� ������. ", i + 1);
			logger->PrintLog(logMessage, false);
			//cout << i + 1 << ". Invalid Item" << endl;
		}
	}
	logger->PrintLog("\n==============================\n", false);
	string logMessage = format("{}.������\n", shopInven.size() + 1);
	logger->PrintLog(logMessage, false);
	//cout << shopInven.size() + 1 << ". Leave the shop" << endl;

	int choice;
	cout << "���� : ";
	cin >> choice;

	if (choice == shopInven.size() + 1)
	{
		logger->PrintLog("������ ���Ÿ� �����߽��ϴ�.\n", (int)EShop, true);
		//cout << "\nYou left the shop" << endl;
		return;
	}

	if (choice < 1 || choice>shopInven.size() + 1)
	{
		logger->PrintLog("�߸��� �����Դϴ�.", (int)EShop, false);
		//cout << "\nInvalid choice" << endl;
		return;
	}
	else
	{
		Item* selectedItem = shopInven[choice - 1];
		if (player.GetGold() >= selectedItem->GetPrice())
		{
			player.BuyItem(selectedItem);
			//player.TakeGold(-selectedItem->GetPrice());
			//player.TakeItem(selectedItem);
			string logMessage = format("[{}]�� �����߽��ϴ�!\n\n", selectedItem->GetName());
			logger->PrintLog(logMessage, (int)EShop, true);
			//cout << "\nYou bought [" << selectedItem->GetName() << "]!\n" << endl;
			logger->PrintLog(format("������ {} gold\n", player.GetGold()), false);
			//cout << "Left gold : " << player.GetGold() << endl;

			shopInven.erase(shopInven.begin() + (choice - 1));
		}
		else
		{
			logger->PrintLog("��尡 �����մϴ�.\n", false);
			//cout << "\nNot enough gold" << endl;
		}
	}
}

void Shop::SellItem(Character& player)
{
	auto inventory = player.GetInventory();
	if (inventory.empty())
	{
		logger->PrintLog("�Ǹ� ������ �������� �����ϴ�!\n", (int)EShop, true);
		//cout << "You have no items to sell!" << endl;
		return;
	}
	logger->PrintLog("�Ǹ��� �������� �������ּ���.\n", (int)EShop, true);
	//cout << "\nSelect the item you want to sell!\n" << endl;
	logger->PrintLog("===========�Ǹ� ����===========\n\n", false);
	//cout << "[Inventory]\n" << endl;
	int index = 1;
	vector <Item*> invenItems;
	for (const auto& item : inventory)
	{
		string logMessage = format("{}. {} (x{}) [�ǸŰ� - {} gold]\n", index, item.second.item->GetName(), item.second.Count, item.second.item->GetSellPrice());
		logger->PrintLog(logMessage, false);
		//cout << index << ". " << item.second.item->GetName() << " (x" << item.second.Count << ")" << " [Price at Sale - " << item.second.item->GetSellPrice() << " gold]" << endl;
		invenItems.push_back(item.second.item);
		index++;
	}
	logger->PrintLog("\n==============================\n", false);
	logger->PrintLog(format("{}. ������\n", index), false);
	//cout << index << ". Leave the Inventory" << endl;

	int choice;
	cout << "���� : ";
	cin >> choice;
	if (choice == index)
	{
		logger->PrintLog("������ �ǸŸ� �����߽��ϴ�.\n", (int)EShop, true);
		//cout << "\nYou left the Inventory" << endl;
		return;
	}
	if (choice<1 || choice>invenItems.size()) {
		logger->PrintLog("�߸��� �Է��Դϴ�.\n", (int)EShop, true);
		//cout << "\nInvaild choice" << endl;
		return;
	}

	Item* selectedItem = invenItems[choice - 1];
	int sellPrice = selectedItem->GetSellPrice();

	player.SellItem(selectedItem->GetName());

	//player.TakeGold(sellPrice);
	//player.SellItem(selectedItem->GetName());
	string logMessage = format("{}��(��) {}gold �� �Ǹ��߽��ϴ�!\n\n", selectedItem->GetName(), sellPrice);
	logger->PrintLog(logMessage, EShop, true);
	//cout << "You sold " << selectedItem->GetName() << " for " << sellPrice << "gold!" << endl;
	logger->PrintLog(format("������ {} gold\n", player.GetGold()), false);
	//cout << "Left gold : " << player.GetGold() << endl;
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
		return;
	}
	int enchantPrice = 100;//��ȭ���

	logger->PrintLog(format("������ {} gold\n\n", player.GetGold()), (int)EShop, true);
	//cout << "\nYou have " << player.GetGold() << " gold." << endl;
	logger->PrintLog(format("��ȭ�� �������� �������ּ���! [��ȭ ��� {} gold]\n",enchantPrice), false);
	//cout << "\nSelect an item to Enchance! (Once " << enchantPrice << " gold)\n" << endl;
	logger->PrintLog("===========��ȭ ����===========\n\n", false);
	for (int i = 0;i < enchantableItems.size();i++)
	{
		string logMessage = format("{}. {} (+{})\n", i + 1, enchantableItems[i]->GetName(), dynamic_cast<EquipableItem*>(enchantableItems[i])->GetEnchantLevel());
		logger->PrintLog(logMessage, false);
		//cout << i + 1 << ". " << enchantableItems[i]->GetName() << "(+" << dynamic_cast<EquipableItem*>(enchantableItems[i])->GetEnchantLevel() << ")" << endl;
	}
	logger->PrintLog("\n==============================\n", false);
	logger->PrintLog(format("{}. ������\n", enchantableItems.size()+1), false);

	int choice;
	cout << "���� : ";
	cin >> choice;
	if (choice == enchantableItems.size()+1)
	{
		logger->PrintLog("������ ��ȭ�� �����߽��ϴ�.\n", (int)EShop, true);
		return;
	}
	if (choice<1 || choice>enchantableItems.size())
	{
		logger->PrintLog("�߸��� �Է��Դϴ�.\n", (int)EShop, true);
		//cout << "Invalid choice!" << endl;
		return;
	}
	if (player.GetGold() < enchantPrice)
	{
		logger->PrintLog("��尡 �����մϴ�.\n", (int)EShop, true);
		//cout << "Not enough gold to enchant!" << endl;
		return;
	}

	EquipableItem* itemToEnchant = dynamic_cast<EquipableItem*>(enchantableItems[choice - 1]);
	EquipableItem* enchantedItem = enchancer.EnchanceItem(itemToEnchant);

	for (int i = 0;i < 2;i++)
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
}
