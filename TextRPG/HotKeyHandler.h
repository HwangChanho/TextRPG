#pragma once
#include <iostream>
#include <windows.h>
#include <thread>
#include <format>
#include "Character.h"

void HotkeyHandler(Character& character) {
    while (true) {
        // Ctrl+0 �Է� Ȯ�� (VK_CONTROL = 0x11, VK_0 = 0x30)
        if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(0x30) & 0x8000)) {
            character.DisplayStatus();
            Sleep(500); // �Է� ���� (�ݺ� ȣ�� ����)
        }

        // ���α׷� ���� Ű (��: Ctrl+Q) ����
        //if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(0x51) & 0x8000)) {
        //    std::cout << "Hotkey Handler ����!" << std::endl;
        //    break;
        //}

        Sleep(100); // CPU ������ ���Ҹ� ���� ���
    }
}