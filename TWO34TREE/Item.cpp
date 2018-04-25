// @author Maxwell Chehab
// Specification of ADT Item
//     data object: a name associated with a phone number
//     operations: create, destroy, copy create, copy
//                 input, output

#include "Item.h"

//allows for input of an item from either the standard input device or a file
//pre input has been opened and readied for the input of
//    7-digit phone number without dashes followed by one space and first-name followed by
//    space and second-name followed by a newline. For example
//    123-4567 Frosty Snowperson
//post rightHandSideItem has been filled with a 7-digit phone number and first-name
//     and last-name from the input. The name data ends with the null character
//usage cin >> myitem;
istream &operator>>(istream &input, Item &rightHandSideItem)
{
    input >> rightHandSideItem.phone;

    char enter;
    input.get(enter);
    return input;
}
//allows for the output of an item to the standard output device or a file
//pre rightHandSideItem has been filled with a 7-digit phone number and name;
//    output has been opened
//post rightHandSideItem has been written to the output device
//     123-4567 Frosty Snowperson
//     there is a newline after the last name
//usage  outfile << myitem;
ostream &operator<<(ostream &output, const Item &rightHandSideItem)
{
    output << rightHandSideItem.phone;
    return output;
}

//creates an empty new name and phone number
//post Item object is an empty name and phone number
//usage Item aItem;
Item::Item()
{
}

//releases memory for name
//pre Item object exists
//post Item object no longer exists, memory has been freed
//usage automatically done at the end of scope
Item::~Item()
{
}

//copies a name and phone number
//pre rightHandSideItem has been assigned a name and phone number
//post Item object has a copy of rightHandSideItem
//usage Item bItem(aItem);
Item::Item(const Item &rightHandSideItem)
{
    phone = rightHandSideItem.phone;
}

//copies a name and phone number
//pre rightHandSideItem has been assigned a name and phone number
//post Item object has a copy of rightHandSideItem
//usage bItem = aItem;
Item &Item::operator=(const Item &rightHandSideItem)
{
    if (this != &rightHandSideItem)
    {
        phone = rightHandSideItem.phone;
    }
    return *this;
}
