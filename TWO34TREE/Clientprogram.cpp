//clientguy

#include "Two34Tree.h"
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

int main()
{
    Key key;
    cout << "key > ";
    cin >> key;
    Two34TreeNode *nodeA = new Two34TreeNode(key);
    cout << "key > ";
    cin >> key;
    Two34TreeNode *nodeB = new Two34TreeNode(key);
    cout << "key > ";
    cin >> key;
    Two34TreeNode *nodeC = new Two34TreeNode(key, nodeA, nodeB);

    cout << nodeC->kids[0]->keys[0] << endl;
    cout << nodeC->kids[3]->keys[0] << endl;
}