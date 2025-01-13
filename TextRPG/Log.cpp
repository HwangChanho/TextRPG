#include "Log.h"

Log* Log::instance = nullptr;

Log* Log::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Log();
	}
	return instance;
}

void Log::SetScreen()
{
	int moniterScreenWidth = GetSystemMetrics(SM_CXSCREEN);		//����� �ػ� ��������
	int moniterScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	int consoleWidth = moniterScreenWidth / 2;					//����� �ػ� ���μ����� ���ݸ�ŭ�� �ܼ�â�� ũ�Ⱑ �ǵ��� ��(â ũ��� ������� 1/4
	int consoleHeight = moniterScreenHeight / 2;
	int charWidth = 8;											//Windows �ܼ�â�� �⺻ ��Ʈ(Raster Fonts)�� ���� ũ�� ��(�ȼ�)  ���� 8�ȼ�  ���� 16�ȼ�
	int charHeight = 16;
	int bufferWidth = consoleWidth / charWidth;					//�ܼ� ������ ũ�⸦ ���� ũ��� ������. �̷��� ���ڿ� ���̿� ���� ��ũ�� �߻����� ����(�����̱� ������)
	int bufferHeight = consoleHeight / charHeight;

	//�ܼ� �ڵ� ������
	HWND console = GetConsoleWindow();	
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	//���� ũ��� �ܼ� ���� ũ�� ���ϰ� â ũ�� ��������
	COORD bufferSize;
	bufferSize.X = bufferWidth;
	bufferSize.Y = bufferHeight;
	SetConsoleScreenBufferSize(consoleHandle, bufferSize);
	SMALL_RECT windowSize = { 0, 0, bufferWidth - 1, bufferHeight - 1 };	//������ ũ�� ����
	SetConsoleWindowInfo(consoleHandle, true, &windowSize);

	MoveWindow(console, moniterScreenWidth / 4, moniterScreenHeight / 4, consoleWidth, consoleHeight, true);	//ȭ�� ����� ����, ũ�� ����
}

string Log::GetLog()
{
	return this->log;
}

void Log::SetLog(string log)
{
	this->log = log;
}

//��ü���� ���޵� ���ڿ��� ��� ���� log�� �����ϰ� ���(Set ��ü�� �ʿ� ���� ���� ����)
void Log::PrintLog(string orderLog, int enumCase)
{
	this->SetLog(orderLog);				//�� ��ü���� SetLog�� ���� ȣ���ϱ⺸��, PrintLog�� ȣ�⿡�� Set�� ����� ���ÿ� �̷�������� ��

	switch (enumCase) //BattlePrint, StatusPrint, ShopRoomPrint, RestRoomPrint, BuffDebuffRoomPrint
	{
	case PrintEnum::BattlePrint:
		break;
	case PrintEnum::StatusPrint:
		this->PrintStatus();
		break;
	case PrintEnum::ShopRoomPrint:
		break;
	case PrintEnum::RestRoomPrint:
		break;
	case PrintEnum::BuffDebuffRoomPrint:
		break;
	default:
		break;
	}
	cout << this->log << endl;
}

//���� ���� �޴� ���
void Log::PrintStartMenu(int caseNumber)
{
	switch (caseNumber)
	{
	case LogEnum::Menu:
		cout << "���� �޴�" << endl;
		cout << "1. ���ӽ���" << endl;
		cout << "2. ��������" << endl;
		break;
	case LogEnum::Start:
		cout << "������ ���۵˴ϴ�." << endl;
	}
}

void Log::PrintInputError()
{
	cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���." << endl;
}

void Log::PrintGameOver(int caseNumber)	//�÷��̾��� ��� ���� ������ ���ῡ ���� �α� ���
{
	switch (caseNumber)
	{
	case LogEnum::GameOver:
		cout << "����Ͽ����ϴ�." << endl;
		cout << "���ο� ������ �����Ͻðڽ��ϱ�?" << endl;
		break;
	case LogEnum::GameEnd:
		cout << "������ �����մϴ�..." << endl;
		break;
	default:
		break;
	}
}

void Log::PrintBattle()
{

}

void Log::PrintStatus()
{

}