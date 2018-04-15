//clientguy

#include "AVLTree.h"
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

//Prints provided input in green text
//post Text is printed in red
//usage printGreen("this is green text");
//Note "\033[1;32mgreen text\033[0m is a terminal escape sequence to print the inner text in green.
void printGreen(const string input)
{
    cout << "\033[1;32m" << input << "\033[0m" << endl;
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

void printBreak()
{
    cout << endl;
    printGreen("-------------------------------------");
    cout << endl;
}

void readInputToTree(istream &input, AVLTree &tree)
{
    Item newItem;
    int numberOfItems;

    input >> numberOfItems;
    input.get();
    for (int i = 0; i < numberOfItems; i++)
    {
        input >> newItem;
        tree.insert(newItem);
    }
}

void runTest(string name, istream &input)
{
    AVLTree tree;
    Item newItem;

    printGreen("Testing " + name);
    readInputToTree(input, tree);

    tree.prettyDisplay();
    input >> newItem;
    printBreak();
    try
    {
        cout << "Inserting " << newItem << endl;
        tree.insert(newItem);
    }
    catch (Exception ex)
    {
        printRed(ex.What());
    }
    tree.prettyDisplay();
}

int main()
{
    ifstream input;

    OpenInputFile(input, "dictionary.dat");
    runTest("Rotate Left, Pivot Index at 0", input);
    runTest("Rotate Left, Right Child", input);
    runTest("Rotate Left, Left Child", input);
    runTest("Rotate Right, Pivot Index at 0", input);
    runTest("Rotate Right, Right Child", input);
    runTest("Rotate Right, Left Child", input);
    runTest("Rotate Double Left Right, Pivot Index at 0, right child", input);
    runTest("Rotate Double Left Right, Pivot Index at 0, left child", input);
    runTest("Rotate Double Left Right, left child", input);
    runTest("Rotate Double Left Right, right child", input);
    runTest("Rotate Double Right Left, Pivot Index at 0, right child", input);
    runTest("Rotate Double Right Left, Pivot Index at 0, left child", input);
    runTest("Rotate Double Left Right, right child", input);
    runTest("Rotate Double Left Right, left child", input);

    printBreak();

    return 0;
}