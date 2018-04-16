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

//fills a provided tree with provided input
//pre tree exists
//Input file starts with number denoting amount of items
//post tree is populated with contents of newItem.
//    cursor of input file is at next line of new the last item
//usage readInputToTree(inputFile, myTree);
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

//executes a test
//pre subcase denotes the name of test, input and output is open
//post output stream is populated with test output.
//usage runTest("my test", input, output);
void runTest(string subcase, istream &input, ostream &output)
{
    AVLTree tree;
    Item newItem;

    output << endl
           << subcase << endl
           << endl;
    readInputToTree(input, tree);

    tree.prettyDisplay(output);
    input >> newItem;
    try
    {
        output << endl
               << newItem
               << endl
               << endl;
        tree.insert(newItem);
    }
    catch (Exception ex)
    {
        output << ex.What() << endl;
    }
    tree.prettyDisplay(output);
    output << endl;
}

int main()
{
    ifstream input;
    ofstream output;

    OpenInputFile(input, "in8.dat");
    OpenOutputFile(output, "avl.dat");

    output
        << "       HAS NO PIVOT" << endl;
    runTest("Test1: CASE OF EMPTY TREE", input, output);
    runTest("Test2: CASE OF HEIGHT 1", input, output);
    runTest("Test2: CASE OF HEIGHT 2", input, output);

    output << "       Added To Short Side" << endl;
    runTest("Test1: CASE OF HEIGHT 4", input, output);
    runTest("Test2: CASE OF HEIGHT 3", input, output);

    output << "       SINGLE ROTATE LEFT" << endl;
    runTest("Test1: PIVOT INDEX AT 0", input, output);
    runTest("Test2: CLOUD POINTING TO RIGHT CHILD", input, output);
    runTest("Test3: CLOUD POINTING TO LEFT CHILD", input, output);

    output << "       SINGLE ROTATE LEFT" << endl;
    runTest("Test1: PIVOT INDEX AT 0", input, output);
    runTest("Test2: CLOUD POINTING TO RIGHT CHILD", input, output);
    runTest("Test3: CLOUD POINTING TO LEFT CHILD", input, output);

    output << "       DOUBLE ROTATE LEFT RIGHT" << endl;
    runTest("Test1: PIVOT INDEX AT 0, NEW AT ITEM RIGHT CHILD", input, output);
    runTest("Test2: PIVOT INDEX AT 0, NEW AT ITEM LEFT CHILD", input, output);
    runTest("Test3: CLOUD POINTING TO LEFT CHILD", input, output);
    runTest("Test4: CLOUD POINTING TO RIGHT CHILD", input, output);

    output << "       DOUBLE ROTATE RIGHT LEFT" << endl;
    runTest("Test1: PIVOT INDEX AT 0, NEW AT ITEM RIGHT CHILD", input, output);
    runTest("Test2: PIVOT INDEX AT 0, NEW AT ITEM LEFT CHILD", input, output);
    runTest("Test3: CLOUD POINTING TO RIGHT CHILD", input, output);
    runTest("Test4: CLOUD POINTING TO LEFT CHILD", input, output);

    input.close();
    output.close();
    return 0;
}