#include "GameManager.h"

namespace GameManger {

    // �̱��� �ν��Ͻ� ��ȯ
    GameManger& GameManger::GetInstance() 
    {
        static GameManger instance;
        return instance;
    }

    // ���� �湮 �Լ�
    void GameManger::VisitShop() 
    {
        // TODO: ���� �ʿ�
    }

    // ���� ���� �Լ�
    void GameManger::BeginBattle() 
    {
        // TODO: ���� �ʿ�
    }

    // BattleManager ���� �Լ�
    void GameManger::GenerateBattleManager() 
    {
        // TODO: ���� �ʿ�
    }

    // �޽� ��� �湮 �Լ�
    void GameManger::VisitRest() 
    {
        // TODO: ���� �ʿ�
    }

    // ������ �湮 �Լ�
    void GameManger::VisiteBuffRoom() 
    {
        // TODO: ���� �ʿ�
    }

    // ĳ���� ���� �Լ�
    Character GameManger::GenerateCharacter() 
    {
        // TODO: ���� �ʿ�
        return Character();
    }

    // ���� �������� ��ȯ �Լ�
    int GameManger::getCurrentStage() 
    {
        // TODO: ���� �ʿ�
        return stage;
    }

    // �������� �ܰ� ����
    void GameManger::SetStage(int num)
    {
        // TODO: ���� �ʿ�
    }

    // ���ӽ���
    void GameManger::BeginPlay()
    {
        // TODO: ���� �ʿ�
    }
} // namespace GameManger