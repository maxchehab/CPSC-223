// Specification of ADT Item
//     data object: a name associated with a phone number
//     operations: create, destroy, copy create, copy
//                 input, output

#ifndef ITEM_H
#define ITEM_H

#include "Key.h"
using namespace std;

class Item : public Key
{

  //allows for input of an item from either the standard input device or a file
  //pre input has been opened and readied for the input of
  //    7-digit phone number without dashes followed by one space and first-name followed by
  //    space and second-name followed by a newline. For example
  //    123-4567 Frosty Snowperson
  //post rightHandSideItem has been filled with a 7-digit phone number and first-name
  //     and last-name from the input
  //usage cin >> myitem;
  friend istream &operator>>(istream &input, Item &rightHandSideItem);

  //allows for the output of an item to the standard output device or a file
  //pre rightHandSideItem has been filled with a 7-digit phone number and name;
  //    output has been opened
  //post rightHandSideItem has been written to the output device
  //     123-4567 Frosty Snowperson
  //usage  outfile << myitem;
  friend ostream &operator<<(ostream &output, const Item &rightHandSideItem);

public:
  //creates an empty new name and phone number
  //post Item object is an empty name and phone number
  //usage Item aItem;
  Item();

  //releases memory for a phone number and name
  //pre Item object exists
  //post Item object no longer exists, memory has been freed
  //usage automatically done at the end of scope
  ~Item();

  //determines of an item is empty
  //pre Item object exists
  //post if Item object is empty returns true else returns false
  //usage if(aitem.isEmpty())
  bool isEmpty();

  //gives an item a used value
  //pre Item object phonePtr is filled
  //post Item object phonePtr[0] = '@'
  //usage if(aitem.setUsed())
  void setUsed();

  //copies a name and phone number
  //pre rightHandSideItem has been assigned a name and phone number
  //post Item object has a copy of rightHandSideItem
  //usage Item bItem(aItem);
  Item(const Item &rightHandSideItem);

  //copies a name and phone number
  //pre rightHandSideItem has been assigned a name and phone number
  //post Item object has a copy of rightHandSideItem
  //usage bItem = aItem;
  Item &operator=(const Item &rightHandSideItem);
};
#endif