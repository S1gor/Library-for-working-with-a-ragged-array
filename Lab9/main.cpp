#include"RaggedArray.h"

int main()
{
	system("chcp 1251"); system("cls");
	srand(time(0));

	RaggedArray mas;

	char filenameTxt[] = "1.txt";
	char filenameBin[] = "2.bin";

	switch (askUserScan())
	{
	case 1:
		mas.data = allocateRaggedArray(mas);
		fillRaggedArrayRandom(mas);
		break;
	case 2:
		fillRaggedArrayFromTxtFile(filenameTxt, mas);
		break;
	case 3:
		fillRaggedArrayFromBinFile(filenameBin, mas);
		break;
	}

	outputRaggedArrayToScreen(mas);

	switch (askUserSave())
	{
	case 1:
		writeRaggedArrayToTxtFile(filenameTxt, mas);
		break;
	case 2:
		writeRaggedArrayToBinFile(filenameBin, mas);
		break;
	case 3:
		exit(0);
	}

	freeRaggedArray(mas);

	return 0;
}