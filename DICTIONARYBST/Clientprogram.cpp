//clientguy

#include "BinarySearchTree.h"
#include "Exception.h"
#include <string>
#include <fstream>
using namespace std;

void printRed(const string input)
{
    cout << "\033[1;31m" << input << "\033[0m" << endl;
}

//prints an exception message
//pre except has been thrown
//post except is printed to the screen with two newlines before and after
//usage PrintExceptionMessage(except);
void PrintExceptionMessage(const Exception &except)
{
    printRed(except.What());
}

//opens an input file with a chosen name
//pre filename is assigned
//post if filename exists in the same directory as the program, it is opened
//      with its file pointer at the beginning of the file
//      else an error message is printed
//usage OpenInputFile(infile, filename);
void OpenInputFile(ifstream &inputFile, string filename)
{
    inputFile.open(filename);
    if (inputFile.fail())
    {
        printRed("Failed to open file.");
        exit(1);
    }
}

//opens an output file with a chosen name
//pre filename is assigned
//post if filename exists in the same directory as the program, it is opened
//      with its file pointer at the beginning of the file
//      else an error message is printed
//usage OpenInputFile(outfile, filename);
void OpenOutputFile(ofstream &outputFile, string filename)
{
    outputFile.open(filename);
    if (outputFile.fail())
    {
        printRed("Failed to open file.");
        exit(1);
    }
}

void CreateTreeFromInputFile(ifstream &inputFile, BinarySearchTree &tree)
{
    int numberItems;

    inputFile >> numberItems;
    inputFile.get();
    try
    {
        tree.rebalance(inputFile, numberItems);
    }
    catch (Exception except)
    {
        PrintExceptionMessage(except);
    }
}

void PrintMenu()
{
    cout << "Your options are:" << endl;

    cout << "\033[1;32md\033[0m  : deletes a phone number and name from the dictionary " << endl;
    cout << "\033[1;32mf\033[0m  : find the name of the contact, given her/his phone number" << endl;
    cout << "\033[1;32mi\033[0m  : insert a new item (phone number and name ) into the dictionary" << endl;
    cout << "\033[1;32ml\033[0m  : list the items in the entire dictionary on the screen in inorder fashion" << endl;
    cout << "\033[1;32mp\033[0m  : print the tree in pretty fashion (showing only the phone numbers)" << endl;
    cout << "\033[1;32mr\033[0m  : rebalance the tree" << endl;
    cout << "\033[1;32ms\033[0m  : save the dictionary to the file in sorted order – inorder --  ready to be read" << endl;
    cout << "\033[1;32me\033[0m  : exit the program which automatically does option s" << endl
         << endl;
}

void DeleteItem(BinarySearchTree &tree)
{
    Key targetPhone;

    cout << "Delete contact by phone number in the formate '#######' > ";
    cin >> targetPhone;

    try
    {
        tree.remove(targetPhone);
        cout << "Successfuly deleted " << targetPhone << endl;
    }
    catch (Exception except)
    {
        PrintExceptionMessage(except);
    }
}

void FindItem(BinarySearchTree &tree)
{
    Item item;
    Key targetPhone;

    cout << "Search for a contact by phone number in the format '#######' > ";
    cin >> targetPhone;

    try
    {
        tree.search(targetPhone, item);
        cout << "Located > " << item;
    }
    catch (Exception except)
    {
        PrintExceptionMessage(except);
    }
}

void InsertItem(BinarySearchTree &tree)
{
    Item item;

    cout << "Provide a contact in the format '####### First Last' > ";
    cin >> item;
    try
    {
        tree.insert(item);
        cout << "Inserted item into tree successfuly" << endl;
    }
    catch (Exception except)
    {
        PrintExceptionMessage(except);
    }
}

void ListTree(BinarySearchTree &tree)
{
    BinaryTree *btreep = &tree;
    btreep->inorderTraverse(cout);
}

void PrintTree(BinarySearchTree &tree)
{
    tree.prettyDisplay();
}

void RebalanceTree(BinarySearchTree &tree)
{
    ofstream outputFile;
    OpenOutputFile(outputFile, "dictionary.dat");
    tree.inorderTraverse(outputFile);
    outputFile.close();

    ifstream inputFile;

    OpenInputFile(inputFile, "dictionary.dat");
    CreateTreeFromInputFile(inputFile, tree);
    inputFile.close();
}

void SaveTree(BinarySearchTree &tree)
{
    ofstream outputFile;
    OpenOutputFile(outputFile, "dictionary.dat");
    tree.inorderTraverse(outputFile);
    outputFile.close();

    cout << "Saved tree to dictionary.dat successfuly." << endl;
}

void Exit(BinarySearchTree &tree)
{
    SaveTree(tree);
}

void GetOption(char &option)
{
    cout << "\033[1;32mEnter your option > \033[0m";
    cin >> option;
    cin.get();
}

bool IsNotExit(const char option)
{
    return option != 'e';
}

void DoOption(const char option, BinarySearchTree &tree)
{
    cout << "Selected [\033[1;32m" << option << "\033[0m]." << endl;
    switch (option)
    {
    case 'd':
        DeleteItem(tree);
        break;
    case 'f':
        FindItem(tree);
        break;
    case 'i':
        InsertItem(tree);
        break;
    case 'l':
        ListTree(tree);
        break;
    case 'p':
        PrintTree(tree);
        break;
    case 'r':
        RebalanceTree(tree);
        break;
    case 's':
        SaveTree(tree);
        break;
    case 'e':
        Exit(tree);
        break;
    default:
        PrintMenu();
        break;
    }
    cout << endl
         << "----------------------------------------------------" << endl
         << endl;
}

int main()
{
    char option;
    BinarySearchTree tree;
    ifstream inputFile;

    OpenInputFile(inputFile, "dictionary.dat");
    CreateTreeFromInputFile(inputFile, tree);
    inputFile.close();

    do
    {
        PrintMenu();
        GetOption(option);
        DoOption(option, tree);
    } while (IsNotExit(option));

    return 0;
}