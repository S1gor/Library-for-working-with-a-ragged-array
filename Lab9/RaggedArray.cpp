#include"RaggedArray.h"

int askUserScan()
{
	int choice = 0;
	do {
		printf("Введите способ записи:\n1 - заполнить массив рандомно\n2 - заполнить массив из файла txt\n3 - заполнить массив из файла bin\nВыбор:");
		scanf_s("%d", &choice);
	} while (choice > 3 || choice < 1);
	return choice;
}
int askUserSave()
{
	int choice = 0;
	do {
		printf("Введите способ сохранения:\n1 - в файл txt\n2 - в файл bin\n3 - выйти\nВыбор:");
		scanf_s("%d", &choice);
	} while (choice > 3 || choice < 1);
	return choice;
}

int scanRowsSize()
{
	int choice = 0;
	do {
		printf("Введите количество строк (0;1000]:\n");
		scanf_s("%d", &choice);
	} while (choice > 1000 || choice < 0);
	return choice;
}
int scanColsSize()
{
	int choice = 0;
	static int counter = 0;
	counter++;
	do {
		printf("№%d - ", counter);
		scanf_s("%d", &choice);
	} while (choice > 1000 || choice < 0);
	return choice;
}

int** allocateRaggedArray(RaggedArray mas)
{
	int rows = scanRowsSize();
	mas.data = (int**)malloc(sizeof(int*) * (rows + 1));
	mas.data[rows] = NULL;

	printf("Введите количество столбцов (0;1000]:\n");
	for (int i = 0; mas.data[i] != NULL; i++)
	{
		int cols = scanColsSize();
		mas.data[i] = (int*)malloc(sizeof(int) * (cols + 1));
		mas.data[i][cols] = NULL;
	}
	return mas.data;
}

void fillRaggedArrayRandom(RaggedArray mas)
{
	for (int i = 0; mas.data[i] != NULL; i++)
		for (int j = 0; mas.data[i][j] != NULL; j++)
			mas.data[i][j] = rand() % 501;
}

void fillRaggedArrayFromTxtFile(const char* filename, RaggedArray& mas)
{
	int rows = 0, cols = 0;

	FILE* f;
	if (fopen_s(&f, filename, "r") != 0) exit(1);

	fscanf_s(f, "%d", &rows);
	mas.data = (int**)malloc(sizeof(int*) * (rows + 1));
	mas.data[rows] = NULL;

	for (int i = 0; mas.data[i] != NULL; i++)
	{
		fscanf_s(f, "%d", &cols);

		mas.data[i] = (int*)malloc(sizeof(int) * (cols + 1));
		mas.data[i][cols] = NULL;

		for (int j = 0; mas.data[i][j] != NULL; j++)
			fscanf_s(f, "%d", &mas.data[i][j]);
	}

	fclose(f);
}

void writeRaggedArrayToTxtFile(const char* filename, RaggedArray mas)
{
	FILE* f;
	if (fopen_s(&f, filename, "w") != 0) exit(1);

	int rows = 0;
	while (mas.data[rows] != NULL) rows++;

	fprintf(f, "%d\n", rows);

	for (int i = 0; mas.data[i] != NULL; i++)
	{
		int cols = 0;
		while (mas.data[i][cols] != NULL) cols++;
		fprintf(f, "%d ", cols);
		for (int j = 0; mas.data[i][j] != NULL; j++)
			fprintf(f, "%d ", mas.data[i][j]);
		fprintf(f, "\n");
	}

	fclose(f);
}

void fillRaggedArrayFromBinFile(const char* filename, RaggedArray& mas)
{
	int rows = 0, cols = 0;

	FILE* f;
	if (fopen_s(&f, filename, "rb") != 0) exit(1);

	fread(&rows, sizeof(int), 1, f);
	mas.data = (int**)malloc(sizeof(int*) * (rows + 1));
	mas.data[rows] = NULL;

	for (int i = 0; mas.data[i] != NULL; i++)
	{
		fread(&cols, sizeof(int), 1, f);
		mas.data[i] = (int*)malloc(sizeof(int) * (cols + 1));
		mas.data[i][cols] = NULL;

		fread(mas.data[i], sizeof(int), cols, f);
	}

	fclose(f);
}

void writeRaggedArrayToBinFile(const char* filename, RaggedArray mas)
{
	int rows = 0;
	FILE* f;
	if (fopen_s(&f, filename, "wb") != 0) exit(1);

	while (mas.data[rows] != NULL) rows++;

	fwrite(&rows, sizeof(int), 1, f);

	for (int i = 0; mas.data[i] != NULL; i++)
	{
		int cols = 0;
		while (mas.data[i][cols] != NULL) cols++;
		fwrite(&cols, sizeof(int), 1, f);
		fwrite(mas.data[i], sizeof(int), cols, f);
	}

	fclose(f);
}

void outputRaggedArrayToScreen(RaggedArray mas)
{
	printf("\n");
	for (int i = 0; mas.data[i] != NULL; i++)
	{
		for (int j = 0; mas.data[i][j] != NULL; j++)
			printf("%5d", mas.data[i][j]);
		printf("\n");
	}
	printf("\n");
}

void freeRaggedArray(RaggedArray mas)
{
	for (int i = 0; mas.data[i] != NULL; i++)
		free(mas.data[i]);
	free(mas.data);
}

int getRows(RaggedArray mas)
{
	int rows = 0;

	while (mas.data[rows] != NULL) rows++;

	return rows;
}

void addNewRowInRaggedArray(RaggedArray& mas, int col)
{
	int rows = 0;

	if (mas.data != NULL)
		rows = getRows(mas);

	mas.data = (int**)realloc(mas.data, sizeof(int*) * (rows + 2));
	mas.data[rows + 1] = NULL;
	
	mas.data[rows] = (int*)malloc(sizeof(int) * (col + 1));
	mas.data[rows][col] = NULL;

	for (int i = 0; mas.data[rows][i] != NULL; i++)
		mas.data[rows][i] = 7;
}

void deleteLastRowInRaggedArray(RaggedArray& mas)
{
	int rows = 0;

	if (mas.data != NULL)
	{
		rows = getRows(mas);

		free(mas.data[rows]);

		mas.data = (int**)realloc(mas.data, sizeof(int*) * rows);
		mas.data[rows - 1] = NULL;
	}
}

void deleteRowInRaggedArray(RaggedArray& mas, int number)
{
	int rows = getRows(mas);

	int* tmp = mas.data[number - 1];

	for (int i = number - 1; mas.data[i] != NULL; i++)
		mas.data[i] = mas.data[i + 1];

	mas.data[rows - 1] = tmp;

	deleteLastRowInRaggedArray(mas);
}