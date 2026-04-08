#include "Standard.h"
#include "HashTable.h"

//Constructor
hashTable::hashTable() {

	_nodeCount = 0;
	//Create an array of node pointers
	_table = new node * [TABLE_SIZE];

	// we want to initiate each row to null
	for (int index = 0; index < TABLE_SIZE; index++) 
	{
		_table[index] = nullptr;

	}
}

//Destructor
hashTable::~hashTable() {
	for (int index = 0; index < TABLE_SIZE; index++) 
	{
		FreeOneRow(&_table[index]);
	}
	delete[] _table;
}

//Is empty
bool hashTable::IsEmpty(node* pNode)
{
	return (pNode == nullptr);

}

void hashTable::FreeOneRow(node** pRow)
{
	node* current = *pRow;

	while (current != nullptr)
	{
		node* temp = current;
		current = current->pNext;

		temp->pNext = nullptr;
		delete temp;
	}
	*pRow = nullptr;
}

void hashTable::IncreaseNodeCount()
{
	//increase the _nodeCount by 1
	_nodeCount++;
}

void hashTable::DecreaseNodeCount()
{
	//decrease the _nodeCount by 1
	_nodeCount--;
}

int hashTable::GetNodeCount()
{
	//return the _nodeCount
	return _nodeCount;
}

int hashTable::GetHashValue(string name) 
{
	int sum = 0;

	//using the for loop, we add up the ASCII values of all the characters in the name
	for (int index = 0; index < name.length(); index++)
	{
		sum += sum += (int)name[index];
	}
	//divide the total by the number of rows and return the remainder
	return sum % TABLE_SIZE;

}

void hashTable::Insert(node* pNewNode)
{
	//current and previous 
	node* current = nullptr;
	node* prev = nullptr;

	//obtain the hash index!
	int index = GetHashValue(pNewNode->data.name);

	//Find the correct position
	FindLocation(_table[index], &current, &prev, pNewNode->data.name);

	//Insert the node
	InsertNewNode(&_table[index], current, prev, pNewNode);

	//Update the count!
	IncreaseNodeCount();
}

void hashTable::FindLocation(node* pList, node** pCurrent, node** pPrev, string value)
{

	// Initialize pointers:
	*pCurrent = pList;  // start at the head of the list
	*pPrev = nullptr;  // no previous node yet

	while (*pCurrent != nullptr && (*pCurrent)->data.name < value)
	{
		// Move prev up to current
		*pPrev = *pCurrent;  

		// Advance current to the next node
		*pCurrent = (*pCurrent)->pNext;
	}
}

void hashTable::InsertNewNode(node** pList, node* pCurrent, node* pPrev, node* pTemp)
{
	// Case 1: Insert at the FRONT of the list

	// Insert at the FRONT of the list
	if (pPrev == nullptr)
	{
		// New node points to current head
		pTemp->pNext = *pList;

		// Update head to be the new node
		*pList = pTemp;
	}
	else
	{
		// Case 2: Insert in the MIDDLE or END

		// New node points to current node
		pTemp->pNext = pCurrent;

		// Previous node now points to new node
		pPrev->pNext = pTemp;
	}
}

void hashTable::Delete(string name)
{
	// Find which row the name belongs to
	int index = GetHashValue(name);

	// Set up traversal pointers
	node* current = _table[index];
	node* prev = nullptr;

	// Traverse the linked list to find the node
	while (current != nullptr && current->data.name != name)
	{
		prev = current;
		current = current->pNext;
	}

	// If node NOT found
	if (current == nullptr)
	{
		cout << "Name is not found: " << name << endl;
		return;
	}

	//Node FOUND? Delete it
	DeleteOneNode(&_table[index], current, prev);

	// Update node count by decreasing it
	DecreaseNodeCount();
}

void hashTable::DeleteOneNode(node** pList, node* current, node* prev)
{
	//Deleting the first  node
	if (prev == nullptr)
	{
		// Move head to next node
		*pList = current->pNext;
	}
	else
	{
		//Deleting the middle or end node
		prev->pNext = current->pNext;
	}

	//disconnect node before deleting
	current->pNext = nullptr;

	// Delete the node
	delete current;
}

void hashTable::PrintAllRows(ofstream& out)
{
	// Loop through every row in the hash table
	for (int index = 0; index < TABLE_SIZE; index++)
	{
		// Print the linked list at this row
		PrintOneRow(out, _table[index]);
	}
}

#include <iomanip> // REQUIRED for setw

void hashTable::PrintHeader(ofstream& out)
{
	// Print top divider line
	PrintDivider(out, STAR, SCREEN_WIDTH);

	// Print column headers using setw (of 30) for alignment
	out << left
		<< setw(30) << "Name"
		<< setw(30) << "Team 1"
		<< setw(30) << "Team 2"
		<< setw(30) << "Team 3"
		<< endl;

	// Print bottom divider line
	PrintDivider(out, STAR, SCREEN_WIDTH);
}

void hashTable::PrintOneRow(ofstream& out, node* pFirstNode)
{
	node* current = pFirstNode;

	// Traverse the linked list
	while (current != nullptr)
	{
		// Print the current node's data
		PrintOneRecord(out, *current);

		// Move to next node
		current = current->pNext;
	}
}

void hashTable::PrintOneRecord(ofstream& out, node oneRecord)
{
	//print the player's names
	out << left << setw(30) << oneRecord.data.name;

	//Team 1
	//If the player has at least 1 team, print it
	if (oneRecord.data.numberOfTeams >= 1)
		out << setw(30) << oneRecord.data.teams[0];
	else
		//otherwise print "No team"
		out << setw(30) << "No team";

	//Team 2
	//If the player has at least 2 teams, print it.
	if (oneRecord.data.numberOfTeams >= 2)
		out << setw(30) << oneRecord.data.teams[1];
	else
		//otherwise print "No team"
		out << setw(30) << "No team";

	//Team 3
	//If the player has at least 3 teams, print it.
	if (oneRecord.data.numberOfTeams >= 3)
		out << setw(30) << "No team";
	else
		//otherwise print "No team"
		out << setw(30) << "No team";
	out << endl;
}

node* hashTable::GetRow(int index)
{
	return _table[index];
}