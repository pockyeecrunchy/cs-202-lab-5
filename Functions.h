#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "HashTable.h"
#include "Standard.h"

//Prototypes
void CreateNode(node* pNewNode, string name);
void ReadDataFile(ifstream& fin, hashTable& table);
void OpenFiles(ifstream& fin, ofstream& fout);
void CloseFiles(ifstream& fin, ofstream& fout);

#endif 