#include <iostream>

using namespace std;

void printMenu();
void getOption(char &);
bool isNotExit(char);
void doOption(char);

int main()
{
    char option;
    do
    {
        printMenu();
        getOption(option);
        doOption(option);
    } while (isNotExit(option));

    return 0;
}

void printMenu()
{
    cout << "Your options are:" << endl;

    cout << "f  : find the name of the contact, given her/his phone number" << endl;
    cout << "i  : insert a new item (phone number and name ) into the dictionary" << endl;
    cout << "l  : list the items in the entire dictionary on the screen in inorder fashion" << endl;
    cout << "p  : print the tree in pretty fashion (showing only the phone numbers)" << endl;
    cout << "r  : rebalance the tree" << endl;
    cout << "s  : save the dictionary to the file in sorted order – inorder --  ready to be read" << endl;
    cout << "e  : exit the program which automatically does option s" << endl
         << endl;
}

void getOption(char &option)
{
    cout << "Enter your option > ";
    cin >> option;
    cin.get();
}

bool isNotExit(char option)
{
    return option != 'e';
}

void doOption(char option)
{
    cout << "Doing " << option << endl
         << endl;
}