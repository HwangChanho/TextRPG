#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <functional>

#include "Log.h"

#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27

class Menu {
public:
    Menu(const std::vector<std::string>& menuItems = {}, const std::vector<std::function<void()>>& actions = {});
    void DisplayMenu(int caseNumber, bool clear, string info);  // �޴� ǥ��
    int GetSelectedIndex();  // ���õ� �׸� �ε��� ��ȯ

    void AddMenuItem(const std::string& item, const std::function<void()>& action);  // �޴� �׸� �߰� (ĸ�ĵȰ� ������� �����Ҵ�Ǿ� std::function �Ҹ��ڿ��� ������, �������� ���ؿ�����)
    // ���� ĸ�ĵ� ��밡��
    void RemoveMenuItem(int index);  // �޴� �׸� ����

    void RunMenu(int caseNumber, bool clear, string info);  // �޴��� �����ϰ� ���õ� �׸� ���� ó��
private:
    //void ShowMenu(int selectedIndex);  // ���õ� �ε����� �������� �޴� ǥ��
    void ShowMenu(int selectedIndex, int caseNumber, bool clear, string info);
    void ShowMenu(int selectedIndex, int caseNumber, bool clear);

    std::vector<std::string> menuItems;  // �޴� �׸� ����Ʈ
    std::vector<std::function<void()>> actions;  // �� �׸� ���� ���� ����Ʈ
    int selectedIndex;  // ���� ���õ� �ε���
};

#endif