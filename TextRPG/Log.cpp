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

//�̹��� ����� ���� ���ĺ��� �ε����� ��ȯ�����ִ� �޼���
int Log::CharToIndex(char c)
{
	return c - 'a';
}

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

	this->playerData =
	{
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaooggoaaaaaaaaaaaaaaaaa",
		"aaaaaaaaagoghhgoaaaaaaaaaaaaaaaa",
		"aaaaaaaaaoghhhhhaaaaaaaaaaaaaaaa",
		"aaaaaaaaagohahahaaaaaaaaaaaaaaaa",
		"aaaaaaaaagihihihaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaghihihaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaiiiaaaaaaaaaaaaaaapaa",
		"aaaaaaaaemmmiiimmeaaaaaaaaaappaa",
		"aaaaaaahemmeimieeehaaaaaaaapppaa",
		"aaaaaahiemeeeieeeehhaaaaaapppaaa",
		"aaaaaahiemmeememehhhaaaaapppaaaa",
		"aaaaaahiieeeeeemeihhaaaapppaaaaa",
		"aaaaaahiiaeeeeemeahhhaapppaaaaaa",
		"aaaaaahiiaeeeeemfaiihhhfpaaaaaaa",
		"aaaaaahiiaffngnnnaaaiihhaaaaaaaa",
		"aaaaaaiiaaefnnnfeaaaaiihaaaaaaaa",
		"aaaaaaiiammeeeemeeaanfaaaaaaaaaa",
		"aaaaaaihhmmeeeemeeaaaaaaaaaaaaaa",
		"aaaaaaaiiemmemeemeaaaaaaaaaaaaaa",
		"aaaaaaaiheemmmeemeaaaaaaaaaaaaaa",
		"aaaaaaaaibbbaaabbbaaaaaaaaaaaaaa",
		"aaaaaaaaabjbaaabjbaaaaaaaaaaaaaa",
		"aaaaaaaaabjbaaabjbaaaaaaaaaaaaaa",
		"aaaaaaaaabjbaaabjjaaaaaaaaaaaaaa",
		"aaaaaaaaajbbaaabbjaaaaaaaaaaaaaa",
		"aaaaaaaaajbbaaabbjaaaaaaaaaaaaaa",
		"aaaaaaaaameaaaaaemaaaaaaaaaaaaaa",
		"aaaaaaaameeaaaaaeemaaaaaaaaaaaaa",
		"aaaaaammmeeaaaaaeeemmaaaaaaaaaaa",
		"aaaaaaeeeeeaaaaaeeeeeaaaaaaaaaaa"
	};
	this->goblinData =
	{
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaahaaahaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaheeeheaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaimmeieaaaaaaaaaaaaa",
		"aaaaaaaaaaaimemmmeeggaaaaaaaaaaa",
		"aaaaaaaaaaaammmmmmegaaaaaaaaaaaa",
		"aaaaaaaaaaaamoeeomeeaaaaaaaaaaaa",
		"aaaaaaaaaaaamemmmeeeaaaaaaaaaaaa",
		"aaaaaaaaaaaackkkccccaaaaaaaaaaaa",
		"aaaaaaaaaaaickaaakccaaaaaaaaaaaa",
		"aaaaaiiaaaiickaaakcaaaaaaaaaaaaa",
		"aaaaaiimeiiiickkkccaiiaaaaaaaaaa",
		"aaaaaiimmiaaicckccaiiiiaaaaaaaaa",
		"aaaaaaaaaaaaaiccccaiaiiaaaaaaaaa",
		"aaaaaaaaaaaaaaiccaiaaaeeaaaaaaaa",
		"aaaaaaaaaaaaagiaaigaaaiiiaaaaaaa",
		"aaaaaaaaaaaaaamggmeaaaiiiaaaaaaa",
		"aaaaaaaaaaaaaaimeeiaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaiimeeiiaaaaaaaaaaaa",
		"aaaaaaaaaaaaiiieeeiiiaaaaaaaaaaa",
		"aaaaaaaaaaaaiiaaaaaiiaaaaaaaaaaa",
		"aaaaaaaaaaaaameaaaemmaaaaaaaaaaa",
		"aaaaaaaaaaaaeeaaaaameaaaaaaaaaaa",
		"aaaaaaaaaaaiiiaaaaaiiiaaaaaaaaaa",
		"aaaaaaaaaaiiiaaaaaaiiiiaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
	};
	this->orcData =
	{
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaiiiihiaaaaaaaaaaa",
		"aaaaaaaaaaaaaaiihhhiiiaaaaaaaaaa",
		"aaaaaaaaaaaaaaiihhiiiiiaaaaaaaaa",
		"aaaaaaaaaahhhhamiiiimaiihhhhaaaa",
		"aaaaaaaaaaaiiiiaaiiaaiiiiiaaaaaa",
		"aaaaaaaaaaaaipiiiipiiiiiiaaaaaaa",
		"aaaaaaaaaaaaaapmmmmpiiiaaaaaaaaa",
		"aaaaaaaaaaaaaiiiiiiimihhaaaaaaaa",
		"aaaaaaaaaaaiiiiiihiiiiihhaaaaaaa",
		"aaaaaaaaaaihhhhiiiiiihhihhaaaaaa",
		"aaaaaaaaaihiihhhhiihhhhihhhaaaaa",
		"aaaaaaaaihiiihhhhiihhhhihhhhaaaa",
		"aaaaaaaaihiiiiiiiiiiiiiiihhhaaaa",
		"aaaaaaaihhiihiiiiihiiiiiaiihiaaa",
		"aaaaaaahhiahihhhhhhhhhhiiaihiaaa",
		"aaaaaaahhiaihhhhhhhhhhhhiaihhaaa",
		"aaaaaahhhiaiihhhhhhhhhhhiaihhhaa",
		"aaaaahhhiaaihhhhhihhhhhiiaihhhaa",
		"aaaaahhiiaaaihhhhhhhhhiiaaaihhaa",
		"aaaaahiiaaaafffnhiihiinffaaiihaa",
		"aaaaaiiaaaaanffnfnnfnffnffaaiiaa",
		"aaaaaaaaaaafnifnffnffnfnnfaaaaaa",
		"aaaaaaaaaaafnhfnifnfnnhnhfaaaaaa",
		"aaaaaaaaaaanaihninnanihnhfaaaaaa",
		"aaaaaaaaaaaaahhhaananihhhaaaaaaa",
		"aaaaaaaaaaaaahhhiaaaaihhhaaaaaaa",
		"aaaaaaaaaaaaahhhiaaaaiihhaaaaaaa",
		"aaaaaaaaaaaahhhiiaaaaihhhaaaaaaa",
		"aaaaaaaaaaahhhihiaaaaiihhhaaaaaa",
		"aaaaaaaaaaaihiiiaaaaaaiiihaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
	};
	this->trollData =
	{
		"aaaaaaaaaaaaaaiihhaaaaaaaaaaaaaa",
		"aaaaaaanfaaaaihihihaaaaaaaaaaaaa",
		"aaaaaanfffaaaihhhhhaaaaaaaaaaaaa",
		"aaaaaannnfaaihaahaahaaaaaaaaaaaa",
		"aaaaanffffaaihhhhhhhaaaaaaaaaaaa",
		"aaaaannfffaaihhmmmmhhhaaaaaaaaaa",
		"aaaaanfnffhiiimmmmmmhihhiaaaaaaa",
		"aaaaanffffhiiimpeepmhihihhiaaaaa",
		"aaaahnnnfhhihiiiiiiiiiihhhhiaaaa",
		"aaahhhnnnhiiiiiiihhihhiihhhhiaaa",
		"aahhihnnfiaiihhhhhhhhhaiihhhhiaa",
		"aahhhinnfaiihhhhihhhhiaaaiiihhaa",
		"ahhhinnffaiihhhhihhhhiiaaahhhiaa",
		"ahhihnnnaaihiiiihhiiihiaaahhhhaa",
		"aihhhnnfaiihhhhhhhhhhiiaaaihhhaa",
		"aaihhhnfaiihhhhhhhhhhiiaaahhhiaa",
		"aaaihhhhaeihhhhhhhhhhhiaaiiihiaa",
		"aaaaihihaeeiihhhhhhhiieaiihhiaaa",
		"aaaaaiihaoeeiiiiaiiiieeaihhhiaaa",
		"aaaaanfaaooeemmiiiieeeoaaiiiaaaa",
		"aaaaafaagogoemmmmmmeeogoaaaaaaaa",
		"aaaaaaaaooogogoemmmgooooaaaaaaaa",
		"aaaaaaagogiogogogogoogogaaaaaaaa",
		"aaaaaaooooiooioooooiooioaaaaaaaa",
		"aaaaaaaoiogogigoigoigohaaaaaaaaa",
		"aaaaaaaaihhgiiioaoiihohhaaaaaaaa",
		"aaaaaaaaihhoiiaaaoiihhhiaaaaaaaa",
		"aaaaaaaiihhiiaaaaaiihiiaaaaaaaaa",
		"aaaaaaaiiihiiaaaaaaiihhaaaaaaaaa",
		"aaaaaaaihhhiaaaaaaaihihhhaaaaaaa",
		"aaaaaaaiiiiiaaaaaaaiiiiiiaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
	};
	this->wolfData =
	{
		"aaaaaaaaaaaahaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaahhaaaaaaaaaaaaaaaaaa",
		"ahaaaaaaaaahhiaaaaaaaaaaaaaaaaaa",
		"aihaaaaaaaahiaaaaaaaaaaaaaaaaaaa",
		"aaihaaaaaahiiaaaaaaaaaaaaaaaaaaa",
		"aaaihiiihhhiaaaaaaaaaaaaaaaaaaaa",
		"aaahihiiihhhaaaaaaaaaaaaaaaaaaaa",
		"aaahhiiihhhhhaaaaaaaaaaaaaaaaaaa",
		"aaahmhhhmmhhhaaaaaaaaaaaaaaaaaaa",
		"aaahhhihhhhhihaaaaaaaaaaaaaaaaaa",
		"aaahhiihhhhhhhhhaaaaaaaaaaaaaaaa",
		"aaaahhiihhhhhhhhhhaaaaaaaaaaaaaa",
		"aaaahiihhphihhhhhhhhaaaaaaaaaaaa",
		"aaaaipahmmhihhhhhhhhhaaaaaaaaaaa",
		"aaaaaaahmhiihhhhhhhhhhaaaaaaaaaa",
		"aaaaaihhhhihhhihhhhhhhhaaaaaaaaa",
		"aaaaaammiihhhhihhhhhhhhhaaaaaaaa",
		"aaaaaammhhhhhiihihhhhhhhhaaaaaaa",
		"aaaaaammihhhiihhihhhhhhhhhaaaaaa",
		"aaaaaamaihiiiihhiiihiihhhhaaaaaa",
		"aaaaaaaaihiiihhiiiiiiiihhhhaaaaa",
		"aaaaaaaaihaiihhiiiihiihhhhhaaaaa",
		"aaaaaaaahhhahhhiiihiihhhhhhaaaaa",
		"aaaaaaaahhhahhhiiihihhhhhhhaaaaa",
		"aaaaaaaahhhahhhaiihihhhhhhhaaiia",
		"aaaaaaahhhaaahhaiiihhhhhhhaaihhh",
		"aaaaaaahhhaaahhaiiiiiihhhhhihhah",
		"aaaaaaihhhaahhhhiiaaiihhaahhhaaa",
		"aaaaahhhhaaihhhhahhhhhhhaaaaaaaa",
		"aaaaahahaahhhhapahhhhhhaaaaaaaaa",
		"aaaaapapaapaapaaapapaapaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
	};
	this->slimeData =
	{
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaakkkkkaaaaaaaaaaaaaa",
		"aaaaaaaaaaakkkkcckkkaaaaaaaaaaaa",
		"aaaaaaaaaakkkkclcdkkkaaaaaaaaaaa",
		"aaaaaaaaakkkkkccddkkkkaaaaaaaaaa",
		"aaaaaaaaakkkkkkddkkkkkkaaaaaaaaa",
		"aaaaaaaakkkkkkkkkkkkkkkaaaaaaaaa",
		"aaaaaaaakkkkkklckkkkkkkaaaaaaaaa",
		"aaaaaaaakcckkkcdkcckklckaaaaaaaa",
		"aaaaaaaklcckkkkkclcckccgaaaaaaaa",
		"aaaaaaakccdkkkkkcccdkkkkgaaaaaaa",
		"aaaaaakkkddkkkkkkddkgkkgkaaaaaaa",
		"aaaaaakkggkkkkcckkkkkcckgaaaaaaa",
		"aaaaakkkgkkkkkkckkkkccccgkaaaaaa",
		"aaaaakkkkkkkkggkkkkkcccdkkaaaaaa",
		"aaaakkkkkkkkglcggkkkkddgkggaaaaa",
		"aaakkckgkkkgllccgkgkkkkkkkgaaaaa",
		"aakkkcdgkkkgcccdkgggkkkkkkkkaaaa",
		"aakkkkkkkkkgggdgklcggkkkkkkgkaaa",
		"aaaakkkkkkggggkkkcdkgkkkkkggaaaa",
		"aaaaaaakkkggkkkkkggkkkkgaagaaaaa",
		"aaaaaaaakkggkgkkgkkkkkggaaaaaaaa",
		"aaaaaaaaakgaaggkggaaakgaaaaaaaaa",
		"aaaaaaaaaaaaaaggaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
	};
	this->goblinRiderData =
	{
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaiaahaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaiccicaaaaaaaeaaaaaa",
		"aaaaaaaaaaaaiccccciiaaaamaaaaaaa",
		"aagaaaaaaaagacicccicaaamaaeaaaaa",
		"aaeaaaaaaaaeaocoiiccaamaaaaaaaaa",
		"aaagaaaaaagaaiiiicccaeaaaaiiihaa",
		"aaaaeaaaaeaaakcaccchiaaaiiihhiaa",
		"aaaaagaageaaakcaachiiaaiiihhiiaa",
		"aaaaieeeeiaeakcaachiaaaiiiiiiaaa",
		"aaaaieiiecgeeacccemaiaiihhhhaaaa",
		"aaaagghhggggeaaemeeiaihhhhiaaaaa",
		"aaaaoahiggogeehieeeaihhiiiihiiia",
		"aaaaggiiggggepieeeiiiiiiiihhhiaa",
		"aaaaagiiiggppiiiaiiiiiiiihiiiaaa",
		"aaaaaaiiiaapiaaiiaaiiiahhhhiaaaa",
		"aaaaaahahaaaaaeiaiahiidbaiaaaaaa",
		"aaaaaaaaaaaaaeiaaiaaidddbaaaaaaa",
		"aaaaaaaaaaaaeiaaaiaaahhhiaaaaaaa",
		"aaaaaaaaaaaiaaaaieagghhiiaaaaaaa",
		"aaaaaaaaaaaaaaaieaaoooccaaaaaaaa",
		"aaaaaaaaaaaaaiaeaaopgooggaaaaaaa",
		"aaaaaaaaaaaaaaaaaogoppgggaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaooggggaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
	};
	this->twinHeadTrollData =
	{
		"aaaaaaaaaaaahhhhaahhhhaaaanfaaaa",
		"aaaaaaanfaaihhhhhiihhhhaannnfaaa",
		"aaaaaannffahihiihihihihaannnnfaa",
		"aaaaaannnfhaahaahiaahaahafnnffaa",
		"aaaaanfnffhhhhhiihhhhhhhanffnfaa",
		"aaaaannfnfheeeehihheeeehhanfnfaa",
		"aaaaannfnfmmmemmihmmemmmhannnfaa",
		"aaaaannfffmpmmpmiimpmmpmhinffaaa",
		"aaaahnnnfhhhhhhhiihhhhhhiinnfaaa",
		"aaahhhnnnhiiiiiihhiiiiiihinnfaaa",
		"aahhihnnfiihhiihhhhhhhiiihnnfiaa",
		"aahhhinnfaihhhhhihhhhiiiannfhhaa",
		"ahhhinnffahihhhhihhhhiiaannfhiaa",
		"aihhhnnnaaihiiiihhiiiiiaannfhiaa",
		"aihhhnnfaihhhhhhhhhhhiiaaanfhiaa",
		"aaihhhnfaihhhhhhhhhhhiiaaanfhiaa",
		"aaaihhhhaaihhhhhhhhhhhiaainfhiaa",
		"aaaaihhhaaeihhhhhhhhiiaahhhhiaaa",
		"aaaaaihhageeiiihahiiiaaaihhhiaaa",
		"aaaaanfaaggeeeeiiiieeagaaiiiaaaa",
		"aaaaafaaggggeeeeeeeeegggaaaaaaaa",
		"aaaaaaaaggggogoeeeegggggaaaaaaaa",
		"aaaaaaagggiggogogogoggggaaaaaaaa",
		"aaaaaaggggigoioooooiggigaaaaaaaa",
		"aaaaaaagiggogigoigoigghiaaaaaaaa",
		"aaaaaaaaihhghiigaoiiighiaaaaaaaa",
		"aaaaaaaaihhohiaaaoiiihhhaaaaaaaa",
		"aaaaaaaihiihiaaaaaihhhhaaaaaaaaa",
		"aaaaaaaiihhhiaaaaaaiihhaaaaaaaaa",
		"aaaaaaaihhhhaaaaaaaihiihhaaaaaaa",
		"aaaaaaaiiiiiaaaaaaaiihhhhaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
	};
	this->treantData =
	{
		"aaaaaaaakkaakkkmaaaaaaaaaaaaaaaa",
		"aaaaaaaakkkkkkefmfeaaaaaaaaaaaaa",
		"aaaaaamkmekkmekefmkkaaaaaaaaaaaa",
		"aaaaamakekkkeekkmfmckkkaaaaaaaaa",
		"aaaaaaekkkkkkkkefmfekckkkkaaaaaa",
		"aaaaaefkkmmmmkkkefmekckkkooaaaaa",
		"aaaaaakkckkkkkafafcmkookccokaaaa",
		"aaaaaakkeccccckececccckkccookaaa",
		"aaaaaafkekccockkckkkkccokkkocaaa",
		"aaaaaaakkkccokccckkccccccocockaa",
		"aaaaaaakkcaackcckkkkcccccokkccaa",
		"aaaaaaakkcaaaaccckokkccccokkkkaa",
		"aaaaaaaokcaaackkckockkccaacckoaa",
		"aaaaaaaoccaaaakckkkcckccaaackoka",
		"aaaaaaaoccaaaackcckkccccaaaakock",
		"aaaaaaackkcaaaockckckcccaaaackka",
		"aaaaaaaakkcaaaokcccckcccaaaaccka",
		"aaaaaaakokcaaakkccccccccaaaackka",
		"aaaaaaakokcaaakccccackccaaaackka",
		"aaaaaakckcccaackcccaccccaaakckka",
		"aaaaakcccccaakkcccoackccaaakakca",
		"aaaackccaaaaakkcoccakkcaaaaoacck",
		"aaackccaaaaakkcoocaaakkcaaaoaoao",
		"aackkccaaaakkkccccaaakkckcaoaoao",
		"ackkckcaaaakcccccaaaaakkkaaoaoao",
		"akakckaaaaackcocaaaaaacckaaoaoao",
		"aoaoaoaaaaackccaaaaaaakckcaaaoao",
		"aoaoaoaaaaakcccaaaaaaackcccaaoao",
		"aoaoaoaaaaakckcaaaaaaackccaaaoao",
		"aaaoaoaaaakkkccaaaaaakckccaaaoaa",
		"aaaoaaaaaakkcccaaaaaakkkccaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
	};
	this->dragonData =
	{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aappphaaaaaaaaaaaaaaaaaaaaaaippa",
		"aaaaiiphhpiaaaaaaaaaaaihhppiiaaa",
		"aaaaaaaaiihpppaaaaapppiiaaaaaaaa",
		"aaaaaaaaaiphpiaaaaaaaaaaaaaaaaaa",
		"aaaaaaiiphihiiaaaahhphpidiiaaaaa",
		"aaaaihhiaiihphaahhphhphhpphiiiaa",
		"aahiiaaaiiiaaphhhhiiidhiipihaiia",
		"aaaaaaaiiaaaaabdhidbbbbdidphdaaa",
		"aaaaaaiiaaaaaaihidaaaaaabiiphaaa",
		"aaaaahaaaaaaaihiiaaaadaaadhhpdaa",
		"aaaaaaaaaahaaihidaaaaaiaaaihhdaa",
		"aaaaaaaaahiabiiiaaaaaaiaaahpiiaa",
		"aaaaaaaphiaaadidaaaaaaaaahhhdaaa",
		"aaaaaphhhpiiaaadaaaaaaaahphddaaa",
		"aaaapphffhpiiddaaaaaaaaphhiidaaa",
		"aaphphhfhhdhppipihhhhphhihdbaaaa",
		"appppphhhiidihpihhiihhhihdbaaaaa",
		"apaaaihidhibdhddddhdhdidbbaaaaaa",
		"aaaaaahdaaaaaadbiababdaaaaaaaaaa",
		"aaaaaaiaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaidaaaaadaaaaaaabaadaaaaaaaa",
		"aaaaabaaaaaaabibabbddbdbiaaaaaaa",
		"aaaaaaaaaaaaaibhaaaaaaiiidaaaaaa",
		"aaaaaaaaaaaaaaihpaaaaadhphaaaaaa",
		"aaaaaaaaaaaaaadiipaaaaahhiaaaaaa",
		"aaaaaaaaaaaabaabhipaaaihhdaaaaaa",
		"ahaaaaaaaaaidaaadihhiihiiaaaaaaa",
		"aaihaaaaaahidaaaadddiiibaaaaaaaa",
		"aaaihhphihiiaaaaaaabddaaaaaaaaaa",
		"aaaaaihididaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
	};
}

const string& Log::GetLog()
{
	return this->log;
}

void Log::SetLog(string log)
{
	this->log = log;
}

//��ü���� ���޵� ���ڿ��� ��� ���� log�� �����ϰ� ���
template<typename T>
void Log::PrintLog(string orderLog, const T& object)
{
	this->SetLog(orderLog);				//�� ��ü���� SetLog�� ���� ȣ���ϱ⺸��, PrintLog�� ȣ�⿡�� Set�� ����� ���ÿ� �̷�������� ��

	/*if constexpr (is_same_v<T, Character>)	//���� ��ü�� ���� Print �ٸ��� ��
	{

	}
	else if constexpr (is_same_v<t, battlemanager>)
	{

	}*/
	cout << this->log;
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

//�̹��� Initialize Ȯ�ο� ���������� ���� �ʿ�
void Log::TestPrint()
{
	int colorIndex = 0;
	vector<string> &data = treantData;
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