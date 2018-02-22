// Specification of ADT Dictionary
//     data object: a bunch of contacts (phone number and name)
//     operations: create, destroy
//                 search the dictionary for an item given its phone number
//                 insert a new item into the dictionary
//                 remove an item from the dictionary given its phone number

#include "Dictionary.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

const int TABLESIZE = 7;

int hashFunction(const Item &theItem)
{
    return theItem.sumDigits() % TABLESIZE;
}

void openInputFile(ifstream &infile)
{
    infile.open("Input.dat");
    if (infile.fail())
    {
        cout << "ERROR in opening Input.dat !!!" << endl;
        exit(1);
    }
}
// displays a dictionary
// pre: output has been opened if it is a file
//      rightHandSideDictionary has been assigned items
// post: output contains each item on a separate line in the format with headings.
//       for example
//       phone       name
//       123-4567 Frosty Snowgu	y
//       111-2222 Icy Dog
// usage: outfile << myDictionary;
ostream &operator<<(ostream &output, const Dictionary &rightHandSideDictionary)
{
    Item nextItem;
    for (int address = 0; address < TABLESIZE; address++)
    {
        nextItem = rightHandSideDictionary.dictionaryPtr->hashPtr[address];
        output << address << " " << nextItem;
    }
    return output;
}

// inputs items into a dictionary
// pre: input has been opened if it is a file
//      2
//      1234567 Frosty Snowguy
//      1112222 Icy Dog
// post: if there is room,
//       all items in the input have been stored in rightHandSideDictionary
// usage: infile >> myDictionary;
istream &operator>>(istream &input, Dictionary &rightHandSideDictionary)
{
    int numberItems;
    input >> numberItems;
}

// creates a new dictionary
// post: Dictionary object exists but is empty
// usage: Dictionary myDictionary;
Dictionary::Dictionary()
{
    dictionaryPtr = new DictionaryRecord;
    dictionaryPtr->numberOfItems = 0;
    dictionaryPtr->hashPtr = new Item[TABLESIZE];
};

// destroys a dictionary
// pre: Dictionary object exists
// post: all memory for Dictionary object has been freed
// usage: automatically done at the end of scope
Dictionary::~Dictionary()
{
}

// searchs for a contact with a particular phone number
// pre targetPhone has been assigned a 7-digit phone number
// post if an item with phone number the same as targetPhone is found then
//          isFound is true and theItem is that item
//       else isFound is false
// usage  contacts.search(targetPhone, anItem, isFound);
void Dictionary::search(const Key &targetPhone, Item &theItem, bool &isFound)
{
}

// inserts a new contacts' item into the dictionary
// pre: newItem has been assigned
// post: if there is room in the Dictionary object, isFull is false
//            and newItem is appropriately added
//       else isFull is false
// usage: myDictionary.insert(myItem, isFull);
void Dictionary::insert(const Item &newItem, bool &isFull)
{
    isFull = dictionaryPtr->numberOfItems == TABLESIZE;
    if (isFull)
        return;

    int hashAddress = hashFunction(newItem);
    int index = hashAddress;
    while (!dictionaryPtr->hashPtr[hashAddress].isEmpty())
    {
        index = (index + 1) % TABLESIZE;
    }
    dictionaryPtr->hashPtr[index] = newItem;
    dictionaryPtr->numberOfItems = dictionaryPtr->numberOfItems + 1;
};

// removes the item associated with a given phone number from the dictionary
// pre: targetPhone is assigned
// post: if targetPhone is found in Dictionary object, isDone is true
//           and the associated Item object (phone and name) has been
//           removed from the Dictionary
//       else isDone is false
// usage: myDictionary.remove(myPhone, isFound);
void Dictionary::remove(const Key &targetPhone, bool &isDone)
{
}

