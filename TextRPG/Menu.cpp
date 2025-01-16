#include "Menu.h"

#include <iostream>
#include <conio.h>
#include <cstdlib> 

using namespace std;

Menu::Menu(const std::vector<std::string>& menuItems, const std::vector<std::function<void()>>& actions)
    : menuItems(menuItems), actions(actions), selectedIndex(0) {
}

void Menu::ShowMenu(int selectedIndex, int caseNumber, bool clear, string info) {
    Log::GetInstance()->PrintLog(info, caseNumber, clear);

    for (int i = 0; i < menuItems.size(); ++i) {
        if (i == selectedIndex) {
            cout << menuItems[i] << " <" << endl;
        }
        else {
            cout << menuItems[i] << endl;
        }
    }
}

void Menu::ShowMenu(int selectedIndex, int caseNumber, bool clear) {
    Log::GetInstance()->PrintLog("", caseNumber, clear);

    for (int i = 0; i < menuItems.size(); ++i) {
        if (i == selectedIndex) {
            cout << menuItems[i] << " <" << endl;
        }
        else {
            cout << menuItems[i] << endl;
        }
    }
}

void Menu::DisplayMenu(int caseNumber, bool clear, string info) {
    ShowMenu(selectedIndex, caseNumber, clear, info);  // �޴��� ù ��° �׸����� ǥ��
}

int Menu::GetSelectedIndex() {
    return selectedIndex;  // ���� ���õ� �׸� �ε��� ��ȯ
}

void Menu::AddMenuItem(const std::string& item, const std::function<void()>& action) {
    menuItems.push_back(item);  // �޴� �׸� �߰�
    actions.push_back(action);  // �ش� �׸��� ���� �߰�
}

void Menu::RemoveMenuItem(int index) {
    if (index >= 0 && index < menuItems.size()) {
        menuItems.erase(menuItems.begin() + index);  // Ư�� �׸� ����
        actions.erase(actions.begin() + index);  // ���۵� �Բ� ����
    }
}

void Menu::RunMenu(int caseNumber, bool clear, string info) {
    char c;
    while (true) {
        if (_kbhit()) {  // Ű �Է��� Ȯ��
            c = _getch();  // Ű �Է� �ޱ�

            if (c == -32) {  // ����Ű �Է�
                c = _getch();  // ����Ű�� ���� �� �ޱ�

                switch (c) {
                case UP:
                    // �� ����Ű
                    selectedIndex = (selectedIndex - 1 + menuItems.size()) % menuItems.size();  // ���� �׸����� �̵�
                    if (info != "")
                    {
                        ShowMenu(selectedIndex, caseNumber, clear, info);
                    }
                    else
                    {
                        ShowMenu(selectedIndex, caseNumber, clear);
                    }
                    break;
                case DOWN:
                    // �Ʒ� ����Ű
                    selectedIndex = (selectedIndex + 1) % menuItems.size();  // ���� �׸����� �̵�
                    if (info != "")
                    {
                        ShowMenu(selectedIndex, caseNumber, clear, info);
                    }
                    else
                    {
                        ShowMenu(selectedIndex, caseNumber, clear);
                    }
                    break;
                default:
                    break;
                }
            }
            else if (c == ENTER) {  // ����Ű �Է�
                /*
                cout << "Selected Index: " << selectedIndex << endl;
                cout << "Executing Action: " << menuItems[selectedIndex] << endl;

                cout << "Menu Items and Actions:" << endl;
                for (size_t i = 0; i < menuItems.size(); ++i) {
                    cout << "  [" << i << "] " << menuItems[i];
                    if (i == selectedIndex) {
                        cout << " (Currently Selected)";
                    }
                    cout << endl;
                }

                cout << "Actions Array Details:" << endl;
                for (size_t i = 0; i < actions.size(); ++i) {
                    cout << "  Action[" << i << "]: ";
                    if (actions[i]) {
                        cout << "Valid Function" << endl;  // ��ȿ�� �Լ��� �����ϴ� ���
                    }
                    else {
                        cout << "Empty/Null Function" << endl;  // �Լ��� ���� ���
                    }
                }

                cout << "selectedIndex: " << selectedIndex << ", actions.size(): " << actions.size() << endl;
                */
                if (selectedIndex >= 0 && selectedIndex < actions.size()) {
                    // cout << "Executing action for index: " << selectedIndex << endl;
                    actions[selectedIndex]();  // ���õ� �׸��� ���� ����
                }
                else {
                    cout << "Invalid selection!" << endl;  // ������ ��� ��� ó��
                }

                // �޴� ���� �� �ݺ����� Ż��
                break;
            }
            else if (c == ESC) {  // ESC Ű �Է� �� ���α׷� ����
                cout << "Exiting..." << endl;
                break;
            }
        }
    }
}
