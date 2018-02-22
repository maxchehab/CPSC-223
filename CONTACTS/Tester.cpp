// testing file for class Key
// Tester.cpp

#include "Item.h"
#include "Key.h"

int main()
{

    // Item.cpp test
    // friend istream &operator>>(istream &input, Item &rightHandSideItem);
    cout << "Testing item.cpp >> operator" << endl;
    Item aItem;
    cout << "Enter a 7-digit phone number then a space then a first name space last name -> ";
    cin >> aItem;

    // friend ostream &operator<<(ostream &output, const Item &rightHandSideItem);
    cout << "Testing item.cpp << operator" << endl;
    cout << aItem;

    // Item(const Item &rightHandSideItem);
    cout << "Testing Item(const item) constructor by copying the previous item into a new one." << endl;
    Item bItem(aItem);
    cout << bItem;

    // Item &operator=(const Item &rightHandSideItem);
    cout << "Testing item.cpp = operator by creating an empty Item and assigning the previous item." << endl;
    Item cItem;
    cItem = bItem;
    cout << cItem;

    // Key.cpp test
    // friend istream &operator>>(istream &input, Key &rightHandSideKey);
    cout << "Testing key.cpp >> operator" << endl;
    Key aKey;
    cout << "Enter a 7-digit phone number without spaces or dashes -> ";
    cin >> aKey;

    // friend ostream &operator<<(ostream &output, const Key &rightHandSideKey);
    cout << "Testing key.cpp << operator" << endl;
    cout << aKey << endl;

    // Key(string keyText);
    cout << "Testing Key(string) constructor by creating a key filled with seven `1`s" << endl;
    Key bKey("1111111");
    cout << bKey << endl;

    //Key &operator=(const Key &rightHandSideKey);
    cout << "Testing Key.cpp = operator by creating an empty Key and assigning the previous key." << endl;
    Key cKey = aKey;
    cout << cKey << endl;

    // int sumDigits() const;
    cout << "Testing key.cpp sumDigits() by printing out the sum of the previous key." << endl;
    cout << cKey.sumDigits() << endl;

    // bool operator==(const Key &rightHandSideKey) const;
    cout << "Testing key.cpp == operator by comparing your inputed key (" << aKey << ") with (" << bKey << ")." << endl;
    cout << (aKey == cKey ? "true" : "false") << endl;
    
    // bool operator<(const Key &rightHandSideKey) const;
    cout << "Testing key.cpp < operator by comparing your inpyted key (" << aKey << ") with (" << bKey << ")." << endl;
    cout << (aKey < cKey ? "true" : "false") << endl;
    return 0;
}
