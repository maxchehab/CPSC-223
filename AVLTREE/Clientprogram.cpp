//clientguy

#include "BinarySearchTree.h"
#include "Exception.h"
#include <string>
#include <fstream>
using namespace std;

//Prints provided input in red text
//post Text is printed in red
//usage printRed("this is red text");
//Note "\033[1;31mred text\033[0m is a terminal escape sequence to print the inner text in red.
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

//Create a tree from an input file
//pre inptFile is open
//post  Provided tree is populated with data from input file
//      if there was an error it will be reported.
//usage CreateTreeFromInputFile(inputFile, mytree);
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

//Prints menu options in colorful format
//post Menu options are printed
//usage PrintMenu()
//Note "\033[1;32mgreen text\033[0m is a terminal escape sequence to print the inner text in green.
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

//Prompts user to delete an item from a tree.
//pre provided tree exists
//post Item is deleted or if an error occurs, the error is reported.
//usage DeleteItem(mytree);
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

//Prompts user to find an item from a tree
//pre provided tree exists
//post found item is printed to the screen or an error will be reported.
//usage FindItem(mytree);
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

//Prompts user to insert item from tree
//pre provided tree exists
//post if an error occurs it will be reported
//usage InsertItem(mytree);
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

//List tree in an inorder traversal
//pre provided tree exists
//post tree is printed in an inorder traversal
//usage ListTree(mytree);
void ListTree(BinarySearchTree &tree)
{
    BinaryTree *btreep = &tree;
    btreep->inorderTraverse(cout);
}

//Tree is pretty displayed to terminal
//pre provided tree exists
//post tree is pretty displayed to the terminal
//usage PrintTree(mytree);
void PrintTree(BinarySearchTree &tree)
{
    tree.prettyDisplay();
}

//Saves tree to file and recreates it. This forces the tree to be sorted
//  in the best possible way.
//pre tree exists
//post provided tree is rebalanced
//usage RebalanceTree(mytree);
void RebalanceTree(BinarySearchTree &tree)
{
    ofstream outputFile;
    ifstream inputFile;

    OpenOutputFile(outputFile, "dictionary.dat");
    tree.inorderTraverse(outputFile);
    outputFile.close();

    OpenInputFile(inputFile, "dictionary.dat");
    CreateTreeFromInputFile(inputFile, tree);
    inputFile.close();
}

//Saves tree to a file
//pre provided tree exist
//post saves a tree to file in an inorder traverse
//usage SaveTree(mytree);
void SaveTree(BinarySearchTree &tree)
{
    ofstream outputFile;

    OpenOutputFile(outputFile, "dictionary.dat");
    tree.inorderTraverse(outputFile);
    outputFile.close();

    cout << "Saved tree to dictionary.dat successfuly." << endl;
}

//Prompts the user for a single character option
//post provided character is populated with user's decision
//usage GetOption(myoption);
void GetOption(char &option)
{
    cout << "\033[1;32mEnter your option > \033[0m";
    cin >> option;
    cin.get();
}

//Determines if the provided option is an exit option
//post returns true or false relative to the provided option
//usage IsNotExit(myoption);
bool IsNotExit(const char option)
{
    return option != 'e';
}

//Executes a method relative to the provided users option.
//pre: the provided option and tree must exists
//post: the method that the option is for is executed
//usage: DoOption(myoption, mytree);
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
        SaveTree(tree);
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