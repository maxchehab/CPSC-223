// Clientprogram.cpp
// Max Chehab
// 4/20/18
// This program will test the operations in class Heap and revised class Key

#include "Exception.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

#include "Key.h"
#include "Heap.h"

//Prints provided input in red text
//post Text is printed in red
//usage printRed("this is red text");
//Note "\033[1;31mred text\033[0m is a terminal escape sequence to print the inner text in red.
void printRed(const string input)
{
    cout << "\033[1;31m" << input << "\033[0m";
}

//Prints provided input in green text
//post Text is printed in red
//usage printGreen("this is green text");
//Note "\033[1;32mgreen text\033[0m is a terminal escape sequence to print the inner text in green.
void printGreen(const string input)
{
    cout << "\033[1;32m" << input << "\033[0m";
}

//opens an input file with a chosen name
//pre filename is assigned
//post if filename exists in the same directory as the program, it is opened
//      with its file pointer at the beginning of the file
//      else an error message is printed
//usage OpenInputFile(infile, filename);
void openInputFile(ifstream &inputFile)
{
    inputFile.open("Heap.dat");
    if (inputFile.fail())
    {
        printRed("File failed to open!!!!\n");
        exit(1);
    }
}

//prints an exception message
//pre except has been thrown
//post except is printed to the screen with two newlines before and after
//usage printExceptionMessage(except);
void printExceptionMessage(const Exception &except)
{
    printRed(except.What() + "\n");
}

int main()
{
    ifstream infile;
    Heap maxheap;
    Key tempKey;

    printGreen("Building heap from input file:\n");
    openInputFile(infile);

    infile >> maxheap;
    cout << maxheap;

    printGreen("\nRemoving largest number\n");
    try
    {
        maxheap.remove(tempKey);
    }
    catch (Exception ex)
    {
        printExceptionMessage(ex);
    }
    printGreen("Largest number was: ");
    cout << tempKey << endl;
    cout << maxheap;

    printGreen("\nRemoving largest number\n");
    try
    {
        maxheap.remove(tempKey);
    }
    catch (Exception ex)
    {
        printExceptionMessage(ex);
    }
    printGreen("Largest number was: ");
    cout << tempKey << endl;
    cout << maxheap;

    printGreen("\nInserting (3)\n");
    tempKey = Key(3);
    try
    {
        maxheap.insert(tempKey);
    }
    catch (Exception ex)
    {
        printExceptionMessage(ex);
    }
    cout << maxheap;

    printGreen("\nInserting (25)\n");
    tempKey = Key(25);
    try
    {
        maxheap.insert(tempKey);
    }
    catch (Exception ex)
    {
        printExceptionMessage(ex);
    }
    cout << maxheap;

    return 0;
}
