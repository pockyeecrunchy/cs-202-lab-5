#ifndef HASHTABLE_H
#define HASHTABLE_H

struct record
{
    string name;
    string teams[3];
    int numberOfTeams;
};

//-------------------------------------------------------------
// Structure: node
//-------------------------------------------------------------
struct node
{
    record data;
    node* pNext;
};

class hashTable {
private:
    node** _table;
    int _nodeCount;

    //private helper methods:
    void IncreaseNodeCount();
    void DecreaseNodeCount();
    int GetHashValue(string name);

    void FindLocation(node* pList, node** pCurrent, node** pPrev, string value);
    void InsertNewNode(node** pList, node* pCurrent, node* pPrev, node* pTemp);

    void PrintOneRecord(ofstream& out, node oneRecord);

    void DeleteOneNode(node** pList, node* current, node* prev);
    void FreeOneRow(node** pRow);

public:

    //Constructor and Destructor
    hashTable();
    ~hashTable();

    node* GetRow(int index);

    void PrintHeader(ofstream& out);
    bool IsEmpty(node* pNode);
    int GetNodeCount();

    void Insert(node* pNewNode);
    
    void PrintOneRow(ofstream& out, node* pFirstNode);
    void PrintAllRows(ofstream& out);

    void Delete(string name);

};

#endif HASHTABLE_H