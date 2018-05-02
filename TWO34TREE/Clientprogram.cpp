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

//fills a provided tree with provided input
//pre tree exists
//Input file starts with number denoting amount of items
//post tree is populated with contents of newKey.
//    cursor of input file is at next line of new the last item
//usage readInputToTree(inputFile, myTree);
void readInputToTree(istream &input, ostream &output, Two34Tree &tree)
{
    Key newKey;
    int numberOfItems;
	string subcase;
	
	input >> numberOfItems;
	input >> subcase;
    input.get();
	
	output << endl << subcase << endl << endl;
	
    for (int i = 0; i < numberOfItems; i++)
    {
        input >> newKey;
		try
		{
			tree.insert(newKey);
		}
		catch(Exception ex)
		{
			output << ex.What() << endl << endl;
			break;
		}
    }
}

//executes a sub cases
//pre input and output is open
//post output stream is populated with test output.
//usage runSubCase(input, output);
void runSubCase(istream &input, ostream &output)
{
	Two34Tree tree;
    Key newKey;
	
	readInputToTree(input, output, tree);

    tree.display(output, 'p');
    input >> newKey;
    try
    {
        output << endl
               << newKey
               << endl
               << endl;
        tree.insert(newKey);
    }
    catch (Exception ex)
    {
        output << ex.What() << endl << endl;
    }
    tree.display(output, 'p');
    output << endl;
}

//executes a given number of sub cases
//pre name denotes the name of test, input and output is open
//post output stream is populated with test output.
//usage runTest("my test", 1, input, output);
void runTest(string name, int amount, istream &input, ostream &output)
{
	output << "          " << name << endl;
	
	for(int i = 0; i < amount; i++) 
	{
		runSubCase(input, output);
	}
}

int main()
{
    Two34Tree tree;
    Key newKey;

	ifstream input;
	ofstream output;

    openOutputFile(output, "Two.out");
	openInputFile(input, "input.dat");

	runTest("1) INSERT TO ROOT", 3, input, output);
	
	runTest("2) FORCE ROOT TO SPLIT", 4, input, output);
	
	runTest("3) INTO LEVEL-TWO NODE", 12, input, output);
	
	runTest("4) FORCE LEVEL-TWO SPLIT", 8, input, output);
	
	runTest("5) INTO THREE LEVEL-TWO NODES", 9, input, output);
	
	runTest("6) FORCE LEVEL-TWO SPLIT CREATE FOUR CHILDREN", 8, input, output);
	
	runTest("EXTRA) FORCE SPLIT ROOT AND ADD TO LEVEL-THREE", 4, input, output);

	runTest("EXTRA) DUPLICATES", 2, input, output);
	
	output << "          EXTRA: FANCY PATTERN. NO ODDS ARE NOT LEAFS AND BASE 2 NUMBERS ARE IN ROOT" << endl;
	for(int i = 1; i < 101; i++)
	{
		tree.insert(Key(i));
	}
	tree.display(output, 'p');
}
