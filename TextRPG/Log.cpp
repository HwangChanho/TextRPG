#include "Log.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Log* Log::instance = nullptr;

Log* Log::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Log();
	}
	return instance;
}

//�̹��� ����� ���� ���ĺ��� �ε����� ��ȯ�����ִ� �޼���
int Log::CharToIndex(char c)
{
	return c - 'a';
}

vector<string> Log::PNGImageToData(string filePath)
{
	vector<string> data;
	string line;
	const char alphabet[] = "abcdefghijklmnop";		//���� ������� ���ĺ����� ��ȯ��
	// PNG ���� �ε�
	int width, height, channels;
	unsigned char* image = stbi_load(filePath.c_str(), &width, &height, &channels, 3); // RGB �������θ� �б�
	if (!image) {
		std::cerr << "�̹��� �о���� ����" << std::endl;
		exit(1);
	}

	//�̹����� �ȼ����� ���ڷ� ��ȯ
	for (int y = 0; y < height; y++)
	{
		line += "\"";
		for (int x = 0; x < width; x++)
		{
			int pixelIndex = (y * width + x) * 3;	//3ä�� RGB
			int r = image[pixelIndex + 0];
			int g = image[pixelIndex + 1];
			int b = image[pixelIndex + 2];

			//�ȼ��� RGB���� ���� ����� ���� �ε��� ã��
			int closestColor = GetClosestColorIndex(r, g, b);

			line += alphabet[closestColor];
		}
		data.push_back(line);
		line = "";
	}
	return data;
}

// RGB ����� �ȷ�Ʈ ���� ���� ��Ŭ���� �Ÿ� ���
int Log::GetClosestColorIndex(int r, int g, int b) {
	int closestIndex = 0;
	int minDistance = INT_MAX;

	for (int i = 0; i < NUMBER_OF_COLOR; i++) {
		int dr = r - palette[i][0];
		int dg = g - palette[i][1];
		int db = b - palette[i][2];
		int distance = dr * dr + dg * dg + db * db;

		if (distance < minDistance) {
			minDistance = distance;
			closestIndex = i;
		}
	}
	return closestIndex;
}

//void Log::ProcessPNG(string filePath)
//{
//	// PNG ���� �ε�
//	int width, height, channels;
//	unsigned char* image = stbi_load(filePath.c_str(), &width, &height, &channels, 3); // RGB �������θ� �б�
//	if (!image) {
//		std::cerr << "�̹��� �о���� ����" << std::endl;
//		return;
//	}
//}

//����� ũ���� 4���� 1 ũ��� �ܼ� â ũ�⸦ �����ϰ� ����� ����� �����, �� stringŸ�� ���Ϳ� �̹��� �ؽ�Ʈ �ʱ�ȭ(32X32 PNG������ 0~15�� ���� ���� ���ĺ����� ��ȯ -> �ܼ� ���� ��ȯ�� ����)
void Log::Initialize()
{
	//���� ũ��� �ܼ� ���� ũ�� ���ϰ� â ũ�� ��������
	COORD bufferSize;
	bufferSize.X = bufferWidth;
	bufferSize.Y = bufferHeight;
	cout << bufferSize.X << ", " << bufferSize.Y << endl;
	SetConsoleScreenBufferSize(consoleHandle, bufferSize);
	SMALL_RECT windowSize = { 0, 0, bufferWidth - 1, bufferHeight - 1 };	//������ ũ�� ����
	SetConsoleWindowInfo(consoleHandle, true, &windowSize);

	MoveWindow(console, moniterScreenWidth / 4, moniterScreenHeight / 4, consoleWidth, consoleHeight, true);	//ȭ�� ����� ����, ũ�� ����

	this->playerData = PNGImageToData("images/Player.png");
	this->goblinData = PNGImageToData("images/Goblin.png");
	this->orcData = PNGImageToData("images/Orc.png");
	this->trollData = PNGImageToData("images/Troll.png");
	this->wolfData = PNGImageToData("images/Wolf.png");
	this->slimeData = PNGImageToData("images/Slime.png");
	this->goblinRiderData = PNGImageToData("images/GoblinRider.png");
	this->twinHeadTrollData = PNGImageToData("images/TwinHeadTroll.png");
	this->treantData = PNGImageToData("images/Treant.png");
	this->dragonData = PNGImageToData("images/Dragon.png");
}

const string& Log::GetLog()
{
	return this->log;
}

void Log::SetLog(string log)
{
	this->log = log;
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

//void Log::PrintBattle(BattleManager& object)
//{
//	string monsterName;
//}

void Log::PrintStatus()
{
	this->PrintImage(playerData);
}

void Log::PrintImage(vector<string>& data)
{
	int colorIndex = 0;
	for (int i = 0; i < data.size(); ++i)
	{
		for (int j = 0; j < IMAGE_SIDE_LENGTH; j++)	//IMAGE_SIDE_LENGTH 32
		{
			int colorIndex = this->CharToIndex(data[i][j]);		//���ĺ��� �ε����� ��ȯ
			if (colorIndex >= 0 && colorIndex <= NUMBER_OF_COLOR)	//NUMBER_OF_COLOR 16
			{
				SetConsoleTextAttribute(consoleHandle, colorIndex);	//���� �ش��ϴ� �ε������� �־� �ܼ� �ؽ�Ʈ�� ���� ����
				cout << "��";	//�� ���� �´� ��Ʈ ���
			}

		}
		cout << "\n";	//�� ����
	}
	SetConsoleTextAttribute(consoleHandle, 15);		//�̹��� ����� �������Ƿ� �ٽ� �� ����(index:15)���� ����
}