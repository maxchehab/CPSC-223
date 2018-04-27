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
string printRed(const string input)
{
    return "\033[1;31m" + input + "\033[0m";
}

//Prints provided input in green text
//post Text is printed in red
//usage printGreen("this is green text");
//Note "\033[1;32mgreen text\033[0m is a terminal escape sequence to print the inner text in green.
string printGreen(const string input)
{
    return "\033[1;32m" + input + "\033[0m";
}

//prints an exception message
//pre except has been thrown
//post except is printed to the screen with two newlines before and after
//usage printExceptionMessage(except);
void printExceptionMessage(const Exception &except)
{
    cout << printRed(except.What()) << endl;
}

//opens an input file with a chosen name
//pre filename is assigned
//post if filename exists in the same directory as the program, it is opened
//      with its file pointer at the beginning of the file
//      else an error message is printed
//usage openInputFile(infile, filename);
void openInputFile(ifstream &inputFile, string filename)
{
    inputFile.open(filename);
    if (inputFile.fail())
    {
        cout << printRed("Failed to open file.") << endl;
        exit(1);
    }
}

//opens an output file with a chosen name
//pre filename is assigned
//post if filename exists in the same directory as the program, it is opened
//      with its file pointer at the beginning of the file
//      else an error message is printed
//usage openInputFile(outfile, filename);
void openOutputFile(ofstream &outputFile, string filename)
{
    outputFile.open(filename);
    if (outputFile.fail())
    {
        cout << printRed("Failed to open file.") << endl;
        exit(1);
    }
}

int main()
{
    Two34Tree tree;
    Key newKey;

    // while (true)
    // {
    //     cout << printGreen("key> ");
    //     cin >> newKey;

    //     try
    //     {
    //         tree.insert(newKey);
    //     }
    //     catch (Exception ex)
    //     {
    //         printExceptionMessage(ex);
    //     }
    //     tree.display(cout, 'p');
    // }

    for (int i = 1; i < 101; i++)
    {
        // newKey = Key(i);
        tree.insert(Key(i));
    }
    tree.display(cout, 'p');
}
