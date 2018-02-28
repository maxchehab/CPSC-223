//clientguy

#include "BinaryTree.h"
#include "Exception.h"
#include <string>
#include <fstream>
using namespace std;

//opens an input file with a chosen name
//pre filename is assigned
//post if filename exists in the same directory as the program, it is opened
//      with its file pointer at the beginning of the file
//      else an error message is printed
//usage OpenInputFile(infile, filename);
void OpenInputFile(ifstream &inputFile, string filename);

//prints an exception message
//pre except has been thrown
//post except is printed to the screen with two newlines before and after
//usage PrintExceptionMessage(except);
void PrintExceptionMessage(const Exception &except);

// traverses and prints tree
// pre: BinaryTree is populated and exists
// post: Binary tree is pretty displayed and in order, post order, and pre order
//		traversals are displayed
// usage: traverseAndPrintTree(tree);
void traverseAndPrintTree(BinaryTree &tree);

int main()
{
    BinaryTree fullTree, completeTree;
    ifstream infile;

    OpenInputFile(infile, "Input.dat");

    try
    {
        fullTree.makeTreeOne(infile);
        completeTree.makeTreeTwo(infile);
    }
    catch (Exception except)
    {
        PrintExceptionMessage(except);
    }

    cout << "Full tree: " << endl;
    traverseAndPrintTree(fullTree);

    cout << "Complete tree: " << endl;
    traverseAndPrintTree(completeTree);

    return 0;
}

// traverses and prints tree
// pre: BinaryTree is populated and exists
// post: In order, post order, and pre order
//		traversals are displayed
// usage: traverseAndPrintTree(tree);
void traverseAndPrintTree(BinaryTree &tree)
{

    tree.prettyDisplay();
    cout << endl
         << "Pre-Order Traversal: " << endl;
    tree.preorderTraverse();

    cout << endl
         << "In-Order Traversal: " << endl;
    tree.inorderTraverse();

    cout << endl
         << "Post-Order Traversal: " << endl;
    tree.postorderTraverse();
    cout << endl;
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
        cout << "File failed to open!!!!" << endl;
        exit(1);
    }
}

//prints an exception message
//pre except has been thrown
//post except is printed to the screen with two newlines before and after
//usage PrintExceptionMessage(except);
void PrintExceptionMessage(const Exception &except)
{
    cout << endl
         << endl;
    cout << except.What();
    cout << endl
         << endl;
}
