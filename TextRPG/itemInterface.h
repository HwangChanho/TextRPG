#pragma once
#include <string>
using namespace std;

class ItemInterface
{
	virtual string GetName() = 0;
	virtual int GetPrice() = 0;
	virtual int GetRarity() = 0;
	virtual string GetItemType() = 0;//�Һ������, ��������
};