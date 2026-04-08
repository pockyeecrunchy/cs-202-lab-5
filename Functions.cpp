
#include "Standard.h"
#include "Functions.h"

void CreateNode(node* pNewNode, string name)
{
    //Set player name
    pNewNode->data.name = name;

    //Initialize next pointer to nu
    pNewNode->pNext = nullptr;

    //Initialize number of teams to 0
    pNewNode->data.numberOfTeams = 0;
}

void ReadDataFile(ifstream& fin, hashTable& table)
{
    //create two local string variables
    string name;
    string team;

    //Create a local node pointer
    node* pNewNode = nullptr;


    // Read until end of file
    while (getline(fin, name))
    {
        // Skip empty lines (just in case)
        if (name == "")
            continue;

        // Create a new node
        pNewNode = new node;

        // Initialize node
        CreateNode(pNewNode, name);

        // Read teams (they start with '!') and the number of teams is less than 3
        while (fin.peek() == '!' && pNewNode->data.numberOfTeams < 3)
        {
            // Ignore the next character
            fin.ignore();

            // Read the team name
            getline(fin, team);

            // Store team in array
            pNewNode->data.teams[pNewNode->data.numberOfTeams] = team;

            // Increase team count
            pNewNode->data.numberOfTeams++;
        }

        // Insert node into hash table
        table.Insert(pNewNode);
    }
}

void OpenFiles(ifstream& fin, ofstream& fout)
{
    // Open input file
    fin.open("players.txt");

    // Open output file
    fout.open("output.txt");
}

void CloseFiles(ifstream& fin, ofstream& fout)
{
    //closes both of the files
    fin.close();
    fout.close();
}

