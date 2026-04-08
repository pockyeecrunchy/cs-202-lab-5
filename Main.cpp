#include "Standard.h"
#include "HashTable.h"
#include "Functions.h"


int main()
{
    // Enable memory leak checking
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Create hash table
    hashTable table;

    // File streams
    ifstream fin;
    ofstream fout;

    // Open files
    OpenFiles(fin, fout);

    // Print header (both screen + file)
    table.PrintHeader(fout);   

// quick & simple screen version
    PrintDivider(cout, STAR, SCREEN_WIDTH);
    cout << left
        << setw(30) << "Name"
        << setw(30) << "Team 1"
        << setw(30) << "Team 2"
        << setw(30) << "Team 3" << endl;
    PrintDivider(cout, STAR, SCREEN_WIDTH);

    // Read data into hash table
    ReadDataFile(fin, table);

    // print first row 
    table.PrintOneRow(fout, table.GetRow(0)); 

    // Print number of records printed
    fout << "\nRecords Printed: " << table.GetNodeCount() << endl;

    int totalNodes = 0;

    for (int index = 0; index < TABLE_SIZE; index++)
    {
        int count = 0;
        node* current = table.GetRow(index);

        while (current != nullptr)
        {
            count++;
            current = current->pNext;
        }

        cout << "Row " << index << ": " << count << " nodes" << endl;
        totalNodes += count;
    }

    //Print the average
    double average = (double)totalNodes / TABLE_SIZE;
    cout << "Average nodes per row: " << average << endl;

    //delete the following names
    table.Delete("Aaron Hernandez");
    table.Delete("Aaron Jones");
    table.Delete("Donald Allen");
    table.Delete("Donald Thompson");
    table.Delete("Joe Montana");
    table.Delete("Frank Turner");
    table.Delete("Gabriel Diaz");
    table.Delete("Jerry Rice");
    table.Delete("Zachary Brown");
    table.Delete("Zachary Brooks");

    //print after deletion
    fout << "\nAfter Deletions:\n";
    table.PrintOneRow(fout, table.GetRow(0));

    fout << "\nRecords Printed: " << table.GetNodeCount() << endl;

    // Recalculate stats
    totalNodes = 0;

    for (int index = 0; index < TABLE_SIZE; index++)
    {
        int count = 0;
        node* current = table.GetRow(index);

        while (current != nullptr)
        {
            count++;
            current = current->pNext;
        }

        cout << "Row " << index << ": " << count << " nodes" << endl;
        totalNodes += count;
    }

    average = (double)totalNodes / TABLE_SIZE;
    cout << "Average nodes per row: " << average << endl;

    // Close the files
    CloseFiles(fin, fout);

    return 0;
}

//The number of elements in each row in the hash table is around 60 nodes.
//Therefore, when the application is supposed to find, insert, or delete an element, 
// the program will simply traverse only 60 nodes rather than traverse all 6000 of them. 
// This is a significant difference. From the perspective of Big O notation, 
//the algorithm used with hash tables reduces the time complexity on average to O(n/k), 
// where n represents the total number of elements in the array (6000), while k represents 
// the number of buckets (100). Because the number of buckets (k) is constant, it can be 
// concluded that the Big O notation is essentially O(1) on average: constant time!
//This compares quite favorably to linear linked list implementation,
// because the latter must traverse up to all 6000 elements in its worst case scenario, 
// thus resulting in a time complexity of O(n).With this in mind, we have reduced the 
// amount of processing needed by 100 times.
//
//