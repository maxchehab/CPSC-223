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

int main()
{
    BinarySearchTree tree;
    Item newItem;
    Item foundItem;

    cout << "insert item > ";
    cin >> newItem;
    try
    {
        tree.search(newItem, foundItem);
        printRed("Exception does not work in search");
    }
    catch (Exception ex)
    {
        if (ex.What() == "The provided phone number is not inside of this tree.")
        {
            printGreen("Exception works in search.");
        }
    }
    try
    {
        tree.insert(newItem);
    }
    catch (Exception ex)
    {
        PrintExceptionMessage(ex);
    }

    try
    {
        tree.search(newItem, foundItem);
    }
    catch (Exception ex)
    {
        PrintExceptionMessage(ex);
    }

    if (newItem == foundItem)
    {
        printGreen("search and insert works");
    }
    else
    {
        printRed("search and insert does not work");
    }

    cout << "newItem: " << newItem;
    cout << "foundItem: " << foundItem;
}