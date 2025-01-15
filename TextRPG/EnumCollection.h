#ifndef ENUM_COLLECTION_H
#define ENUM_COLLECTION_H

namespace Enums
{
	enum LogEnum { EMenu, EStart, EGameOver, EGameEnd };
	enum PrintEnum { EBattlePrint, EStatusPrint, EShopRoomPrint, ERestRoomPrint, EBuffDebuffRoomPrint };
	//SetConsoleTextAttribute���� ������ 16���� ����ϰ�, ���⿡ ���� �ε����� �ؽ�Ʈ�󿡼� �ش� ���ĺ����� ��ȯ�ؼ� ��������
	//enum ImageColor { a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p };
	//PrintLog() ����, �� ��° ���ڷ� �ش� �� �������ָ� �ش� �̹��� ��µ�. ���� �̹��� ���� ��� �׳� PrintLog("���ڿ�") �Ͻø� �˴ϴ�. �����ε� �����ؼ� EJustString �����߽��ϴ�.
	enum EnumPrintLog { ECharacter, EGoblin, EOrc, ETroll, EWolf, ESlime, EGoblinRider, ETwinHeadTroll, ETreant, EDragon, EBuff, EDeBuff, EShop, ERest };
}

#endif