#pragma once
#include <thread>

namespace PI {
    extern bool isInputEnabled;
    extern bool isRunning;

    void ProcessInput();
    void ClearInputBuffer(); // ClearInputBuffer �Լ� ����
}