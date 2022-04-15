#ifndef _RAGGEDARRAY_H_
#define _RAGGEDARRAY_H_

#include<iostream>

struct RaggedArray
{
	int** data = NULL;
};

int askUserScan();
int askUserSave();

int scanRowsSize();
int scanColsSize();

int** allocateRaggedArray(RaggedArray mas);

void fillRaggedArrayRandom(RaggedArray mas);

void fillRaggedArrayFromTxtFile(const char* filename, RaggedArray& mas);

void writeRaggedArrayToTxtFile(const char* filename, RaggedArray mas);

void fillRaggedArrayFromBinFile(const char* filename, RaggedArray& mas);

void writeRaggedArrayToBinFile(const char* filename, RaggedArray mas);

void outputRaggedArrayToScreen(RaggedArray mas);

void freeRaggedArray(RaggedArray mas);

int getRows(RaggedArray mas);

void addNewRowInRaggedArray(RaggedArray& mas, int col);

void deleteLastRowInRaggedArray(RaggedArray& mas);

void deleteRowInRaggedArray(RaggedArray& mas, int number);

#endif