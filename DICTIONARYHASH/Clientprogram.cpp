#include <fstream>
#include <iostream>
#include <cstdlib>

#include "Item.h"
#include "Dictionary.h"

using namespace std;

// opens an input file
// pre: unopened file
// post: file has been opened or program has
//		 exited due to error.
// usage: openInputFile(input);
void openInputFile(ifstream &infile)
{
    infile.open("Input.dat");
    if (infile.fail())
    {
        cout << "ERROR in opening Input.dat !!!" << endl;
        exit(1);
    }
}

// inserts input file into dictionary
// pre: empty dictionary
// post: dictionary is populated with items from input file
// usage: partA(inputFile, dictionary);
void partA(ifstream &input, Dictionary &dictionary)
{
    input >> dictionary;
    cout << dictionary << endl;
}

// inserts next three rows as items from input file into dictionary
// pre: dictionary with four items
// post: dictionary with three more items
// usage: partB(inputFile, dictionary);
void partB(ifstream &input, Dictionary &dictionary)
{
    bool isFull = false;
    Item item;

    for (int i = 0; i < 3 && !isFull; i++)
    {
        input >> item;
        dictionary.insert(item, isFull);
    }
    cout << dictionary << endl;
}

// Searches for the next two phone numbers inside of input file
// in dictionary.
// pre: input file has two phone numbers in a row
// 1234567
// 1111011
// post: searches and finds first and last name cordinating to
// profided phone numbers
// usage: partC(inputFile, dictionary);
void partC(ifstream &input, Dictionary &dictionary)
{
    Item item;
    Key key;
    bool isFound;

    for (int i = 0; i < 2; i++)
    {
        input >> key;
        cout << "Searching for " << key << endl;

        dictionary.search(key, item, isFound);
        if (isFound)
        {
            cout << "Found " << item << endl;
        }
        else
        {
            cout << "Could not find " << key << endl;
        }
        cout << endl;
    }
}

// Removes for the next phone number inside of input file
// in dictionary.
// pre: input file a phone number
// 1111101
// post: searches and removes the provided phone number
// usage: partD(inputFile, dictionary);
void partD(ifstream &input, Dictionary &dictionary)
{
    Key key;
    bool isDone;

    input >> key;
    cout << "Removing " << key << endl;
    dictionary.remove(key, isDone);
    if (isDone)
    {
        cout << "Removed successfuly." << endl
             << dictionary << endl;
    }
    else
    {
        cout << "Removed unsuccessfuly." << endl
             << dictionary << endl;
    }
}

// Searches for the next phone number inside of input file
// in dictionary.
// pre: input file has a phone number in a row
// 1110111
// post:searches and finds first and last name cordinating to
// profided phone number
// usage: partE(inputFile, dictionary);
void partE(ifstream &input, Dictionary &dictionary)
{
    Item item;
    bool isFound;

    Key key;
    input >> key;
    cout << "Searching for " << key << endl;

    dictionary.search(key, item, isFound);
    if (isFound)
    {
        cout << "Found " << item << endl;
    }
    else
    {
        cout << "Could not find " << key << endl;
    }
    cout << endl;
}

int main()
{
    Item anItem;
    Dictionary dictionary;
    ifstream input;

    openInputFile(input);
    partA(input, dictionary);
    partB(input, dictionary);
    partC(input, dictionary);
    partD(input, dictionary);
    partE(input, dictionary);

    input.close();

    return 0;
}
